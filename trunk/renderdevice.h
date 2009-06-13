#include <windows.h>

class RenderDevice
{
public:
	RenderDevice();
	~RenderDevice();

	bool Initialize(HWND handle, int width, int height);
	bool Finalize();

protected:
	void InitD3DPresentParameters();
	bool CreateD3DDevice();

private:
	HWND mWinHandle;
	int mWinWidth, mWinHeight;
	D3DPRESENT_PARAMETERS	md3dpp;	/// D3D presentation parameters.
}