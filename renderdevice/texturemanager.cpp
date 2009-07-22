#include "renderdevice.h"
#include "texturemanager.h"

TextureManager::TextureManager()
: mResourceMgr(NULL)
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

    mResourceMgr = new ResourceManager<TextureResource>(capacity);
    return true;
}

bool TextureManager::Finalize()
{
    if (NULL == mResourceMgr)
        return false;

    delete mResourceMgr;
    mResourceMgr = NULL;
    return true;
}

TextureManager::TextureHandle TextureManager::FindOrLoadTexture(const char *filename)
{
    assert(NULL != filename);

    TextureHandle texHandle = mResourceMgr->AddRef(filename);
    if (cInvalidHandle != texHandle)
        return texHandle;   ///< Directly return the existed texture's handle after added its refcount.

    /**FIX ME. Should change to asynchronous file loading.*/
    FILE *file = fopen(filename, "rb");
    if (NULL == file)
        return cInvalidHandle;

    /** Load data from file to memory*/
    fseek(file, 0, SEEK_END);
    int byteSize = ftell(file);
    char *data = new char[fileSize];
    fseek(file, , SEEK_SET);
    fread((void *)data, 1, byteSize, file);
    fclose(file);

    /** Call RenderDevice class interface to create Texture.*/
    Texture *texture = gRenderDevice->CreateTexture(data, byteSize);
    delete [] data;

    if (NULL == texture)
        return cInvalidHandle;

    /** Insert the new Texture instance to resource manager.*/
    texHandle = mResourceMgr->AddResource(filename, texture);
    return texHandle;
}

TextureManager::TextureHandle TextureManager::FindOrCreateTexture(const char *name, const TextureSpec &textureSpec)
{
    assert(NULL != name);

    TextureHandle texHandle = mResourceMgr->AddRef(name);
    if (cInvalidHandle != texHandle)
        return texHandle;   ///< Directly return the existed texture's handle after added its refcount.

    Texture *texture = gRenderDevice->CreateTexture(spec);
    if (NULL == texture)
        return cInvalidHandle;
    texHandle = mResourceMgr->AddResource(name, texture);
    return texHandle;
}


TextureManager::TextureHandle TextureManager::FindTexture(const char *name)
{
    assert(NULL != name);

    TextureHandle texHandle = mResourceMgr->AddRef(name);
    return texhandle;
}

bool TextureManager::ReleaseTexture(TextureHandle & handle)
{
    bool destroyed = mResourceMgr->ReleaseRef(handle);
    if (destroyed)
        handle = cInvalidHandle;
    return destroyed;
}

const TextureSpec* TextureManager::GetTextureSpec(const TextureHandle& handle)
{
    Texture *texture = mResourceMgr->FindResource(handle);
    return &texture->spec;
}


