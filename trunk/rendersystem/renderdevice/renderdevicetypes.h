#ifndef _RENDERERDEVICETYPES_H_
#define _RENDERERDEVICETYPES_H_

#ifdef _D3D9
#include "./d3d9/renderdevicetypes_d3d9.h"
#endif

struct RenderDeviceSetting
{
    hScreen screenHandle;
    bool    fullscreen;
    int     width, height;
};

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

enum ELockType
{
    LOCKTYPE_READ             =  0,
    LOCKTYPE_WRITE            =  1 << 0,
    LOCKTYPE_DISCARD_WRITE    =  1 << 1,
    LOCKTYPE_READ_AND_WRITE   =  1 << 2,

    LOCKTYPE_DEFAULT          =  LOCKTYPE_WRITE,
};

enum EPrimitiveType
{
    PT_TRIANGLE_LIST,
    PT_TRIANGLE_FAN,
    PT_TRIANGLE_STRIP,
    PT_LINE_LIST,
    PT_LINE_STRIP,
    PT_POINT_LIST
};

struct Texture
{
    struct Spec
    {
        EPixelFormat format;

        int  width;
        int  height;
        int  mipLevels;
        bool linear;
        int  usage;
        bool gamaCorrection;

        Spec();
        void Reset();
    };

    Texture();
    ~Texture();  

    Spec          spec;
    APITexture*   apitexture;              ///< Point to graphics API's texture resource.
};

typedef Texture::Spec TextureSpec;

enum ECubeFace 
{
    CUBE_X,
    CUBE_NX,
    CUBE_Y,
    CUBE_NY,
    CUBE_Z,
    CUBE_NZ,
    CUBE_MAX
};


struct Vertices
{
    struct Spec
    {
    
    };
};

typedef Vertices::Spec VertexBufSpec;

struct RegistersMap
{

};

struct IndexBuffer
{
    struct Spec
    {
    
    };
};

typedef IndexBuffer::Spec IndexBufSpec;

struct VertexShader
{
    struct Spec
    {
    
    };
};

struct PixelShader
{
    struct Spec
    {
    
    };
};

struct OcclusionQuery
{
    
};


#endif //_RENDERERDEVICETYPES_H_