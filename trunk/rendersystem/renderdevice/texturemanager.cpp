#include <stdio.h>
#include "renderdevice.h"
#include "texturemanager.h"


TextureManager::TextureManager()
: renderDevice(NULL)
, mResourceMgr(NULL)
{
}

TextureManager::~TextureManager()
{
    Finalize();
}

bool TextureManager::Initialize(int capacity)
{
    if (NULL != mResourceMgr)
        return false;

    renderDevice = RenderDevice::instance();

    mResourceMgr = new ResourceManager<Texture>(capacity);

    return true;
}

void TextureManager::Finalize()
{
    if (NULL != mResourceMgr)
    {
        delete mResourceMgr;
        mResourceMgr = NULL;
    }

    renderDevice = NULL;
}

TextureManager::hTexture TextureManager::FindOrLoadTexture(const char *filename)
{
    assert(NULL != filename);

    hTexture texHandle = mResourceMgr->AddRef(filename);
    if (cInvalidHandle != texHandle)
        return texHandle;    ///< Directly return the existed texture's handle after added its refcount.

    /**FIX ME. Should change to asynchronous file loading.*/
    FILE *file = fopen(filename, "rb");
    if (NULL == file)
        return cInvalidHandle;

    /** Load data from file to memory*/
    fseek(file, 0, SEEK_END);
    int byteSize = ftell(file);
    char *data = new char[byteSize];
    fseek(file, 0, SEEK_SET);
    fread((void *)data, 1, byteSize, file);
    fclose(file);

    /** Call RenderDevice class interface to create Texture.*/
    Texture *texture = renderDevice->CreateTexture(data, byteSize);
    delete [] data;

    if (NULL == texture)
        return cInvalidHandle;

    /** Insert the new Texture instance to resource manager.*/
    texHandle = mResourceMgr->AddResource(filename, texture);
    return texHandle;
}

TextureManager::hTexture TextureManager::FindOrCreateTexture(const char *name, const Texture::Spec &spec)
{
    assert(NULL != name);

    hTexture texHandle = mResourceMgr->AddRef(name);
    if (cInvalidHandle != texHandle)
        return texHandle;    ///< Directly return the existed texture's handle after added its refcount.

    Texture *texture = renderDevice->CreateTexture(spec);
    if (NULL == texture)
        return cInvalidHandle;
    texHandle = mResourceMgr->AddResource(name, texture);
    return texHandle;
}


TextureManager::hTexture TextureManager::FindTexture(const char *name)
{
    assert(NULL != name);

    hTexture texHandle = mResourceMgr->AddRef(name);
    return texHandle;
}

bool TextureManager::ReleaseTexture(hTexture & handle)
{
    bool destroyed = mResourceMgr->ReleaseRef(handle);
    if (destroyed)
        handle = cInvalidHandle;
    return destroyed;
}

const Texture::Spec* TextureManager::GetTextureSpec(const hTexture& handle)
{
    const Texture *texture = mResourceMgr->FindResource(handle);
    return &texture->spec;
}


