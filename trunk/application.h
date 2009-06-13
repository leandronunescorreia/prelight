#ifndef _DEFERREDSHADINGAPP_H_
#define _DEFERREDSHADINGAPP_H_


//--------------------------------------------------------------------------------------
// UI control IDs
//--------------------------------------------------------------------------------------
enum
{
    IDC_TOGGLEFULLSCREEN,
    IDC_TOGGLEREF,
    IDC_CHANGEDEVICE,
    IDC_SCISSORING,
    IDC_SCISOROUTLINE,
    IDC_MRTBUFFERS,
    IDC_TONEMAP,
    IDC_DEPTHBIAS_SLIDER,
    IDC_DEPTHBIAS_STATIC,
    IDC_SLOPEBIAS_SLIDER,
    IDC_SLOPEBIAS_STATIC,
    IDC_CONTROLLIGHT,
    IDC_ANIMATELIGHTS,
    IDC_LAST
};

extern const Application *gApplication;

class Application
{
    //--------------------------------------------------------------------------------------
    // Forward declarations 
    //--------------------------------------------------------------------------------------
    static bool    CALLBACK IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext );
    static bool    CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext );
    static HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
    static HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
    static void    CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
    static void    CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
    static LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext );
    static void    CALLBACK KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
    static void    CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );
    static void    CALLBACK OnLostDevice( void* pUserContext );
    static void    CALLBACK OnDestroyDevice( void* pUserContext );
    
    void    Init();
    void    RenderText();
    
    //--------------------------------------------------------------------------------------
    // Global Variables
    //--------------------------------------------------------------------------------------
    CFirstPersonCamera           mCamera;                // A model viewing camera
    CDXUTDialog                  mHUD;                   // dialog for standard controls
    CDXUTDialogResourceManager   mDialogResourceManager; // manager for shared resources of dialogs
    CD3DSettingsDlg              mSettingsDlg;           // Device settings dialog
    ID3DXFont*                   mFont;                 // Font for drawing text
    ID3DXSprite*                 mTextSprite;           // Sprite for batching draw text calls
    bool					     mShowHelp;
    bool					     mShowUI;
    bool					     mControlLightMode;
    DefaultShading*		         mDefaultShading;
}

#endif