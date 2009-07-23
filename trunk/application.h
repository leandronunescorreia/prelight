#ifndef _DEFERREDSHADINGAPP_H_
#define _DEFERREDSHADINGAPP_H_


extern const Application *gApplication;

class Application
{
public:
    void    Init();
    void    Run();

protected:
    void    InitScreen();
}

#endif