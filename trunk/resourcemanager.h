#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

template <>
struct ResourceSlot
{
    void *resource;
    int   handle;

}

class ResourceManager
{
public:


}

	//HRESULT LoadTextures(GetFilePathCallback);
	//HRESULT LoadTexture(const tstring&, LPDIRECT3DTEXTURE9&, GetFilePathCallback, D3DFORMAT format = D3DFMT_A8R8G8B8, D3DPOOL pool = D3DPOOL_DEFAULT);
	//void ReleaseTextures();
	//HRESULT LoadMeshes(GetFilePathCallback);
	//HRESULT LoadCameras();
	//HRESULT LoadLights();

#endif