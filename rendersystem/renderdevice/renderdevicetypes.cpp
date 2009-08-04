#include "renderdevicetypes.h"
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
    usage     = RES_USAGE_DEFAULT;
}

Texture::Texture()
{
    apitexture = NULL;
}

Texture::~Texture()
{
    static RenderDevice *renderdevice = RenderDevice::instance();
    renderdevice->DestroyTexture(this);
}

