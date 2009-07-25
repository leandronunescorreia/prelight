#include "../renderdevice.h"

bool RenderDevice::API_Initialize(const RenderDevice::Setting &setting)
{
    return true;
}

void RenderDevice::API_Finalize()
{

}

bool RenderDevice::API_ChangeSetting(const RenderDevice::Setting &setting)
{
    return true;
}

bool RenderDevice::API_BeginRender()
{
    return true;
}

void RenderDevice::API_EndRender()
{

}

void RenderDevice::API_Clear(const unsigned int *color, const float *depth, const int *stencil, const Rect *rect /*= 0*/, unsigned int rectcount /*= 0*/)
{

}

void RenderDevice::API_SwapBuffers()
{

}

/** RenderStates accessor functions*/ 
//@{
void RenderDevice::API_SetColorWrite(bool write)
{

}

void RenderDevice::API_SetFillMode(EFillMode fillMode)
{

}

void RenderDevice::API_SetFaceCull(EFaceCull faceCull)
{

}

void RenderDevice::API_SetAlphaTest(float alpha)
{

}

void RenderDevice::API_SetBlendFactor(EBlendFactor srcFactor, EBlendFactor destFactor)
{

}

void RenderDevice::API_SetDepthFunc(ECompareFunc compareFunc)
{

}

void RenderDevice::API_SetDepthWrite(bool write)
{

}

void RenderDevice::API_SetStencilFunc(ECompareFunc compareFunc, int ref, int mask)
{

}

void RenderDevice::API_SetStencilWriteMask(int mask)
{

}

void RenderDevice::API_SetStencilOp(EStencilOP fail, EStencilOP zfail, EStencilOP zpass)
{

}

//@}    

/** Bind texture with sampler.*/
void RenderDevice::API_SetSamplerTexture(int idx, const Texture *texture)
{

}

/** Render Target*/
//@{
void RenderDevice::API_SetRenderTarget(int idx, Texture *texture)
{

}

void RenderDevice::API_SetDepthStencilTexture(Texture *texture)
{

}
//@}


/** Texture functions*/
//@{
Texture* RenderDevice::API_CreateTexture(const TextureSpec &spec)
{
    return NULL;
}

Texture* RenderDevice::API_CreateTexture(const void *data, int byteSize)
{
    return NULL;
}

bool RenderDevice::API_DestroyTexture(Texture *texture)
{
    return true;
}
      
void* RenderDevice::API_LockTexture(Texture *texture, int mipLevel, ELockType lockType, int *pitch /*= 0*/)
{
    return NULL;
}

void RenderDevice::API_UnlockTexture(Texture *texture, int mipLevel)
{

}

//@}     


/** Vertex buffer functions*/
//@{
Vertices* RenderDevice::API_CreateVertices(int vertexCount, int vertexStride, EResourceUsage usage /*= RES_USAGE_WRITEONLY*/)
{
    return NULL;
}

void RenderDevice::API_DestroyVertices(Vertices *vbuf)
{

}

void* RenderDevice::API_LockVertices(Vertices *vbuf, int firstVertex /*= 0*/, int numVertices /*= 0*/, ELockType lockType /*= LOCKTYPE_WRITE*/)
{
    return NULL;
}

void RenderDevice::API_UnlockVertices(Vertices *vbuf)
{

}
//@}            


/** Stream functions*/
//@{
void RenderDevice::API_SetStreamSource(int idx, Vertices *vertexSource, int offsetInBytes /*= 0*/)
{

}

RegistersMap* RenderDevice::API_CreateRegistersMap(const Vertices::Spec &spec)
{
    return NULL;
}

void RenderDevice::API_DestroyRegistersMap(RegistersMap *registersMap)
{

}

void RenderDevice::API_SetRegistersMap(RegistersMap *registersMap)
{

}

//@}            


/** Index buffer functions*/
//@{
IndexBuffer* RenderDevice::API_CreateIndexBuffer(int indexCount, int indexStride, EResourceUsage usage /*= RES_USAGE_WRITEONLY*/)
{
    return NULL;
}

void RenderDevice::API_DestroyIndexBuffer(IndexBuffer *ibuf)
{

}

void* RenderDevice::API_LockIndexBuffer(IndexBuffer *ibuf, int firstIndex /*= 0*/, int numIndices /*= 0*/, ELockType lockType /*= LOCKTYPE_WRITE*/)
{
    return NULL;
}

void RenderDevice::API_UnlockIndexBuffer(IndexBuffer *ibuf)
{

}

void RenderDevice::API_SetIndexBuffer(IndexBuffer *ibuf)
{

}

//@}


/** Vertex Shader functions*/
//@{
VertexShader* RenderDevice::API_CreateVertexShader(const char *code, int size)
{
    return NULL;
}

void RenderDevice::API_DestroyVertexShader(VertexShader *vshader)
{

}

void RenderDevice::API_SetVertexShader(VertexShader *vshader)
{

}

void RenderDevice::API_SetVertexShaderConstant(int startRegister, const float *value, int count)
{

}

void RenderDevice::API_SetVertexShaderConstant(int startRegister, const int *value, int count)
{

}
//@}

/** Pixel Shader functions*/
//@{
PixelShader* RenderDevice::API_CreatePixelShader(const char *code, int size)
{
    return NULL;
}

void RenderDevice::API_DestroyPixelShader(PixelShader *pshader)
{

}

void RenderDevice::API_SetPixelShader(PixelShader *pshader)
{

}

void RenderDevice::API_SetPixelShaderConstant(int startRegister, const float *value, int count)
{

}

void RenderDevice::API_SetPixelShaderConstant(int startRegister, const int *value, int count)
{

}

//@}


/** Occusion Query */
//@{
OcclusionQuery* RenderDevice::API_CreateOcclusionQuery()
{
    return NULL;
}

void RenderDevice::API_DestroyOcclusionQuery(OcclusionQuery *oquery)
{

}

void RenderDevice::API_BeginOcclusionQuery(OcclusionQuery *oquery)
{

}

void RenderDevice::API_EndOcclusionQuery(OcclusionQuery *oquery)
{

}

bool RenderDevice::API_GetOcclusionQueryResult(OcclusionQuery, int &numPixels)
{
    return true;
}

//@}


/** Draw call*/
//@{
void RenderDevice::API_DrawPrimitive(EPrimitiveType primType, int startVertex, int primCount)
{

}

void RenderDevice::API_DrawPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride)
{

}

void RenderDevice::API_DrawIndexedPrimitive(EPrimitiveType primType, int startIndex, int primCount, int minVertex, int numVertices, int baseVertexIndex /*= 0*/)
{

}

void RenderDevice::API_DrawIndexedPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride, const void *indexData, int indexStride, int minVertex, int numVertices)
{

}

//@}


/** Cursor*/
//@{
void RenderDevice::API_ShowCursor(bool show)
{

}

void RenderDevice::API_SetCursorTexture(int id, int xHotSpot, int yHotSpot)
{

}

void RenderDevice::API_SetCursorPosition(int x, int y)
{

}