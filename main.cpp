#include "application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
    if (Application::self()->Initialize())
    {
        while( Application::self()->Run() )
            ;

        return Application::self()->Finalize();
    }
    return -1;
}