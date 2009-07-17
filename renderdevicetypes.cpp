#include "rendererdevicetypes.h"


TextureSpec::TextureSpec()    
{
    Reset();
}

void TextureSpec::Reset()
{
    format = FMT_UNKNOWN;
    width  = 0;
    height = 0;
    mipLevels = 0;
    linear    = false;
    usage     = RES_USAGE_DEFAULT;
    gammaCorrection = false;
}


#endif //_RENDERERDEVICETYPES_H_