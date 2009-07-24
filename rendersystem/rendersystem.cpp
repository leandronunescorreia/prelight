#include "rendersystem.h"

RenderSystem* RenderSystem::rendersysInstance = NULL;

RenderSystem* RenderSystem::self()
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
    if (!mInited)
        return;

}