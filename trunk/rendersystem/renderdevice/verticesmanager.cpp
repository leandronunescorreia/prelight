#include "renderdevice.h"
#include "verticesmanager.h"

VerticesManager::VerticesManager()
: mResourceMgr(NULL)
{
}

VerticesManager::~VerticesManager()
{
    Finalize();
}

bool VerticesManager::Initialize(int capacity)
{
    if (NULL != mResourceMgr)
        return false;

    mResourceMgr = new ResourceManager<Vertices>(capacity);
    return true;
}

bool VerticesManager::Finalize()
{
    if (NULL == mResourceMgr)
        return false;

    delete mResourceMgr;
    mResourceMgr = NULL;
    return true;
}

VerticesManager::hVertices VerticesManager::CreateVertices(const char *name, const VerticesSpec &verticesSpec)
{
    assert(NULL != name);

    hVertices vbHandle = mResourceMgr->AddRef(name);
    if (cInvalidHandle != vbHandle)
        return vbHandle;    ///< Directly return the existed vertices's handle after added its refcount.

    Vertices *vertices = gRenderDevice->CreateVertices(spec);
    if (NULL == vertices)
        return cInvalidHandle;
    vbHandle = mResourceMgr->AddResource(name, vertices);
    return vbHandle;
}


VerticesManager::hVertices VerticesManager::FindVertices(const char *name)
{
    assert(NULL != name);

    hVertices vbHandle = mResourceMgr->AddRef(name);
    return texhandle;
}

bool VerticesManager::ReleaseVertices(hVertices & handle)
{
    bool destroyed = mResourceMgr->ReleaseRef(handle);
    if (destroyed)
        handle = cInvalidHandle;
    return destroyed;
}

const VerticesSpec* VerticesManager::GetVerticesSpec(const hVertices& handle)
{
    Vertices *vertices = mResourceMgr->FindResource(handle);
    return &vertices->spec;
}


