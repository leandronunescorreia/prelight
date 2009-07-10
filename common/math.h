#ifndef _MATH_H_
#define _MATH_H_

#include <assert.h>
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <float.h>

#define math_pi			      3.14159265358979323846264338327950288419716939937510582f

#define math_to_rad             math_pi / 180.0f
#define math_to_deg             180.f / math_pi
#define math_eps		        10e-6f
#define math_big_eps            10e-2f
#define math_small_eps          10e-6f
#define math_sqrthalf           0.7071067811865475244f

struct vec2;
struct vec3;
struct vec4;


struct vec2
{
    vec2() { }
    vec2(float x, float y) : x(x), y(y) { }
    vec2(const float* xy) : x(xy[0]), y(xy[1]) { }
    vec2(const vec2& u) : x(u.x), y(u.y) { }
    vec2(const vec3&);

    bool operator==(const vec2 & u) const
    {
        return (u.x == x && u.y == y) ? true : false;
    }

    bool operator!=(const vec2 & u) const
    {
        return !(*this == u );
    }

    vec2 & operator*=(const float & lambda)
    {
        x*= lambda;
        y*= lambda;
        return *this;
    }

    vec2 & operator-=(const vec2 & u)
    {
        x-= u.x;
        y-= u.y;
        return *this;
    }

    vec2 & operator+=(const vec2 & u)
    {
        x+= u.x;
        y+= u.y;
        return *this;
    }

    float & operator[](int i)
    {
        return vec_array[i];
    }

    const float operator[](int i) const
    {
        return vec_array[i];
    }

	float sq_norm() const { return x * x + y * y; }
	float norm() const { return sqrtf(sq_norm()); }

    union {
        struct {
            float x,y;          // standard names for components
        };
        struct {
            float s,t;          // standard names for components
        };
        float vec_array[2];     // array access
    };
};

inline const vec2 operator+(const vec2& u, const vec2& v)
{
    return vec2(u.x + v.x, u.y + v.y);
}

inline const vec2 operator-(const vec2& u, const vec2& v)
{
    return vec2(u.x - v.x, u.y - v.y);
}

inline const vec2 operator*(const float s, const vec2& u)
{
	return vec2(s * u.x, s * u.y);
}

inline const vec2 operator/(const vec2& u, const float s)
{
	return vec2(u.x / s, u.y / s);
}

inline const vec2 operator*(const vec2&u, const vec2&v)
{
	return vec2(u.x * v.x, u.y * v.y);
}

struct vec3
{
	vec3() { }
    vec3(float x, float y, float z) : x(x), y(y), z(z) { }
    vec3(const float* xyz) : x(xyz[0]), y(xyz[1]), z(xyz[2]) { }
	vec3(const vec2& u) : x(u.x), y(u.y), z(1.0f) { }
	vec3(const vec3& u) : x(u.x), y(u.y), z(u.z) { }
	vec3(const vec4&);

    bool operator==(const vec3 & u) const
    {
        return (u.x == x && u.y == y && u.z == z) ? true : false;
    }

    bool operator!=( const vec3& rhs ) const
    {
        return !(*this == rhs );
    }

    vec3 & operator*=(const float & lambda)
    {
        x*= lambda;
        y*= lambda;
        z*= lambda;
        return *this;
    }

    vec3 operator - () const
	{
		return vec3(-x, -y, -z);
	}

    vec3 & operator-=(const vec3 & u)
    {
        x-= u.x;
        y-= u.y;
        z-= u.z;
        return *this;
    }

    vec3 & operator+=(const vec3 & u)
    {
        x+= u.x;
        y+= u.y;
        z+= u.z;
        return *this;
    }
	float normalize();
	void orthogonalize( const vec3& v );
	void orthonormalize( const vec3& v )
	{
		orthogonalize( v ); //  just orthogonalize...
		normalize();        //  ...and normalize it
	}

	float sq_norm() const { return x * x + y * y + z * z; }
	float norm() const { return sqrtf(sq_norm()); }

    float & operator[](int i)
    {
        return vec_array[i];
    }

    const float operator[](int i) const
    {
        return vec_array[i];
    }

    union {
        struct {
            float x,y,z;        // standard names for components
        };
        struct {
            float s,t,r;        // standard names for components
        };
        float vec_array[3];     // array access
    };
};

inline const vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline const vec3 operator-(const vec3& u, const vec3& v)
{
    return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline const vec3 operator^(const vec3& u, const vec3& v)
{
    return vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

inline const vec3 operator*(const float s, const vec3& u)
{
	return vec3(s * u.x, s * u.y, s * u.z);
}

inline const vec3 operator/(const vec3& u, const float s)
{
	return vec3(u.x / s, u.y / s, u.z / s);
}

inline const vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline vec2::vec2(const vec3& u)
{
	float k = 1 / u.z;
	x = k * u.x;
	y = k * u.y;
}

struct vec4
{
	vec4() { }
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
    vec4(const float* xyzw) : x(xyzw[0]), y(xyzw[1]), z(xyzw[2]), w(xyzw[3]) { }
	vec4(const vec3& u) : x(u.x), y(u.y), z(u.z), w(1.0f) { }
	vec4(const vec4& u) : x(u.x), y(u.y), z(u.z), w(u.w) { }

    bool operator==(const vec4 & u) const
    {
        return (u.x == x && u.y == y && u.z == z && u.w == w) ? true : false;
    }

    bool operator!=( const vec4& rhs ) const
    {
        return !(*this == rhs );
    }


    vec4 & operator*=(const float & lambda)
    {
        x*= lambda;
        y*= lambda;
        z*= lambda;
        w*= lambda;
        return *this;
    }

    vec4 & operator-=(const vec4 & u)
    {
        x-= u.x;
        y-= u.y;
        z-= u.z;
        w-= u.w;
        return *this;
    }

    vec4 & operator+=(const vec4 & u)
    {
        x+= u.x;
        y+= u.y;
        z+= u.z;
        w+= u.w;
        return *this;
    }

    vec4 operator - () const
	{
		return vec4(-x, -y, -z, -w);
	}

    float & operator[](int i)
    {
        return vec_array[i];
    }

    const float operator[](int i) const
    {
        return vec_array[i];
    }

    union {
        struct {
            float x,y,z,w;          // standard names for components
        };
        struct {
            float s,t,r,q;          // standard names for components
        };
        float vec_array[4];     // array access
    };
};

inline const vec4 operator+(const vec4& u, const vec4& v)
{
	return vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

inline const vec4 operator-(const vec4& u, const vec4& v)
{
    return vec4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

inline const vec4 operator*(const float s, const vec4& u)
{
	return vec4(s * u.x, s * u.y, s * u.z, s * u.w);
}

inline const vec4 operator/(const vec4& u, const float s)
{
    return vec4(u.x / s, u.y / s, u.z / s, u.w / s);
}

inline const vec4 operator*(const vec4& u, const vec4& v)
{
	return vec4(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w);
}

inline vec3::vec3(const vec4& u)
{
	x = u.x;
	y = u.y;
	z = u.z;
}

// quaternion
struct quat;  

/*
    for all the matrices...a<x><y> indicates the element at row x, col y

    For example:
    a01 <-> row 0, col 1 
*/

struct mat3
{
    mat3();
    mat3(const float * array);
    mat3(const mat3 & M);
    mat3( const float& f0,  const float& f1,  const float& f2,  
          const float& f3,  const float& f4,  const float& f5,  
          const float& f6,  const float& f7,  const float& f8 )
  		  : a00( f0 ), a10( f1 ), a20( f2 ), 
            a01( f3 ), a11( f4 ), a21( f5 ),
  		    a02( f6 ), a12( f7 ), a22( f8) { }

    const vec3 col(const int i) const
    {
        return vec3(&m[i * 3]);
    }

    const vec3 operator[](int i) const
    {
        return vec3(m[i], m[i + 3], m[i + 6]);
    }

    const float& operator()(const int& i, const int& j) const
    {
        return m[ j * 3 + i ];
    }

    float& operator()(const int& i, const int& j)
    {
        return  m[ j * 3 + i ];
    }

    mat3 & operator*=(const float & lambda)
    {
        for (int i = 0; i < 9; ++i)
            m[i] *= lambda;
        return *this;
    }

    mat3 & operator-=(const mat3 & M)
    {
        for (int i = 0; i < 9; ++i)
            m[i] -= M.m[i];
        return *this;
    }

    void set_row(int i, const vec3 & v)
    {
        m[i] = v.x;
        m[i + 3] = v.y;
        m[i + 6] = v.z;
    }

	void set_col(int i, const vec3 & v)
	{
        m[i * 3] = v.x;
        m[i * 3 + 1] = v.y;
        m[i * 3 + 2] = v.z;
	}

    void set_rot(const float & theta, const vec3 & v);
    void set_rot(const vec3 & u, const vec3 & v);

    // Matrix norms...
    // Compute || M ||
    //                1
    float norm_one();

    // Compute || M ||
    //                +inf
    float norm_inf();

    union {
        struct {
            float a00, a10, a20;        // standard names for components
            float a01, a11, a21;        // standard names for components
            float a02, a12, a22;        // standard names for components
        };
        float m[9];     // array access
    };
};

const vec3 operator*(const mat3&, const vec3&);
const vec3 operator*(const vec3&, const mat3&);

struct mat4
{
    mat4();
    mat4(const float * array);
    mat4(const mat4 & M);

    mat4( const float& f0,  const float& f1,  const float& f2,  const float& f3,
  		  const float& f4,  const float& f5,  const float& f6,  const float& f7,
  		  const float& f8,  const float& f9,  const float& f10, const float& f11,
  		  const float& f12, const float& f13, const float& f14, const float& f15 )
  		  : a00( f0 ), a10( f1 ), a20( f2 ), a30( f3 ),
  		    a01( f4 ), a11( f5 ), a21( f6 ), a31( f7 ),
  		    a02( f8 ), a12( f9 ), a22( f10), a32( f11),
			a03( f12), a13( f13), a23( f14), a33( f15) { }
 
    const vec4 col(const int i) const
    {
        return vec4(&m[i * 4]);
    }
    
    const vec4 operator[](const int& i) const
    {
        return vec4(m[i], m[i + 4], m[i + 8], m[i + 12]);
    }
   
    const float& operator()(const int& i, const int& j) const
    {
        return m[ j * 4 + i ];
    }

    float& operator()(const int& i, const int& j)
    {
        return  m[ j * 4 + i ];
    }

    void set_col(int i, const vec4 & v)
    {
        float *col = &m[i * 4];
        col[0] = v.x;
        col[1] = v.y;
        col[2] = v.z;
        col[3] = v.w;
    }

    void set_row(int i, const vec4 & v)
    {
        m[i] = v.x;
        m[i + 4] = v.y;
        m[i + 8] = v.z;
        m[i + 12] = v.w;
    }

    mat3 & get_rot(mat3 & M) const;
    quat & get_rot(quat & q) const;
    void set_rot(const quat & q);
    void set_rot(const mat3 & M);
    void set_rot(const float & theta, const vec3 & v);
    void set_rot(const vec3 & u, const vec3 & v);

	void set_scale(const vec3& s);
	vec3& get_scale(vec3& s) const;
    void set_translation(const vec3 & t);
    vec3 & get_translation(vec3 & t) const;

	mat4 operator*(const mat4&) const;

    union {
        struct {
            float a00, a10, a20, a30;   // standard names for components
            float a01, a11, a21, a31;   // standard names for components
            float a02, a12, a22, a32;   // standard names for components
            float a03, a13, a23, a33;   // standard names for components
        };
        struct {
            float _11, _12, _13, _14;   // standard names for components
            float _21, _22, _23, _24;   // standard names for components
            float _31, _32, _33, _34;   // standard names for components
            float _41, _42, _43, _44;   // standard names for components
        };
        union {
            struct {
                float b00, b10, b20, p; // standard names for components
                float b01, b11, b21, q; // standard names for components
                float b02, b12, b22, r; // standard names for components
                float x, y, z, w;       // standard names for components
            };
        };
        float m[16];     // array access
    };
};

const vec4 operator*(const mat4&, const vec4&);
const vec4 operator*(const vec4&, const mat4&);

// quaternion
struct quat {
public:
    quat();
	quat(float x, float y, float z, float w);
	quat(const quat& quat);
	quat(const vec3& axis, float angle);
	quat(const mat3& rot);
	quat& operator=(const quat& quat);
	quat operator-()
	{
		return quat(-x, -y, -z, -w);
	}
    quat Inverse();
	void Normalize();
	void FromMatrix(const mat3& mat);
	void ToMatrix(mat3& mat) const;
	quat& operator*=(const quat& q);
	static const quat Identity;
	float& operator[](int i) { return comp[i]; }
	const float operator[](int i) const { return comp[i]; }
	union {
		struct {
			float x, y, z, w;
		};
		float comp[4];
	};
};

const quat operator*(const quat&, const quat&);
extern quat & add_quats(quat & p, const quat & q1, const quat & q2);
extern float dot(const quat & p, const quat & q);
extern quat & dot(float s, const quat & p, const quat & q);
extern quat & slerp_quats(quat & p, float s, const quat & q1, const quat & q2);
extern quat & axis_to_quat(quat & q, const vec3 & a, const float phi);
extern mat3 & quat_2_mat(mat3 &M, const quat &q );
extern quat & mat_2_quat(quat &q,const mat3 &M);


// constant algebraic values
static const float mat4_id_raw[] =         { 1.0f, 0.0f, 0.0f, 0.0f,
                                             0.0f, 1.0f, 0.0f, 0.0f,
                                             0.0f, 0.0f, 1.0f, 0.0f,
                                             0.0f, 0.0f, 0.0f, 1.0f };
                                          
static const float mat4_null_raw[] =       { 0.0f, 0.0f, 0.0f, 0.0f,
                                             0.0f, 0.0f, 0.0f, 0.0f,
                                             0.0f, 0.0f, 0.0f, 0.0f,
                                             0.0f, 0.0f, 0.0f, 0.0f };
                                          
static const float mat4_scale_bias_raw[] = { 0.5f, 0.0f, 0.0f, 0.0f,
                                             0.0f, 0.5f, 0.0f, 0.0f,
                                             0.0f, 0.0f, 0.5f, 0.0f,
                                             0.5f, 0.5f, 0.5f, 1.0f };
                                          
static const float mat3_id_raw[] =         { 1.0f, 0.0f, 0.0f,
                                             0.0f, 1.0f, 0.0f,
                                             0.0f, 0.0f, 1.0f };


static const vec2      vec2_null(0.0f,0.0f);
static const vec4      vec4_one(1.0f,1.0f,1.0f,1.0f);
static const vec3      vec3_one(1.0f,1.0f,1.0f);
static const vec3      vec3_null(0.0f,0.0f,0.0f);
static const vec3      vec3_x(1.0f,0.0f,0.0f);
static const vec3      vec3_y(0.0f,1.0f,0.0f);
static const vec3      vec3_z(0.0f,0.0f,1.0f);
static const vec3      vec3_neg_x(-1.0f,0.0f,0.0f);
static const vec3      vec3_neg_y(0.0f,-1.0f,0.0f);
static const vec3      vec3_neg_z(0.0f,0.0f,-1.0f);
static const vec4      vec4_null(0.0f,0.0f,0.0f,0.0f);
static const vec4      vec4_x(1.0f,0.0f,0.0f,0.0f);
static const vec4      vec4_neg_x(-1.0f,0.0f,0.0f,0.0f);
static const vec4      vec4_y(0.0f,1.0f,0.0f,0.0f);
static const vec4      vec4_neg_y(0.0f,-1.0f,0.0f,0.0f);
static const vec4      vec4_z(0.0f,0.0f,1.0f,0.0f);
static const vec4      vec4_neg_z(0.0f,0.0f,-1.0f,0.0f);
static const vec4      vec4_w(0.0f,0.0f,0.0f,1.0f);
static const vec4      vec4_neg_w(0.0f,0.0f,0.0f,-1.0f);
static const quat      quat_id(0.0f,0.0f,0.0f,1.0f);
static const mat4      mat4_id(mat4_id_raw);
static const mat3      mat3_id(mat3_id_raw);
static const mat4      mat4_null(mat4_null_raw);
static const mat4      mat4_scale_bias(mat4_scale_bias_raw);

// normalizes a vector and return a reference of itself
extern vec2 & normalize(vec2 & u);
extern vec3 & normalize(vec3 & u);
extern vec4 & normalize(vec4 & u);

// Computes the squared magnitude
inline float math_sq_norm(const vec3 & n)
{ return n.x * n.x + n.y * n.y + n.z * n.z; }

inline float math_sq_norm(const vec4 & n)
{ return n.x * n.x + n.y * n.y + n.z * n.z + n.w * n.w; }

// Computes the magnitude
inline float math_norm(const vec3 & n)
{ return sqrtf(math_sq_norm(n)); }

inline float math_norm(const vec4 & n)
{ return sqrtf(math_sq_norm(n)); }


// computes the cross product ( v cross w) and stores the result in u
// i.e.     u = v cross w
extern vec3 & cross(vec3 & u, const vec3 & v, const vec3 & w);

// computes the dot product ( v dot w) and stores the result in u
// i.e.     u = v dot w
extern float & dot(float & u, const vec3 & v, const vec3 & w);
extern float dot(const vec3 & v, const vec3 & w);
extern float & dot(float & u, const vec4 & v, const vec4 & w);
extern float dot(const vec4 & v, const vec4 & w);
extern float & dot(float & u, const vec3 & v, const vec4 & w);
extern float dot(const vec3 & v, const vec4 & w);
extern float & dot(float & u, const vec4 & v, const vec3 & w);
extern float dot(const vec4 & v, const vec3 & w);

// compute the reflected vector R of L w.r.t N - vectors need to be 
// normalized
//
//                R     N     L
//                  _       _
//                 |\   ^   /|
//                   \  |  /
//                    \ | /
//                     \|/
//                      +
extern vec3 & reflect(vec3 & r, const vec3 & n, const vec3 & l);

// Computes u = v * lambda + u
extern vec3 & madd(vec3 & u, const vec3 & v, const float & lambda);
// Computes u = v * lambda
extern vec3 & mult(vec3 & u, const vec3 & v, const float & lambda);
// Computes u = v * w
extern vec3 & mult(vec3 & u, const vec3 & v, const vec3 & w);
// Computes u = v + w
extern vec3 & add(vec3 & u, const vec3 & v, const vec3 & w);
// Computes u = v - w
extern vec3 & sub(vec3 & u, const vec3 & v, const vec3 & w);

// Computes u = u * s
extern vec2 & scale(vec2 & u, const float s);
extern vec3 & scale(vec3 & u, const float s);
extern vec4 & scale(vec4 & u, const float s);

// Computes u = M * v
extern vec3 & mult(vec3 & u, const mat3 & M, const vec3 & v);
extern vec4 & mult(vec4 & u, const mat4 & M, const vec4 & v);

// Computes u = v * M
extern vec3 & mult(vec3 & u, const vec3 & v, const mat3 & M);
extern vec4 & mult(vec4 & u, const vec4 & v, const mat4 & M);

// Computes u = M(4x4) * v and divides by w
extern vec3 & mult_pos(vec3 & u, const mat4 & M, const vec3 & v);
// Computes u = M(4x4) * v
extern vec3 & mult_dir(vec3 & u, const mat4 & M, const vec3 & v);
// Computes u = M(4x4) * v and does not divide by w (assumed to be 1)
extern vec3 & mult(vec3& u, const mat4& M, const vec3& v);

// Computes u = v * M(4x4) and divides by w
extern vec3 & mult_pos(vec3 & u, const vec3 & v, const mat4 & M);
// Computes u = v * M(4x4)
extern vec3 & mult_dir(vec3 & u, const vec3 & v, const mat4 & M);
// Computes u = v * M(4x4) and does not divide by w (assumed to be 1)
extern vec3 & mult(vec3& u, const vec3& v, const mat4& M);

// Computes A += B
extern mat4 & add(mat4 & A, const mat4 & B);
extern mat3 & add(mat3 & A, const mat3 & B);

// Computes C = A + B
extern mat4 & add(mat4 & C, const mat4 & A, const mat4 & B);
extern mat3 & add(mat3 & C, const mat3 & A, const mat3 & B);

// Computes C = A * B
extern mat4 & mult(mat4 & C, const mat4 & A, const mat4 & B);
extern mat3 & mult(mat3 & C, const mat3 & A, const mat3 & B);

// Compute M = -M
extern mat4 & negate(mat4 & M);
extern mat3 & negate(mat3 & M);

// Computes B = Transpose(A)
//       T
//  B = A
extern mat3 & transpose(mat3 & B, const mat3 & A);
extern mat4 & transpose(mat4 & B, const mat4 & A);

// Computes B = Transpose(B)
//       T
//  B = B
extern mat3 & transpose(mat3 & B);
extern mat4 & transpose(mat4 & B);

// Computes B = inverse(A)
//       -1
//  B = A
extern mat4 & invert(mat4 & B, const mat4 & A);
extern mat3 & invert(mat3 & B, const mat3 & A);

// Computes B = inverse(A)
//                                       T  T
//                   (R t)             (R -R t)
// assuming that A = (0 1) so that B = (0    1)
//  B = A
extern mat4 & invert_rot_trans(mat4 & B, const mat4 & A);

extern mat4 & look_at(mat4 & M, const vec3 & eye, const vec3 & center, const vec3 & up);
extern mat4 & frustum(mat4 & M, const float l, const float r, const float b, 
               const float t, const float n, const float f);

extern mat4 & perspective(mat4 & M, const float fovy, const float aspect, const float n, const float f);
extern mat4 & ortho(mat4 & M, const float left, 
                              const float right, 
                              const float bottom, 
                              const float top,
                              const float n,
                              const float f);

/* Decompose Affine Matrix 
 *    A = TQS, where
 * A is the affine transform
 * T is the translation vector
 * Q is the rotation (quaternion)
 * S is the scale vector
 * f is the sign of the determinant
*/
extern void decomp_affine(const mat4 & A, vec3 & T, quat & Q, quat & U, vec3 & S, float & f);
// quaternion
extern quat & normalize(quat & p);
extern quat & conj(quat & p);
extern quat & conj(quat & p, const quat & q);
extern quat & add_quats(quat & p, const quat & q1, const quat & q2);
extern quat & axis_to_quat(quat & q, const vec3 & a, const float phi);
extern mat3 & quat_2_mat(mat3 &M, const quat &q );
extern quat & mat_2_quat(quat &q,const mat3 &M);
extern quat & mat_2_quat(quat &q,const mat4 &M);

// surface properties
extern mat3 & tangent_basis(mat3 & basis,const vec3 & v0,const vec3 & v1,const vec3 & v2,const vec2 & t0,const vec2 & t1,const vec2 & t2, const vec3 & n);

// linear interpolation
inline float lerp(float t, float a, float b)
{ return a * (1.0f - t) + t * b; }

inline vec3 & lerp(vec3 & w, const float & t, const vec3 & u, const vec3 & v)
{ w.x = lerp(t, u.x, v.x); w.y = lerp(t, u.y, v.y); w.z = lerp(t, u.z, v.z); return w; }

inline vec4 & lerp(vec4 & w, const float & t, const vec4 & u, const vec4 & v)
{ w.x = lerp(t, u.x, v.x); w.y = lerp(t, u.y, v.y); w.z = lerp(t, u.z, v.z); w.w = lerp(t, u.w, v.w); return w; }

// utilities
inline float math_min(const float & lambda, const float & n)
{ return (lambda < n ) ? lambda : n; }

inline float math_max(const float & lambda, const float & n)
{ return (lambda > n ) ? lambda : n; }

inline float math_clamp(float u, const float min, const float max)
{ u = (u < min) ? min : u; u = (u > max) ? max : u; return u; }

extern float math_random();

extern quat & trackball(quat & q, vec2 & pt1, vec2 & pt2, float trackballsize);

extern vec3 & cube_map_normal(int i, int x, int y, int cubesize, vec3 & v);

// Componentwise maximum and minium 
inline void math_max(vec3 & vOut, const vec3 & vFirst, const vec3 & vSecond)
{
    vOut.x = math_max(vFirst.x, vSecond.x);
    vOut.y = math_max(vFirst.y, vSecond.y);
    vOut.z = math_max(vFirst.z, vSecond.z);
}

inline void math_min(vec3 & vOut, const vec3 & vFirst, const vec3 & vSecond)
{
    vOut.x = math_min(vFirst.x, vSecond.x);
    vOut.y = math_min(vFirst.y, vSecond.y);
    vOut.z = math_min(vFirst.z, vSecond.z);
}


// geometry
// computes the area of a triangle
extern float math_area(const vec3 & v1, const vec3 & v2, const vec3 &v3);
// computes the perimeter of a triangle
extern float math_perimeter(const vec3 & v1, const vec3 & v2, const vec3 &v3);
// find the inscribed circle
extern float math_find_in_circle( vec3 & center, const vec3 & v1, const vec3 & v2, const vec3 &v3);
// find the circumscribed circle
extern float math_find_circ_circle( vec3 & center, const vec3 & v1, const vec3 & v2, const vec3 &v3);

// fast cosine functions
extern float fast_cos(const float x);
extern float ffast_cos(const float x);

// determinant
float det(const mat3 & A);

extern void math_is_valid(const vec3& v);
extern void math_is_valid(float lambda);
#endif 
