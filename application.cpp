#include "stdafx_pch.h"
#include "application.h"

Application* Application::appInstance = NULL;

Application::Application()
{
}

inline Application* Application::self()
{
    if (NULL == appInstance)
        appInstance = new Application();

    return appInstance;
}


Application::~Application()
{
    
}


const AppSetting Application::sDefaultSetting = { true, false, 1024, 768 };

bool Application::Initialize(const AppSetting *setting /*= NULL*/)
{
    if (NULL == setting)
    {
        mSetting = sDefaultSetting;
    }
    else
    {
        mSetting = *setting;
    }

    if (!InitScreen())
        return false;

    return true;
}


bool Application::Run()
{
    return true;
}


int Application::Finalize()
{
    return 0;
}


bool Application::InitScreen()
{
    LPCWSTR className = (LPCWSTR)"Deferred-Lighting renderer";
    LPCWSTR winTitle = (LPCWSTR)"Deferred-Lighting render demo";

    /** Register the window's class.*/
    WNDCLASSEXW wc = 
    {
        sizeof(WNDCLASSEXW),
        CS_CLASSDC,
        Application::WndProc,
        0,
        0,
        GetModuleHandle(NULL),
        NULL,
        NULL,
        NULL,
        NULL,
        className,
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
        width = ::GetSystemMetrics(SM_CXSCREEN);
        height = ::GetSystemMetrics(SM_CYSCREEN);
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
    HWND hwnd = CreateWindowExW(
                                exstyle,
                                className,
                                winTitle,
                                WS_OVERLAPPEDWINDOW,
                                x,
                                y,
                                width,
                                height,
                                GetDesktopWindow(),
                                NULL,
                                GetModuleHandle(NULL),
                                NULL
                               );
    assert(NULL != hwnd);

    ShowWindow(hwnd, SW_SHOWNORMAL);

    SetForegroundWindow(hwnd);
    UpdateWindow(hwnd);
    return true;
}

LONG WINAPI Application::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}