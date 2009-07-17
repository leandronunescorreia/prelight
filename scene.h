#ifndef _SCENE_H_
#define _SCENE_H_
#include "dxstdafx.h"
#include <vector>
#include <map>
#include <string>
#include "math.h"

////smart pointer to simplify freeing of temporary heap allocation
//template<class T> class Ptr {
//public:
//    Ptr(unsigned int n) { m_Ptr = (n ? new T[n] : 0); }
//    ~Ptr() { if (m_Ptr) delete [] m_Ptr; }
//    T& operator[](unsigned int i) { return m_Ptr[i]; }
//private:
//    T* m_Ptr;
//};

struct Vertex {
    
    vec3     pos;   
    vec2     texcoord;   
    D3DCOLOR color;      
    vec3     normal;     
    vec3     tangent;    
    vec3     bitangent;  

    Vertex() {}
	Vertex( const vec3& pos ) : pos(pos) {}
	Vertex( const vec3& pos, D3DCOLOR color ) : pos(pos), color(color) {}
	Vertex( const vec3& pos, const vec2& texcoord, D3DCOLOR color ) : pos(pos), texcoord(texcoord), color(color) {}
};

class Model
{
public:
    Model : mMesh(NULL), mMaterial(NULL) ();
    Model(const std::string& name, const mat4& worldMatrix, const Mesh* mesh, const Material* material);
    ~Model();

    bool Draw();

    std::string         mName;
    mat4                mWorldMatrix;
    Mesh *              mMesh;
    Material *          mMaterial;
}

class Material
{
public:
    Material() : mDiffuseTexture(NULL), mNormalMap(NULL) {};
    Material(const std::string& name, const vec4& diffuse, const vec4& specular, const vec4& shininess);
    ~Material() {};

    std::string         mName;

    vec4   mDiffuse;        
    vec4   mSpecular;       
    vec4   mShininess;      ///< specular exponent

    std::string         mDiffuseName, mNormalName;
    IDirect3DTexture9*  mDiffuseTexture, mNormalMap;    ///< Device resources.
}

class Mesh
{
public:
    Mesh() : mVertexBuffer(NULL), mIndexBuffer(NULL) {};
    Mesh(const std::string& name) : mVertexBuffer(NULL), mIndexBuffer(NULL) {};
    ~Mesh() { Free(); };

    bool CreateBuffer();
    bool FreeBuffer() { SAFE_RELEASE(mVertexBuffer); SAFE_RELEASE(mIndexBuffer); }
    bool DrawPrimitive() const;


    std::string                 mName;

    std::vector<Vertex>         mVertices;
    std::vector<unsigned int>   mIndices;
    
    /// device resources
    IDirect3DVertexBuffer9*     mVertexBuffer;
    IDirect3DIndexBuffer9*      mIndexBuffer;
};

class Light {
public:
    static Light* CreateSunLight(const char* name, const vec3& direction, const vec4& color);
    static Light* CreateOmniLight(const char* name, const vec3& pos, float attenuStart, float attenuEnd, const vec4& color);
    static Light* CreateSpotLight(const char* name, const vec3& pos, );
    AddSpotLight(Vec3^ pos, Vec3^ anglesDeg, float attenStart, float attenEnd, float fov_x, float fov_y, float softness, RGBA^ color, bool castShadows, int shadowmapResolution)

    enum LightType
    {
        LT_SUNLIGHT,
        LT_OMNI,
        LT_SPOTLIGHT,
    };

    
    std::string     mName;
    LightType       mType;
    vec4            mColor;
    mat4            mWorldMatrix;
    float           mFarAttenuationStart, mFarAttenuationEnd;
    float           mFovX, mFovY;       ///< Only for spotlight.
    float           mSoftness;          ///< Ratio of the spotlight's penumbra.

private:
    Light() {};
};


class Scene {
public:
	Scene();
	~Scene();

    void Reset();
    bool Load(const std::string& fileName);      // Load scene data from the scene file.
    void Free();                                 // Clear scene data and device resources.
    

	bool Draw();                                 // Render current scene data by using RenderDevice.

    float mTime;
};

#endif
