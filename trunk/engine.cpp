#include "stdafx_pch.h"
#include "engine.h"

/** 
multimon.h is a stub module that fakes multiple monitor apis on Win32 OSes without them.
Only once source file should #define COMPILE_MULTIMON_STUBS
*/
#ifdef WIN32
#define COMPILE_MULTIMON_STUBS
#include <multimon.h> 
#endif

Engine* Engine::engineInstance = NULL;

Engine::Engine()
: mInited(false)
, mSetting(sDefaultSetting)
, mScreenHandle(NULL)
, mRenderSystem(NULL)
{
#ifdef WIN32
    mWindowClassName = (LPCWSTR)L"Deferred-Lighting renderer";
    mWindowTitle = (LPCWSTR)L"Deferred-Lighting render demo";
#endif
}

Engine* Engine::instance()
{
    if (NULL == engineInstance)
        engineInstance = new Engine();

    return engineInstance;
}


Engine::~Engine()
{
    Finalize();
}


const Engine::Setting Engine::sDefaultSetting = { true, false, 1024, 768 };

bool Engine::Initialize(const Engine::Setting *setting /*= NULL*/)
{
    if (mInited)
        return false;
        
    if (NULL != setting)
        mSetting = *setting;

    bool isOk = true;

    if (isOk) 
        isOk = InitializeScreen();

    if (isOk) 
        isOk = InitializeRenderSystem();

    if (!isOk)
    {
        Finalize();
        return false;
    }

    mInited = true;
    return true;
}


bool Engine::Update()
{
    if (!mInited)
        return false;;

    if (!UpdateSystemMessage())
        return false;
    
    return true;
}


void Engine::Finalize()
{
    FinalizeRenderSystem();
    FinalizeScreen();   ///< Finalize screen at the last.
    mInited = false;
}

#ifdef WIN32
bool Engine::InitializeScreen()
{
    /** Register the window's class.*/
    WNDCLASSEXW wc = 
    {
        sizeof(WNDCLASSEXW),
        CS_CLASSDC,
        WndProc,
        0,
        0,
        GetModuleHandle(NULL),
        NULL,
        NULL,
        NULL,
        NULL,
        mWindowClassName,
        NULL
    };
    RegisterClassExW(&wc);

    /** Calculate the window's position and size.*/
    DWORD exstyle = 0;
    int x = 0, y = 0;
    int width = mSetting.resolutionX, height = mSetting.resolutionY;
    if (mSetting.fullScreen)
    {
        exstyle = WS_EX_TOPMOST;
        x = y = 0;
        width = GetSystemMetrics(SM_CXSCREEN);
        height = GetSystemMetrics(SM_CYSCREEN);
    }
    else
    {
        RECT windowRect = {0, 0, width, height};
        AdjustWindowRect( &windowRect, WS_OVERLAPPEDWINDOW, FALSE);
        width = windowRect.right - windowRect.left;
        height = windowRect.bottom - windowRect.top;

        int screenx = GetSystemMetrics(SM_CXSCREEN);
        int screeny = GetSystemMetrics(SM_CYSCREEN);
        x = (screenx - width) / 2;
        y = (screeny - height) / 2;
    }

    /** Create a new visible window.*/
    HWND hWnd = CreateWindowExW(
                                exstyle,
                                mWindowClassName,
                                mWindowTitle,
                                WS_POPUP,
                                x,
                                y,
                                width,
                                height,
                                GetDesktopWindow(),
                                NULL,
                                GetModuleHandle(NULL),
                                NULL
                               );
    assert(NULL != hWnd);

    mSetting.resolutionX = width;
    mSetting.resolutionY = height;

    ShowWindow(hWnd, SW_SHOWNORMAL);

    /** Fill window with black color.*/
    HDC hdc = GetDC(hWnd);
    RECT rect = { 0, 0, 0, 0 };
    GetClientRect(hWnd, &rect);
    HBRUSH blackbrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    FillRect(hdc, &rect, blackbrush);
    ReleaseDC(hWnd, hdc);

    SetForegroundWindow(hWnd);
    UpdateWindow(hWnd);

    mScreenHandle = hWnd;
    return true;
}

void Engine::FinalizeScreen()
{
    if (NULL == mScreenHandle)
        return;

    DestroyWindow(mScreenHandle);
    UnregisterClassW(mWindowClassName, GetModuleHandle(NULL));
}
#endif


inline hScreen Engine::GetScreenHandle()
{
    return mScreenHandle;
}

#ifdef WIN32
bool Engine::UpdateSystemMessage()
{
    MSG msg;

	while (PeekMessageW(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if (GetMessageW(&msg, NULL, 0, 0) == 0)
			return false;
     	TranslateMessage( &msg );
     	DispatchMessageW( &msg );
	}
    return true;
}


LRESULT CALLBACK Engine::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            PostQuitMessage(0);
        return 0;

	case WM_CLOSE:
        Engine::instance()->Finalize();
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	// Not handled.
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
#endif

bool Engine::InitializeRenderSystem()
{
    mRenderSystem = RenderSystem::instance();
    RenderSystem::Setting setting = {mScreenHandle, mSetting.fullScreen, mSetting.resolutionX, mSetting.resolutionY};
    mRenderSystem->Initialize(setting);
    
    return true;
}

void Engine::FinalizeRenderSystem()
{
    if (NULL == mRenderSystem)
        return;

    mRenderSystem->Finalize();
    mRenderSystem = NULL;
}