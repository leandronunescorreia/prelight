#ifndef _HANDLETABLE_H_
#define _HANDLETABLE_H_

/**
\class StringHashTable
Hash mapping strings to integers

/remark It won't alloc buffer to duplicate the key string, but simply 
keep a reference to the string be passed to it. It presume its 
user will host the key string buffer. And it won't check the key string's 
length, it presume its user will shoulder this responsibility.
*/
class StringHashTable
{
    struct Node
    {
        Node(const char *p_key, unsigned int hash, int value, Node *next);
        ~Node();    ///< Deleting a node will cause its subsequent nodes be deleted too.

        const char* key;
        unsigned int hash;
        int    value;
        Node* next;
    };

public:
    explicit    StringHashTable(int numBuckets);
                 ~StringHashTable();

    bool        Insert(const char *key, int value);
    bool        Erase(const char *key);

    bool        FindValue(const char *key, int& value);

private:
    int          HashString(const char *str, unsigned int& hash);

    Node**       mBuckets;
    int          mNumBuckets;

private:
    StringHashTable(const StringHashTable&);
    StringHashTable& operator=(const StringHashTable&);
};



/**
\class HandleTable
Manage handle slots by counting their reference counts.
Its slots can be setted to point to resources and count reference counts for these resources.
It doesn't free resources memory but only notify its caller when nothing is reference to one of its slots.
*/
class HandleTable
{
public:
    typedef int Handle;
    static const Handle cInvalidHandle = (Handle)-1;
    static const int    cMaxNumSlots = 0x7fff;

    struct Slot
    {
        Handle    handle;
        int       refcount;
        char*    name;
        void*    data;

        Slot();
        ~Slot();
    };

public:
    explicit HandleTable(int capacity);
              ~HandleTable();

    Slot*    AllocSlot();

    Slot*    AddRef(const Handle& handle);
    Slot*    ReleaseRef(const Handle& handle);

    Slot*    FindSlot(const Handle& handle);

    int     Capacity()  { return mCapacity; }
    int     Count()     { return mCount; }

private:
    Slot*    mSlots;
    int     mCapacity;
    int     mCount;
    int     mFirstEmptySlot;

private:
    HandleTable(const HandleTable&);
    HandleTable& operator=(const HandleTable&);
};

#endif