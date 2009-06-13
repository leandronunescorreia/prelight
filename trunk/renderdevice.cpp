#include "renderdevice.h"

RenderDevice::RenderDevice():
mWinHandle(-1)
{

}

RenderDevice::~RenderDevice()
{
	Finalize();
}

bool RenderDevice::Initialize(HWND handle, int width, int height)
{
	mWinHandle = handle;
	return true;
}

bool RenderDevice::Finalize()
{
	return true;
}

void RenderDevice::InitD3DPresentParameters()
{
	memset( &md3dpp, 0, sizeof(md3dpp) );

	md3dpp.Windowed = TRUE;
	md3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	md3dpp.EnableAutoDepthStencil = TRUE;
	md3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	md3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	md3dpp.BackBufferWidth = WindowWidth();
	md3dpp.BackBufferHeight = WindowHeight();
	md3dpp.BackBufferFormat = backBufferFormat;
	md3dpp.BackBufferCount = 1;
	md3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	md3dpp.hDeviceWindow = ( HWND )RenderSys().GetRenderWindowHandle();
}

bool RenderDevice::CreateD3DDevice()
{

}