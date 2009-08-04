#include "apibridge.h"

static IDirect3D9*       d3d = NULL;
static IDirect3DDevice9* d3dDevice = NULL;

static UINT              adapter    = D3DADAPTER_DEFAULT;
static D3DDEVTYPE        deviceType = D3DDEVTYPE_HAL;
static D3DPRESENT_PARAMETERS d3dpp;

/**
Forward declaration of utility functions and data.
*/
//@{


//@}

APIRenderDevice* APIBridge::GetAPIRenderDevice()
{
    return d3dDevice;
}

static void InitD3DPresentParameters(const RenderDevice::Setting& setting)
{
	memset( &d3dpp, 0, sizeof(d3dpp) );

    if( setting.fullscreen )
	{
        d3dpp.BackBufferWidth  = setting.width;
        d3dpp.BackBufferHeight = setting.height;
        d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;   ///< FIX ME: Should be got from RenderDevice::Setting.
		d3dpp.BackBufferCount  = 1;

        d3dpp.MultiSampleType    = D3DMULTISAMPLE_NONE;
        d3dpp.MultiSampleQuality = 0;
        d3dpp.SwapEffect         = D3DSWAPEFFECT_DISCARD;

        d3dpp.hDeviceWindow = setting.screen;
		d3dpp.Windowed      = FALSE;
		
		d3dpp.EnableAutoDepthStencil = TRUE;
        d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;    ///< FIX ME: Should be got from RenderDevice::Setting.
        d3dpp.Flags                  = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
		
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		
	}
	else
	{
        d3dpp.BackBufferWidth  = setting.width;
        d3dpp.BackBufferHeight = setting.height;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferCount  = 1;

        d3dpp.MultiSampleType    = D3DMULTISAMPLE_NONE;
        d3dpp.MultiSampleQuality = 0;
        d3dpp.SwapEffect         = D3DSWAPEFFECT_DISCARD;

        d3dpp.hDeviceWindow = setting.screen;
		d3dpp.Windowed      = TRUE;
		
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
        d3dpp.Flags                  = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;

		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
}

bool APIBridge::Initialize(const RenderDevice::Setting &setting)
{
    d3d = Direct3DCreate9( D3D_SDK_VERSION );
    if (NULL == d3d)
        return false;
    
    InitD3DPresentParameters(setting);

	adapter    = D3DADAPTER_DEFAULT;
	deviceType = D3DDEVTYPE_HAL;

#ifdef _DEBUG
	for( UINT i = 0; i < d3d->GetAdapterCount(); ++i )
	{
		D3DADAPTER_IDENTIFIER9	identifier;

		HRESULT hr = d3d->GetAdapterIdentifier(i, 0, &identifier);
        if (D3D_OK != hr)
            return false;

		if( NULL != strstr(identifier.Description, "PerfHUD") )
		{
			adapter    = i;
			deviceType = D3DDEVTYPE_REF;
			break;
		}
	}
#endif

    HWND hwnd = setting.screen;
    /**REMARK: We may need D3DCREATE_MULTITHREADED flag in the future.*/
	HRESULT hr = d3d->CreateDevice(	adapter, deviceType, hwnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING ,
									&d3dpp, &d3dDevice );
    
    d3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	d3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    return true;
}

void APIBridge::Finalize()
{

}

bool APIBridge::ChangeSetting(const RenderDevice::Setting &setting)
{
    return true;
}

bool APIBridge::BeginRender()
{
    return true;
}

void APIBridge::EndRender()
{

}

void APIBridge::Clear(const unsigned int *color, const float *depth, const int *stencil)
{
    DWORD    clearFlag    = 0;
    D3DCOLOR clearColor   = 0x00000000;
    float    clearZ       = 1.0f;
    DWORD    clearStencil = 0x00;

    if (color)
    {
        clearFlag |= D3DCLEAR_TARGET;
        clearColor = static_cast<D3DCOLOR>(*color);
    }
    if (depth)
    {
        clearFlag |= D3DCLEAR_ZBUFFER;
        clearZ = *depth;
    }
    if (stencil)
    {
        clearFlag |= D3DCLEAR_STENCIL;
        clearStencil = *stencil;
    }
    assert(0 != clearFlag);

    d3dDevice->Clear( 0, NULL, clearFlag, clearColor, clearZ, clearStencil );
}

void APIBridge::SwapBuffers()
{
    d3dDevice->Present(NULL, NULL, NULL, NULL);
}

/** RenderStates accessor functions*/ 
//@{
void APIBridge::SetColorWrite(bool write)
{

}

void APIBridge::SetFillMode(EFillMode fillMode)
{

}

void APIBridge::SetFaceCull(EFaceCull faceCull)
{

}

void APIBridge::SetAlphaTest(float alpha)
{

}

void APIBridge::SetBlendFactor(EBlendFactor srcFactor, EBlendFactor destFactor)
{

}

void APIBridge::SetDepthFunc(ECompareFunc compareFunc)
{

}

void APIBridge::SetDepthWrite(bool write)
{

}

void APIBridge::SetStencilFunc(ECompareFunc compareFunc, int ref, int mask)
{

}

void APIBridge::SetStencilWriteMask(int mask)
{

}

void APIBridge::SetStencilOp(EStencilOP fail, EStencilOP zfail, EStencilOP zpass)
{

}

//@}    

/** Bind texture with sampler.*/
void APIBridge::SetSamplerTexture(int idx, const Texture *texture)
{

}

/** Render Target*/
//@{
void APIBridge::SetRenderTarget(int idx, Texture *texture)
{

}

void APIBridge::SetDepthStencilTexture(Texture *texture)
{

}
//@}


/** Texture functions*/
//@{
Texture* APIBridge::CreateTexture(const TextureSpec &spec)
{
    return NULL;
}

Texture* APIBridge::CreateTexture(const void *data, int byteSize)
{
    IDirect3DTexture9 *d3dTexture = NULL;
    /** The created d3dTexture is located in managed pool.*/
    if (D3D_OK != D3DXCreateTextureFromFileInMemory(d3dDevice, data, byteSize, &d3dTexture))
        return NULL;

    Texture *texture = new Texture;
    texture->apitexture = d3dTexture;

    /** Get d3d texture's attributes, copy them to texture spec.*/
    D3DSURFACE_DESC desc;
    d3dTexture->GetLevelDesc(0, &desc);

    Texture::Spec& spec = texture->spec;
    spec.format = static_cast<EPixelFormat>(desc.Format);
    spec.usage = static_cast<EResourceUsage>(desc.Usage);
    spec.width = desc.Width;
    spec.height = desc.Height;
    spec.mipLevels = d3dTexture->GetLevelCount();

    return texture;
}

bool APIBridge::DestroyTexture(Texture *texture)
{
    return true;
}
      
void* APIBridge::LockTexture(Texture *texture, int mipLevel, ELockType lockType, int *pitch /*= 0*/)
{
    return NULL;
}

void APIBridge::UnlockTexture(Texture *texture, int mipLevel)
{

}

//@}     


/** Vertex buffer functions*/
//@{
Vertices* APIBridge::CreateVertices(int vertexCount, int vertexStride, EResourceUsage usage /*= RES_USAGE_WRITEONLY*/)
{
    return NULL;
}

void APIBridge::DestroyVertices(Vertices *vbuf)
{

}

void* APIBridge::LockVertices(Vertices *vbuf, int firstVertex /*= 0*/, int numVertices /*= 0*/, ELockType lockType /*= LOCKTYPE_WRITE*/)
{
    return NULL;
}

void APIBridge::UnlockVertices(Vertices *vbuf)
{

}
//@}            


/** Stream functions*/
//@{
void APIBridge::SetStreamSource(int idx, Vertices *vertexSource, int offsetInBytes /*= 0*/)
{

}

RegistersMap* APIBridge::CreateRegistersMap(const Vertices::Spec &spec)
{
    return NULL;
}

void APIBridge::DestroyRegistersMap(RegistersMap *registersMap)
{

}

void APIBridge::SetRegistersMap(RegistersMap *registersMap)
{

}

//@}            


/** Index buffer functions*/
//@{
IndexBuffer* APIBridge::CreateIndexBuffer(int indexCount, int indexStride, EResourceUsage usage /*= RES_USAGE_WRITEONLY*/)
{
    return NULL;
}

void APIBridge::DestroyIndexBuffer(IndexBuffer *ibuf)
{

}

void* APIBridge::LockIndexBuffer(IndexBuffer *ibuf, int firstIndex /*= 0*/, int numIndices /*= 0*/, ELockType lockType /*= LOCKTYPE_WRITE*/)
{
    return NULL;
}

void APIBridge::UnlockIndexBuffer(IndexBuffer *ibuf)
{

}

void APIBridge::SetIndexBuffer(IndexBuffer *ibuf)
{

}

//@}


/** Vertex Shader functions*/
//@{
VertexShader* APIBridge::CreateVertexShader(const char *code, int size)
{
    return NULL;
}

void APIBridge::DestroyVertexShader(VertexShader *vshader)
{

}

void APIBridge::SetVertexShader(VertexShader *vshader)
{

}

void APIBridge::SetVertexShaderConstant(int startRegister, const float *value, int count)
{

}

void APIBridge::SetVertexShaderConstant(int startRegister, const int *value, int count)
{

}
//@}

/** Pixel Shader functions*/
//@{
PixelShader* APIBridge::CreatePixelShader(const char *code, int size)
{
    return NULL;
}

void APIBridge::DestroyPixelShader(PixelShader *pshader)
{

}

void APIBridge::SetPixelShader(PixelShader *pshader)
{

}

void APIBridge::SetPixelShaderConstant(int startRegister, const float *value, int count)
{

}

void APIBridge::SetPixelShaderConstant(int startRegister, const int *value, int count)
{

}

//@}


/** Occusion Query */
//@{
OcclusionQuery* APIBridge::CreateOcclusionQuery()
{
    return NULL;
}

void APIBridge::DestroyOcclusionQuery(OcclusionQuery *oquery)
{

}

void APIBridge::BeginOcclusionQuery(OcclusionQuery *oquery)
{

}

void APIBridge::EndOcclusionQuery(OcclusionQuery *oquery)
{

}

bool APIBridge::GetOcclusionQueryResult(OcclusionQuery, int &numPixels)
{
    return true;
}

//@}


/** Draw call*/
//@{
void APIBridge::DrawPrimitive(EPrimitiveType primType, int startVertex, int primCount)
{

}

void APIBridge::DrawPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride)
{

}

void APIBridge::DrawIndexedPrimitive(EPrimitiveType primType, int startIndex, int primCount, int minVertex, int numVertices, int baseVertexIndex /*= 0*/)
{

}

void APIBridge::DrawIndexedPrimitiveUP(EPrimitiveType primType, int primCount, const void *vertexData, int vertexStride, const void *indexData, int indexStride, int minVertex, int numVertices)
{

}

//@}


/** Cursor*/
//@{
void APIBridge::ShowCursor(bool show)
{

}

void APIBridge::SetCursorTexture(int id, int xHotSpot, int yHotSpot)
{

}

void APIBridge::SetCursorPosition(int x, int y)
{

}


/**Definition of utility functions and data*/
//@{


//@}