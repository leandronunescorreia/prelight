#include "rendersystem.h"

RenderSystem* RenderSystem::rendersysInstance = NULL;

RenderSystem* RenderSystem::instance()
{
    if (NULL == rendersysInstance)
        rendersysInstance = new RenderSystem();
    return rendersysInstance;
}

RenderSystem::RenderSystem()
: mInited(false)
{
}


RenderSystem::~RenderSystem()
{
    Finalize();
}

bool RenderSystem::Initialize(const RenderSystem::Setting& setting)
{
    if (mInited)
        return false;
    mSetting = setting;
    
    bool isOk = true;
    mRenderDevice = RenderDevice::instance();
    if (isOk)
    {
        RenderDevice::Setting setting = { 
                                            mSetting.screen, 
                                            mSetting.fullScreen, 
                                            mSetting.width, 
                                            mSetting.height 
                                        };

        isOk = mRenderDevice->Initialize(setting);
    }

    if (!isOk)
    { 
        Finalize();
        return false;
    }
    mInited = true;
    return true;
}

bool RenderSystem::ChangeSetting(const RenderSystem::Setting& setting)
{
    if (!mInited)
        return false;
    mSetting = setting;

    return true;
}

void RenderSystem::Update(int usec)
{
    if (!mInited)
        return;
}

void RenderSystem::Finalize()
{
    RenderDevice::instance()->Finalize();
    mRenderDevice = NULL;
}