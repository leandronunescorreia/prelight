#include "engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
    if (Engine::instance()->Initialize())
    {
        while( Engine::instance()->Update() )
        {};
    }
    return 0;
}