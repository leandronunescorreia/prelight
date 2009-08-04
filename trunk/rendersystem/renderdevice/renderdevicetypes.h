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


/** 
Render states' types

Many enum type states use the same integer value with api's format, then we don't need 
frequently convert it to api's format value at runtime. 

/remark The problem is we will have different enum value for different api.
If we want save states for different graphic api using, we should save string 
or at least enum value's index. 

FIX ME: Consider using macros to define enum and string array at same time and 
        keep them consistent.
*/

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
    FMT_UNKNOWN       = API_FMT_UNKNOW,

    FMT_A8R8G8B8      = API_FMT_A8R8G8B8,
    FMT_X8R8G8B8      = API_FMT_X8R8G8B8,

    FMT_DXT1          = API_FMT_DXT1,
    FMT_DXT3          = API_FMT_DXT3,
    FMT_DXT5          = API_FMT_DXT5,

    FMT_D24S8         = API_FMT_D24S8,
    FMT_D24X8         = API_FMT_D24X8,

    FMT_R16F          = API_FMT_R16F,
    FMT_R32F          = API_FMT_R32F,
    FMT_G16R16F       = API_FMT_G16R16F,
    FMT_A16B16G16R16F = API_FMT_A16B16G16R16F,
    FMT_A32B32G32R32F = API_FMT_A32B32G32R32F,
};


enum EResourceUsage
{
    RES_USAGE_DEFAULT      = API_USAGE_DEFAULT,
    RES_USAGE_DYNAMIC      = API_USAGE_DYNAMIC,
    RES_USAGE_WRITEONLY    = API_USAGE_WRITEONLY,
    RES_USAGE_RENDERTARGET = API_USAGE_RENDERTARGET,
    RES_USAGE_DEPTHSTENCIL = API_USAGE_DEPTHSTENCIL,
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
        EPixelFormat    format;
        EResourceUsage  usage;
        int             width;
        int             height;
        int             mipLevels;

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