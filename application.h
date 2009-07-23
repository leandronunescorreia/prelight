#ifndef _APPLICATION_H_
#define _APPLICATION_H_

struct AppSetting
{
    bool cmdConsole;
    bool fullScreen;
    int  resolutionX, resolutionY;
};

class Application
{
    static Application* appInstance;
    Application();

public:
    static Application* self();
    ~Application();

    bool    Initialize(const AppSetting *setting = NULL);
    bool    Run();
    int     Finalize();

protected:
    bool    InitScreen();

    static LONG WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    AppSetting mSetting;
    const static AppSetting sDefaultSetting;
};

#endif