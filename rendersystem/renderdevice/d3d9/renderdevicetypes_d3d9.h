#ifndef _RENDERDEVICETYPES_D3D9_H_
#define _RENDERDEVICETYPES_D3D9_H_

#include "dxstdafx.h"

typedef IDirect3D9               APIInterface;
typedef IDirect3DDevice9         APIRenderDevice;
typedef IDirect3DBaseTexture9    APITexture;


typedef HWND                     hScreen;

enum API_PIXEL_FORMAT
{
    API_FMT_UNKNOW        =  D3DFMT_UNKNOWN,      
                            
    API_FMT_A8R8G8B8      =  D3DFMT_A8R8G8B8,     
    API_FMT_X8R8G8B8      =  D3DFMT_X8R8G8B8,     
                            
    API_FMT_DXT1          =  D3DFMT_DXT1,         
    API_FMT_DXT3          =  D3DFMT_DXT3,         
    API_FMT_DXT5          =  D3DFMT_DXT5,         
                            
    API_FMT_D24S8         =  D3DFMT_D24S8,        
    API_FMT_D24X8         =  D3DFMT_D24X8,        
                            
    API_FMT_R16F          =  D3DFMT_R16F,         
    API_FMT_R32F          =  D3DFMT_R32F,         
    API_FMT_G16R16F       =  D3DFMT_G16R16F,      
    API_FMT_A16B16G16R16F =  D3DFMT_A16B16G16R16F,
    API_FMT_A32B32G32R32F =  D3DFMT_A32B32G32R32F,
};


enum API_USAGE
{
    API_USAGE_DEFAULT      = 0,
    API_USAGE_DYNAMIC      = D3DUSAGE_DYNAMIC,
    API_USAGE_WRITEONLY    = D3DUSAGE_WRITEONLY,
    API_USAGE_RENDERTARGET = D3DUSAGE_RENDERTARGET,
    API_USAGE_DEPTHSTENCIL = D3DUSAGE_DEPTHSTENCIL,
};


#endif //_RENDERDEVICETYPES_D3D9_H_