#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include <stdio.h>
#include "./renderdevice/renderdevice.h"

class RenderSystem
{
public:
    struct Setting
    {
        hScreen screen;
        bool    fullScreen;
        int     width, height;
    };

    static RenderSystem* instance();
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

    RenderDevice *mRenderDevice;
    
};

#endif