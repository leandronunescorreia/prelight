#include "rendererdevicetypes.h"
#include "renderdevice.h"

Texture::Spec::Spec()    
{
    Reset();
}

void Texture::Spec::Reset()
{
    format = FMT_UNKNOWN;
    width  = 0;
    height = 0;
    mipLevels = 0;
    linear    = false;
    usage     = RES_USAGE_DEFAULT;
    gammaCorrection = false;
}

Texture::Texture()
{
    apitexture = NULL;
}

Texture::~Texture()
{
    gRenderDevice->DestroyTexture(this);
}

#endif //_RENDERERDEVICETYPES_H_