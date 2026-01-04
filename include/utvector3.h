#ifndef __UT_VECTOR3_H__
#define __UT_VECTOR3_H__

#include "utconfig.h"
#include "utalgorithm.h"
#include "utvector2.h"

#include <math.h>

namespace utb {
    namespace math {

        template < typename T >
        class vector3  {
        public:
            using value_type = T;
            using self_type = vector3 <T> ;
            using pointer = T* ;
                
            union  {
                struct {
                    value_type x;
                    value_type y;
                    value_type z;
                };
                value_type c[3];
            };
              
            vector3() 														{}
	        vector3(value_type _x, value_type _y, value_type _z) : x(_x), y(_y), z(_z)	{}
	        vector3(value_type _f) : x(_f), y(_f), z(_f)			{}
            vector3(const self_type& vec) : x(vec.x), y(vec.y), z(vec.z)	{}
            vector3(const vector2<T>& vec) : x(vec.x), y(vec.y), z(0)	{}
            vector3(const pointer lpvec) : x(lpvec[0]), y(lpvec[1]), z(lpvec[2])	{}

            operator pointer ()		{ return (pointer)(c); }
            operator void* ()		{ return (void*)(c); }
                
            self_type& operator =  (const self_type& v)	{ 
                x = v.x; y = v.y; z = v.z; return *this; } 
            self_type& operator = (const vector2<T>& v)     {
                x = v.x; y = v.y; z = 0; return *this; }
            self_type& operator += (const self_type& v)	{
                x += v.x; y += v.y; z += v.z; return *this; }
            self_type& operator -= (const self_type& v) { 
                x -= v.x; y -= v.y; z -= v.z; return *this; }
            self_type& operator *= (const self_type& v)	{ 
                x *= v.x; y *= v.y; z *= v.z; return *this; }
            self_type& operator /= (const self_type& v)	{ 
                x /= v.x; y /= v.y; z /= v.z; return *this; }

            self_type& operator /= (const value_type& f)	{ 
                x /= f; y /= f; z /= f; return *this; }
            self_type& operator *= (const value_type& f)	{ 
                x *= f; y *= f; z *= f; return *this; }
	    };
        
        template < typename T >
        inline vector3<T> operator + (const vector3<T>& a, const vector3<T>& b)					
            { return vector3<T> (a.x + b.x, a.y + b.y, a.z + b.z); }
	    template < typename T >
        inline vector3<T> operator - (const vector3<T>& a, const vector3<T>& b)					
            { return vector3<T> (a.x - b.x, a.y - b.y, a.z - b.z); }
	    template < typename T >
        inline vector3<T> operator - (const vector3<T>& a)										
            { return vector3<T> (-a.x, -a.y, -a.z); }
	    template < typename T >
        inline vector3<T> operator * (const vector3<T>& a,const vector3<T>& b)						
            { return vector3<T> (a.x * b.x, a.y * b.y, a.z * b.z); }
	    template < typename T >
        inline vector3<T> operator * (const vector3<T>& a, const T& b)						
            { return vector3<T> (a.x * b, a.y * b, a.z * b); }
	    template < typename T >
        inline vector3<T> operator * (const T& a,const vector3<T>& b)						
            { return vector3<T> (a * b.x, a * b.y, a * b.z); }
        template < typename T >
        inline vector3<T> operator / (const vector3<T>& a,const vector3<T>& b)						
            { return vector3<T> (a.x / b.x, a.y / b.y, a.z / b.z); }
	    template < typename T >
        inline vector3<T> operator / (const T& a,const vector3<T>& b)						
            { return vector3<T> (a / b.x, a / b.y, a / b.z); }
	    template < typename T >
        inline vector3<T> operator / (const vector3<T>& a,const T& b)						
            { return vector3<T> (a.x / b, a.y / b, a.z / b); }

        template < typename T >
	    inline bool operator == (const vector3<T>& a, const vector3<T>& b)						
            { return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z)); }
	    template < typename T >
        inline bool operator != (const vector3<T>& a, const vector3<T>& b)						
            { return ((a.x != b.x) && (a.y != b.y) && (a.z != b.z)); }
	    template < typename T >
        inline bool operator <= (const vector3<T>& a, const vector3<T>& b)						
            { return ((a.x <= b.x) && (a.y <= b.y) && (a.z <= b.z)); }
	    template < typename T >
        inline bool operator >= (const vector3<T>& a, const vector3<T>& b)						
            { return ((a.x >= b.x) && (a.y >= b.y) && (a.z >= b.z)); }
	    template < typename T >
        inline bool operator < (const vector3<T>& a, const vector3<T>& b)							
            { return ((a.x < b.x) && (a.y < b.y) && (a.z < b.z)); }
	    template < typename T >
        inline bool operator > (const vector3<T>& a, const vector3<T>& b)							
            { return ((a.x > b.x) && (a.y > b.y) && (a.z > b.z)); }
        template < typename T >
        inline T lenghtSq(const vector3<T>& v)									
            { return (v.x * v.x + v.y * v.y + v.z * v.z); }
        template < typename T >
	    inline T lenght(const vector3<T>& v)									
            { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }
        template < typename T >
	    inline vector3<T> normalize(const vector3<T>& v)									
            { return v / (T)sqrt(double(v.x * v.x + v.y * v.y + v.z * v.z)); }
        template < typename T >
	    inline vector3<T> normalizex(const vector3<T>& v)								
            { return v / (T)(sqrt(double(v.x * v.x + v.y * v.y + v.z * v.z)) + 0.0001); }
        template < typename T >
	    inline vector3<T> cross(const vector3<T>& v1, vector3<T>& v2)						
            { return vector3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x); }
	    template < typename T >
        inline T dot(const vector3<T>& v1, const vector3<T>& v2)					
            { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;}
	    template < typename T >
        inline T angle(const vector3<T>& v1, const vector3<T>& v2)				
            { return (T)(acos(double((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z)) /
                        sqrt((double)((v1.x * v1.x + v1.y * v1.y + v1.z * v1.z)) * T((v2.x * v2.x + v2.y * v2.y + v2.z * v2.z))))); }
	    template < typename T >
        inline vector3<T> interpolate_coords(const vector3<T>& v1, const vector3<T>& v2, const float p)								
            { return v1 + p * (v2 - v1); }
	    template < typename T >
        inline vector3<T> interpolate_normal(const vector3<T>& v1, const vector3<T>& v2, const float p)								
            { return normalize(v1 + p * (v2 - v1)); }
	    template < typename T >
        inline bool nearequal(const vector3<T>& v1, vector3<T>& v2, const vector2<T>& epsilon)							
            { return ( abs(float(v1.x - v2.x )) <= epsilon && ( abs(float(v1.y - v2.y)) <= epsilon) && (abs(float(v1.z - v2.z)) <= epsilon)); }
   
        template <typename T>
        inline vector3<T> _min(const vector3<T>& c1, const vector3<T>& c2)
            {return vector3<T>(utb::min<T>(c1.x, c2.x), utb::min<T>(c1.y, c2.y), utb::min<T>(c1.z, c2.z));}
        template <typename T>
        inline vector3<T> _max(const vector3<T>& c1, const vector3<T>& c2)
            {return vector3<T>(utb::max<T>(c1.x, c2.x), utb::max<T>(c1.y, c2.y), utb::max<T>(c1.z, c2.z));}
	    template <typename T>
        inline vector3<T> scale(const vector3<T>& v, const float s)
            {return vector3<T>(v.x * s, v.y*s, v.z*s);}

        using vec3f = vector3 <float>  ;
        using vec3d = vector3 <double>;
    }
}

#endif