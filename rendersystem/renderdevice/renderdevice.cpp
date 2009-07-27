#include "renderdevice.h"
#include "./d3d9/apibridge.h"


RenderDevice RenderDevice::renderdeviceInstance;
RenderDevice* gRenderDevice = RenderDevice::instance();

RenderDevice::RenderDevice()
: mInited(false)
{
}

RenderDevice* RenderDevice::instance()
{
    return &renderdeviceInstance;
}

RenderDevice::~RenderDevice()
{
}

bool  RenderDevice::Initialize(const RenderDevice::Setting &setting)
{
    if (mInited)
        return false;

    bool isOk = true;

    mSetting = setting;
    mBeginRenderCount = 0;
    
    if (isOk)
        isOk = APIBridge::Initialize(mSetting);

    if (isOk)
        isOk = mTextureManager.Initialize(1024);

    if (!isOk)
    {
        Finalize();
        return false;
    }

    mInited = true;
    return true;
}

bool RenderDevice::Finalize()
{
    mTextureManager.Finalize();
    APIBridge::Finalize();

    mInited = false;
    return true;
}

inline const RenderDevice::Setting& RenderDevice::GetSetting()
{
    return mSetting;
}


bool  RenderDevice::ChangeSetting(const RenderDevice::Setting &setting)
{
    if (!APIBridge::ChangeSetting(setting))
        return false;

    mSetting = setting;
    return true;
}
    

bool  RenderDevice::BeginRender()
{
    if (0 == mBeginRenderCount)
    {
        if (!APIBridge::BeginRender())
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
        APIBridge::EndRender();
    }

    mBeginRenderCount--;
    return true;
}

void  RenderDevice::Clear(const unsigned int *color, const float *depth, const int *stencil)
{
    APIBridge::Clear(color, depth, stencil);
}

void  RenderDevice::SwapBuffers()
{
    assert(0 == mBeginRenderCount);
    APIBridge::SwapBuffers();
}
    
/** RenderStates accessor functions*/ 
//@{
void  RenderDevice::SetColorWrite(bool write)
{
    if (write != mRenderStates.mColorWrite)
    {
        APIBridge::SetColorWrite(write);
        mRenderStates.mColorWrite = write;
    }
}

void  RenderDevice::SetFillMode(EFillMode fillMode)
{
    if (fillMode != mRenderStates.mFillMode)
    {
        APIBridge::SetFillMode(fillMode);
        mRenderStates.mFillMode = fillMode;
    }
}

void  RenderDevice::SetFaceCull(EFaceCull faceCull)
{
    if (faceCull != mRenderStates.mFaceCull)
    {
        APIBridge::SetFaceCull(faceCull);
        mRenderStates.mFaceCull = faceCull;
    }
}

void  RenderDevice::SetAlphaTest(float alpha)
{
    if (alpha != mRenderStates.mAlphaTestValue)
    {
        APIBridge::SetAlphaTest(alpha);
        mRenderStates.mAlphaTestValue = alpha;
    }
}

void  RenderDevice::SetBlendFactor(EBlendFactor srcFactor, EBlendFactor destFactor)
{
    if (srcFactor != mRenderStates.mSrcBlendFactor || destFactor != mRenderStates.mDestBlendFactor)
    {
        APIBridge::SetBlendFactor(srcFactor, destFactor);
        mRenderStates.mSrcBlendFactor = srcFactor;
        mRenderStates.mDestBlendFactor = destFactor;
    }
}

void  RenderDevice::SetDepthFunc(ECompareFunc compareFunc)
{
    if (compareFunc != mRenderStates.mDepthFunc)
    {
        APIBridge::SetDepthFunc(compareFunc);
        mRenderStates.mDepthFunc = compareFunc;
    }
}

void  RenderDevice::SetDepthWrite(bool write)
{
    if (write != mRenderStates.mDepthWrite)
    {
        APIBridge::SetDepthWrite(write);
        mRenderStates.mDepthWrite = write;
    }
}

void  RenderDevice::SetStencilFunc(ECompareFunc compareFunc, int ref, int mask)
{
    if (compareFunc != mRenderStates.mStencilFunc || ref != mRenderStates.mStencilRef || mask != mRenderStates.mStencilMask)
    {
        APIBridge::SetStencilFunc(compareFunc, ref, mask);
        mRenderStates.mStencilFunc = compareFunc;
        mRenderStates.mStencilRef = ref;
        mRenderStates.mStencilMask = mask;
    }
}

void  RenderDevice::SetStencilWriteMask(int mask)
{
    if (mask != mRenderStates.mStencilWriteMask)
    {
        APIBridge::SetStencilWriteMask(mask);
        mRenderStates.mStencilWriteMask = mask;
    }
}

void  RenderDevice::SetStencilOp(EStencilOP fail, EStencilOP zfail, EStencilOP zpass)
{
    if (fail != mRenderStates.mStencilFailOP || zfail != mRenderStates.mStencilZFailOP || zpass != mRenderStates.mStencilZPassOP)
    {
        APIBridge::SetStencilOp(fail, zfail, zpass);
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
    APIBridge::SetSamplerTexture(idx, texture);
}

/** Set color texture as rendertarget*/
void  RenderDevice::SetRenderTarget(int idx, Texture *texture)
{
    assert(idx < MAX_RENDERTARGETS && idx >= 0);
    APIBridge::SetRenderTarget(idx, texture);
}

/** Set depth texture as rendertarget's depth buffer*/
void  RenderDevice::SetDepthStencilTexture(Texture *texture)
{
    APIBridge::SetDepthStencilTexture(texture);
}


/** Texture functions*/
//@{
Texture* RenderDevice::CreateTexture(const TextureSpec &spec)
{
    return APIBridge::CreateTexture(spec);
}

Texture* RenderDevice::CreateTexture(const void *data, int byteSize)
{
    return APIBridge::CreateTexture(data, byteSize);
}

bool     RenderDevice::DestroyTexture(Texture *texture)
{
    return APIBridge::DestroyTexture(texture);
}
          
void*    RenderDevice::LockTexture(Texture *texture, int mipLevel, ELockType lockType, int *pitch /*= 0*/)
{
    return APIBridge::LockTexture(texture, mipLevel, lockType, pitch);
}

void     RenderDevice::UnlockTexture(Texture *texture, int mipLevel)
{
    APIBridge::UnlockTexture(texture, mipLevel);
}

//@}     
       

/** Vertex buffer functions*/
//@{
Vertices* RenderDevice::CreateVertices(int vertexCount, int vertexStride, EResourceUsage usage /*= RES_USAGE_WRITEONLY*/)
{
    return NULL;
}

void  RenderDevice::DestroyVertices(Vertices *vbuf)
{
    
}

void* RenderDevice::LockVertices(Vertices *vbuf, int firstVertex /*= 0*/, int numVertices /*= 0*/, ELockType lockType /*= LOCKTYPE_WRITE*/)
{
    return NULL;
}

void RenderDevice::UnlockVertices(Vertices *vbuf)
{

}

//@}            


/** Stream functions*/
//@{
void RenderDevice::SetStreamSource(int idx, Vertices *vertexSource, int offsetInBytes /*= 0*/)
{

}

RegistersMap* RenderDevice::CreateRegistersMap(const Vertices::Spec &spec)
{
    return NULL;
}

void  RenderDevice::DestroyRegistersMap(RegistersMap *registersMap)
{

}

void  RenderDevice::SetRegistersMap(RegistersMap *registersMap)
{

}

//@}            


/** Index buffer functions*/
//@{
IndexBuffer* RenderDevice::CreateIndexBuffer(int indexCount, int indexStride, EResourceUsage usage /*= RES_USAGE_WRITEONLY*/)
{
    return NULL;
}

void RenderDevice::DestroyIndexBuffer(IndexBuffer *ibuf)
{

}

void* RenderDevice::LockIndexBuffer(IndexBuffer *ibuf, int firstIndex /*= 0*/, int numIndices /*= 0*/, ELockType lockType /*= LOCKTYPE_WRITE*/)
{
    return NULL;
}

void RenderDevice::UnlockIndexBuffer(IndexBuffer *ibuf)
{

}

void RenderDevice::SetIndexBuffer(IndexBuffer *ibuf)
{
    
}

//@}


/** Vertex Shader functions*/
//@{
VertexShader* RenderDevice::CreateVertexShader(const char *code, int size)
{
    return NULL;
}

void RenderDevice::DestroyVertexShader(VertexShader *vshader)
{
    
}

void RenderDevice::SetVertexShader(VertexShader *vshader)
{

}

void RenderDevice::SetVertexShaderConstant(int startRegister, const float *value, int count)
{

}

void RenderDevice::SetVertexShaderConstant(int startRegister, const int *value, int count)
{

}

//@}


/** Pixel Shader functions*/
//@{
PixelShader* RenderDevice::CreatePixelShader(const char *code, int size)
{
    return NULL;
}

void RenderDevice::DestroyPixelShader(PixelShader *pshader)
{

}

void RenderDevice::SetPixelShader(PixelShader *pshader)
{

}

void RenderDevice::SetPixelShaderConstant(int startRegister, const float *value, int count)
{

}

void RenderDevice::SetPixelShaderConstant(int startRegister, const int *value, int count)
{

}

//@}


/** Occusion Query */
//@{
OcclusionQuery* RenderDevice::CreateOcclusionQuery()
{
    return NULL;
}

void RenderDevice::DestroyOcclusionQuery(OcclusionQuery *oquery)
{

}

void RenderDevice::BeginOcclusionQuery(OcclusionQuery *oquery)
{

}

void RenderDevice::EndOcclusionQuery(OcclusionQuery *oquery)
{

}

bool RenderDevice::GetOcclusionQueryResult(OcclusionQuery, int &numPixels)
{
    return true;
}

//@}


/** Draw call*/
//@{
void RenderDevice::DrawPrimitive(EPrimitiveType primType, int startVertex, int primCount)
{

}

void RenderDevice::DrawPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride)
{

}

void RenderDevice::DrawIndexedPrimitive(EPrimitiveType primType, int startIndex, int primCount, int minVertex, int numVertices, int baseVertexIndex /*= 0*/)
{

}

void RenderDevice::DrawIndexedPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride, const void *indexData, int indexStride, int minVertex, int numVertices)
{

}

//@}             


/** Cursor*/
//@{
void RenderDevice::ShowCursor(bool show)
{

}

void RenderDevice::SetCursorTexture(int id, int xHotSpot, int yHotSpot)
{

}

void RenderDevice::SetCursorPosition(int x, int y)
{

}

//@}             
                 
APIRenderDevice* RenderDevice::GetAPIRenderDevice()
{
    return APIBridge::GetAPIRenderDevice();
}