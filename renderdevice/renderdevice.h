#ifndef _RENDERDEVICE_H_
#define _RENDERDEVICE_H_

#ifdef WIN32
#include <windows.h>
#endif

#include "renderdevicetypes.h"
#include "texturemanager.h"

enum
{
    MAX_RENDERTARGETS    = 4,
    MAX_VERTEX_STREAMS   = 8,
    MAX_TEXTURE_SAMPLERS = 16
};

struct RenderDeviceSettings
{
    RenderDeviceSettings();
    int m_iWidth;
    int m_iHeight;
    bool m_bFullScreen;
    bool m_bStencilBuffer;
    bool m_bCopySwap;
    bool m_bNVPerfHUD;

    EVSync m_eVSync;
    bool m_bFpuPreserve;
    void *m_hWnd;
    long (*m_MsgProcCallback)(void *hWnd, unsigned int msg, unsigned int wParam, long lParam, bool &bNoFurtherProcessing);
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

    ECmpFunc     mDepthFunc;
    bool         mDepthWrite;

    ECompareFunc mStencilFunc;
    unsigned int mStencilRef;
    unsigned int mStencilMask;
    unsigned int mStencilWriteMask;
    EStencilOP   mStencilFailOP, mStencilZFailOP, mStencilZPassOP;
};

class RenderDevice
{
public:
    static RenderDevice sRenderDevice;

    bool    Initialize(const RenderDeviceSettings &settings);
    bool    Finalize();

    const   RenderDeviceSetting& GetSetting();
    bool    ChangeSettings(const RenderDeviceSettings &settings);
          

    bool    BeginRender();
    bool    EndRender();
          
    void    Clear(const unsigned int *color, const float *depth, const int *stencil, const Rect const *rect = 0, unsigned int rectcount = 0);
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
            
    void*   GetAPIRenderDevice();
            
            
    const   RenderStates&       GetRenderStates();
    const   SamplerStates&      GetSamplerStates(int idx);

    void    GetBackBufferSize(int &w, int &h);
    void*   GetWindow();
    long    WindowProc(void *hWnd, unsigned int msg, unsigned int wparam, long lparam);
    void    SetAnimationTime(float time);
    bool    CheckDeviceLost();

protected:
    RenderDevice();
    ~RenderDevice();

    /** Texture functions*/
    //@{
    Texture* CreateTexture(const TextureSpec &spec);
    Texture* CreateTexture(const void *data, int byteSize);
    bool     DestroyTexture(Texture *texture);

    void*    LockTexture(Texture *texture, int mipLevel, ELockType lockType, int *pitch = 0);
    void     UnlockTexture(Texture *texture, int mipLevel);
    //@}

    /** Bind texture with sampler.*/
    void     SetSamplerTexture(int idx, const Texture *texture);

    /** Render Target*/
    //@{
    void     SetRenderTarget(int idx, Texture *texture);
    void     SetDepthStencilTexture(Texture *texture);
    //@}

    /** Vertex buffer functions*/
    //@{
    VertexBuffer*  CreateVertexBuffer(int vertexCount, int vertexStride, EResourceUsage usage = RES_USAGE_WRITEONLY);
    void           DestroyVertexBuffer(VertexBuffer *vbuf);
    void*          LockVertexBuffer(VertexBuffer *vbuf, int firstVertex = 0, int numVertices = 0, ELockType lockType = LOCK_WRITE);
    void           UnlockVertexBuffer(VertexBuffer *vbuf);
    //@}

    /** Stream functions*/
    //@{
    void               SetStreamSource(int idx, VertexBuffer *vertexSource, int offsetInBytes = 0);
    StreamRegisterMap* CreateStreamRegistersMap(const CVertexSpec &spec);
    void               DestroyStreamRegistersMap(StreamRegisterMap* map);
    void               SetStreamRegistersMap(StreamRegisterMap* map);
    //@}

    /** Index buffer functions*/
    //@{
    IndexBuffer*   CreateIndexBuffer(int indexCount, int indexStride, EResourceUsage usage = RES_USAGE_WRITEONLY);
    void           DestroyIndexBuffer(IndexBuffer *buf);
    void*          LockIndexBuffer(IndexBuffer *buf, int firstIndex = 0, int numIndices = 0, ELockType lock = LOCK_WRITE);
    void           UnlockIndexBuffer(IndexBuffer *buf);
    void           SetIndexBuffer(IndexBuffer *buf);
    //@}


    /** Vertex Shader functions*/
    //@{
    VertexShader*  CreateVertexShader(const char *code, int size);
    void           DestroyVertexShader(VertexShader *vshader);
    void           SetVertexShader(VertexShader *vshader);
    void           SetVertexShaderConstant(int startRegister, const float *value, int count);
    void           SetVertexShaderConstant(int startRegister, const int *value, int count);
    //@}

    /** Pixel Shader functions*/
    //@{
    PixelShader*   CreatePixelShader(const char *code, int size);
    void           DestroyPixelShader(PixelShader *pshader);
    void           SetPixelShader(PixelShader *pshader);
    void           SetPixelShaderConstant(int startRegister, const float *value, int count);
    void           SetPixelShaderConstant(int startRegister, const int *value, int count);
    //@}

    /** Occusion Query */
    //@{
    OcclusionQuery* CreateOcclusionQuery();
    void            DestroyOcclusionQuery(OcclusionQuery *oquery);
    void            BeginOcclusionQuery(OcclusionQuery *oquery);
    void            EndOcclusionQuery(OcclusionQuery *oquery);
    bool            GetOcclusionQueryResult(OcclusionQuery, int &numPixels);
    //@}

    void  OnLostDevice();
    void  OnResetDevice();

    bool mInitialized;
    int  mBeginRenderCount;

    RenderDeviceSettings   mSettings;
    RenderStates        mRenderStates;

    TextureManager      mTextureManager;

    APIRenderDevice*    mAPIRenderDevice;

private:
    /** Actual API bridge functions, only convert function call to graphics api call, don't access device member.*/
    //@{
    bool  API_Initialize(const RenderDeviceSettings &settings);
    void  API_Finalize();

    bool  API_ChangeSettings(const RenderDeviceSettings &settings);
    

    bool  API_BeginRender();
    void  API_EndRender();

    void  API_Clear(const unsigned int *color, const float *depth, const int *stencil, const Rect const *rect = 0, unsigned int rectcount = 0);
    void  API_SwapBuffers();
    
    /** RenderStates accessor functions*/ 
    //@{
    void  API_SetColorWrite(bool write);
    void  API_SetFillMode(EFillMode fillMode); 
    void  API_SetFaceCull(EFaceCull faceCull);
    void  API_SetAlphaTest(float alpha);
    void  API_SetBlendFactor(EBlendFactor srcFactor, EBlendFactor destFactor);
    void  API_SetDepthFunc(ECompareFunc compareFunc);
    void  API_SetDepthWrite(bool write);
    void  API_SetStencilFunc(ECompareFunc compareFunc, int ref, int mask);
    void  API_SetStencilWriteMask(int mask);
    void  API_SetStencilOp(EStencilOP fail, EStencilOP zfail, EStencilOP zpass);
    //@}     

    /** Bind texture with sampler.*/
    void     API_SetSamplerTexture(int idx, const Texture *texture);

    /** Render Target*/
    //@{
    void     API_SetRenderTarget(int idx, Texture *texture);
    void     API_SetDepthStencilTexture(Texture *texture);
    //@}

    /** Texture functions*/
    //@{
    Texture* API_CreateTexture(const TextureSpec &spec);
    Texture* API_CreateTexture(const void *data, int byteSize);
    bool     API_DestroyTexture(Texture *texture);
             
    void*    API_LockTexture(Texture *texture, int mipLevel, ELockType lockType, int *pitch = 0);
    void     API_UnlockTexture(Texture *texture, int mipLevel);
    //@}     
             
    /** Vertex buffer functions*/
    //@{
    VertexBuffer*  API_CreateVertexBuffer(int vertexCount, int vertexStride, EResourceUsage usage = RES_USAGE_WRITEONLY);
    void           API_DestroyVertexBuffer(VertexBuffer *vbuf);
    void*          API_LockVertexBuffer(VertexBuffer *vbuf, int firstVertex = 0, int numVertices = 0, ELockType lockType = LOCK_WRITE);
    void           API_UnlockVertexBuffer(VertexBuffer *vbuf);
    //@}           

    /** Stream functions*/
    //@{
    void           API_SetStreamSource(int idx, VertexBuffer *vertexSource, int offsetInBytes = 0);
    StreamMap*     API_CreateStreamRegistersMap(const CVertexSpec &spec);
    void           API_DestroyStreamRegistersMap(StreamMap *streamMap);
    void           API_SetStreamRegistersMap(StreamMap *streamMap);
    //@}           

    /** Index buffer functions*/
    //@{
    IndexBuffer*   API_CreateIndexBuffer(int indexCount, int indexStride, EResourceUsage usage = RES_USAGE_WRITEONLY);
    void           API_DestroyIndexBuffer(IndexBuffer *ibuf);
    void*          API_LockIndexBuffer(IndexBuffer *ibuf, int firstIndex = 0, int numIndices = 0, ELockType lockType = LOCK_WRITE);
    void           API_UnlockIndexBuffer(IndexBuffer *ibuf);
    void           API_SetIndexBuffer(IndexBuffer *ibuf);
    //@}


    /** Vertex Shader functions*/
    //@{
    VertexShader*  API_CreateVertexShader(const char *code, int size);
    void           API_DestroyVertexShader(VertexShader *vshader);
    void           API_SetVertexShader(VertexShader *vshader);
    void           API_SetVertexShaderConstant(int startRegister, const float *value, int count);
    void           API_SetVertexShaderConstant(int startRegister, const int *value, int count);
    //@}

    /** Pixel Shader functions*/
    //@{
    PixelShader*   API_CreatePixelShader(const char *code, int size);
    void           API_DestroyPixelShader(PixelShader *pshader);
    void           API_SetPixelShader(PixelShader *pshader);
    void           API_SetPixelShaderConstant(int startRegister, const float *value, int count);
    void           API_SetPixelShaderConstant(int startRegister, const int *value, int count);
    //@}

    /** Occusion Query */
    //@{
    OcclusionQuery* API_CreateOcclusionQuery();
    void            API_DestroyOcclusionQuery(OcclusionQuery *oquery);
    void            API_BeginOcclusionQuery(OcclusionQuery *oquery);
    void            API_EndOcclusionQuery(OcclusionQuery *oquery);
    bool            API_GetOcclusionQueryResult(OcclusionQuery, int &numPixels);
    //@}

    /** Draw call*/
    //@{
    void            API_DrawPrimitive(EPrimitiveType primType, int startVertex, int primCount);
    void            API_DrawPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride);
    void            API_DrawIndexedPrimitive(EPrimitiveType primType, int startIndex, int primCount, int minVertex, int numVertices, int baseVertexIndex = 0);
    void            API_DrawIndexedPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride, const void *indexData, int indexStride, int minVertex, int numVertices);
    //@}

    /** Cursor*/
    //@{
    void            API_ShowCursor(bool show);
    void            API_SetCursorTexture(int id, int xHotSpot, int yHotSpot);
    void            API_SetCursorPosition(int x, int y);
    //@}

    //@}

};

extern RenderDevice *gRenderDevice;


#endif  //_RENDERDEVICE_H_