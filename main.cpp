#include "dxstdafx.h"
#include "application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
    // Set DXUT's callback functions. 
    DXUTSetCallbackDeviceCreated( Application::OnCreateDevice );
    DXUTSetCallbackDeviceReset( Application::OnResetDevice );
    DXUTSetCallbackDeviceLost( Application::OnLostDevice );
    DXUTSetCallbackDeviceDestroyed( Application::OnDestroyDevice );
    DXUTSetCallbackMsgProc( Application::MsgProc );
    DXUTSetCallbackKeyboard( Application::KeyboardProc );
    DXUTSetCallbackFrameRender( Application::OnFrameRender );
    DXUTSetCallbackFrameMove( Application::OnFrameMove );

    // Show the cursor and clip it when in full screen
    DXUTSetCursorSettings( true, true );

    gApplication->Init();

    // Initialize the sample framework and create the desired Win32 window and Direct3D 
    // device for the application. Calling each of these functions is optional, but they
    // allow you to set several options which control the behavior of the framework.
    DXUTInit( true, true, true ); // Parse the command line, handle the default hotkeys, and show msgboxes
    DXUTCreateWindow( L"Light Pre-Pass Application" );
    DXUTCreateDevice( D3DADAPTER_DEFAULT, true, 512, 512, IsDeviceAcceptable, ModifyDeviceSettings );

    // Pass control to the sample framework for handling the message pump and 
    // dispatching render calls. The sample framework will call your FrameMove 
    // and FrameRender callback when there is idle time between handling window messages.
    DXUTMainLoop();

    // Perform any application-level cleanup here. Direct3D device resources are released within the
    // appropriate callback functions and therefore don't require any cleanup code here.
    return DXUTGetExitCode();
}
