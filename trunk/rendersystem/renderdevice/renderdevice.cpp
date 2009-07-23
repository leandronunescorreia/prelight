#include "renderdevice.h"


RenderDevice *gRenderDevice = NULL;

RenderDevice::RenderDevice()
: mInitialized(false),
, mBeginRenderCount(0),
{
}

RenderDevice::~RenderDevice()
{
}

bool  RenderDevice::Initialize(const RenderDeviceSettings &settings)
{
    if (mInitialized)
        return false;

    if (!API_Initialize(settings))
        return false;

    mSettings = settings;
    mBeginSceneDepth = 0;
    mInitialized = true;
    gRenderDevice = this;


    if (!mTextureManager.Initialize())
    {
        Finalize();
        return false;
    }

    return true;
}

bool RenderDevice::Finalize()
{
    if (!mInitialized)
        return false;

    mTextureManager.Finalize();

    gRenderDevice = NULL;
    mInitialized = false;
    mSettings.Reset();
    
    API_Finalize();
    return true;
}

inline const RenderDeviceSetting& RenderDevice::GetSetting()
{
    return mSettings;
}


bool  RenderDevice::ChangeSettings(const RenderDeviceSettings &settings)
{
    if (!API_ChangeSetting(settings))
        return false;

    m_Setting = settings;
    return true;
}
    

bool  RenderDevice::BeginRender()
{
    if (0 == mBeginRenderCount)
    {
        if (!API_BeginScene())
            return false;
    }

    mBeginRenderCount++;
    return true;
}

bool RenderDevice::EndRender()
{
    if (0 == mBeginRenderCount)
        return false;

    if (1 == mBeginRenderCount)
    {
        API_EndScene();
    }

    mBeginRenderCount--;
    return true;
}

void  RenderDevice::Clear(const unsigned int *color, const float *depth, const int *stencil, const Rect const *rect /*= 0*/, unsigned int rectcount /*= 0*/)
{
    API_Clear(color, depth, stencil, rect, rectcount);
}

void  RenderDevice::SwapBuffers()
{
    assert(0 == mBeginRenderCount;
    API_SwapBuffers();
}
    
/** RenderStates accessor functions*/ 
//@{
void  RenderDevice::SetColorWrite(bool write)
{
    if (write != mRenderStates.mColorWrite)
    {
        API_SetColorWrite(write);
        mRenderStates.mColorWrite = write;
    }
}

void  RenderDevice::SetFillMode(EFillMode fillMode)
{
    if (fillMode != mRenderStates.mFillMode)
    {
        API_SetFillMode(fillMode);
        mRenderStates.mFillMode = fillMode;
    }
}

void  RenderDevice::SetFaceCull(EFaceCull faceCull)
{
    if (faceCull != mRenderStates.mFaceCull)
    {
        API_SetFaceCull(faceCull);
        mRenderStates.mFaceCull = faceCull;
    }
}

void  RenderDevice::SetAlphaTest(float alpha)
{
    if (alpha != mRenderStates.mAlphaTestValue)
    {
        API_SetAlphaTest(alpha);
        mRenderStates.mAlphaTestValue = alpha;
    }
}

void  RenderDevice::SetBlendFactor(EBlendFactor srcFactor, EBlendFactor destFactor)
{
    if (srcFactor != mRenderStates.mSrcBlendFactor || destFactor != mRenderStates.mDestBlendFactor)
    {
        API_SetBlendFactor(srcFactor, destFactor);
        mRenderStates.mSrcBlendFactor = srcFactor;
        mRenderStates.mDestBlendFactor = destFactor;
    }
}

void  RenderDevice::SetDepthFunc(ECompareFunc compareFunc)
{
    if (compareFunc != mRenderStates.mDepthFunc)
    {
        API_SetDepthFunc(compareFunc);
        mRenderStates.mDepthFunc = compareFunc;
    }
}

void  RenderDevice::SetDepthWrite(bool write)
{
    if (write != mRenderStates.mDepthWrite)
    {
        API_SetDepthWrite(write);
        mRenderStates.mDepthWrite = write;
    }
}

void  RenderDevice::SetStencilFunc(ECompareFunc compareFunc, int ref, int mask)
{
    if (compareFunc != mRenderStates.mStencilFunc || ref != mRenderStates.mStencilRef || mask != mRenderStates.mStencilMark)
    {
        API_SetStencilFunc(compareFunc, ref, mask);
        mRenderStates.mStencilFunc = compareFunc;
        mRenderStates.mStencilRef = ref;
        mRenderStates.mStencilMask = mask;
    }
}

void  RenderDevice::SetStencilWriteMask(int mask)
{
    if (mask != mRenderStates.mStencilWriteMask)
    {
        API_SetStencilWriteMask(mask);
        mRenderStates.mStencilWriteMask = mask;
    }
}

void  RenderDevice::SetStencilOp(EStencilOP fail, EStencilOP zfail, EStencilOP zpass)
{
    if (fail != mRenderStates.mStencilFailOP || zfail != mRenderStates.mStencilZFailOP || zpass != mRenderStates.mStencilZPassOP)
    {
        API_SetStencilOP(fail, zfail, zpass);
        mRenderStates.mStencilFailOP = fail;
        mRenderStates.mStencilZFailOP = zfail;
        mRenderStates.mStencilZPassOP = zpass;
    }
}
//@}


/** Bind texture with sampler.*/
void  RenderDevice::SetSamplerTexture(int idx, const Texture *texture)
{
    assert(idx < MAX_TEXTURE_SAMPLERS && idx >= 0);
    API_SetSamplerTexture(idx, texture);
}

/** Set color texture as rendertarget*/
void  RenderDevice::SetRenderTarget(int idx, Texture *texture)
{
    assert(idx < MAX_RENDERTARGETS && idx >= 0);
    API_SetRenderTarget(idx, texture);
}

/** Set depth texture as rendertarget*/
void  RenderDevice::SetDepthStencilTexture(Texture *texture)
{
    API_SetDepthStencilTexture(texture);
}

/** Texture functions*/
//@{
Texture* RenderDevice::CreateTexture(const TextureSpec &spec)
{
    return API_CreateTextuer(spec);
}

Texture* RenderDevice::CreateTexture(const void *data, int byteSize)
{
    return API_CreateTextue(data, byteSize);
}

bool     RenderDevice::DestroyTexture(Texture *texture)
{
    return API_DestroyTexture(texture);
}
         
void*    RenderDevice::LockTexture(Texture *texture, int mipLevel, ELockType lockType, int *pitch /*= 0*/)
{
    return API_LockTexture(texture, mipLevel, lockType, pitch);
}

void     RenderDevice::UnlockTexture(Texture *texture, int mipLevel)
{
    API_UnlockTexture(texture, mipLevel);
}

//@}     
         
/** Vertex buffer functions*/
//@{
VertexBuffer*  RenderDevice::CreateVertexBuffer(int vertexCount, int vertexStride, EResourceUsage usage = RES_USAGE_WRITEONLY);
void           RenderDevice::DestroyVertexBuffer(VertexBuffer *vbuf);
void*          RenderDevice::LockVertexBuffer(VertexBuffer *vbuf, int firstVertex = 0, int numVertices = 0, ELockType lockType = LOCK_WRITE);
void           RenderDevice::UnlockVertexBuffer(VertexBuffer *vbuf);
//@}           

/** Stream functions*/
//@{
void           RenderDevice::SetStreamSource(int idx, VertexBuffer *vertexSource, int offsetInBytes = 0);
StreamMap*     RenderDevice::CreateStreamRegistersMap(const CVertexSpec &spec);
void           RenderDevice::DestroyStreamRegistersMap(StreamMap *streamMap);
void           RenderDevice::SetStreamRegistersMap(StreamMap *streamMap);
//@}           

/** Index buffer functions*/
//@{
IndexBuffer*   RenderDevice::CreateIndexBuffer(int indexCount, int indexStride, EResourceUsage usage = RES_USAGE_WRITEONLY);
void           RenderDevice::DestroyIndexBuffer(IndexBuffer *ibuf);
void*          RenderDevice::LockIndexBuffer(IndexBuffer *ibuf, int firstIndex = 0, int numIndices = 0, ELockType lockType = LOCK_WRITE);
void           RenderDevice::UnlockIndexBuffer(IndexBuffer *ibuf);
void           RenderDevice::SetIndexBuffer(IndexBuffer *ibuf);
//@}


/** Vertex Shader functions*/
//@{
VertexShader*  RenderDevice::CreateVertexShader(const char *code, int size);
void           RenderDevice::DestroyVertexShader(VertexShader *vshader);
void           RenderDevice::SetVertexShader(VertexShader *vshader);
void           RenderDevice::SetVertexShaderConstant(int startRegister, const float *value, int count);
void           RenderDevice::SetVertexShaderConstant(int startRegister, const int *value, int count);
//@}

/** Pixel Shader functions*/
//@{
PixelShader*   RenderDevice::CreatePixelShader(const char *code, int size);
void           RenderDevice::DestroyPixelShader(PixelShader *pshader);
void           RenderDevice::SetPixelShader(PixelShader *pshader);
void           RenderDevice::SetPixelShaderConstant(int startRegister, const float *value, int count);
void           RenderDevice::SetPixelShaderConstant(int startRegister, const int *value, int count);
//@}

/** Occusion Query */
//@{
OcclusionQuery* RenderDevice::CreateOcclusionQuery();
void            RenderDevice::DestroyOcclusionQuery(OcclusionQuery *oquery);
void            RenderDevice::BeginOcclusionQuery(OcclusionQuery *oquery);
void            RenderDevice::EndOcclusionQuery(OcclusionQuery *oquery);
bool            RenderDevice::GetOcclusionQueryResult(OcclusionQuery, int &numPixels);
//@}

/** Draw call*/
//@{
void            RenderDevice::DrawPrimitive(EPrimitiveType primType, int startVertex, int primCount);
void            RenderDevice::DrawPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride);
void            RenderDevice::DrawIndexedPrimitive(EPrimitiveType primType, int startIndex, int primCount, int minVertex, int numVertices, int baseVertexIndex = 0);
void            RenderDevice::DrawIndexedPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride, const void *indexData, int indexStride, int minVertex, int numVertices);
//@}            

/** Cursor*/
//@{
void            RenderDevice::ShowCursor(bool show);
void            RenderDevice::SetCursorTexture(int id, int xHotSpot, int yHotSpot);
void            RenderDevice::SetCursorPosition(int x, int y);
//@}            
                
void*           RenderDevice::GetAPIRenderDevice();