#include <string.h>
#include <assert.h>

#include "resourcemanager.h"


template<class ResType>
ResourceManager<ResType>::ResourceManager(int capacity /*= 1024*/)
: mHandleTable(capacity)
, mNameTable(capacity * 2) ///< Make name hash table's loading factor is under 0.5.
{
    assert(capacity > 0);
}

template<class ResType>
ResourceManager<ResType>::~ResourceManager()
{
}

/** 
If a resource which uses this name already existed, release the old resource and bind the name with the /para res.
/return handle of the /param res
*/
template<class ResType>
typename ResourceManager<ResType>::Handle ResourceManager<ResType>::AddResource(const char* name, Resource* res)
{
    assert(NULL != name && strlen(name) < cMaxNameLength);

    Handle handle;
    if (mNameTable.FindValue(name, handle))
    {
        HandleTable::Slot *slot = mHandleTable.AddRef(handle);
        if ((void*)res == slot->data)
            return slot->handle;

        if (NULL != slot->data)
            delete (Resource*)(slot->data);

        slot->data = (void*)res;
        return handle;
    }

    /**Allocate a new slot for this name res pair.*/
    HandleTable::Slot *slot = mHandleTable.AllocSlot();
    slot->name = _strdup(name);
    slot->data = (void*)res;
    mNameTable.Insert(slot->name, (int)slot->handle);
    return slot->handle;
}

template<class ResType>
typename ResourceManager<ResType>::Handle ResourceManager<ResType>::AddRef(const char* name)
{
    assert(NULL != name && strlen(name) < cMaxNameLength);

    Handle handle;
    if(!mNameTable.FindValue(name, handle))
        return cInvalidHandle;

    mHandleTable.AddRef(handle);
    return handle;
}

template<class ResType>
bool ResourceManager<ResType>::ReleaseRef(const Handle& handle)
{
    HandleTable::Slot *unrefSlot = mHandleTable.ReleaseRef(handle);
    if (NULL != unrefSlot)
    {
        mNameTable.Erase(unrefSlot->name);

        /** Release the slot's resource when nothing is referencing to it.*/
        delete [] unrefSlot->name;
        unrefSlot->name = NULL;

        if (NULL != unrefSlot->data)
        {    
            delete (Resource*)(unrefSlot->data);
            unrefSlot->data = NULL;
        }
        return true;
    }
    return false;
}

template<class ResType>
const char* ResourceManager<ResType>::FindName(const Handle& handle)
{
    HandleTable::Slot *slot = mHandleTable.FindSlot(handle);
    return slot->name;
}