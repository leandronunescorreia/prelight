#define STRICT
#include "ApplicationApp.h"

#include "deferredshading.h"
#include "prelightshading.h"


Application _Application;
const Application *gApplication = &_Application;

/**

*/
void Application::Init()
{
	mDefaultShading = new DeferredShading();
	mDefaultShading->OneTimeSceneInit();

    // Initialize dialogs
    mSettingsDlg.Init( &mDialogResourceManager );
    mHUD.Init( &mDialogResourceManager );
    mHUD.SetCallback( OnGUIEvent );
    mHUD.AddButton( IDC_TOGGLEFULLSCREEN, L"Toggle full screen", 35, 34, 125, 22 );
    mHUD.AddButton( IDC_TOGGLEREF, L"Toggle REF (F3)", 35, 58, 125, 22, VK_F3 );
    mHUD.AddButton( IDC_CHANGEDEVICE, L"Change device (F2)", 35, 82, 125, 22, VK_F2 );

	mHUD.AddButton( IDC_SCISSORING, L"Disable Scissoring (C)", 0, 0, 140, 22, L'C' );
	mHUD.AddButton( IDC_SCISOROUTLINE, L"Show Scissor Outline (V)", 0, 0, 140, 22, L'V' );
	CDXUTListBox* pList;
	mHUD.AddListBox( IDC_MRTBUFFERS, 0, 0, 125, 70, 0, &pList );
	
	int i = 0;
	pList->AddItem( L"MRT0 - Diffuse Texture", (void*)(i++));
	pList->AddItem( L"MRT1 - Normals", (void*)(i++));
	pList->AddItem( L"MRT2 - Depth", (void*)(i++));
	pList->AddItem( L"Final Scene", (void*)(i));
	pList->SelectItem(i);

	mHUD.AddButton( IDC_TONEMAP, L"Disable Tone Mapping (T)", 0, 0, 140, 22, L'T' );

	mHUD.AddSlider( IDC_DEPTHBIAS_SLIDER, 0, 0, 125, 22, 0, 500, mDefaultShading->m_fDepthBias*100000.0f );
	TCHAR sz[100];
	_sntprintf( sz, 33, L"Depth Bias: %.4f", mDefaultShading->m_fDepthBias = ((float)mHUD.GetSlider(IDC_DEPTHBIAS_SLIDER)->GetValue()/100000.0f) );
	sz[99] = 0;
	mHUD.AddStatic( IDC_DEPTHBIAS_STATIC, sz, 0, 0, 125, 22 );

	mHUD.AddSlider( IDC_SLOPEBIAS_SLIDER, 0, 0, 125, 22, 0, 1000, mDefaultShading->m_fBiasSlope*10.0f );
	_sntprintf( sz, 33, L"Slope Bias: %.1f", mDefaultShading->m_fBiasSlope = ((float)mHUD.GetSlider(IDC_DEPTHBIAS_SLIDER)->GetValue()/10.0f) );
	sz[99] = 0;
	mHUD.AddStatic( IDC_SLOPEBIAS_STATIC, sz, 0, 0, 125, 22 );

	mHUD.AddButton( IDC_CONTROLLIGHT, L"Control Light (P)", 0, 0, 140, 22, L'P' );
	mHUD.AddButton( IDC_ANIMATELIGHTS, L"Animate Lights (L)", 0, 0, 140, 22, L'L' );
}


/**
It will be called during device initialization.
Checks the device for some minimum set of capabilities, and rejects those that don't pass by returning false.
*/
bool CALLBACK Application::IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, 
                                           D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
	bool bCapsAcceptable = true;

    IDirect3D9* d3d9= DXUTGetD3DObject();
    if (
        FAILED( d3d9->CheckDeviceFormat(D3DADAPTER_DEFAULT, pCaps->DeviceType, 
                                        D3DFMT_X8R8G8B8, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, 
		                                D3DRTYPE_TEXTURE, D3DFMT_A16B16G16R16F) )
        )
		bCapsAcceptable = false;
	if (FAILED(mDefaultShading->ConfirmDevice(pCaps,0,AdapterFormat, BackBufferFormat)))
		bCapsAcceptable = false;

	return bCapsAcceptable;
}


/**
It will be callbacked immediately before a device is created.
Allow the application to modify the device settings. The supplied pDeviceSettings parameter 
contains the settings that the framework has selected for the new device, and the 
application can make any desired changes directly to this structure.  Note however that 
the sample framework will not correct invalid device settings so care must be taken 
to return valid device settings, otherwise IDirect3D9::CreateDevice() will fail.  
*/
bool CALLBACK Application::ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext )
{
    return true;
}


/**
It will be called immediately after the Direct3D device has been created,
which will happen during application initialization and windowed/full screen toggles. 
This is the best location to create D3DPOOL_MANAGED resources since these 
resources need to be reloaded whenever the device is destroyed. 
Remark: Resources created here should be released in the OnDestroyDevice callback. 
*/
HRESULT CALLBACK Application::OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
    HRESULT hr;

    V_RETURN( mDialogResourceManager.OnCreateDevice( pd3dDevice ) );
    V_RETURN( mSettingsDlg.OnCreateDevice( pd3dDevice ) );

    // Initialize the font
    V_RETURN( D3DXCreateFont( pd3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, 
                             OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
                             L"Arial", &mFont ) );

	return S_OK;
}


/**
This callback function will be called immediately after the Direct3D device has been reset, 
which will happen after a lost device scenario. 
This is the best location to create D3DPOOL_DEFAULT resources since these resources need to be 
reloaded whenever the device is lost. 
Remark: Resources created here should be released in the OnLostDevice callback. 
*/
HRESULT CALLBACK Application::OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	HRESULT hr;

    V_RETURN( mDialogResourceManager.OnResetDevice() );
    V_RETURN( mSettingsDlg.OnResetDevice() );

	mDefaultShading->m_iBBHeight = pBackBufferSurfaceDesc->Height;
	mDefaultShading->m_iBBWidth = pBackBufferSurfaceDesc->Width;

	D3DCAPS9 deviceCaps;
	pd3dDevice->GetDeviceCaps(&deviceCaps);
	mDefaultShading->m_bCanTonemap = mDefaultShading->m_bCanTonemap && SUCCEEDED(DXUTGetD3DObject()->CheckDeviceFormat(D3DADAPTER_DEFAULT, 
		deviceCaps.DeviceType, D3DFMT_X8R8G8B8, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, D3DRTYPE_TEXTURE, 
		D3DFMT_A16B16G16R16F));

	V_RETURN(mDefaultShading->RestoreDeviceObjects(pd3dDevice));

	if ( mFont )
        V_RETURN( mFont->OnResetDevice() );

    // Create a sprite to help batch calls when drawing many lines of text
    V_RETURN( D3DXCreateSprite( pd3dDevice, &mTextSprite ) );

	D3DXVECTOR3 eyePt( 3.4184132f, -47.082867f, 25.271486f);
	D3DXVECTOR3 vLookatPt( 3.2370236f, -47.331966f, 24.320147f);// = mDefaultShading->m_Scene->m_Center;
	mCamera.SetViewParams( &eyePt, &vLookatPt);
	mDefaultShading->m_View = *mCamera.GetViewMatrix();

    float viewRadius = 100.f;
	//float viewRadius = 1.5f * mDefaultShading->m_Scene->m_Radius;
	// Setup the camera's projection parameters
	float zFar = 10.0f * viewRadius / 2.0f;
	float zNear = 0.2f;
	float fAspectRatio = pBackBufferSurfaceDesc->Width / (FLOAT)pBackBufferSurfaceDesc->Height;
	mCamera.SetProjParams( D3DXToRadian(60.0f), fAspectRatio, zNear, zFar );
	//mCamera.SetWindow( pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );
	mDefaultShading->m_Projection = *mCamera.GetProjMatrix();

    mHUD.SetLocation( 0, 0 );
    mHUD.SetSize( pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );

	int iY = 15;
    mHUD.GetControl( IDC_TOGGLEFULLSCREEN )->SetLocation( pBackBufferSurfaceDesc->Width - 135, iY);
    mHUD.GetControl( IDC_TOGGLEREF )->SetLocation( pBackBufferSurfaceDesc->Width - 135, iY += 24 );
    mHUD.GetControl( IDC_CHANGEDEVICE )->SetLocation( pBackBufferSurfaceDesc->Width - 135, iY += 24 );

	iY += 24;
	mHUD.GetControl( IDC_SCISSORING )->SetLocation( pBackBufferSurfaceDesc->Width - 145, iY += 24 );
	mHUD.GetControl( IDC_SCISOROUTLINE )->SetLocation( pBackBufferSurfaceDesc->Width - 145, iY += 24 );
	mHUD.GetControl( IDC_TONEMAP )->SetLocation( pBackBufferSurfaceDesc->Width - 145, iY += 24 );
	mHUD.GetControl( IDC_CONTROLLIGHT )->SetLocation( pBackBufferSurfaceDesc->Width - 145, iY += 24 );
	mHUD.GetControl( IDC_ANIMATELIGHTS )->SetLocation( pBackBufferSurfaceDesc->Width - 145, iY += 24 );

	mHUD.GetControl( IDC_MRTBUFFERS )->SetLocation( pBackBufferSurfaceDesc->Width - (iY = 135), pBackBufferSurfaceDesc->Height - 80 );

	mHUD.GetControl( IDC_DEPTHBIAS_SLIDER )->SetLocation( pBackBufferSurfaceDesc->Width - (iY += 135), pBackBufferSurfaceDesc->Height - 35 );
	mHUD.GetControl( IDC_DEPTHBIAS_STATIC )->SetLocation( pBackBufferSurfaceDesc->Width - (iY), pBackBufferSurfaceDesc->Height - 50 );

	mHUD.GetControl( IDC_SLOPEBIAS_SLIDER )->SetLocation( pBackBufferSurfaceDesc->Width - (iY += 135), pBackBufferSurfaceDesc->Height - 35 );
	mHUD.GetControl( IDC_SLOPEBIAS_STATIC )->SetLocation( pBackBufferSurfaceDesc->Width - (iY), pBackBufferSurfaceDesc->Height - 50 );

	pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);


    return S_OK;
}


/**
It will be called once at the beginning of every frame. 
This is the best location for your application to handle updates to the scene, 
but is not intended to contain actual rendering calls, 
which should instead be placed in the OnFrameRender callback.  
*/
void CALLBACK Application::OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    mCamera.FrameMove( fElapsedTime );
}


/**
It will be called at the end of every frame to perform all the rendering calls for the scene, 
and it will also be called if the window needs to be repainted. 
After this function has returned, the sample framework will call IDirect3DDevice9::Present to 
display the contents of the next buffer in the swap chain
*/
void CALLBACK Application::OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    // If the settings dialog is being shown, then
    // render it instead of rendering the app's scene
    if ( mSettingsDlg.IsActive() )
    {
        mSettingsDlg.OnRender( fElapsedTime );
        return;
    }

    HRESULT hr;

	// Begin the scene
    if (SUCCEEDED(pd3dDevice->BeginScene()))
    {
		mDefaultShading->m_View = *mCamera.GetViewMatrix();
		mDefaultShading->m_Projection = *mCamera.GetProjMatrix();

		mDefaultShading->Render(pd3dDevice);
        // Render stats and help text  
        RenderText();

		V( mHUD.OnRender( fElapsedTime ) );

        // End the scene.
        V( pd3dDevice->EndScene() );
    }
}


//--------------------------------------------------------------------------------------
// Render the help and statistics text. This function uses the ID3DXFont interface for 
// efficient text rendering.
//--------------------------------------------------------------------------------------
void Application::RenderText()
{
    // The helper object simply helps keep track of text position, and color
    // and then it calls pFont->DrawText( m_pSprite, strMsg, -1, &rc, DT_NOCLIP, m_clr );
    // If NULL is passed in as the sprite object, then it will work however the 
    // pFont->DrawText() will not be batched together.  Batching calls will improves performance.
    CDXUTTextHelper txtHelper( mFont, mTextSprite, 15 );
    const D3DSURFACE_DESC* pd3dsdBackBuffer = DXUTGetBackBufferSurfaceDesc();

	// Output statistics
	txtHelper.Begin();
	txtHelper.SetInsertionPos( 5, 15 );
	if ( mShowUI )
	{
		txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
		txtHelper.DrawTextLine( DXUTGetFrameStats() );
		txtHelper.DrawTextLine( DXUTGetDeviceStats() );

		// Display any additional information text here

		if ( !mShowHelp )
		{
			txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ));
			txtHelper.DrawTextLine( TEXT("F1      - Toggle help text") );
		}
	}

	if ( mShowHelp )
	{
		// Display help text here
		txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
		txtHelper.DrawTextLine( TEXT("F1      - Toggle help text") );
		txtHelper.DrawTextLine( TEXT("H       - Toggle UI") );
		txtHelper.DrawTextLine( TEXT("ESC  - Quit") );
		txtHelper.DrawTextLine( TEXT("") );
		txtHelper.DrawTextLine( TEXT("W,A,S,D - Move") );
		txtHelper.DrawTextLine( TEXT("Q,E     - Strafe Up/Down") );
	}
	txtHelper.End();
}


//--------------------------------------------------------------------------------------
// Before handling window messages, the sample framework passes incoming windows 
// messages to the application through this callback function. If the application sets 
// *pbNoFurtherProcessing to TRUE, then the sample framework will not process this message.
//--------------------------------------------------------------------------------------
LRESULT CALLBACK Application::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext )
{
    // Always allow dialog resource manager calls to handle global messages
    // so GUI state is updated correctly
    mDialogResourceManager.MsgProc( hWnd, uMsg, wParam, lParam );

    if ( mSettingsDlg.IsActive() )
    {
        mSettingsDlg.MsgProc( hWnd, uMsg, wParam, lParam );
        return 0;
    }

    // Give the dialogs a chance to handle the message first
    *pbNoFurtherProcessing = mHUD.MsgProc( hWnd, uMsg, wParam, lParam );
    if ( *pbNoFurtherProcessing )
        return 0;

	if ( !(mControlLightMode && (wParam == 'w' || wParam == 'W' || wParam == 'a' || wParam == 'A' || wParam == 's' || wParam == 'S' || wParam == 'd' || wParam == 'D' || wParam == 'q' || wParam == 'Q' || wParam == 'e' || wParam == 'E')))
	    // Pass all remaining windows messages to camera so it can respond to user input
		mCamera.HandleMessages( hWnd, uMsg, wParam, lParam );

    return 0;
}


//--------------------------------------------------------------------------------------
// As a convenience, the sample framework inspects the incoming windows messages for
// keystroke messages and decodes the message parameters to pass relevant keyboard
// messages to the application.  The framework does not remove the underlying keystroke 
// messages, which are still passed to the application's MsgProc callback.
//--------------------------------------------------------------------------------------
void CALLBACK Application::KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
	if ( bKeyDown )
	{
		switch( nChar )
		{
		case VK_F1:
			mShowHelp = !mShowHelp;
			break;

		case 'H':
		case 'h':
			mShowUI = !mShowUI;
			for ( int i = 0; i < IDC_LAST; i++ )
				mHUD.GetControl(i)->SetVisible( mShowUI );
			break;
		case 'w':
		case 'W':
			if (mControlLightMode)
				mDefaultShading->m_Lights[1].Position.x += 0.5f;
			break;
		case 'a':
		case 'A':
			if (mControlLightMode)
				mDefaultShading->m_Lights[1].Position.z += 0.5f;
			break;
		case 's':
		case 'S':
			if (mControlLightMode)
				mDefaultShading->m_Lights[1].Position.x -= 0.5f;
			break;
		case 'd':
		case 'D':
			if (mControlLightMode)
				mDefaultShading->m_Lights[1].Position.z -= 0.5f;
			break;
		case 'q':
		case 'Q':
			if (mControlLightMode)
				mDefaultShading->m_Lights[1].Position.y += 0.5f;
			break;
		case 'e':
		case 'E':
			if (mControlLightMode)
				mDefaultShading->m_Lights[1].Position.y -= 0.5f;
			break;
		}
	}
}

//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void CALLBACK Application::OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{
	switch( nControlID )
    {
        case IDC_TOGGLEFULLSCREEN: DXUTToggleFullScreen(); break;
        case IDC_TOGGLEREF:        DXUTToggleREF(); break;
        case IDC_CHANGEDEVICE:     mSettingsDlg.SetActive( !mSettingsDlg.IsActive() ); break;
		case IDC_SCISSORING:
			{
				mDefaultShading->m_bDoScissor = !mDefaultShading->m_bDoScissor;
				if ( mDefaultShading->m_bDoScissor )
					mHUD.GetButton( IDC_SCISSORING )->SetText(L"Enable Scissoring (C)");
				else
					mHUD.GetButton( IDC_SCISSORING )->SetText(L"Disable Scissoring (C)");
					
				break;
			}
		case IDC_SCISOROUTLINE:
			{
				if ( mDefaultShading->m_bDebugScissor = !mDefaultShading->m_bDebugScissor )
					mHUD.GetButton( IDC_SCISOROUTLINE )->SetText( L"Hide Scissor Outline (V)" );
				else
					mHUD.GetButton( IDC_SCISOROUTLINE )->SetText( L"Show Scissor Outline (V)" );
				break;
			}
		case IDC_MRTBUFFERS:
			{
				switch (mHUD.GetListBox( IDC_MRTBUFFERS )->GetSelectedIndex())
				{
				case 0:
					mDefaultShading->m_currRenderMode = RM_CHANNEL0;
					break;
				case 1:
					mDefaultShading->m_currRenderMode = RM_CHANNEL1;
					break;
				case 2:
					mDefaultShading->m_currRenderMode = RM_CHANNEL2;
					break;
				case 3:
					mDefaultShading->m_currRenderMode = RM_NORMAL;
					break;
				}
				break;
			}
		case IDC_TONEMAP:
			{
				mDefaultShading->m_bTonemap = !mDefaultShading->m_bTonemap;
				if ( mDefaultShading->m_bTonemap  )
					mHUD.GetButton( IDC_TONEMAP )->SetText( L"Enable Tone Mapping (T)" );
				else
					mHUD.GetButton( IDC_TONEMAP )->SetText( L"Disable Tone Mapping (T)" );
				break;
			}
		case IDC_DEPTHBIAS_SLIDER:
			{
				TCHAR sz[100];
				_sntprintf( sz, 33, L"Depth Bias: %.4f", mDefaultShading->m_fDepthBias = ((float)mHUD.GetSlider(IDC_DEPTHBIAS_SLIDER)->GetValue()/100000.0f) );
				sz[99] = 0;
				mHUD.GetStatic(IDC_DEPTHBIAS_STATIC)->SetText(sz);
				break;
			}
		case IDC_SLOPEBIAS_SLIDER:
			{
				TCHAR sz[100];
				_sntprintf( sz, 33, L"Slope Bias: %.1f", mDefaultShading->m_fBiasSlope = ((float)mHUD.GetSlider(IDC_SLOPEBIAS_SLIDER)->GetValue()/10.0f));
				sz[99] = 0;
				mHUD.GetStatic(IDC_SLOPEBIAS_STATIC)->SetText(sz);
				break;
			}
		case IDC_CONTROLLIGHT:
			{
				mControlLightMode = !mControlLightMode;
				if ( mControlLightMode )
					mHUD.GetButton( IDC_CONTROLLIGHT )->SetText( L"Control Light (P)" );
				else
					mHUD.GetButton( IDC_CONTROLLIGHT )->SetText( L"Control Camera (P)" );
				break;
			}
		case IDC_ANIMATELIGHTS:
			{
				mDefaultShading->m_bAnimateLights = !mDefaultShading->m_bAnimateLights;
				break;
			}
    }
}


//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has 
// entered a lost state and before IDirect3DDevice9::Reset is called. Resources created
// in the OnResetDevice callback should be released here, which generally includes all 
// D3DPOOL_DEFAULT resources. See the "Lost Devices" section of the documentation for 
// information about lost devices.
//--------------------------------------------------------------------------------------
void CALLBACK Application::OnLostDevice( void* pUserContext )
{
    mDialogResourceManager.OnLostDevice();
    mSettingsDlg.OnLostDevice();

    if ( mFont )
        mFont->OnLostDevice();

	SAFE_RELEASE(mTextSprite);

	mDefaultShading->InvalidateDeviceObjects();
}


//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has 
// been destroyed, which generally happens as a result of application termination or 
// windowed/full screen toggles. Resources created in the OnCreateDevice callback 
// should be released here, which generally includes all D3DPOOL_MANAGED resources. 
//--------------------------------------------------------------------------------------
void CALLBACK Application::OnDestroyDevice( void* pUserContext )
{
    mDialogResourceManager.OnDestroyDevice();
    mSettingsDlg.OnDestroyDevice();

    SAFE_RELEASE(mFont);
}