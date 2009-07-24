#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include <stdio.h>

class RenderSystem
{
public:
    struct Setting
    {
        bool fullScreen;
        int  width, height;
    };

    static RenderSystem* self();
private:
    RenderSystem();
public:
    ~RenderSystem();

    bool Initialize(const Setting& setting);
    bool ChangeSetting(const Setting& setting);
    void Update(int usec);
    void Finalize();

protected:
    static RenderSystem* rendersysInstance;

    bool    mInited;
    Setting mSetting;
    
};

#endif