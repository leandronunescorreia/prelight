#include <string>
#include <assert.h>

#include "handletable.h"


StringHashTable::Node::Node(const char *p_key, unsigned int hash, int value, Node *next)
: key(p_key)
{
    this->hash  = hash;
    this->value = value;
    this->next  = next;
}

        
StringHashTable::Node::~Node() 
{
    if (NULL != next) 
        delete next; ///< Delete its subsequent nodes first.
}



/** Initialize fixed size buckets(node pointer) list. */
StringHashTable::StringHashTable(int numBuckets)
: mNumBuckets(numBuckets)
{
    assert(numBuckets > 0);

    mBuckets = new Node*[numBuckets];
    memset(mBuckets, 0, sizeof(mBuckets[0]) * numBuckets);
}

/** Release all buckets' child nodes list, before release buckets themself. */
StringHashTable::~StringHashTable()
{
    for (int i = 0; i < mNumBuckets; ++i)
    {
        if (NULL != mBuckets[i])
        {
            Node *bucket = mBuckets[i];
            delete bucket;
        }
    }
    delete [] mBuckets;
}

/** 
Hash function.
Algorithm is copyed from template <class _InIt>	inline size_t _Hash_value(_InIt _Begin, _InIt _End) in <xhash>
\return bucket index from return value, hash value from hash param.
*/
int StringHashTable::HashString(const char *str, unsigned int& hash)
{
    const static unsigned int magicNumeric = 16777619U;
    const static unsigned int hashSeed = 2166136261U;

    hash = hashSeed;
    for (const char* c = str; 0 != *c; c++)
        hash = magicNumeric * hash ^ (unsigned int)*c;
    return hash % mNumBuckets;
}


/** 
Insert key value pair node.
/return true means there is actually a new key/node has been inserted.
        false means there is no new node has been inserted.
*/
bool StringHashTable::Insert(const char *key, int value)
{
    assert(NULL != key);

    unsigned int hash;
    Node** pBucket = &mBuckets[HashString(key, hash)];

    for (Node *node = *pBucket; NULL != node; node = node->next)
    {
        if (node->hash == hash && 0 == strcmp(node->key, key))
        {
            /** Change the existed key/node's old value to an new value.*/
            node->value = value; 
            return false;
        }
    }

    /** Insert the new node to the bucket's begin. */
    Node* newNode = new Node(key, hash, value, *pBucket);
    *pBucket = newNode;

    return true;    
}

/**
Remove the key specified node from the hash table and free it space.
/return true means there is actually a key/node has been erased.
*/
bool StringHashTable::Erase(const char *key)
{
    assert(NULL != key);

    unsigned int hash;
    Node** pBucket = &mBuckets[HashString(key, hash)];

    for (Node** ppNode = pBucket; NULL != *ppNode; ppNode = &(*ppNode)->next)
    {
        Node *node = *ppNode;
        if (node->hash == hash && 0 == strcmp(node->key, key))
        {
            *ppNode = node->next;
            node->next = NULL;  ///< Don't delete its subsequent nodes.
            delete node;
            return true;    
        }
    }

    return false;
}

/** 
Find key's corresponding value
/param value key's value if found, otherwise undefined.
/return true if found, otherwise false.
*/
bool StringHashTable::FindValue(const char *key, int& value)
{
    assert(NULL != key);

    unsigned int hash;
    Node* bucket = mBuckets[HashString(key, hash)];

    for (Node *node = bucket; NULL != node; node = node->next)
    {
        if (node->hash == hash && 0 == strcmp(node->key, key))
        {
            value = node->value;
            return true;
        }
    }
    return false;
}



HandleTable::Slot::Slot() 
: handle(cInvalidHandle)
, refcount(0)
, name(NULL)
, data(NULL) 
{
}

HandleTable::Slot::~Slot() 
{ 
    assert(NULL == name && NULL == data); 
}



HandleTable::HandleTable(int capacity)
: mCapacity(capacity)
, mCount(0)
, mFirstEmptySlot(0)
{
    assert(capacity > 0 && capacity < cMaxNumSlots);

    mSlots = new Slot[mCapacity];
}

HandleTable::~HandleTable()
{
    assert(0 == mCount); ///< HandleTable must be empty before its destruction.
    delete [] mSlots;
}

/**
Find a empty slot, mark it as be used, and start counting reference count for it.
Caller can use the returned slot to point to anything.
*/
HandleTable::Slot* HandleTable::AllocSlot()
{
    Slot* slot = &mSlots[mFirstEmptySlot];
    slot->handle = (Handle)mFirstEmptySlot;
    slot->refcount = 1;
    slot->name = NULL;
    slot->data = NULL;

    ++mCount;

    if (mCount < mCapacity)
    {
        int i = mFirstEmptySlot + 1;
        while(i < mCapacity && cInvalidHandle == mSlots[i].handle) 
            ++i;
        mFirstEmptySlot = i;
    }
    else
        mFirstEmptySlot = mCapacity;

    return slot;
}

HandleTable::Slot* HandleTable::AddRef(const Handle& handle)
{
    assert(handle == mSlots[(int)handle].handle);

    Slot* slot = &mSlots[(int)handle];
    slot->refcount += 1;
    return slot;
}

/**
Release a reference for specified handle. 
/return A pointer to the slot, if nothing references it any more. Otherwise return NULL.
/remark The code who called this function should check the the return value, if its 
        a valid slot pointer, the caller code should release memory space pointed by this slot.
*/
HandleTable::Slot* HandleTable::ReleaseRef(const Handle& handle)
{
    assert(handle == mSlots[(int)handle].handle);

    Slot* slot = &mSlots[(int)handle];
    slot->refcount--;
    if (0 == slot->refcount)
    {
        if ((int)slot->handle < mFirstEmptySlot)
            mFirstEmptySlot = (int)slot->handle;
        --mCount;

        slot->handle = cInvalidHandle;
        return slot;
    }
    return NULL;
}

HandleTable::Slot* HandleTable::FindSlot(const Handle& handle)
{
    assert(handle == mSlots[(int)handle].handle);
    return &mSlots[(int)handle];
}