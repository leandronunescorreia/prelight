#include "math.h"

mat3::mat3()
{
}

mat3::mat3(const float* array)
{
    memcpy(mat_array, array, sizeof(float) * 9);
}

mat3::mat3(const mat3 & M)
{
    memcpy(mat_array, M.mat_array, sizeof(float) * 9);
}

mat4::mat4()
{
}

mat4::mat4(const float* array)
{
    memcpy(mat_array, array, sizeof(float) * 16);
}

mat4::mat4(const mat4& M)
{
    memcpy(mat_array, M.mat_array, sizeof(float) * 16);
}

vec3 & cross(vec3 & u, const vec3 & v, const vec3 & w)
{
    u.x = v.y*w.z - v.z*w.y;
    u.y = v.z*w.x - v.x*w.z;
    u.z = v.x*w.y - v.y*w.x;
    return u;
}



float & dot(float& u, const vec3& v, const vec3& w)
{
    u = v.x*w.x + v.y*w.y + v.z*w.z;
    return u;
}

float dot(const vec3& v, const vec3& w)
{
    return v.x*w.x + v.y*w.y + v.z*w.z;
}

float & dot(float& u, const vec4& v, const vec4& w)
{
    u = v.x*w.x + v.y*w.y + v.z*w.z + v.w*w.w;
    return u;
}

float dot(const vec4& v, const vec4& w)
{
    return v.x*w.x + v.y*w.y + v.z*w.z + v.w*w.w;
}

float & dot(float& u, const vec3& v, const vec4& w)
{
    u = v.x*w.x + v.y*w.y + v.z*w.z;
    return u;
}

float dot(const vec3& v, const vec4& w)
{
    return v.x*w.x + v.y*w.y + v.z*w.z;
}

float & dot(float& u, const vec4& v, const vec3& w)
{
    u = v.x*w.x + v.y*w.y + v.z*w.z;
    return u;
}

float dot(const vec4& v, const vec3& w)
{
    return v.x*w.x + v.y*w.y + v.z*w.z;
}

vec3 & reflect(vec3& r, const vec3& n, const vec3& l)
{
    float n_dot_l;
    n_dot_l = 2.0f * dot(n_dot_l,n,l);
    mult(r,l,-1.0f);
    madd(r,n,n_dot_l);
    return r;
}

vec3 & madd(vec3 & u, const vec3& v, const float& lambda)
{
    u.x += v.x*lambda;
    u.y += v.y*lambda;
    u.z += v.z*lambda;
    return u;
}

vec3 & mult(vec3 & u, const vec3& v, const float& lambda)
{
    u.x = v.x*lambda;
    u.y = v.y*lambda;
    u.z = v.z*lambda;
    return u;
}

vec3 & mult(vec3 & u, const vec3& v, const vec3& w)
{
    u.x = v.x*w.x;
    u.y = v.y*w.y;
    u.z = v.z*w.z;
    return u;
}

vec3 & sub(vec3 & u, const vec3& v, const vec3& w)
{
    u.x = v.x - w.x;
    u.y = v.y - w.y;
    u.z = v.z - w.z;
    return u;
}

vec3 & add(vec3 & u, const vec3& v, const vec3& w)
{
    u.x = v.x + w.x;
    u.y = v.y + w.y;
    u.z = v.z + w.z;
    return u;
}

void vec3::orthogonalize( const vec3& v )
{
	//  determine the orthogonal projection of this on v : dot( v , this ) * v
	//  and subtract it from this resulting in the orthogonalized this
	vec3 res = dot( v, vec3(x, y, z) ) * v;
	x -= res.x;
	y -= res.y;
	z -= res.y;
}

float vec3::normalize()
{
	float norm = sqrtf(x * x + y * y + z * z);
	if (norm > math_eps)
		norm = 1.0f / norm;
	else
		norm = 0;
	x *= norm;
	y *= norm;
	z *= norm;
	return norm;
}

vec2 & scale(vec2& u, const float s)
{
    u.x *= s;
    u.y *= s;
    return u;
}

vec3 & scale(vec3& u, const float s)
{
    u.x *= s;
    u.y *= s;
    u.z *= s;
    return u;
}

vec4 & scale(vec4& u, const float s)
{
    u.x *= s;
    u.y *= s;
    u.z *= s;
    u.w *= s;
    return u;
}

vec3 & mult(vec3& u, const mat3& M, const vec3& v)
{
    u.x = M.a00 * v.x + M.a01 * v.y + M.a02 * v.z;
    u.y = M.a10 * v.x + M.a11 * v.y + M.a12 * v.z;
    u.z = M.a20 * v.x + M.a21 * v.y + M.a22 * v.z;
    return u;
}

vec3 & mult(vec3& u, const vec3& v, const mat3& M)
{
    u.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z;
    u.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z;
    u.z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z;
    return u;
}

const vec3 operator*(const mat3& M, const vec3& v)
{
	vec3 u;
    u.x = M.a00 * v.x + M.a01 * v.y + M.a02 * v.z;
    u.y = M.a10 * v.x + M.a11 * v.y + M.a12 * v.z;
    u.z = M.a20 * v.x + M.a21 * v.y + M.a22 * v.z;
    return u;
}

const vec3 operator*(const vec3& v, const mat3& M)
{
	vec3 u;
    u.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z;
    u.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z;
    u.z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z;
    return u;
}

vec4 & mult(vec4& u, const mat4& M, const vec4& v)
{
    u.x = M.a00 * v.x + M.a01 * v.y + M.a02 * v.z + M.a03 * v.w;
    u.y = M.a10 * v.x + M.a11 * v.y + M.a12 * v.z + M.a13 * v.w;
    u.z = M.a20 * v.x + M.a21 * v.y + M.a22 * v.z + M.a23 * v.w;
    u.w = M.a30 * v.x + M.a31 * v.y + M.a32 * v.z + M.a33 * v.w;
    return u;
}

vec4 & mult(vec4& u, const vec4& v, const mat4& M)
{
    u.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30 * v.w;
    u.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31 * v.w;
    u.z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32 * v.w;
    u.w = M.a03 * v.x + M.a13 * v.y + M.a23 * v.z + M.a33 * v.w;
    return u;
}

const vec4 operator*(const mat4& M, const vec4& v)
{
	vec4 u;
    u.x = M.a00 * v.x + M.a01 * v.y + M.a02 * v.z + M.a03 * v.w;
    u.y = M.a10 * v.x + M.a11 * v.y + M.a12 * v.z + M.a13 * v.w;
    u.z = M.a20 * v.x + M.a21 * v.y + M.a22 * v.z + M.a23 * v.w;
    u.w = M.a30 * v.x + M.a31 * v.y + M.a32 * v.z + M.a33 * v.w;
    return u;
}

const vec4 operator*(const vec4& v, const mat4& M)
{
	vec4 u;
    u.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30 * v.w;
    u.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31 * v.w;
    u.z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32 * v.w;
    u.w = M.a03 * v.x + M.a13 * v.y + M.a23 * v.z + M.a33 * v.w;
    return u;
}

vec3 & mult_pos(vec3& u, const mat4& M, const vec3& v)
{
    float oow;
    float divider = v.x * M.a30 + v.y * M.a31 + v.z * M.a32 + M.a33;
    if (divider < math_eps && divider > -math_eps)
        oow = 1.0f ;
    else
        oow = 1.0f / divider;
    u.x = (M.a00 * v.x + M.a01 * v.y + M.a02 * v.z + M.a03) * oow;
    u.y = (M.a10 * v.x + M.a11 * v.y + M.a12 * v.z + M.a13) * oow;
    u.z = (M.a20 * v.x + M.a21 * v.y + M.a22 * v.z + M.a23) * oow;
    return u;
}

vec3 & mult_pos(vec3& u, const vec3& v, const mat4& M)
{
    float oow;
    float divider = v.x * M.a03 + v.y * M.a13 + v.z * M.a23 + M.a33;
    if (divider < math_eps && divider > -math_eps)
        oow = 1.0f ;
    else
        oow = 1.0f / divider;

    u.x = (M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30) * oow;
    u.y = (M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31) * oow;
    u.z = (M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32) * oow;
    return u;
}

vec3 & mult_dir(vec3& u, const mat4& M, const vec3& v)
{
    u.x = M.a00 * v.x + M.a01 * v.y + M.a02 * v.z;
    u.y = M.a10 * v.x + M.a11 * v.y + M.a12 * v.z;
    u.z = M.a20 * v.x + M.a21 * v.y + M.a22 * v.z;
    return u;
}

vec3 & mult_dir(vec3& u, const vec3& v, const mat4& M)
{
    u.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z;
    u.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z;
    u.z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z;
    return u;
}

vec3 & mult(vec3& u, const mat4& M, const vec3& v)
{
    u.x = M.a00 * v.x + M.a01 * v.y + M.a02 * v.z + M.a03;
    u.y = M.a10 * v.x + M.a11 * v.y + M.a12 * v.z + M.a13;
    u.z = M.a20 * v.x + M.a21 * v.y + M.a22 * v.z + M.a23;
    return u;
}

vec3 & mult(vec3& u, const vec3& v, const mat4& M)
{
    u.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30;
    u.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31;
    u.z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32;
    return u;
}

mat4 & add(mat4& A, const mat4& B)
{
    A.a00 += B.a00;
    A.a10 += B.a10;
    A.a20 += B.a20;
    A.a30 += B.a30;
    A.a01 += B.a01;
    A.a11 += B.a11;
    A.a21 += B.a21;
    A.a31 += B.a31;
    A.a02 += B.a02;
    A.a12 += B.a12;
    A.a22 += B.a22;
    A.a32 += B.a32;
    A.a03 += B.a03;
    A.a13 += B.a13;
    A.a23 += B.a23;
    A.a33 += B.a33;
    return A;
}

mat3 & add(mat3& A, const mat3& B)
{
    A.a00 += B.a00;
    A.a10 += B.a10;
    A.a20 += B.a20;
    A.a01 += B.a01;
    A.a11 += B.a11;
    A.a21 += B.a21;
    A.a02 += B.a02;
    A.a12 += B.a12;
    A.a22 += B.a22;
    return A;
}


// Computes C = A + B
mat4 & add(mat4 & C, const mat4 & A, const mat4 & B)
{
                                // If there is selfassignment involved
                                // we can't go without a temporary.
    if (&C == &A || &C == &B)
    {
        mat4 mTemp;

        mTemp.a00 = A.a00 + B.a00;
        mTemp.a01 = A.a01 + B.a01;
        mTemp.a02 = A.a02 + B.a02;
        mTemp.a03 = A.a03 + B.a03;
        mTemp.a10 = A.a10 + B.a10;
        mTemp.a11 = A.a11 + B.a11;
        mTemp.a12 = A.a12 + B.a12;
        mTemp.a13 = A.a13 + B.a13;
        mTemp.a20 = A.a20 + B.a20;
        mTemp.a21 = A.a21 + B.a21;
        mTemp.a22 = A.a22 + B.a22;
        mTemp.a23 = A.a23 + B.a23;
        mTemp.a30 = A.a30 + B.a30;
        mTemp.a31 = A.a31 + B.a31;
        mTemp.a32 = A.a32 + B.a32;
        mTemp.a33 = A.a33 + B.a33;
    
        C = mTemp;
    }
    else
    {
        C.a00 = A.a00 + B.a00;
        C.a01 = A.a01 + B.a01;
        C.a02 = A.a02 + B.a02;
        C.a03 = A.a03 + B.a03;
        C.a10 = A.a10 + B.a10;
        C.a11 = A.a11 + B.a11;
        C.a12 = A.a12 + B.a12;
        C.a13 = A.a13 + B.a13;
        C.a20 = A.a20 + B.a20;
        C.a21 = A.a21 + B.a21;
        C.a22 = A.a22 + B.a22;
        C.a23 = A.a23 + B.a23;
        C.a30 = A.a30 + B.a30;
        C.a31 = A.a31 + B.a31;
        C.a32 = A.a32 + B.a32;
        C.a33 = A.a33 + B.a33;
    }
    return C;
}

mat3 & add(mat3 & C, const mat3 & A, const mat3 & B)
{
                                // If there is selfassignment involved
                                // we can't go without a temporary.
    if (&C == &A || &C == &B)
    {
        mat3 mTemp;

        mTemp.a00 = A.a00 + B.a00;
        mTemp.a01 = A.a01 + B.a01;
        mTemp.a02 = A.a02 + B.a02;
        mTemp.a10 = A.a10 + B.a10;
        mTemp.a11 = A.a11 + B.a11;
        mTemp.a12 = A.a12 + B.a12;
        mTemp.a20 = A.a20 + B.a20;
        mTemp.a21 = A.a21 + B.a21;
        mTemp.a22 = A.a22 + B.a22;
   
        C = mTemp;
    }
    else
    {
        C.a00 = A.a00 + B.a00;
        C.a01 = A.a01 + B.a01;
        C.a02 = A.a02 + B.a02;
        C.a10 = A.a10 + B.a10;
        C.a11 = A.a11 + B.a11;
        C.a12 = A.a12 + B.a12;
        C.a20 = A.a20 + B.a20;
        C.a21 = A.a21 + B.a21;
        C.a22 = A.a22 + B.a22;
    }
    return C;
}


// C = A * B

// C.a00 C.a01 C.a02 C.a03   A.a00 A.a01 A.a02 A.a03   B.a00 B.a01 B.a02 B.a03
//                                                                            
// C.a10 C.a11 C.a12 C.a13   A.a10 A.a11 A.a12 A.a13   B.a10 B.a11 B.a12 B.a13
//                                                                         
// C.a20 C.a21 C.a22 C.a23   A.a20 A.a21 A.a22 A.a23   B.a20 B.a21 B.a22 B.a23  
//                                                                            
// C.a30 C.a31 C.a32 C.a33 = A.a30 A.a31 A.a32 A.a33 * B.a30 B.a31 B.a32 B.a33

mat4 & mult(mat4& C, const mat4& A, const mat4& B)
{
                                // If there is selfassignment involved
                                // we can't go without a temporary.
    if (&C == &A || &C == &B)
    {
        mat4 mTemp;

        mTemp.a00 = A.a00 * B.a00 + A.a01 * B.a10 + A.a02 * B.a20 + A.a03 * B.a30;
        mTemp.a10 = A.a10 * B.a00 + A.a11 * B.a10 + A.a12 * B.a20 + A.a13 * B.a30;
        mTemp.a20 = A.a20 * B.a00 + A.a21 * B.a10 + A.a22 * B.a20 + A.a23 * B.a30;
        mTemp.a30 = A.a30 * B.a00 + A.a31 * B.a10 + A.a32 * B.a20 + A.a33 * B.a30;
        mTemp.a01 = A.a00 * B.a01 + A.a01 * B.a11 + A.a02 * B.a21 + A.a03 * B.a31;
        mTemp.a11 = A.a10 * B.a01 + A.a11 * B.a11 + A.a12 * B.a21 + A.a13 * B.a31;
        mTemp.a21 = A.a20 * B.a01 + A.a21 * B.a11 + A.a22 * B.a21 + A.a23 * B.a31;
        mTemp.a31 = A.a30 * B.a01 + A.a31 * B.a11 + A.a32 * B.a21 + A.a33 * B.a31;
        mTemp.a02 = A.a00 * B.a02 + A.a01 * B.a12 + A.a02 * B.a22 + A.a03 * B.a32;
        mTemp.a12 = A.a10 * B.a02 + A.a11 * B.a12 + A.a12 * B.a22 + A.a13 * B.a32;
        mTemp.a22 = A.a20 * B.a02 + A.a21 * B.a12 + A.a22 * B.a22 + A.a23 * B.a32;
        mTemp.a32 = A.a30 * B.a02 + A.a31 * B.a12 + A.a32 * B.a22 + A.a33 * B.a32;
        mTemp.a03 = A.a00 * B.a03 + A.a01 * B.a13 + A.a02 * B.a23 + A.a03 * B.a33;
        mTemp.a13 = A.a10 * B.a03 + A.a11 * B.a13 + A.a12 * B.a23 + A.a13 * B.a33;
        mTemp.a23 = A.a20 * B.a03 + A.a21 * B.a13 + A.a22 * B.a23 + A.a23 * B.a33;
        mTemp.a33 = A.a30 * B.a03 + A.a31 * B.a13 + A.a32 * B.a23 + A.a33 * B.a33;
    
        C = mTemp;
    }
    else
    {
        C.a00 = A.a00 * B.a00 + A.a01 * B.a10 + A.a02 * B.a20 + A.a03 * B.a30;
        C.a10 = A.a10 * B.a00 + A.a11 * B.a10 + A.a12 * B.a20 + A.a13 * B.a30;
        C.a20 = A.a20 * B.a00 + A.a21 * B.a10 + A.a22 * B.a20 + A.a23 * B.a30;
        C.a30 = A.a30 * B.a00 + A.a31 * B.a10 + A.a32 * B.a20 + A.a33 * B.a30;
        C.a01 = A.a00 * B.a01 + A.a01 * B.a11 + A.a02 * B.a21 + A.a03 * B.a31;
        C.a11 = A.a10 * B.a01 + A.a11 * B.a11 + A.a12 * B.a21 + A.a13 * B.a31;
        C.a21 = A.a20 * B.a01 + A.a21 * B.a11 + A.a22 * B.a21 + A.a23 * B.a31;
        C.a31 = A.a30 * B.a01 + A.a31 * B.a11 + A.a32 * B.a21 + A.a33 * B.a31;
        C.a02 = A.a00 * B.a02 + A.a01 * B.a12 + A.a02 * B.a22 + A.a03 * B.a32;
        C.a12 = A.a10 * B.a02 + A.a11 * B.a12 + A.a12 * B.a22 + A.a13 * B.a32;
        C.a22 = A.a20 * B.a02 + A.a21 * B.a12 + A.a22 * B.a22 + A.a23 * B.a32;
        C.a32 = A.a30 * B.a02 + A.a31 * B.a12 + A.a32 * B.a22 + A.a33 * B.a32;
        C.a03 = A.a00 * B.a03 + A.a01 * B.a13 + A.a02 * B.a23 + A.a03 * B.a33;
        C.a13 = A.a10 * B.a03 + A.a11 * B.a13 + A.a12 * B.a23 + A.a13 * B.a33;
        C.a23 = A.a20 * B.a03 + A.a21 * B.a13 + A.a22 * B.a23 + A.a23 * B.a33;
        C.a33 = A.a30 * B.a03 + A.a31 * B.a13 + A.a32 * B.a23 + A.a33 * B.a33;
    }

    return C;
}

mat4 mat4::operator*(const mat4& B) const
{
    mat4 C;
    C.a00 = a00 * B.a00 + a01 * B.a10 + a02 * B.a20 + a03 * B.a30;
    C.a10 = a10 * B.a00 + a11 * B.a10 + a12 * B.a20 + a13 * B.a30;
    C.a20 = a20 * B.a00 + a21 * B.a10 + a22 * B.a20 + a23 * B.a30;
    C.a30 = a30 * B.a00 + a31 * B.a10 + a32 * B.a20 + a33 * B.a30;
    C.a01 = a00 * B.a01 + a01 * B.a11 + a02 * B.a21 + a03 * B.a31;
    C.a11 = a10 * B.a01 + a11 * B.a11 + a12 * B.a21 + a13 * B.a31;
    C.a21 = a20 * B.a01 + a21 * B.a11 + a22 * B.a21 + a23 * B.a31;
    C.a31 = a30 * B.a01 + a31 * B.a11 + a32 * B.a21 + a33 * B.a31;
    C.a02 = a00 * B.a02 + a01 * B.a12 + a02 * B.a22 + a03 * B.a32;
    C.a12 = a10 * B.a02 + a11 * B.a12 + a12 * B.a22 + a13 * B.a32;
    C.a22 = a20 * B.a02 + a21 * B.a12 + a22 * B.a22 + a23 * B.a32;
    C.a32 = a30 * B.a02 + a31 * B.a12 + a32 * B.a22 + a33 * B.a32;
    C.a03 = a00 * B.a03 + a01 * B.a13 + a02 * B.a23 + a03 * B.a33;
    C.a13 = a10 * B.a03 + a11 * B.a13 + a12 * B.a23 + a13 * B.a33;
    C.a23 = a20 * B.a03 + a21 * B.a13 + a22 * B.a23 + a23 * B.a33;
    C.a33 = a30 * B.a03 + a31 * B.a13 + a32 * B.a23 + a33 * B.a33;
    return C;
}

// C = A * B

// C.a00 C.a01 C.a02   A.a00 A.a01 A.a02   B.a00 B.a01 B.a02
//                                                          
// C.a10 C.a11 C.a12   A.a10 A.a11 A.a12   B.a10 B.a11 B.a12
//                                                          
// C.a20 C.a21 C.a22 = A.a20 A.a21 A.a22 * B.a20 B.a21 B.a22

mat3 & mult(mat3& C, const mat3& A, const mat3& B)
{
                                // If there is sel fassignment involved
                                // we can't go without a temporary.
    if (&C == &A || &C == &B)
    {
        mat3 mTemp;

        mTemp.a00 = A.a00 * B.a00 + A.a01 * B.a10 + A.a02 * B.a20;
        mTemp.a10 = A.a10 * B.a00 + A.a11 * B.a10 + A.a12 * B.a20;
        mTemp.a20 = A.a20 * B.a00 + A.a21 * B.a10 + A.a22 * B.a20;
        mTemp.a01 = A.a00 * B.a01 + A.a01 * B.a11 + A.a02 * B.a21;
        mTemp.a11 = A.a10 * B.a01 + A.a11 * B.a11 + A.a12 * B.a21;
        mTemp.a21 = A.a20 * B.a01 + A.a21 * B.a11 + A.a22 * B.a21;
        mTemp.a02 = A.a00 * B.a02 + A.a01 * B.a12 + A.a02 * B.a22;
        mTemp.a12 = A.a10 * B.a02 + A.a11 * B.a12 + A.a12 * B.a22;
        mTemp.a22 = A.a20 * B.a02 + A.a21 * B.a12 + A.a22 * B.a22;

        C = mTemp;
    }
    else
    {
        C.a00 = A.a00 * B.a00 + A.a01 * B.a10 + A.a02 * B.a20;
        C.a10 = A.a10 * B.a00 + A.a11 * B.a10 + A.a12 * B.a20;
        C.a20 = A.a20 * B.a00 + A.a21 * B.a10 + A.a22 * B.a20;
        C.a01 = A.a00 * B.a01 + A.a01 * B.a11 + A.a02 * B.a21;
        C.a11 = A.a10 * B.a01 + A.a11 * B.a11 + A.a12 * B.a21;
        C.a21 = A.a20 * B.a01 + A.a21 * B.a11 + A.a22 * B.a21;
        C.a02 = A.a00 * B.a02 + A.a01 * B.a12 + A.a02 * B.a22;
        C.a12 = A.a10 * B.a02 + A.a11 * B.a12 + A.a12 * B.a22;
        C.a22 = A.a20 * B.a02 + A.a21 * B.a12 + A.a22 * B.a22;
    }

    return C;
}


mat3 & transpose(mat3& A)
{
    float tmp;
    tmp = A.a01;
    A.a01 = A.a10;
    A.a10 = tmp;

    tmp = A.a02;
    A.a02 = A.a20;
    A.a20 = tmp;

    tmp = A.a12;
    A.a12 = A.a21;
    A.a21 = tmp;
    return A;
}

mat4 & transpose(mat4& A)
{
    float tmp;
    tmp = A.a01;
    A.a01 = A.a10;
    A.a10 = tmp;

    tmp = A.a02;
    A.a02 = A.a20;
    A.a20 = tmp;

    tmp = A.a03;
    A.a03 = A.a30;
    A.a30 = tmp;

    tmp = A.a12;
    A.a12 = A.a21;
    A.a21 = tmp;

    tmp = A.a13;
    A.a13 = A.a31;
    A.a31 = tmp;

    tmp = A.a23;
    A.a23 = A.a32;
    A.a32 = tmp;
    return A;
}

mat4 & transpose(mat4& B, const mat4& A)
{
    B.a00 = A.a00;
    B.a01 = A.a10;
    B.a02 = A.a20;
    B.a03 = A.a30;
    B.a10 = A.a01;
    B.a11 = A.a11;
    B.a12 = A.a21;
    B.a13 = A.a31;
    B.a20 = A.a02;
    B.a21 = A.a12;
    B.a22 = A.a22;
    B.a23 = A.a32;
    B.a30 = A.a03;
    B.a31 = A.a13;
    B.a32 = A.a23;
    B.a33 = A.a33;
    return B;
}

mat3 & transpose(mat3& B, const mat3& A)
{
    B.a00 = A.a00;
    B.a01 = A.a10;
    B.a02 = A.a20;
    B.a10 = A.a01;
    B.a11 = A.a11;
    B.a12 = A.a21;
    B.a20 = A.a02;
    B.a21 = A.a12;
    B.a22 = A.a22;
    return B;
}

/*
    calculate the determinent of a 2x2 matrix in the from

    | a1 a2 |
    | b1 b2 |

*/
float det2x2(float a1, float a2, float b1, float b2)
{
    return a1 * b2 - b1 * a2;
}

/*
    calculate the determinent of a 3x3 matrix in the from

    | a1 a2 a3 |
    | b1 b2 b3 |
    | c1 c2 c3 |

*/
float det3x3(float a1, float a2, float a3, 
                         float b1, float b2, float b3, 
                         float c1, float c2, float c3)
{
    return a1 * det2x2(b2, b3, c2, c3) - b1 * det2x2(a2, a3, c2, c3) + c1 * det2x2(a2, a3, b2, b3);
}

mat4 & invert(mat4& B, const mat4& A)
{
    float det,oodet;

    B.a00 =  det3x3(A.a11, A.a21, A.a31, A.a12, A.a22, A.a32, A.a13, A.a23, A.a33);
    B.a10 = -det3x3(A.a10, A.a20, A.a30, A.a12, A.a22, A.a32, A.a13, A.a23, A.a33);
    B.a20 =  det3x3(A.a10, A.a20, A.a30, A.a11, A.a21, A.a31, A.a13, A.a23, A.a33);
    B.a30 = -det3x3(A.a10, A.a20, A.a30, A.a11, A.a21, A.a31, A.a12, A.a22, A.a32);

    B.a01 = -det3x3(A.a01, A.a21, A.a31, A.a02, A.a22, A.a32, A.a03, A.a23, A.a33);
    B.a11 =  det3x3(A.a00, A.a20, A.a30, A.a02, A.a22, A.a32, A.a03, A.a23, A.a33);
    B.a21 = -det3x3(A.a00, A.a20, A.a30, A.a01, A.a21, A.a31, A.a03, A.a23, A.a33);
    B.a31 =  det3x3(A.a00, A.a20, A.a30, A.a01, A.a21, A.a31, A.a02, A.a22, A.a32);

    B.a02 =  det3x3(A.a01, A.a11, A.a31, A.a02, A.a12, A.a32, A.a03, A.a13, A.a33);
    B.a12 = -det3x3(A.a00, A.a10, A.a30, A.a02, A.a12, A.a32, A.a03, A.a13, A.a33);
    B.a22 =  det3x3(A.a00, A.a10, A.a30, A.a01, A.a11, A.a31, A.a03, A.a13, A.a33);
    B.a32 = -det3x3(A.a00, A.a10, A.a30, A.a01, A.a11, A.a31, A.a02, A.a12, A.a32);

    B.a03 = -det3x3(A.a01, A.a11, A.a21, A.a02, A.a12, A.a22, A.a03, A.a13, A.a23);
    B.a13 =  det3x3(A.a00, A.a10, A.a20, A.a02, A.a12, A.a22, A.a03, A.a13, A.a23);
    B.a23 = -det3x3(A.a00, A.a10, A.a20, A.a01, A.a11, A.a21, A.a03, A.a13, A.a23);
    B.a33 =  det3x3(A.a00, A.a10, A.a20, A.a01, A.a11, A.a21, A.a02, A.a12, A.a22);

    det = (A.a00 * B.a00) + (A.a01 * B.a10) + (A.a02 * B.a20) + (A.a03 * B.a30);

                                // The following divions goes unchecked for division
                                // by zero. We should consider throwing an exception
                                // if det < eps.
    oodet = 1.0f / det;

    B.a00 *= oodet;
    B.a10 *= oodet;
    B.a20 *= oodet;
    B.a30 *= oodet;

    B.a01 *= oodet;
    B.a11 *= oodet;
    B.a21 *= oodet;
    B.a31 *= oodet;

    B.a02 *= oodet;
    B.a12 *= oodet;
    B.a22 *= oodet;
    B.a32 *= oodet;

    B.a03 *= oodet;
    B.a13 *= oodet;
    B.a23 *= oodet;
    B.a33 *= oodet;

    return B;
}

mat4 & invert_rot_trans(mat4& B, const mat4& A)
{
    B.a00 = A.a00;
    B.a10 = A.a01;
    B.a20 = A.a02;
    B.a30 = A.a30;
    B.a01 = A.a10;
    B.a11 = A.a11;
    B.a21 = A.a12;
    B.a31 = A.a31;
    B.a02 = A.a20;
    B.a12 = A.a21;
    B.a22 = A.a22;
    B.a32 = A.a32;
    B.a03 = - (A.a00 * A.a03 + A.a10 * A.a13 + A.a20 * A.a23);
    B.a13 = - (A.a01 * A.a03 + A.a11 * A.a13 + A.a21 * A.a23);
    B.a23 = - (A.a02 * A.a03 + A.a12 * A.a13 + A.a22 * A.a23);
    B.a33 = A.a33;
    return B;
}

float det(const mat3& A)
{
    return det3x3(A.a00, A.a01, A.a02, 
                 A.a10, A.a11, A.a12, 
                 A.a20, A.a21, A.a22);
}

mat3 & invert(mat3& B, const mat3& A)
{
    float det,oodet;

    B.a00 =  (A.a11 * A.a22 - A.a21 * A.a12);
    B.a10 = -(A.a10 * A.a22 - A.a20 * A.a12);
    B.a20 =  (A.a10 * A.a21 - A.a20 * A.a11);
    B.a01 = -(A.a01 * A.a22 - A.a21 * A.a02);
    B.a11 =  (A.a00 * A.a22 - A.a20 * A.a02);
    B.a21 = -(A.a00 * A.a21 - A.a20 * A.a01);
    B.a02 =  (A.a01 * A.a12 - A.a11 * A.a02);
    B.a12 = -(A.a00 * A.a12 - A.a10 * A.a02);
    B.a22 =  (A.a00 * A.a11 - A.a10 * A.a01);

    det = (A.a00 * B.a00) + (A.a01 * B.a10) + (A.a02 * B.a20);
    
    oodet = 1.0f / det;

    B.a00 *= oodet; B.a01 *= oodet; B.a02 *= oodet;
    B.a10 *= oodet; B.a11 *= oodet; B.a12 *= oodet;
    B.a20 *= oodet; B.a21 *= oodet; B.a22 *= oodet;
    return B;
}

vec2 & normalize(vec2& u)
{
    float norm = sqrtf(u.x * u.x + u.y * u.y);
    if (norm > math_eps)
        norm = 1.0f / norm;
    else
        norm = 0;
    return scale(u,norm); 
}

vec3 & normalize(vec3& u)
{
    float norm = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z);
    if (norm > math_eps)
        norm = 1.0f / norm;
    else
        norm = 0;
    return scale(u,norm); 
}

vec4 & normalize(vec4& u)
{
    float norm = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z + u.w * u.w);
    if (norm > math_eps)
        norm = 1.0f / norm;
    else
        norm = 0;
    return scale(u,norm); 
}

quat & normalize(quat & p)
{
    float norm = sqrtf(p.x * p.x + p.y * p.y + p.z * p.z + p.w * p.w);
    if (norm > math_eps)
        norm = 1.0f / norm;
    else
        norm = 0;
    p.x *= norm;
    p.y *= norm;
    p.z *= norm;
    p.w *= norm;
    return p; 
}

mat4 & look_at(mat4& M, const vec3& eye, const vec3& center, const vec3& up)
{
    vec3 x, y, z;

    // make rotation matrix

    // Z vector
    z.x = eye.x - center.x;
    z.y = eye.y - center.y;
    z.z = eye.z - center.z;
    normalize(z);

    // Y vector
    y.x = up.x;
    y.y = up.y;
    y.z = up.z;

    // X vector = Y cross Z
    cross(x,y,z);

    // Recompute Y = Z cross X
    cross(y,z,x);

    // cross product gives area of parallelogram, which is < 1.0 for
    // non-perpendicular unit-length vectors; so normalize x, y here
    normalize(x);
    normalize(y);

    M.a00 = x.x; M.a01 = x.y; M.a02 = x.z; M.a03 = -x.x * eye.x - x.y * eye.y - x.z*eye.z;
    M.a10 = y.x; M.a11 = y.y; M.a12 = y.z; M.a13 = -y.x * eye.x - y.y * eye.y - y.z*eye.z;
    M.a20 = z.x; M.a21 = z.y; M.a22 = z.z; M.a23 = -z.x * eye.x - z.y * eye.y - z.z*eye.z;
    M.a30 = 0; M.a31 = 0; M.a32 = 0; M.a33 = 1.0f;
    return M;
}

mat4 & frustum(mat4& M, const float l, const float r, const float b, 
               const float t, const float n, const float f)
{
    M.a00 = (2.0f*n) / (r-l);
    M.a10 = 0.0;
    M.a20 = 0.0;
    M.a30 = 0.0;

    M.a01 = 0.0;
    M.a11 = (2.0f*n) / (t-b);
    M.a21 = 0.0;
    M.a31 = 0.0;

    M.a02 = (r+l) / (r-l);
    M.a12 = (t+b) / (t-b);
    M.a22 = -(f+n) / (f-n);
    M.a32 = -1.0f;

    M.a03 = 0.0;
    M.a13 = 0.0;
    M.a23 = -(2.0f*f*n) / (f-n);
    M.a33 = 0.0;
    return M;
}

mat4 & perspective(mat4& M, const float fovy, const float aspect, const float n, const float f)
{
    float xmin, xmax, ymin, ymax;

    ymax = n * tanf(fovy * math_to_rad * 0.5f);
    ymin = -ymax;

    xmin = ymin * aspect;
    xmax = ymax * aspect;

    return frustum(M, xmin, xmax, ymin, ymax, n, f);
}

extern mat4 & ortho(mat4 & M, const float left, 
                              const float right, 
                              const float bottom, 
                              const float top,
                              const float n,
                              const float f)
{
    M.a00 = 2.0f / (right - left);
    M.a01 = 0;
    M.a02 = 0;
    M.a03 = - (right + left) / (right - left);
    M.a10 = 0;
    M.a11 = 2.0f / (top - bottom);
    M.a12 = 0;
    M.a13 = - (top + bottom) / (top - bottom);
    M.a20 = 0;
    M.a21 = 0;
    M.a22 = - 2.0f / (f - n);
    M.a23 = - (f + n) / (f - n);
    M.a30 = 0;
    M.a31 = 0;
    M.a32 = 0;
    M.a33 = 1.0f;
    return M;
}

const quat quat::Identity(0, 0, 0, 1);

quat::quat()
{
}

quat::quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

quat::quat(const quat& quat)
{
	x = quat.x;
	y = quat.y;
	z = quat.z;
	w = quat.w;
}

quat::quat(const vec3& axis, float angle)
{
	float len = axis.norm();
	if (len) {
		float invLen = 1 / len;
		float angle2 = angle / 2;
		float scale = sinf(angle2) * invLen;
		x = scale * axis[0];
		y = scale * axis[1];
		z = scale * axis[2];
		w = cosf(angle2);
	}
}

quat::quat(const mat3& rot)
{
	FromMatrix(rot);
}

quat& quat::operator=(const quat& quat)
{
	x = quat.x;
	y = quat.y;
	z = quat.z;
	w = quat.w;
	return *this;
}

quat quat::Inverse()
{
	return quat(- x, - y, - z, w);
}

void quat::Normalize()
{
	float len = sqrtf(x * x + y * y + z * z + w * w);
	if (len > 0) {
		float invLen = 1 / len;
		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;
	}
}

void quat::FromMatrix(const mat3& mat)
{
	float trace = mat(0, 0) + mat(1, 1) + mat(2, 2);
	if (trace > 0) 
    {
		float scale = sqrtf(trace + 1.0f);
		w = 0.5f * scale;
		scale = 0.5f / scale;
		x = scale * (mat(2, 1) - mat(1, 2));
		y = scale * (mat(0, 2) - mat(2, 0));
		z = scale * (mat(1, 0) - mat(0, 1));
	}
	else 
    {
		static int next[] = { 1, 2, 0 };
		int i = 0;
		if (mat(1, 1) > mat(0, 0))
			i = 1;
		if (mat(2, 2) > mat(i, i))
			i = 2;
		int j = next[i];
		int k = next[j];
		float scale = sqrtf(mat(i, i) - mat(j, j) - mat(k, k) + 1);
		float* q[] = { &x, &y, &z };
		*q[i] = 0.5f * scale;
		scale = 0.5f / scale;
		w = scale * (mat(k, j) - mat(j, k));
		*q[j] = scale * (mat(j, i) + mat(i, j));
		*q[k] = scale * (mat(k, i) + mat(i, k));
	}
}

void quat::ToMatrix(mat3& mat) const
{
	float x2 = x * 2;
	float y2 = y * 2;
	float z2 = z * 2;
	float wx = x2 * w;
	float wy = y2 * w;
	float wz = z2 * w;
	float xx = x2 * x;
	float xy = y2 * x;
	float xz = z2 * x;
	float yy = y2 * y;
	float yz = z2 * y;
	float zz = z2 * z;
	mat(0, 0) = 1 - (yy + zz);
	mat(0, 1) = xy - wz;
	mat(0, 2) = xz + wy;
	mat(1, 0) = xy + wz;
	mat(1, 1) = 1 - (xx + zz);
	mat(1, 2) = yz - wx;
	mat(2, 0) = xz - wy;
	mat(2, 1) = yz + wx;
	mat(2, 2) = 1 - (xx + yy);
}

const quat operator*(const quat& p, const quat& q)
{
	return quat(
		p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y,
		p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z,
		p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x,
		p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z
	);
}

quat& quat::operator*=(const quat& q)
{
	*this = *this * q;
	return *this;
}

mat3 & quat_2_mat(mat3& M, const quat& q)
{
	q.ToMatrix(M);
    return M;
}

quat & mat_2_quat(quat& q, const mat3& M)
{
	q.FromMatrix(M);
    return q;
} 

quat & mat_2_quat(quat& q, const mat4& M)
{
	mat3 m;
	M.get_rot(m);
	q.FromMatrix(m);
    return q;
} 

/*
    Given an axis and angle, compute quaternion.
 */
quat & axis_to_quat(quat& q, const vec3& a, const float phi)
{
    vec3 tmp(a.x, a.y, a.z);

    normalize(tmp);
	float s = sinf(phi/2.0f);
    q.x = s * tmp.x;
    q.y = s * tmp.y;
    q.z = s * tmp.z;
    q.w = cosf(phi/2.0f);
    return q;
}

quat & conj(quat & p)
{
    p.x = -p.x;
    p.y = -p.y;
    p.z = -p.z;
    return p;
}

 quat & conj(quat& p, const quat& q)
{
    p.x = -q.x;
    p.y = -q.y;
    p.z = -q.z;
    p.w = q.w;
    return p;
}

 quat & add_quats(quat& p, const quat& q1, const quat& q2)
{
    quat t1, t2;

    t1 = q1;
    t1.x *= q2.w;
    t1.y *= q2.w;
    t1.z *= q2.w;

    t2 = q2;
    t2.x *= q1.w;
    t2.y *= q1.w;
    t2.z *= q1.w;

    p.x = (q2.y * q1.z) - (q2.z * q1.y) + t1.x + t2.x;
    p.y = (q2.z * q1.x) - (q2.x * q1.z) + t1.y + t2.y;
    p.z = (q2.x * q1.y) - (q2.y * q1.x) + t1.z + t2.z;
    p.w = q1.w * q2.w - (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z);

    return p;
}

float & dot(float& s, const quat& q1, const quat& q2)
{
    s = q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
    return s;
}

float dot(const quat& q1, const quat& q2)
{
    return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
}

#ifndef acosf
#define acosf acos
#endif

quat & slerp_quats(quat & p, float s, const quat & q1, const quat & q2)
{
    float cosine = dot(q1, q2);
	if (cosine < -1)
		cosine = -1;
	else if (cosine > 1)
		cosine = 1;
    float angle = (float)acosf(cosine);
    if (fabs(angle) < math_eps) {
		p = q1;
        return p;
	}
    float sine = sinf(angle);
    float sineInv = 1.0f / sine;
    float c1 = sinf((1.0f - s) * angle) * sineInv;
    float c2 = sinf(s * angle) * sineInv;
	p.x = c1 * q1.x + c2 * q2.x;
	p.y = c1 * q1.y + c2 * q2.y;
	p.z = c1 * q1.z + c2 * q2.z;
	p.w = c1 * q1.w + c2 * q2.w;
    return p;
}

const int HALF_RAND = (RAND_MAX / 2);

 float math_random()
{
	return ((float)(rand() - HALF_RAND) / (float)HALF_RAND);
}

// v is normalized
// theta in radians
void mat3::set_rot(const float& theta, const vec3& v) 
{
    float ct = float(cos(theta));
    float st = float(sin(theta));

    float xx = v.x * v.x;
    float yy = v.y * v.y;
    float zz = v.z * v.z;
    float xy = v.x * v.y;
    float xz = v.x * v.z;
    float yz = v.y * v.z;

    a00 = xx + ct*(1-xx);
    a01 = xy + ct*(-xy) + st*-v.z;
    a02 = xz + ct*(-xz) + st*v.y;

    a10 = xy + ct*(-xy) + st*v.z;
    a11 = yy + ct*(1-yy);
    a12 = yz + ct*(-yz) + st*-v.x;

    a20 = xz + ct*(-xz) + st*-v.y;
    a21 = yz + ct*(-yz) + st*v.x;
    a22 = zz + ct*(1-zz);
}

void mat3::set_rot(const vec3& u, const vec3& v)
{
    float phi;
    float h;
    float lambda;
    vec3 w;

    cross(w,u,v);
    dot(phi,u,v);
    dot(lambda,w,w);
    if (lambda > math_eps)
        h = (1.0f - phi) / lambda;
    else
        h = lambda;
    
    float hxy = w.x * w.y * h;
    float hxz = w.x * w.z * h;
    float hyz = w.y * w.z * h;

    a00 = phi + w.x * w.x * h;
    a01 = hxy - w.z;
    a02 = hxz + w.y;

    a10 = hxy + w.z;
    a11 = phi + w.y * w.y * h;
    a12 = hyz - w.x;

    a20 = hxz - w.y;
    a21 = hyz + w.x;
    a22 = phi + w.z * w.z * h;
}

float mat3::norm_one()
{
    float sum, max = 0;
    sum = fabs(a00) + fabs(a10) + fabs(a20);
    if (max < sum)
        max = sum;
    sum = fabs(a01) + fabs(a11) + fabs(a21);
    if (max < sum)
        max = sum;
    sum = fabs(a02) + fabs(a12) + fabs(a22);
    if (max < sum)
        max = sum;
    return max;
}

float mat3::norm_inf()
{
    float sum, max = 0;
    sum = fabs(a00) + fabs(a01) + fabs(a02);
    if (max < sum)
        max = sum;
    sum = fabs(a10) + fabs(a11) + fabs(a12);
    if (max < sum)
        max = sum;
    sum = fabs(a20) + fabs(a21) + fabs(a22);
    if (max < sum)
        max = sum;
    return max;
}

void mat4::set_rot(const quat& q)
{
	mat3 m;
	q.ToMatrix(m);
	set_rot(m);
}

// v is normalized
// theta in radians
void mat4::set_rot(const float& theta, const vec3& v) 
{
    float ct = float(cos(theta));
    float st = float(sin(theta));

    float xx = v.x * v.x;
    float yy = v.y * v.y;
    float zz = v.z * v.z;
    float xy = v.x * v.y;
    float xz = v.x * v.z;
    float yz = v.y * v.z;

    a00 = xx + ct*(1-xx);
    a01 = xy + ct*(-xy) + st*-v.z;
    a02 = xz + ct*(-xz) + st*v.y;

    a10 = xy + ct*(-xy) + st*v.z;
    a11 = yy + ct*(1-yy);
    a12 = yz + ct*(-yz) + st*-v.x;

    a20 = xz + ct*(-xz) + st*-v.y;
    a21 = yz + ct*(-yz) + st*v.x;
    a22 = zz + ct*(1-zz);
}

void mat4::set_rot(const vec3& u, const vec3& v)
{
    float phi;
    float h;
    float lambda;
    vec3 w;

    cross(w,u,v);
    dot(phi,u,v);
    dot(lambda,w,w);
    if (lambda > math_eps)
        h = (1.0f - phi) / lambda;
    else
        h = lambda;
    
    float hxy = w.x * w.y * h;
    float hxz = w.x * w.z * h;
    float hyz = w.y * w.z * h;

    a00 = phi + w.x * w.x * h;
    a01 = hxy - w.z;
    a02 = hxz + w.y;

    a10 = hxy + w.z;
    a11 = phi + w.y * w.y * h;
    a12 = hyz - w.x;

    a20 = hxz - w.y;
    a21 = hyz + w.x;
    a22 = phi + w.z * w.z * h;
}

void mat4::set_rot(const mat3& M)
{
    // copy the 3x3 rotation block
    a00 = M.a00; a10 = M.a10; a20 = M.a20;
    a01 = M.a01; a11 = M.a11; a21 = M.a21;
    a02 = M.a02; a12 = M.a12; a22 = M.a22;
}

void mat4::set_scale(const vec3& s)
{
	a00 = s.x;
	a11 = s.y;
	a22 = s.z;
}

vec3& mat4::get_scale(vec3& s) const
{
	s.x = a00;
	s.y = a11;
	s.z = a22;
	return s;
}

void mat4::set_translation(const vec3& t)
{
    a03 = t.x;
    a13 = t.y;
    a23 = t.z;
}

vec3 & mat4::get_translation(vec3& t) const
{
    t.x = a03;
    t.y = a13;
    t.z = a23;
    return t;
}

mat3 & mat4::get_rot(mat3& M) const
{
    // assign the 3x3 rotation block
    M.a00 = a00; M.a10 = a10; M.a20 = a20;
    M.a01 = a01; M.a11 = a11; M.a21 = a21;
    M.a02 = a02; M.a12 = a12; M.a22 = a22;
    return M;
}

quat & mat4::get_rot(quat& q) const
{
	mat3 m;
	get_rot(m);
	q.FromMatrix(m);
    return q;
}

mat4 & negate(mat4 & M)
{
    for (int i = 0; i < 16; ++i)
        M.mat_array[i]= -M.mat_array[i];
    return M;
}

mat3 & negate(mat3 & M)
{
    for (int i = 0; i < 9; ++i)
        M.mat_array[i]= -M.mat_array[i];
    return M;
}

mat3& tangent_basis(mat3& basis, const vec3& v0, const vec3& v1, const vec3& v2, const vec2& t0, const vec2& t1, const vec2& t2, const vec3 & n)
{
    vec3 cp;
    vec3 e0(v1.x - v0.x, t1.s - t0.s, t1.t - t0.t);
    vec3 e1(v2.x - v0.x, t2.s - t0.s, t2.t - t0.t);

    cross(cp,e0,e1);
    if ( fabs(cp.x) > math_eps)
    {
        basis.a00 = -cp.y / cp.x;        
        basis.a10 = -cp.z / cp.x;
    }

    e0.x = v1.y - v0.y;
    e1.x = v2.y - v0.y;

    cross(cp,e0,e1);
    if ( fabs(cp.x) > math_eps)
    {
        basis.a01 = -cp.y / cp.x;        
        basis.a11 = -cp.z / cp.x;
    }

    e0.x = v1.z - v0.z;
    e1.x = v2.z - v0.z;

    cross(cp,e0,e1);
    if ( fabs(cp.x) > math_eps)
    {
        basis.a02 = -cp.y / cp.x;        
        basis.a12 = -cp.z / cp.x;
    }

    // tangent...
    float oonorm = 1.0f / sqrtf(basis.a00 * basis.a00 + basis.a01 * basis.a01 + basis.a02 * basis.a02);
    basis.a00 *= oonorm;
    basis.a01 *= oonorm;
    basis.a02 *= oonorm;

    // binormal...
    oonorm = 1.0f / sqrtf(basis.a10 * basis.a10 + basis.a11 * basis.a11 + basis.a12 * basis.a12);
    basis.a10 *= oonorm;
    basis.a11 *= oonorm;
    basis.a12 *= oonorm;

    // normal...
    // compute the cross product TxB
    basis.a20 = basis.a01*basis.a12 - basis.a02*basis.a11;
    basis.a21 = basis.a02*basis.a10 - basis.a00*basis.a12;
    basis.a22 = basis.a00*basis.a11 - basis.a01*basis.a10;

    oonorm = 1.0f / sqrtf(basis.a20 * basis.a20 + basis.a21 * basis.a21 + basis.a22 * basis.a22);
    basis.a20 *= oonorm;
    basis.a21 *= oonorm;
    basis.a22 *= oonorm;

    // Gram-Schmidt orthogonalization process for B
    // compute the cross product B=NxT to obtain 
    // an orthogonal basis
    basis.a10 = basis.a21*basis.a02 - basis.a22*basis.a01;
    basis.a11 = basis.a22*basis.a00 - basis.a20*basis.a02;
    basis.a12 = basis.a20*basis.a01 - basis.a21*basis.a00;

    if (basis.a20 * n.x + basis.a21 * n.y + basis.a22 * n.z < 0)
    {
        basis.a20 = -basis.a20;
        basis.a21 = -basis.a21;
        basis.a22 = -basis.a22;
    }
    return basis;
}

/*
 * Project an x,y pair onto a sphere of radius r OR a hyperbolic sheet
 * if we are away from the center of the sphere.
 */
 float tb_project_to_sphere(float r, float x, float y)
{
    float d, t, z;

    d = sqrtf(x*x + y*y);
    if (d < r * 0.70710678118654752440) {    /* Inside sphere */
        z = sqrtf(r*r - d*d);
    } else {           /* On hyperbola */
        t = r / (float)1.41421356237309504880;
        z = t*t / d;
    }
    return z;
}

/*
 * Ok, simulate a track-ball.  Project the points onto the virtual
 * trackball, then figure out the axis of rotation, which is the cross
 * product of P1 P2 and O P1 (O is the center of the ball, 0,0,0)
 * Note:  This is a deformed trackball-- is a trackball in the center,
 * but is deformed into a hyperbolic sheet of rotation away from the
 * center.  This particular function was chosen after trying out
 * several variations.
 *
 * It is assumed that the arguments to this routine are in the range
 * (-1.0 ... 1.0)
 */
quat & trackball(quat& q, vec2& pt1, vec2& pt2, float trackballsize)
{
    vec3 a; // Axis of rotation
    float phi;  // how much to rotate about axis
    vec3 d;
    float t;

    if (pt1.x == pt2.x && pt1.y == pt2.y) 
    {
        // Zero rotation
        q = quat_id;
        return q;
    }

    // First, figure out z-coordinates for projection of P1 and P2 to
    // deformed sphere
    vec3 p1(pt1.x,pt1.y,tb_project_to_sphere(trackballsize,pt1.x,pt1.y));
    vec3 p2(pt2.x,pt2.y,tb_project_to_sphere(trackballsize,pt2.x,pt2.y));

    //  Now, we want the cross product of P1 and P2
    cross(a,p1,p2);

    //  Figure out how much to rotate around that axis.
    d.x = p1.x - p2.x;
    d.y = p1.y - p2.y;
    d.z = p1.z - p2.z;
    t = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z) / (trackballsize);

    // Avoid problems with out-of-control values...

    if (t > 1.0f)
        t = 1.0f;
    if (t < -1.0f) 
        t = -1.0f;
    phi = 2.0f * float(asin(t));
    axis_to_quat(q,a,phi);
    return q;
}

vec3& cube_map_normal(int i, int x, int y, int cubesize, vec3& v)
{
    float s, t, sc, tc;
    s = (float(x) + 0.5f) / float(cubesize);
    t = (float(y) + 0.5f) / float(cubesize);
    sc = s * 2.0f - 1.0f;
    tc = t * 2.0f - 1.0f;

    switch (i) 
    {
        case 0:
            v.x = 1.0f;
            v.y = -tc;
            v.z = -sc;
            break;
        case 1:
            v.x = -1.0f;
            v.y = -tc;
            v.z = sc;
            break;
        case 2:
            v.x = sc;
            v.y = 1.0f;
            v.z = tc;
            break;
        case 3:
            v.x = sc;
            v.y = -1.0f;
            v.z = -tc;
            break;
        case 4:
            v.x = sc;
            v.y = -tc;
            v.z = 1.0f;
            break;
        case 5:
            v.x = -sc;
            v.y = -tc;
            v.z = -1.0f;
            break;
    }
    normalize(v);
    return v;
}

// computes the area of a triangle
float math_area(const vec3& v1, const vec3& v2, const vec3& v3)
{
    vec3 cp_sum;
    vec3 cp;
    cross(cp_sum, v1, v2);
    cp_sum += cross(cp, v2, v3);
    cp_sum += cross(cp, v3, v1);
    return math_norm(cp_sum) * 0.5f; 
}

// computes the perimeter of a triangle
float math_perimeter(const vec3& v1, const vec3& v2, const vec3& v3)
{
    float perim;
    vec3 diff;
    sub(diff, v1, v2);
    perim = math_norm(diff);
    sub(diff, v2, v3);
    perim += math_norm(diff);
    sub(diff, v3, v1);
    perim += math_norm(diff);
    return perim;
}

// compute the center and radius of the inscribed circle defined by the three vertices
float math_find_in_circle(vec3& center, const vec3& v1, const vec3& v2, const vec3& v3)
{
    float area = math_area(v1, v2, v3);
    // if the area is null
    if (area < math_eps)
    {
        center = v1;
        return 0;
    }

    float oo_perim = 1.0f / math_perimeter(v1, v2, v3);

    vec3 diff;

    sub(diff, v2, v3);
    mult(center, v1, math_norm(diff));

    sub(diff, v3, v1);
    madd(center, v2, math_norm(diff));
    
    sub(diff, v1, v2);
    madd(center, v3, math_norm(diff));

    center *= oo_perim;

    return 2.0f * area * oo_perim;
}

// compute the center and radius of the circumscribed circle defined by the three vertices
// i.e. the osculating circle of the three vertices
float math_find_circ_circle( vec3& center, const vec3& v1, const vec3& v2, const vec3& v3)
{
    vec3 e0;
    vec3 e1;
    float d1, d2, d3;
    float c1, c2, c3, oo_c;

    sub(e0, v3, v1);
    sub(e1, v2, v1);
    dot(d1, e0, e1);

    sub(e0, v3, v2);
    sub(e1, v1, v2);
    dot(d2, e0, e1);

    sub(e0, v1, v3);
    sub(e1, v2, v3);
    dot(d3, e0, e1);

    c1 = d2 * d3;
    c2 = d3 * d1;
    c3 = d1 * d2;
    oo_c = 1.0f / (c1 + c2 + c3);

    mult(center,v1,c2 + c3);
    madd(center,v2,c3 + c1);
    madd(center,v3,c1 + c2);
    center *= oo_c * 0.5f;
 
    return 0.5f * sqrtf((d1 + d2) * (d2 + d3) * (d3 + d1) * oo_c);
}

 float ffast_cos(const float x)
{
    // assert:  0 <= fT <= PI/2
    // maximum absolute error = 1.1880e-03
    // speedup = 2.14

    float x_sqr = x*x;
    float res = float(3.705e-02);
    res *= x_sqr;
    res -= float(4.967e-01);
    res *= x_sqr;
    res += 1.0f;
    return res;
}


 float fast_cos(const float x)
{
    // assert:  0 <= fT <= PI/2
    // maximum absolute error = 2.3082e-09
    // speedup = 1.47

    float x_sqr = x*x;
    float res = float(-2.605e-07);
    res *= x_sqr;
    res += float(2.47609e-05);
    res *= x_sqr;
    res -= float(1.3888397e-03);
    res *= x_sqr;
    res += float(4.16666418e-02);
    res *= x_sqr;
    res -= float(4.999999963e-01);
    res *= x_sqr;
    res += 1.0f;
    return res;
}

void math_is_valid(const vec3& v)
{
    assert(!_isnan(v.x) && !_isnan(v.y) && !_isnan(v.z) &&
        _finite(v.x) && _finite(v.y) && _finite(v.z));
}

void math_is_valid(float lambda)
{
    assert(!_isnan(lambda) && _finite(lambda));
}


/************************************************************************************************
*                                                                                               *
*                                                                                               *
*************************************************************************************************/


// Return index of column of M containing maximum abs entry, or -1 if M=0
int find_max_col(mat3 & M)
{
    float   abs, max = 0;
    int         col = -1;

    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            abs = M(i,j); 
            if (abs < 0) 
                abs = -abs;
            if (abs > max) 
            {
                max = abs; 
                col = j;
            }
        }
    }
    return col;
}

// Setup u for Household reflection to zero all v components but first
void make_reflector(const vec3 &v, vec3 &u)
{
    float s = sqrtf(dot(v, v));
    u = v; 
    u.z += ((v.z < 0) ? -s : s);
    s = sqrtf(2.0f / dot(u, u));
    u *= s; 
}

// Apply Householder reflection represented by u to column vectors of M
void reflect_cols(mat3 &M, vec3 &u)
{
    for (int i=0; i < 3; ++i) 
    {
        float s = dot(u , M.col(i));
        for (int j=0; j < 3; ++j) 
            M(j,i) -= u[j]*s;
    }
}
// Apply Householder reflection represented by u to row vectors of M
void reflect_rows(mat3 & M, vec3 &u)
{
    for (int i=0; i<3; ++i) 
    {
        float s = dot(u, M[i]);
        for (int j=0; j < 3; ++j) 
            M(i,j) -= u[j]*s;
    }
}

// Find orthogonal factor Q of rank 1 (or less) M
void do_rank1(mat3 & M, mat3& Q)
{
    vec3        v1, v2;
    float   s;
    int         col;

    Q = mat3_id;
    /* If rank(M) is 1, we should find a non-zero column in M */
    col = find_max_col(M);
    if ( col < 0 ) 
        return; /* Rank is 0 */
    v1 = M.col(col); 

    make_reflector(v1, v1); 
    reflect_cols(M, v1);

    v2[0] = M[2][0]; v2[1] = M[2][1]; v2[2] = M[2][2];
    make_reflector(v2, v2); reflect_rows(M, v2);
    s = M[2][2];
    if (s < 0) 
        Q(2,2) = -1.0f;
    reflect_cols(Q, v1); reflect_rows(Q, v2);
}

// Find orthogonal factor Q of rank 2 (or less) M using adjoint transpose
void do_rank2(mat3& M, mat3 &MadjT, mat3& Q)
{
    vec3        v1, v2;
    float   w, x, y, z, c, s, d;
    int         col;
    // If rank(M) is 2, we should find a non-zero column in MadjT
    col = find_max_col(MadjT);
    if (col<0) 
    {
        do_rank1(M, Q); 
        return;
    } // Rank<2
    v1[0] = MadjT[0][col]; 
    v1[1] = MadjT[1][col]; 
    v1[2] = MadjT[2][col];
    make_reflector(v1, v1); 
    reflect_cols(M, v1);
    cross(v2, M[0], M[1]);
    make_reflector(v2, v2); 
    reflect_rows(M, v2);
    w = M[0][0]; 
    x = M[0][1]; 
    y = M[1][0]; 
    z = M[1][1];
    if (w*z>x*y) 
    {
        c = z+w; s = y-x; d = sqrtf(c*c+s*s); c = c/d; s = s/d;
        Q(0,0) = Q(1,1) = c; Q(0,1) = -(Q(1,0) = s);
    }
    else 
    {
        c = z-w; s = y+x; d = sqrtf(c*c+s*s); c = c/d; s = s/d;
        Q(0,0) = -(Q(1,1) = c); Q(0,1) = Q(1,0) = s;
    }
    Q(0,2) = Q(2,0) = Q(1,2) = Q(2,1) = 0; Q(2,2) = 1.0f;
    reflect_cols(Q, v1); 
    reflect_rows(Q, v2);
}

//******* Polar Decomposition *******

/* Polar Decomposition of 3x3 matrix in 4x4,
 * M = QS.  See Nicholas Higham and Robert S. Schreiber,
 * Fast Polar Decomposition of An Arbitrary Matrix,
 * Technical Report 88-942, October 1988,
 * Department of Computer Science, Cornell University.
 */
float polar_decomp(const mat3 & M, mat3 & Q, mat3 & S)
{
    mat3 tmp;
    mat3 Mk, MadjTk, Ek;

    float d, M_one, M_inf, MadjT_one, MadjT_inf, E_one, gamma, g1, g2;

    transpose(Mk,M);
    M_one = Mk.norm_one();  
    M_inf = Mk.norm_inf();

    do {
        invert(MadjTk,Mk);
        transpose(MadjTk);
        MadjTk*=det(MadjTk);

        d = dot(Mk.col(0), MadjTk.col(0));

        if (d == 0) 
        {
            do_rank2(Mk, MadjTk, Mk);
            break;
        }

        MadjT_one = MadjTk.norm_one(); 
        MadjT_inf = MadjTk.norm_inf();

        gamma = sqrtf(sqrtf((MadjT_one*MadjT_inf)/(M_one*M_inf))/fabs(d));

        g1 = gamma*0.5f;
        g2 = 0.5f / (gamma*d);

        Ek = Mk;
        tmp = Mk;
        tmp *= g1;
        MadjTk *= g2;
        add(Mk,tmp,MadjTk);
        Ek-=Mk;

        E_one = Ek.norm_one();
        M_one = Mk.norm_one();  
        M_inf = Mk.norm_inf();
    } 
    while (E_one>(M_one*math_eps));

    transpose(Q,Mk); 
    mult(S, Mk, M);  
    
    float x;
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = i; j < 3; ++j)
        {
            x = 0.5f * (S[i][j]+S[j][i]);
            S(i,j) = x;
            S(j,i) = x;
        }
    }
    return (d);
}

//******* Spectral Decomposition *******

/* Compute the spectral decomposition of symmetric positive semi-definite S.
 * Returns rotation in U and scale factors in result, so that if K is a diagonal
 * matrix of the scale factors, then S = U K (U transpose). Uses Jacobi method.
 * See Gene H. Golub and Charles F. Van Loan. Matrix Computations. Hopkins 1983.
 */

vec3 & spect_decomp(vec3 & kv, mat3 & S, mat3 & U)
{
#define X 0
#define Y 1
#define Z 2
#define W 3

    vec3 Diag,OffD; // OffD is off-diag (by omitted index)
    float g,h,fabsh,fabsOffDi,t,theta,c,s,tau,ta,OffDq,a,b;
    static char nxt[] = {Y,Z,X};

    U = mat3_id;
    Diag[X] = S(X,X); Diag[Y] = S(Y,Y); Diag[Z] = S(Z,Z);
    OffD[X] = S(Y,Z); OffD[Y] = S(Z,X); OffD[Z] = S(X,Y);
    for (int sweep=20; sweep>0; --sweep) 
    {
        float sm = (fabs(OffD[X])+fabs(OffD[Y])+fabs(OffD[Z]));
        if (sm == 0) 
            break;
        for (int i=Z; i>=X; --i) 
        {
            int p = nxt[i]; 
            int q = nxt[p];
            fabsOffDi = fabs(OffD[i]);
            g = float(100.0)*fabsOffDi;
            if (fabsOffDi > 0) 
            {
                h = Diag[q] - Diag[p];
                fabsh = fabs(h);
                if (fabsh+g==fabsh) 
                {
                    t = OffD[i]/h;
                } 
                else 
                {
                    theta = 0.5f*h/OffD[i];
                    t = 1.0f/(fabs(theta)+sqrt(theta*theta+1.0f));
                    if (theta < 0) 
                        t = -t;
                }
                c = 1.0f/sqrt(t*t+1.0f); 
                s = t*c;
                tau = s/(c+1.0f);
                ta = t*OffD[i]; 
                OffD[i] = 0;
                Diag[p] -= ta; 
                Diag[q] += ta;
                OffDq = OffD[q];
                OffD[q] -= s*(OffD[p] + tau*OffD[q]);
                OffD[p] += s*(OffDq   - tau*OffD[p]);
                for (int j=Z; j>=X; --j) 
                {
                    a = U(j,p); b = U(j,q);
                    U(j,p) -= s*(b + tau*a);
                    U(j,q) += s*(a - tau*b);
                }
            }
        }
    }
    kv = Diag; 
    return kv;
}

/******* Spectral Axis Adjustment *******/

/* Given a unit quaternion, q, and a scale vector, k, find a unit quaternion, p,
 * which permutes the axes and turns freely in the plane of duplicate scale
 * factors, such that q p has the largest possible w component, i.e. the
 * smallest possible angle. Permutes k's components to go with q p instead of q.
 * See Ken Shoemake and Tom Duff. Matrix Animation and Polar Decomposition.
 * Proceedings of Graphics Interface 1992. Details on p. 262-263.
 */
quat & snuggle(quat & p, quat & q, vec3 & k)
{
#define sgn(n,v)    ((n)?-(v):(v))
#define swap(a,i,j) {a[3]=a[i]; a[i]=a[j]; a[j]=a[3];}
#define cycle(a,p)  if (p) {a[3]=a[0]; a[0]=a[1]; a[1]=a[2]; a[2]=a[3];}\
                    else   {a[3]=a[2]; a[2]=a[1]; a[1]=a[0]; a[0]=a[3];}
    vec4 ka;
    int i, turn = -1;
    ka = k;
    if (ka[X]==ka[Y]) 
    {
        if (ka[X]==ka[Z]) 
            turn = W; 
        else 
            turn = Z;
    }
    else {if (ka[X]==ka[Z]) turn = Y; else if (ka[Y]==ka[Z]) turn = X;}
    if (turn>=0) 
    {
        quat qtoz, qp;
        unsigned neg[3], win;
        double mag[3], t;
        static quat qxtoz = quat(0.0f,math_sqrthalf,0.0f,math_sqrthalf);
        static quat qytoz = quat(math_sqrthalf,0.0f,0.0f,math_sqrthalf);
        static quat qppmm = quat(0.5, 0.5,-0.5,-0.5);
        static quat qpppp = quat(0.5, 0.5, 0.5, 0.5);
        static quat qmpmm = quat(-0.5, 0.5,-0.5,-0.5);
        static quat qpppm = quat(0.5, 0.5, 0.5,-0.5);
        static quat q0001 = quat(0.0, 0.0, 0.0, 1.0);
        static quat q1000 = quat(1.0, 0.0, 0.0, 0.0);
        switch (turn) 
        {
            default: 
                return (conj(p,q));
            case X: 
                qtoz = qxtoz;
                q *= qtoz; 
                swap(ka,X,Z) 
                break;
            case Y: 
                qtoz = qytoz;
                q *= qtoz; 
                swap(ka,Y,Z) 
                break;
            case Z: 
                qtoz = q0001; 
                break;
        }
        conj(q);
        mag[0] = (double)q.z*q.z+(double)q.w*q.w - 0.5;
        mag[1] = (double)q.x*q.z-(double)q.y*q.w;
        mag[2] = (double)q.y*q.z+(double)q.x*q.w;
        for (i=0; i<3; i++) 
            if (neg[i] = (mag[i]<0.0)) 
                mag[i] = -mag[i];
        if (mag[0]>mag[1]) 
        {
            if (mag[0]>mag[2]) 
                win = 0; 
            else 
                win = 2;
        }
        else               
        {
            if (mag[1]>mag[2]) 
                win = 1; 
            else 
                win = 2;
        }
        switch (win) 
        {
            case 0: 
                if (neg[0]) 
                    p = q1000; 
                else 
                    p = q0001; 
                break;
            case 1: 
                if (neg[1]) 
                    p = qppmm; 
                else p = qpppp; 
                cycle(ka,0) 
                break;
            case 2: 
                if (neg[2]) 
                    p = qmpmm; 
                else 
                    p = qpppm; 
                cycle(ka,1) 
                break;
        }
        add_quats(qp, q, p);
        t = sqrt(mag[win]+0.5);
        p *= quat(0.0f,0.0f,-qp.z/t,qp.w/t);
        conj(p);
        p *= qtoz;
    }
    else 
    {
        float qa[4], pa[4];
        unsigned lo, hi, neg[4], par = 0;
        double all, big, two;
        qa[0] = q.x; qa[1] = q.y; qa[2] = q.z; qa[3] = q.w;
        for (i=0; i<4; i++) {
            pa[i] = 0.0;
            if (neg[i] = (qa[i]<0.0)) qa[i] = -qa[i];
            par ^= neg[i];
        }
        /* Find two largest components, indices in hi and lo */
        if (qa[0]>qa[1]) lo = 0; else lo = 1;
        if (qa[2]>qa[3]) hi = 2; else hi = 3;
        if (qa[lo]>qa[hi]) {
            if (qa[lo^1]>qa[hi]) {hi = lo; lo ^= 1;}
            else {hi ^= lo; lo ^= hi; hi ^= lo;}
        } else {if (qa[hi^1]>qa[lo]) lo = hi^1;}
        all = (qa[0]+qa[1]+qa[2]+qa[3])*0.5;
        two = (qa[hi]+qa[lo])*math_sqrthalf;
        big = qa[hi];
        if (all>two) {
            if (all>big) {/*all*/
                {int i; for (i=0; i<4; i++) pa[i] = sgn(neg[i], 0.5f);}
                cycle(ka,par)
            } else {/*big*/ pa[hi] = sgn(neg[hi],1.0f);}
        } else {
            if (two>big) {/*two*/
                pa[hi] = sgn(neg[hi],math_sqrthalf); pa[lo] = sgn(neg[lo], math_sqrthalf);
                if (lo>hi) {hi ^= lo; lo ^= hi; hi ^= lo;}
                if (hi==W) {hi = "\001\002\000"[lo]; lo = 3-hi-lo;}
                swap(ka,hi,lo)
            } else {/*big*/ pa[hi] = sgn(neg[hi],1.0f);}
        }
        p.x = -pa[0]; p.y = -pa[1]; p.z = -pa[2]; p.w = pa[3];
    }
    k = ka;
    return (p);
}

/* Decompose Affine Matrix 
 *    A = TQS, where
 * A is the affine transform
 * T is the translation vector
 * Q is the rotation (quaternion)
 * U is the rotation component of the scaling factor (shear = U * S)
 * S is the scale vector
 * f is the sign of the determinant
 *
 * See Ken Shoemake and Tom Duff. Matrix Animation and Polar Decomposition.
 * Proceedings of Graphics Interface 1992.
 */
void decomp_affine(const mat4 & A, vec3 & T, quat & Q, quat & U, vec3 & S, float & f)
{
    mat3    matQ, matS, matU, matM;
    quat    p;
    
    float det;
    A.get_translation(T);
    A.get_rot(matM);
    det = polar_decomp(matM, matQ, matS);

    if (det < 0)
    {
        negate(matQ);
        f = -1.0f;
    } 
    else 
        f = 1.0f;

    mat_2_quat(Q, matQ);
    spect_decomp(S, matS, matU);
    mat_2_quat(U, matU);

    U *= snuggle(p, U, S);
    U *= p;
}

