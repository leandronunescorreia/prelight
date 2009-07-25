#if 1
#include "dxstdafx.h"

typedef IDirect3DBaseTexture9    APITexture;
typedef IDirect3DDevice9         APIRenderDevice;

typedef HWND                     hScreen;
#else
typedef void*    APITexture;
typedef void*    APIRenderDevice;

typedef void*    hScreen;
#endif