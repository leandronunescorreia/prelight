#include "dxstdafx.h"

typedef IDirect3DBaseTexture9    APITexture;
typedef IDirect3DDevice9        APIRenderDevice;

typedef HWND                     APIWindow;
typedef long (*m_MsgProcCallback)(void *hWnd, unsigned int msg, unsigned int wParam, long lParam, bool &bNoFurtherProcessing);