#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "renderdevicetypes.h"
#include "../../common/resourcemanager.h"


class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    typedef ResourceManager<Texture>::Handle hTexture;
    static const hTexture cInvalidHandle = ResourceManager<Texture>::cInvalidHandle;

    /**
    /param capacity is the maximum texture count can exists in TextureManager.
    */
    bool        Initialize(int capacity);
    bool        Finalize();

    /** Find a texture by name, load a new texture from disk if this name doesn't exist.*/
    hTexture	FindOrLoadTexture(const char *filename);

    /** Find a texture by name, create a new empty texture if this name doesn't exist or existed texture's spec doesn't match.*/
    hTexture    FindOrCreateTexture(const char *name, const TextureSpec &spec);

    /** Find a texture by name and increase refcount, return invalid handle if this name doesn't exist.*/
    hTexture    FindTexture(const char *name);

    /** Decrease texture's refcount. Set \param handle to invalid texture handle.*/
    bool        ReleaseTexture(hTexture& handle);

    /** Reload texture from disk without change texture's refcount.*/
	bool	    ReloadTexture(Texture texture);

    /** Get texture's handle.*/
    const TextureSpec*  GetTextureSpec(const hTexture& handle);

private:
    ResourceManager<Texture> *mResourceMgr;
};

#endif