#include "renderdevice.h"
#include "verticesmanager.h"

VerticesManager::VerticesManager()
: renderDevice(NULL)
, mResourceMgr(NULL)
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

    renderDevice = RenderDevice::instance();
    mResourceMgr = new ResourceManager<Vertices>(capacity);

    return true;
}

void VerticesManager::Finalize()
{
    if (NULL != mResourceMgr)
    {
        delete mResourceMgr;
        mResourceMgr = NULL;
    }

    renderDevice = NULL;
}

VerticesManager::hVertices VerticesManager::CreateVertices(const char *name, const Vertices::Spec &spec)
{
    assert(NULL != name);

    hVertices verticesHandle = mResourceMgr->AddRef(name);
    if (cInvalidHandle != verticesHandle)
        return verticesHandle;    ///< Directly return the existed vertices's handle after added its refcount.

    Vertices *vertices = renderDevice->CreateVertices(spec.length, spec.stride, spec.usage);
    if (NULL == vertices)
        return cInvalidHandle;
    verticesHandle = mResourceMgr->AddResource(name, vertices);
    return verticesHandle;
}

VerticesManager::hVertices VerticesManager::FindVertices(const char *name)
{
    assert(NULL != name);

    hVertices verticesHandle = mResourceMgr->AddRef(name);
    return verticesHandle;
}

bool VerticesManager::ReleaseVertices(hVertices & handle)
{
    bool destroyed = mResourceMgr->ReleaseRef(handle);
    if (destroyed)
        handle = cInvalidHandle;
    return destroyed;
}

const Vertices::Spec* VerticesManager::GetVerticesSpec(const hVertices& handle)
{
    const Vertices *vertices = mResourceMgr->FindResource(handle);
    return &vertices->spec;
}
