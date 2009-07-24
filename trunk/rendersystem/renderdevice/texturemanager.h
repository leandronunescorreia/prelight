#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "renderdevicetypes.h"
#include "..\common\resourcemanager.h"


class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    typedef ResourceManager<TextureResource>::Handle TextureHandle;
    static const TextureHandle cInvalidHandle = ResourceManager<TextureResource>::cInvalidHandle;

    bool Initialize(int capacity);
    bool Finalize();

    /** Find a texture by name, load a new texture from disk if this name doesn't exist.*/
    TextureHandle	  FindOrLoadTexture(const char *filename);

    /** Find a texture by name, create a new empty texture if this name doesn't exist or existed texture's spec doesn't match.*/
    TextureHandle    FindOrCreateTexture(const char *name, const TextureSpec &textureSpec);

    /** Find a texture by name and increase refcount, return invalid handle if this name doesn't exist.*/
    TextureHandle    FindTexture(const char *name);

    /** Decrease texture's refcount. Set \param handle to invalid texture handle.*/
    bool           ReleaseTexture(TextureHandle& handle);

    /** Reload texture from disk without change texture's refcount.*/
	bool	        ReloadTexture(Texture texture);

    /** Get texture's handle.*/
    const TextureSpec*  GetTextureSpec(const TextureHandle& handle);

private:
    ResourceManager<TextureResource> *mResourceMgr;
};

#endif