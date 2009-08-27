#ifndef _RENDERDEVICE_H_
#define _RENDERDEVICE_H_

#include "renderdevicetypes.h"
#include "texturemanager.h"
#include "verticesmanager.h"

enum
{
    MAX_RENDERTARGETS    = 4,
    MAX_VERTEX_STREAMS    = 8,
    MAX_TEXTURE_SAMPLERS = 16
};

struct RenderStates
{
    /** Only support all color channel writing be enabled/disabled simultaeously.*/
    bool         mColorWrite;        

    EFillMode    mFillMode;
    EFaceCull    mFaceCull;

    /** Only support alpha greater compare now. AlphaTest will be disabled if mAlphaTestValue equal to 0.*/
    float        mAlphaTestValue;

    /** Only support color adding operation. Don't support seperatly alpha blending.*/
    EBlendFactor mSrcBlendFactor, mDestBlendFactor; 

    ECompareFunc mDepthFunc;
    bool         mDepthWrite;

    ECompareFunc mStencilFunc;
    unsigned int mStencilRef;
    unsigned int mStencilMask;
    unsigned int mStencilWriteMask;
    EStencilOP   mStencilFailOP, mStencilZFailOP, mStencilZPassOP;
};


/**
/class RenderDevice
RenderDevice hidden differents for different Graphics APIs (e.g. DirectX, XBOX 360 DirectX, OpenGL).
All GPU commands should be called through it.

RenderDevice can create some resources are called kernel resources.
-texture (normal textures, rendertargets)
-shader (vertex shader, pixel shader)
-vertex buffer
-index buffer

RenderDevice can creat them but doesn't manage them. 
RenderDevice has references to TextureManager, ShaderManager, VerticesManager, IndicesManager class instance.
These classes implement resouces management all these kernel resources, and hide their but expose handle of them.
*/

class RenderDevice
{
    friend class  TextureManager;
    friend struct Texture;

    friend class  VerticesManager;
    friend struct Vertices;


public:
    struct Setting
    {
        hScreen screen;
        bool    fullscreen;
        int     width, height;
    };

private:
    static RenderDevice renderdeviceInstance;
    RenderDevice();
public:
    static  RenderDevice* instance();
    ~RenderDevice();

    bool    Initialize(const Setting &setting);
    bool    Finalize();

    const   Setting& GetSetting();
    bool    ChangeSetting(const Setting &setting);
           

    bool    BeginRender();
    bool    EndRender();
    
    /**
    Doesn't support sub-rects clear. It's useless.
    And entire depth & stencil buffer clear is much faster and will save bandwidth becasue Z compression.
    If you really need sub-rects clear, you should use other ways and carefully plan these operations.
    */
    void    Clear(const unsigned int *color, const float *depth, const int *stencil);
    void    SwapBuffers();
           
    /** RenderStates accessor functions*/ 
    //@{
    void    SetColorWrite(bool write);
    void    SetFillMode(EFillMode fillMode); 
    void    SetFaceCull(EFaceCull faceCull);
    void    SetAlphaTest(float alpha);
    void    SetBlendFactor(EBlendFactor srcFactor, EBlendFactor destFactor);
    void    SetDepthFunc(ECompareFunc compareFunc);
    void    SetDepthWrite(bool write);
    void    SetStencilFunc(ECompareFunc compareFunc, int ref, int mask);
    void    SetStencilWriteMask(int mask);
    void    SetStencilOp(EStencilOP fail, EStencilOP zfail, EStencilOP zpass);
    //@}

    /** Draw call*/
    //@{
    void    DrawPrimitive(EPrimitiveType primType, int startVertex, int primCount);
    void    DrawPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride);
    void    DrawIndexedPrimitive(EPrimitiveType primType, int startIndex, int primCount, int minVertex, int numVertices, int baseVertexIndex = 0);
    void    DrawIndexedPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride, const void *indexData, int indexStride, int minVertex, int numVertices);
    //@}    

    /** Cursor*/
    //@{
    void    ShowCursor(bool show);
    void    SetCursorTexture(int id, int xHotSpot, int yHotSpot);
    void    SetCursorPosition(int x, int y);
    //@}    
             
    APIRenderDevice* GetAPIRenderDevice();
             
    const    RenderStates&        GetRenderStates();

    void    GetBackBufferSize(int &w, int &h);
    void*   GetWindow();
    long    WindowProc(void *hWnd, unsigned int msg, unsigned int wparam, long lparam);
    void    SetAnimationTime(float time);
    bool    CheckDeviceLost();

protected:
    /** Texture functions*/
    //@{
    Texture*            CreateTexture(const Texture::Spec &spec);
    Texture*            CreateTexture(const void *data, int byteSize);
    bool                DestroyTexture(Texture *texture);

    void*               LockTexture(Texture *texture, int mipLevel, ELockType lockType, int *pitch = 0);
    void                UnlockTexture(Texture *texture, int mipLevel);
    //@}

    /** Bind texture with sampler.*/
    void                SetSamplerTexture(int idx, const Texture *texture);

    /** Render Target*/
    //@{
    void                SetRenderTarget(int idx, Texture *texture);
    void                SetDepthStencilTexture(Texture *texture);
    //@}

    /** Vertex buffer functions*/
    //@{
    Vertices*           CreateVertices(const Vertices::Spec& spec);
    void                DestroyVertices(Vertices *vertices);
    void*               LockVertices(Vertices *vertices, int firstVertex = 0, int numVertices = 0, ELockType lockType = LOCKTYPE_WRITE);
    void                UnlockVertices(Vertices *vertices);
    //@}                

    /** Stream functions*/
    //@{
    void                SetStreamSource(int idx, Vertices *vertexSource, int offsetInBytes = 0);
    RegistersMap*       CreateRegistersMap(const Vertices::Spec &spec);
    void                DestroyRegistersMap(RegistersMap* map);
    void                SetRegistersMap(RegistersMap* map);
    //@}

    /** Index buffer functions*/
    //@{
    Indices*            CreateIndices(int indexCount, int indexStride, EResourceUsage usage = RES_USAGE_WRITEONLY);
    void                DestroyIndices(Indices *buf);
    void*               LockIndices(Indices *buf, int firstIndex = 0, int numIndices = 0, ELockType lock = LOCKTYPE_WRITE);
    void                UnlockIndices(Indices *buf);
    void                SetIndices(Indices *buf);
    //@}


    /** Vertex Shader functions*/
    //@{
    VertexShader*       CreateVertexShader(const char *code, int size);
    void                DestroyVertexShader(VertexShader *vshader);
    void                SetVertexShader(VertexShader *vshader);
    void                SetVertexShaderConstant(int startRegister, const float *value, int count);
    void                SetVertexShaderConstant(int startRegister, const int *value, int count);
    //@}

    /** Pixel Shader functions*/
    //@{
    PixelShader*        CreatePixelShader(const char *code, int size);
    void                DestroyPixelShader(PixelShader *pshader);
    void                SetPixelShader(PixelShader *pshader);
    void                SetPixelShaderConstant(int startRegister, const float *value, int count);
    void                SetPixelShaderConstant(int startRegister, const int *value, int count);
    //@}

    /** Occusion Query */
    //@{
    OcclusionQuery*    CreateOcclusionQuery();
    void               DestroyOcclusionQuery(OcclusionQuery *oquery);
    void               BeginOcclusionQuery(OcclusionQuery *oquery);
    void               EndOcclusionQuery(OcclusionQuery *oquery);
    bool               GetOcclusionQueryResult(OcclusionQuery, int &numPixels);
    //@}

    void  OnLostDevice();
    void  OnResetDevice();

    bool  mInited;
    int   mBeginRenderCount;

    Setting                 mSetting;
    RenderStates            mRenderStates;

    TextureManager          mTextureManager;
    VerticesManager         mVerticesManager;
};

#endif  //_RENDERDEVICE_H_