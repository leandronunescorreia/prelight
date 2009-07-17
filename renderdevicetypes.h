#ifndef _RENDERERDEVICETYPES_H_
#define _RENDERERDEVICETYPES_H_

struct RenderDeviceSetting
{
    int width, height;
}

struct Rect
{
    int x;
    int y;
    int width;
    int height;
};


/** Render states' value types*/
//@{
enum EFaceCull
{
    FC_NONE,
    FC_CW,
    FC_CCW
};

enum EFillMode
{
    FILL_POINT,
    FILL_WIREFRAME,
    FILL_SOLID
};

enum EBlendFactor
{
    BLEND_ZERO,
    BLEND_ONE,
    BLEND_SRC_COLOR,
    BLEND_DEST_COLOR,
    BLEND_ONE_MINUS_SRC_COLOR,
    BLEND_ONE_MINUS_DEST_COLOR,
    BLEND_SRC_ALPHA,
    BLEND_DEST_ALPHA,
    BLEND_ONE_MINUS_SRC_ALPHA,
    BLEND_ONE_MINUS_DEST_ALPHA
};

enum ECompareFunc
{
    CMP_NEVER,
    CMP_LESS,
    CMP_EQUAL,
    CMP_LESS_EQUAL,
    CMP_GREATER,
    CMP_NOT_EQUAL,
    CMP_GREATER_EQUAL,
    CMP_ALWAYS
};

enum EStencilOP
{
    STENCIL_KEEP,
    STENCIL_ZERO,
    STENCIL_REPLACE,
    STENCIL_INCR,
    STENCIL_DECR,
    STENCIL_INVERT
};

enum ESamplerState
{
    SAMP_MAXMIPLEVEL,
    SAMP_MAXANISOTROPY,
};

enum ETextureAddressMode
{
    TADDRESS_WRAP,
    TADDRESS_CLAMP,
    TADDRESS_BORDER
};

enum ETextureFilter
{
    TFILTER_NEAREST,
    TFILTER_LINEAR,
    TFILTER_ANISOTROPIC,
    TFILTER_NO_MIPMAP,
};
//@}

enum EPixelFormat
{
    FMT_UNKNOWN,

    FMT_A8R8G8B8,
    FMT_X8R8G8B8,

    FMT_DXT1,
    FMT_DXT3,
    FMT_DXT5,

    FMT_D24S8,
    FMT_D24X8,

    FMT_R16F,
    FMT_R32F,
    FMT_G16R16F,
    FMT_A16B16G16R16F,
    FMT_A32B32G32R32F,
};

enum EResourceUsage
{
    RES_USAGE_DEFAULT      =    0,
    RES_USAGE_DYNAMIC      =    1 << 0,
    RES_USAGE_WRITEONLY    =    1 << 1,
    RES_USAGE_RENDERTARGET =    1 << 2,
    RES_USAGE_DEPTHSTENCIL =    1 << 3,
};

struct TextureSpec
{
    EPixelFormat format;
    int  width;
    int  height;
    int  mipLevels;
    bool linear;
    int  usage;
    bool gamaCorrection;
    
    TextureSpec();
    void Reset();
};


#endif //_RENDERERDEVICETYPES_H_