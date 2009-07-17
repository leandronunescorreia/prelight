#include <windows.h>
#include "renderdevicetypes.h"

class RenderDevice
{
public:
    RenderDevice();
    ~RenderDevice();

    bool  Initialize(const RenderDeviceSettings &settings);
    void  Uninitialize();

    const RenderDeviceSetting& GetSetting();
    bool  ChangeSettings(const RenderDeviceSettings &settings);
    

    bool  BeginScene();
    void  EndScene();

    void  Clear(const unsigned int *color, const float *depth, const int *stencil, const Rect const *rect = 0, unsigned int rectcount = 0, );
    void  SwapBuffers();
    
    /** RenderStates accessor functions*/ 
    //@{
    void  SetColorWrite(bool r, bool g, bool b, bool a);
    void  SetFillMode(EFillMode fillMode); 
    void  SetFaceCull(EFaceCull faceCull);

    void  SetAlphaTest(float alpha);
    
    void  SetBlendFactor(EBlendFactor srcFactor, EBlendFactor dstFactor);

    void  SetDepthFunc(ECompareFunc compareFunc);

    void  SetStencilFunc(ECompareFunc comparefunc, int ref, int mask);
    void  SetStencilWriteMask(int mask);
    void  SetStencilOp(EStencilOP fail, EStencilOP zfail, EStencilOP zpass);

    void  SetSamplerState(int sampler, ESamplerState state, int value, );
    void  SetTextureAddressMode(int sampler, ETextureAddressMode mode);
    void  SetTextureFilter(int sampler, ETextureFilter magFilter, ETextureFilter minFilter, ETextureFilter mipFilter);
    void  SetTextureBorderColor(int sampler, int r, int g, int b, int a);
    void  SetMipmapLodBias(int sampler, float bias);
    //@}

    hTexture CreateTexture(const TextureSpec &spec, const char *name=0);
    int   CreateTextureFromCache(const char *name);
    int   CreateAnimatedTexture(int *textures, int numTextures, float fps, const char *name=0);
    int   CreateDummyTexture(const char *name=0);
    int   CreateDummyAnimatedTexture(const char *name=0);
    void  DeleteTexture(int id);   // id can be texture or animated texture
    int   ReplaceTexture(int id, const TextureSpec &spec);
    int   ReplaceAnimatedTexture(int id, int *textures, int numTextures, float fps);
    void* LockTexture(int id, int mipLevel=0, int *pitch=0, int lock=RES_LOCK_WRITE);
    void  UnlockTexture(int id, int mipLevel=0);
    void* LockCubeTexture(int id, ECubeFace face, int mipLevel=0, int *pitch=0, int lock=RES_LOCK_WRITE);
    void  UnlockCubeTexture(int id, ECubeFace face, int mipLevel=0);
    void* LockVolumeTexture(int id, int mipLevel=0, int *rowPitch=0, int *slicePitch=0, int lock=RES_LOCK_WRITE);
    void  UnlockVolumeTexture(int id, int mipLevel=0);
    void  SetTexture(int id, int sampler=0);    // id can be texture, animated texture or render target
    void  GetTextureSize(int id, int &width, int &height);  // id can be texture, animated texture or render target
    void  CopyBackBufferToTexture(int id, int srcX, int srcY, int srcW, int srcH, int destX, int destY, int destW, int destH);

    void  SaveTextureToFile (int id, char const *path, EImageFileFormat destFormat=IFF_DDS, EPixelFormat sourceFormat=FMT_UNKNOWN);
    void  SaveRenderTargetToFile (int id, char const *path, EImageFileFormat destFormat=IFF_DDS, EPixelFormat sourceFormat=FMT_UNKNOWN);

    void  ResolveRenderTarget (int id);
    void  ResolveCurrentDepth (int dstTexture);

    int   CreateRenderTarget(const CRenderTargetSpec &spec, const char *name=0);
    int   CreateRenderTarget(int colorRT, int depthRT, const char *name=0);
    int   CreateRenderTargetFromCache(const char *name);
    void  DeleteRenderTarget(int id);
    void  SetRenderTarget(int id, int idx=0);
    void  SetCubeRenderTarget(int id, ECubeFace face, int idx=0);
    void  ResolveCurrentRenderTarget(int id, int idx=0);

    int   CreateVertexBuffer(int vertexCount, int vertexStride, int usage=RES_USAGE_WRITEONLY, const char *name=0);
    int   CreateVertexBufferFromCache(const char *name);
    void  DeleteVertexBuffer(int id);
    int   ReplaceVertexBuffer(int id, int vertexCount, int vertexStride, int usage=RES_USAGE_WRITEONLY);
    void* LockVertexBuffer(int id, int firstVertex=0, int numVertices=0, int lock=RES_LOCK_WRITE);
    void  UnlockVertexBuffer(int id);
    void  SetVertexBuffer(int id, int stream=0, int offsetInBytes=0);

    int   CreateIndexBuffer(int indexCount, int indexStride, int usage=RES_USAGE_WRITEONLY, const char *name=0);
    int   CreateIndexBufferFromCache(const char *name);
    void  DeleteIndexBuffer(int id);
    int   ReplaceIndexBuffer(int id, int indexCount, int indexStride, int usage=RES_USAGE_WRITEONLY);
    void* LockIndexBuffer(int id, int firstIndex=0, int numIndices=0, int lock=RES_LOCK_WRITE);
    void  UnlockIndexBuffer(int id);
    void  SetIndexBuffer(int id);

    int   CreateVertexShader(const void *code, int size, const char *name=0);
    int   CreateVertexShaderFromCache(const char *name);
    void  DeleteVertexShader(int id);
    void  SetVertexShader(int id);
    void  SetVertexShaderConstant(int startRegister, const float *value, int vcount);
    void  SetVertexShaderConstant(int startRegister, const int *value, int vcount);

    int   CreatePixelShader(const void *code, int size, const char *name=0);
    int   CreatePixelShaderFromCache(const char *name);
    void  DeletePixelShader(int id);
    void  SetPixelShader(int id);
    void  SetPixelShaderConstant(int startRegister, const float *value, int vcount);
    void  SetPixelShaderConstant(int startRegister, const int *value, int vcount);

    int   CreateVertexDeclaration(const CVertexSpec &spec, const char *name=0);
    int   CreateVertexDeclarationFromCache(const char *name);
    void  DeleteVertexDeclaration(int id);
    void  SetVertexDeclaration(int id);

    int   CreateOcclusionQuery();
    void  DeleteOcclusionQuery(int id);
    void  BeginOcclusionQuery(int id);
    void  EndOcclusionQuery(int id);
    bool  GetOcclusionQueryResult(int id, int &pixels);

    void  DrawPrimitive(EPrimitiveType primType, int startVertex, int primCount);
    void  DrawPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride);
    void  DrawIndexedPrimitive(EPrimitiveType primType, int startIndex, int primCount, int minVertex, int numVertices, int baseVertexIndex=0);
    void  DrawIndexedPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride, const void *indexData, int indexStride, int minVertex, int numVertices);

    void ShowCursor(bool show);
    void SetCursorTexture(int id, int xHotSpot, int yHotSpot);
    void SetCursorPosition(int x, int y);

    static unsigned int PackColor(int r, int g, int b, int a=255);
    static unsigned int PackColor(float r, float g, float b, float a=1.0f);
    static void UnpackColor(unsigned int color, int &r, int &g, int &b, int &a);
    static void UnpackColor(unsigned int color, float &r, float &g, float &b, float &a);

    bool  CheckResourceFormat(EResourceType rt, EPixelFormat format, int usage);
	bool  CheckDeviceMultiSampleType (EMultiSampleType mst, EPixelFormat fmt);
    void* GetInternalDevice();
    const CResource* GetResource(int id);

    // pix named event
    void BeginPerfEvent(const char *name, int color);
    void EndPerfEvent();

    enum
    {
        CLIP_PLANES_MAX = 6,
        RENDERTARGETS_MAX = 4,
        VERTEX_STREAMS_MAX = 16,
        TEXTURE_SAMPLERS_MAX = 16
    };

    class RenderStates
    {
    public:
        bool m_bAlphaTest;
        bool m_bBlend;
        bool m_bSeparateAlphaBlend;
        bool m_bCullFace;
        bool m_bColorWrite[4];
        bool m_bDepthTest;
        bool m_bDepthWrite;
        bool m_bStencilTest;
        bool m_bStencilTwoSided;
        bool m_bHiStencilTest;
        bool m_bHiStencilWrite;
        bool m_bScissorTest;
        bool m_bPointSprite;
        bool m_bSRGBWrite;
        unsigned int m_iClearColor;
        unsigned int m_iClearColorR;
        unsigned int m_iClearColorG;
        unsigned int m_iClearColorB;
        unsigned int m_iClearColorA;
        unsigned int m_iClearStencil;
        unsigned int m_iClipPlanes;
        unsigned int m_iStencilWriteMask;
        unsigned int m_iCCWStencilWriteMask;
        unsigned int m_iAlphaRef;
        unsigned int m_iStencilRef;
        unsigned int m_iStencilMask;
        unsigned int m_iCCWStencilRef;
        unsigned int m_iCCWStencilMask;
        unsigned int m_iHiStencilRef;
        float m_fClearDepth;
        float m_fPointSize;
        float m_fPolygonOffsetFactor;
        float m_fPolygonOffsetUnits;
        float m_fZNear;
        float m_fZFar;
        float m_ClipPlaneEquation[CLIP_PLANES_MAX][4];
        EFrontFace m_eFrontFace;
        EFillMode m_eFillMode;
        ECmpFunc m_eAlphaFunc;
        ECmpFunc m_eDepthFunc;
        ECmpFunc m_eStencilFunc;
        ECmpFunc m_eCCWStencilFunc;
        ECmpFunc m_eHiStencilFunc;
        EBlendFactor m_eSrcBlendFactor;
        EBlendFactor m_eDestBlendFactor;
        EBlendOp m_eBlendOp;
        EBlendFactor m_eSrcBlendFactorAlpha;
        EBlendFactor m_eDestBlendFactorAlpha;
        EBlendOp m_eBlendOpAlpha;
        EStencilOP m_eStencilFail;
        EStencilOP m_eStencilZFail;
        EStencilOP m_eStencilZPass;
        EStencilOP m_eCCWStencilFail;
        EStencilOP m_eCCWStencilZFail;
        EStencilOP m_eCCWStencilZPass;

        Rect m_Viewport;
        Rect m_Scissor;
    };

    class SamplerStates
    {
    public:
        ETextureAddressMode m_ETextureAddressMode;
        ETextureFilter m_eMagFilter;
        ETextureFilter m_eMinFilter;
        ETextureFilter m_eMipFilter;
        float m_fMipmapLodBias;
        unsigned int m_iBorderColor;
        unsigned int m_iMaxMipLevel;
        unsigned int m_iMaxAnisotropy;
    };

    class ActiveResources
    {
    public:
        int m_iTextureID[TEXTURE_SAMPLERS_MAX];
        int m_iRenderTargetID[RENDERTARGETS_MAX];
        int m_iVertexBufferID[VERTEX_STREAMS_MAX];
        int m_iDepthStencilID;
        int m_iIndexBufferID;
        int m_iVertexDeclarationID;
        int m_iVertexShaderID;
        int m_iPixelShaderID;
    };

    class Caps
    {
    public:
        bool m_bDynamicTextures;
        bool m_bScissorTest;
        bool m_bStencilTwoSided;
        bool m_b32BitsIndexBuffer;
        bool m_bOcclusionQuery;
        int m_iMaxTextureWidth;
        int m_iMaxTextureHeight;
        int m_iMaxUserClipPlanes;
        int m_iMaxStreams;
        int m_iMaxSimultaneousRenderTargets;         
        int m_iVertexShaderVersionMajor;
        int m_iVertexShaderVersionMinor;
        int m_iPixelShaderVersionMajor;
        int m_iPixelShaderVersionMinor;
        float m_fMaxPointSize;
    };
   
    class CYBORG_API Statistic
    {
    public:
        Statistic();
        void Reset();

        int m_iNumTextures;
        int m_iNumRenderTargets;
        int m_iNumVertexShaders;
        int m_iNumPixelShaders;
        int m_iNumVertexBuffers;
        int m_iNumIndexBuffers;
        int m_iNumVertexDeclarations;

        int m_iTexturesSize;
        int m_iRenderTargetsSize;
        int m_iVertexShadersSize;
        int m_iPixelShadersSize;
        int m_iVertexBuffersSize;
        int m_iIndexBuffersSize;
        int m_iVertexDeclarationsSize;

        int m_iAvailableTextureMemory;
    };

    const RenderStates& GetRenderStates();
    const SamplerStates& GetSamplerStates(int sampler=0);
    const ActiveResources& GetActiveResources();
    const Statistic& GetStatistic();

    ERenderDeviceType GetDeviceType();
    const Caps& GetCaps();
    void  GetBackBufferSize(int &w, int &h);
    void* GetWindow();
    long  WindowProc(void *hWnd, unsigned int msg, unsigned int wparam, long lparam);
    void  SetAnimationTime(float time);
    bool  CheckDeviceLost();
    void  WaitUntilGpuIdle();

    void  AllowGammaCorrection (bool allow);
    bool  IsGammaCorrectionAllowed (void);
    
    bool  IsJustReset (void);
    void  ClearJustReset(void);

protected:

    void  OnLostDevice();
    void  OnResetDevice();

    int   CreateSurface(const CSurfaceSpec &spec, const char *name=0);
    int   CreateSurfaceFromCache(const char *name);
    void  DeleteSurface(int id);
    void  SetDepthStencilSurface(int id);
    void  SetDepthStencilTexture(int id);
    void  SetRenderTargetSurface(int id, int idx);
    void  SetRenderTargetTexture(int id, int idx);
    void  SetRenderTargetCubeTexture(int id, ECubeFace face, int idx);
    int   GetRealTextureID(int id);

    friend class CTextureResource;
    friend class CSurfaceResource;
    friend class CRenderTargetResource;
    friend class CBufferResource;
    friend class CShaderResource;
    friend class CVertexDeclarationResource;
    friend class COcclusionQueryResource;

    virtual void  _GetVideoMode(CVideoMode &videoMode)=0;
    virtual unsigned int _GetAdapterModesCount (EPixelFormat format);
    virtual void  _GetAdapterModes (EPixelFormat format, CVideoMode videoModes[]);
    virtual bool  _CreateDevice()=0;
    virtual void  _DestroyDevice()=0;
    virtual void  _OnLostDevice()=0;
    virtual void  _OnResetDevice()=0;
    virtual bool  _ChangeSettings(const CRenderDeviceSettings &settings)=0;

    virtual bool  _BeginScene()=0;
    virtual void  _EndScene()=0;
    virtual bool  _IsBeginSceneSucceeded()=0;
    virtual bool  _IsReady()=0;

    virtual void  _Clear(bool color, bool zbuffer, bool stencil, unsigned short rectcount, Rect const *rect)=0;
    virtual void  _SwapBuffers(void *hWnd)=0;
    virtual void  _SwapBuffers(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, void *hWnd)=0;
    virtual void  _SetViewport(int x, int y, int w, int h)=0;

    virtual void  _SetRenderState(RenderStateType state, int value)=0;
    virtual void  _SetPolygonOffset(float slop, float scale)=0;
    virtual void  _SetColorWrite(bool r, bool g, bool b, bool a)=0;
    virtual void  _SetPointSize(float s)=0;
    virtual void  _SetClipPlane(float plane[4], int idx)=0;
    virtual void  _SetScissorRect(int x, int y, int w, int h)=0;
    virtual void  _SetFrontFace(EFrontFace f)=0;
    virtual void  _SetFillMode(EFillMode f)=0;
    virtual void  _SetAlphaFunc(ECmpFunc func, int ref)=0;
    virtual void  _SetBlendFunc(EBlendFactor sfactor, EBlendFactor dfactor)=0;
    virtual void  _SetBlendOp(EBlendOp op)=0;
    virtual void  _SetBlendFuncAlpha(EBlendFactor sfactor, EBlendFactor dfactor)=0;
    virtual void  _SetBlendOpAlpha(EBlendOp op)=0;
    virtual void  _SetDepthRange(float znear, float zfar)=0;
    virtual void  _SetDepthFunc(ECmpFunc func)=0;
    virtual void  _SetStencilFunc(ECmpFunc func, int ref, int mask)=0;
    virtual void  _SetStencilOp(EStencilOP fail, EStencilOP zfail, EStencilOP zpass)=0;
    virtual void  _SetStencilWriteMask(int mask)=0;
    virtual void  _SetCCWStencilFunc(ECmpFunc func, int ref, int mask)=0;
    virtual void  _SetCCWStencilOp(EStencilOP fail, EStencilOP zfail, EStencilOP zpass)=0;
    virtual void  _SetCCWStencilWriteMask(int mask)=0;
    virtual void  _SetHiStencilFunc(ECmpFunc func, int ref)=0;
    virtual void  _FlushHiZStencil(bool asynchronous)=0;

    virtual void  _SetSamplerState(ESamplerState state, int value, int sampler)=0;
    virtual void  _SetTextureAddressMode(ETextureAddressMode mode, int sampler)=0;
    virtual void  _SetTextureFilter(ETextureFilter magFilter, ETextureFilter minFilter, ETextureFilter mipFilter, int sampler)=0;
    virtual void  _SetTextureBorderColor(unsigned int color, int sampler)=0;
    virtual void  _SetMipmapLodBias(float bias, int sampler)=0;

    virtual bool  _CreateTexture(CTextureResource &r, const TextureSpec &spec)=0;
    virtual void  _DeleteTexture(CTextureResource &r)=0;
    virtual void* _LockTexture(CTextureResource &r, int mipLevel, int *pitch, int lock)=0;
    virtual void  _UnlockTexture(CTextureResource &r, int mipLevel)=0;
    virtual void* _LockCubeTexture(CTextureResource &r,  ECubeFace face, int mipLevel, int *pitch, int lock)=0;
    virtual void  _UnlockCubeTexture(CTextureResource &r, ECubeFace face, int mipLevel)=0;
    virtual void* _LockVolumeTexture(CTextureResource &r, int mipLevel, int *rowPitch, int *slicePitch, int lock)=0;
    virtual void  _UnlockVolumeTexture(CTextureResource &r, int mipLevel)=0;
    virtual void  _SetTexture(CTextureResource &r, int sampler)=0;
    virtual void  _CopyBackBufferToTexture(CTextureResource &r, int srcX, int srcY, int srcW, int srcH, int destX, int destY, int destW, int destH)=0;

    virtual void  _SaveTextureToFile (CTextureResource &r, char const *path, EImageFileFormat destFormat, EPixelFormat format) {}
    virtual void  _SaveBackBufferToFile (char const *path, EImageFileFormat destFormat, EPixelFormat format) {}

    virtual void  _ResolveRenderTarget (int id) = 0;
    virtual void  _ResolveCurrentDepth (int dstTexture) = 0;

    virtual bool  _CreateSurface(CSurfaceResource &r, const CSurfaceSpec &spec)=0;
    virtual void  _DeleteSurface(CSurfaceResource &r)=0;
    virtual void  _SetDepthStencilSurface(CSurfaceResource &r)=0;
    virtual void  _SetDepthStencilTexture(CTextureResource &r)=0;
    virtual void  _SetNullDepthStencilSurface()=0;

    virtual void  _AdjustRenderTargetSpec(CRenderTargetSpec &spec)=0;
    virtual void  _SetRenderTargetSurface(CSurfaceResource &r, int idx)=0;
    virtual void  _SetRenderTargetTexture(CTextureResource &r, int idx)=0;
    virtual void  _SetRenderTargetCubeTexture(CTextureResource &r, ECubeFace face, int idx)=0;
    virtual void  _ResolveCurrentRenderTargetToTexture(CTextureResource &r, int idx)=0;

    virtual bool  _CreateVertexShader(CShaderResource &r, const void *code)=0;
    virtual void  _DeleteVertexShader(CShaderResource &r)=0;
    virtual void  _SetVertexShader(CShaderResource &r)=0;
    virtual void  _SetVertexShaderConstantF(int startRegister, const float *value, int vcount)=0;
    virtual void  _SetVertexShaderConstantI(int startRegister, const int *value, int vcount)=0;

    virtual bool  _CreatePixelShader(CShaderResource &r, const void *code)=0;
    virtual void  _DeletePixelShader(CShaderResource &r)=0;
    virtual void  _SetPixelShader(CShaderResource &r)=0;
    virtual void  _SetPixelShaderConstantF(int startRegister, const float *value, int vcount)=0;
    virtual void  _SetPixelShaderConstantI(int startRegister, const int *value, int vcount)=0;

    virtual bool  _CreateVertexBuffer(CBufferResource &r)=0;
    virtual void  _DeleteVertexBuffer(CBufferResource &r)=0;
    virtual void* _LockVertexBuffer(CBufferResource &r, int offset, int size, int lock)=0;
    virtual void  _UnlockVertexBuffer(CBufferResource &r)=0;
    virtual void  _SetVertexBuffer(CBufferResource &r, int stream, int offsetInBytes)=0;

    virtual bool  _CreateIndexBuffer(CBufferResource &r)=0;
    virtual void  _DeleteIndexBuffer(CBufferResource &r)=0;
    virtual void* _LockIndexBuffer(CBufferResource &r, int offset, int size, int lock)=0;
    virtual void  _UnlockIndexBuffer(CBufferResource &r)=0;
    virtual void  _SetIndexBuffer(CBufferResource &r)=0;

    virtual bool  _CreateVertexDeclaration(CVertexDeclarationResource &r, const CVertexSpec &spec)=0;
    virtual void  _DeleteVertexDeclaration(CVertexDeclarationResource &r)=0;
    virtual void  _SetVertexDeclaration(CVertexDeclarationResource &r)=0;

    virtual bool  _CreateOcclusionQuery(COcclusionQueryResource &r)=0;
    virtual void  _DeleteOcclusionQuery(COcclusionQueryResource &r)=0;
    virtual void  _BeginOcclusionQuery(COcclusionQueryResource &r)=0;
    virtual void  _EndOcclusionQuery(COcclusionQueryResource &r)=0;
    virtual bool  _GetOcclusionQueryResult(COcclusionQueryResource &r, int &pixels)=0;

    virtual void  _DrawPrimitive(EPrimitiveType primType, int startVertex, int primCount)=0;
    virtual void  _DrawPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride)=0;
    virtual void  _DrawIndexedPrimitive(EPrimitiveType primType, int startIndex, int primCount, int minVertex, int numVertices, int baseVertexIndex)=0;
    virtual void  _DrawIndexedPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride, const void *indexData, int indexStride, int minVertex, int numVertices)=0;

    virtual void  _ShowCursor(bool show)=0;
    virtual void  _SetCursorTexture(CTextureResource &r, int xHotSpot, int yHotSpot)=0;
    virtual void  _SetCursorPosition(int x, int y)=0;

    virtual bool  _CheckResourceFormat(EResourceType rt, EPixelFormat format, int usage)=0;

	virtual bool  _CheckDeviceMultiSampleType (EMultiSampleType mst, EPixelFormat fmt) = 0;

    virtual void* _GetInternalDevice()=0;
    virtual long  _WindowProc(void *hWnd, unsigned int msg, unsigned int wparam, long lparam)=0;
    virtual bool  _CheckDeviceLost()=0;     // must be called on the same thread as device is created
    virtual void  _WaitUntilGpuIdle()=0;
    virtual void  _UpdateStatistic()=0;

    virtual void  _BeginUseDevice()=0;
    virtual void  _EndUseDevice()=0;

    virtual void  _BeginPerfEvent(const char *name, int color=0xffff)=0;
    virtual void  _EndPerfEvent()=0;


    RenderStates m_RenderStates;
    SamplerStates m_SamplerStates[TEXTURE_SAMPLERS_MAX];
    ActiveResources m_ActiveResources;
    Caps m_Caps;
    Statistic m_Statistic;

    bool m_bInitialized;
    ERenderDeviceType m_eDeviceType;
    CRenderDeviceSettings m_Settings;
    int m_iBackBufferWidth;
    int m_iBackBufferHeight;
    float m_fAnimationTime;
    void *m_hWnd;
    long (*m_MsgProcCallback)(void *hWnd, unsigned int msg, unsigned int wParam, long lParam, bool &bNoFurtherProcessing);

    CTextureResourceCache *m_pTextureCache;
    CSurfaceResourceCache *m_pSurfaceCache;
    CRenderTargetResourceCache *m_pRenderTargetCache;
    CBufferResourceCache *m_pVertexBufferCache;
    CBufferResourceCache *m_pIndexBufferCache;
    CShaderResourceCache *m_pVertexShaderCache;
    CShaderResourceCache *m_pPixelShaderCache;
    CVertexDeclarationResourceCache *m_pVertexDeclarationCache;
    COcclusionQueryResourceCache *m_pOcclusionQueryCache;
    CAnimatedTextureResourceCache *m_pAnimatedTextureCache;

    int m_iDummyTexture;
    CTextureResource *m_pDummyTextureRes;

    bool m_bGammaCorrectionAllowed;
    bool m_bJustReset;
};



struct RenderStates
{
    bool m_bAlphaTest;
    bool m_bBlend;
    bool m_bSeparateAlphaBlend;
    bool m_bCullFace;
    bool m_bColorWrite[4];
    bool m_bDepthTest;
    bool m_bDepthWrite;
    bool m_bStencilTest;
    bool m_bStencilTwoSided;
    bool m_bHiStencilTest;
    bool m_bHiStencilWrite;
    bool m_bScissorTest;
    bool m_bPointSprite;
    bool m_bSRGBWrite;
    unsigned int m_iClearColor;
    unsigned int m_iClearColorR;
    unsigned int m_iClearColorG;
    unsigned int m_iClearColorB;
    unsigned int m_iClearColorA;
    unsigned int m_iClearStencil;
    unsigned int m_iClipPlanes;
    unsigned int m_iStencilWriteMask;
    unsigned int m_iCCWStencilWriteMask;
    unsigned int m_iAlphaRef;
    unsigned int m_iStencilRef;
    unsigned int m_iStencilMask;
    unsigned int m_iCCWStencilRef;
    unsigned int m_iCCWStencilMask;
    unsigned int m_iHiStencilRef;
    float m_fClearDepth;
    float m_fPointSize;
    float m_fPolygonOffsetFactor;
    float m_fPolygonOffsetUnits;
    float m_fZNear;
    float m_fZFar;
    float m_ClipPlaneEquation[CLIP_PLANES_MAX][4];
    EFrontFace m_eFrontFace;
    EFillMode m_eFillMode;
    ECmpFunc m_eAlphaFunc;
    ECmpFunc m_eDepthFunc;
    ECmpFunc m_eStencilFunc;
    ECmpFunc m_eCCWStencilFunc;
    ECmpFunc m_eHiStencilFunc;
    EBlendFactor m_eSrcBlendFactor;
    EBlendFactor m_eDestBlendFactor;
    EBlendOp m_eBlendOp;
    EBlendFactor m_eSrcBlendFactorAlpha;
    EBlendFactor m_eDestBlendFactorAlpha;
    EBlendOp m_eBlendOpAlpha;
    EStencilOP m_eStencilFail;
    EStencilOP m_eStencilZFail;
    EStencilOP m_eStencilZPass;
    EStencilOP m_eCCWStencilFail;
    EStencilOP m_eCCWStencilZFail;
    EStencilOP m_eCCWStencilZPass;

    Rect m_Viewport;
    Rect m_Scissor;
};
