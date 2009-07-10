#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "HandleTable.h"

/**
/class ResourceManager
Generic resource data manager class.
*/
template<class ResType>
class ResourceManager
{
public:
    typedef ResType Resource;
    typedef HandleTable::Handle Handle;

    static const int cMaxNameLength = 256;
    static const Handle cInvalidHandle = HandleTable::cEmptyHandle;

    ResourceManager(int capacity = 1024);
    ~ResourceManager();

    Handle AddResource(const char* name, Resource* res);

    Handle AddRef(const char* name);
    bool   ReleaseRef(const Handle& handle);

    const char* FindName(const Handle& handle);

    int Capacity()      { return mHandleTable->Capacity();  }
    int ResourceCount() { return mHandleTable->Count();     }

private:
    HandleTable         mHandleTable;
    StringHashTable     mNameTable;

private:
    ResourceManager(const ResourceManager&);
    ResourceManager& operator=(const ResourceManager&);
};



#endif