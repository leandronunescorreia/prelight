#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include "./renderdevice/renderdevice.h"

/**
/class RenderSystem
RenderSystem is an abstract layer for all visible things.

RenderSystem contain some resources. These resources are called render resource:
- renderscene, renderscene contain many types renderobjects:
- rendermodel(like static model, skin model, particle, decal), 
- material, 
- mesh, 
- renderlight, 
- camera.

Every renderscene should be automatically organized by as an octree, this octree 
can be used do a quick frustum culling for specify camera.

CPU side algorithm (like frustrum culling) should be implement in RenderSystem class.

RenderSystem has no idea about vertexbuffer, indexbuffer and shader resource.
These resources are called kernel resource. 
All kernel resources should be generate and managed at RenderDevice class layer.

RenderPath class will link RenderSystem's render resources with RenderDevice's kernel resource.
It create kernel resources for render resources, and it contains the strategy of how to render 
renderresources by using kernel resources.

GPU side algorithm (like occlussion query for render resources) should be implement in RenderPath class.
*/

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