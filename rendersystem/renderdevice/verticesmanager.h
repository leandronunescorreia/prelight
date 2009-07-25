#ifndef _VERTICESMANAGER_H_
#define _VERTICESMANAGER_H_

#include "renderdevicetypes.h"
#include "../../common/resourcemanager.h"


class VerticesManager
{
public:
    VerticesManager();
    ~VerticesManager();

    typedef ResourceManager<Vertices>::Handle hVertices;
    static const hVertices cInvalidHandle = ResourceManager<Vertices>::cInvalidHandle;

    bool Initialize(int capacity);
    bool Finalize();

    /** Find a vertices by name, create a new empty vertices if this name doesn't exist or existed vertices's spec doesn't match.*/
    hVertices      CreateVertices(const char *name, const VerticesSpec &spec);

    /** Find a vertices by name and increase refcount, return invalid handle if this name doesn't exist.*/
    hVertices      FindVertices(const char *name);

    /** Decrease vertices's refcount. Set \param handle to invalid vertices handle.*/
    bool           ReleaseVertices(hVertices& handle);

    /** Get vertices's handle.*/
    const VerticesSpec* GetVerticesSpec(const hVertices& handle);

private:
    ResourceManager<Vertices> *mResourceMgr;
};

#endif