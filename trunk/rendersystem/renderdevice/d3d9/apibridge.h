#ifndef _APIBRIDGE_H_
#define _APIBRIDGE_H_

#include "../renderdevice.h"

class APIBridge
{
public:
    static APIRenderDevice*    GetAPIRenderDevice();

    /** Actual API bridge functions, only convert function call to graphics api call, don't access device member.*/
    //@{
    static bool  Initialize(const RenderDevice::Setting &setting);
    static void  Finalize();

    static bool  ChangeSetting(const RenderDevice::Setting &setting);


    static bool  BeginRender();
    static void  EndRender();

    static void  Clear(const unsigned int *color, const float *depth, const int *stencil);
    static void  SwapBuffers();

    /** RenderStates accessor functions*/ 
    //@{
    static void  SetColorWrite(bool write);
    static void  SetFillMode(EFillMode fillMode); 
    static void  SetFaceCull(EFaceCull faceCull);
    static void  SetAlphaTest(float alpha);
    static void  SetBlendFactor(EBlendFactor srcFactor, EBlendFactor destFactor);
    static void  SetDepthFunc(ECompareFunc compareFunc);
    static void  SetDepthWrite(bool write);
    static void  SetStencilFunc(ECompareFunc compareFunc, int ref, int mask);
    static void  SetStencilWriteMask(int mask);
    static void  SetStencilOp(EStencilOP fail, EStencilOP zfail, EStencilOP zpass);
    //@}     

    /** Bind texture with sampler.*/
    static void  SetSamplerTexture(int idx, const Texture *texture);

    /** Render Target*/
    //@{
    static void  SetRenderTarget(int idx, Texture *texture);
    static void  SetDepthStencilTexture(Texture *texture);
    //@}

    /** Texture functions*/
    //@{
    static Texture*        CreateTexture(const TextureSpec &spec);
    static Texture*        CreateTexture(const void *data, int byteSize);
    static bool            DestroyTexture(Texture *texture);
    
    static void*           LockTexture(Texture *texture, int mipLevel, ELockType lockType, int *pitch = 0);
    static void            UnlockTexture(Texture *texture, int mipLevel);
    //@}     

    /** Vertex buffer functions*/
    //@{
    static Vertices*       CreateVertices(int vertexCount, int vertexStride, EResourceUsage usage = RES_USAGE_WRITEONLY);
    static void            DestroyVertices(Vertices *vbuf);
    static void*           LockVertices(Vertices *vbuf, int firstVertex = 0, int numVertices = 0, ELockType lockType = LOCKTYPE_WRITE);
    static void            UnlockVertices(Vertices *vbuf);
    //@}            

    /** Stream functions*/
    //@{
    static void            SetStreamSource(int idx, Vertices *vertexSource, int offsetInBytes = 0);
    static RegistersMap*   CreateRegistersMap(const Vertices::Spec &spec);
    static void            DestroyRegistersMap(RegistersMap *registersMap);
    static void            SetRegistersMap(RegistersMap *registersMap);
    //@}            

    /** Index buffer functions*/
    //@{
    static IndexBuffer*    CreateIndexBuffer(int indexCount, int indexStride, EResourceUsage usage = RES_USAGE_WRITEONLY);
    static void            DestroyIndexBuffer(IndexBuffer *ibuf);
    static void*           LockIndexBuffer(IndexBuffer *ibuf, int firstIndex = 0, int numIndices = 0, ELockType lockType = LOCKTYPE_WRITE);
    static void            UnlockIndexBuffer(IndexBuffer *ibuf);
    static void            SetIndexBuffer(IndexBuffer *ibuf);
    //@}


    /** Vertex Shader functions*/
    //@{
    static VertexShader*   CreateVertexShader(const char *code, int size);
    static void            DestroyVertexShader(VertexShader *vshader);
    static void            SetVertexShader(VertexShader *vshader);
    static void            SetVertexShaderConstant(int startRegister, const float *value, int count);
    static void            SetVertexShaderConstant(int startRegister, const int *value, int count);
    //@}

    /** Pixel Shader functions*/
    //@{
    static PixelShader*    CreatePixelShader(const char *code, int size);
    static void            DestroyPixelShader(PixelShader *pshader);
    static void            SetPixelShader(PixelShader *pshader);
    static void            SetPixelShaderConstant(int startRegister, const float *value, int count);
    static void            SetPixelShaderConstant(int startRegister, const int *value, int count);
    //@}

    /** Occusion Query */
    //@{
    static OcclusionQuery*  CreateOcclusionQuery();
    static void             DestroyOcclusionQuery(OcclusionQuery *oquery);
    static void             BeginOcclusionQuery(OcclusionQuery *oquery);
    static void             EndOcclusionQuery(OcclusionQuery *oquery);
    static bool             GetOcclusionQueryResult(OcclusionQuery, int &numPixels);
    //@}

    /** Draw call*/
    //@{
    static void             DrawPrimitive(EPrimitiveType primType, int startVertex, int primCount);
    static void             DrawPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride);
    static void             DrawIndexedPrimitive(EPrimitiveType primType, int startIndex, int primCount, int minVertex, int numVertices, int baseVertexIndex = 0);
    static void             DrawIndexedPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride, const void *indexData, int indexStride, int minVertex, int numVertices);
    //@}

    /** Cursor*/
    //@{
    static void             ShowCursor(bool show);
    static void             SetCursorTexture(int id, int xHotSpot, int yHotSpot);
    static void             SetCursorPosition(int x, int y);
    //@}
    
    //@}
};

#endif  //_APIBRIDGE_H_