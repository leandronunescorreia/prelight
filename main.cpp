#include "engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
    if (Engine::self()->Initialize())
    {
        while( Engine::self()->Update() )
        {};
    }
    return 0;
}