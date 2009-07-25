#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "stdafx_pch.h"
#include "./rendersystem/rendersystem.h"

class Engine
{
public:
    struct Setting
    {
        bool cmdConsole;
        bool fullScreen;
        int  resolutionX, resolutionY;
    };

    static Engine* instance();
private:
    Engine();
public:
    ~Engine();

    bool    Initialize(const Setting *setting = NULL);
    bool    Update();
    void     Finalize();

protected:
    bool    InitializeScreen();
    void    FinalizeScreen();
    hScreen GetScreenHandle();
    bool    UpdateSystemMessage();

    bool    InitializeRenderSystem();
    void    FinalizeRenderSystem();

private:
#ifdef WIN32
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif

protected:
    static Engine* engineInstance;
    const static Setting sDefaultSetting;

    bool    mInited;
    Setting mSetting;
    hScreen mScreenHandle;

    RenderSystem*           mRenderSystem;

    //Console         *mConsole;
    //UISystem        *mUISystem;
    //FileSystem      *mFileSystem;

#ifdef WIN32
    LPCWSTR mWindowClassName;
    LPCWSTR mWindowTitle;
#endif
};

#endif