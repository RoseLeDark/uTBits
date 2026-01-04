#ifndef __UT_VECTOR4_H__
#define __UT_VECTOR4_H__

#include "utconfig.h"
#include "utalgorithm.h"
#include "utvector2.h"

#include <math.h>

namespace utb {
    namespace math {

        template < typename T >
        class vector4  {
        public:
            using value_type = T;
            using self_type = vector4 <T> ;
            using pointer = T* ;
                
            union  {
                struct {
                    value_type x;
                    value_type y;
                    value_type z;
                    value_type w;
                };
                value_type c[4];
            };
              
            vector4() 														{}
	        vector4(value_type _x, value_type _y, value_type _z, value_type _w) : x(_x), y(_y), z(_z), w(_w)	{}
	        vector4(value_type _f) : x(_f), y(_f), z(_f), w(_f)			{}
            vector4(const self_type& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w)	{}
            vector4(const vector2<T>& vec) : x(vec.x), y(vec.y), z(0), w(0)	{}
            vector4(const pointer lpvec) : x(lpvec[0]), y(lpvec[1]), z(lpvec[2]), w(lpvec[3])	{}

            operator pointer ()		{ return (pointer)(c); }
            operator void* ()		{ return (void*)(c); }
                
            self_type& operator =  (const self_type& v)	{ 
                x = v.x; y = v.y; z = v.z; w = v.w; return *this; } 
            self_type& operator = (const vector2<T>& v)     {
                x = v.x; y = v.y; z = 0; w = 0; return *this; }
            self_type& operator += (const self_type& v)	{
                x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
            self_type& operator -= (const self_type& v) { 
                x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
            self_type& operator *= (const self_type& v)	{ 
                x *= v.x; y *= v.y; z *= v.z; w *= v.w;  return *this; }
            self_type& operator /= (const self_type& v)	{ 
                x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

            self_type& operator /= (const value_type& f)	{ 
                x /= f; y /= f; z /= f; w /= f; return *this; }
            self_type& operator *= (const value_type& f)	{ 
                x *= f; y *= f; z *= f; w *= f; return *this; }
	    };
        
        template < typename T >
        inline vector4<T> operator + (const vector4<T>& a, const vector4<T>& b)					
            { return vector4<T> (a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	    template < typename T >
        inline vector4<T> operator - (const vector4<T>& a, const vector4<T>& b)					
            { return vector4<T> (a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
	    template < typename T >
        inline vector4<T> operator - (const vector4<T>& a)										
            { return vector4<T> (-a.x, -a.y, -a.z, -a.w); }     

	    template < typename T >
        inline vector4<T> operator * (const vector4<T>& a,const vector4<T>& b)						
            { return vector4<T> (a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
	    template < typename T >
        inline vector4<T> operator * (const vector4<T>& a, const T& b)						
            { return vector4<T> (a.x * b, a.y * b, a.z * b, a.w * b); }
	    template < typename T >
        inline vector4<T> operator * (const T& a,const vector4<T>& b)						
            { return vector4<T> (a * b.x, a * b.y, a * b.z, a * b.w); }

        template < typename T >
        inline vector4<T> operator / (const vector4<T>& a,const vector4<T>& b)						
            { return vector4<T> (a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
	    template < typename T >
        inline vector4<T> operator / (const T& a,const vector4<T>& b)						
            { return vector4<T> (a / b.x, a / b.y, a / b.z, a / b.w); }
	    template < typename T >
        inline vector4<T> operator / (const vector4<T>& a,const T& b)						
            { return vector4<T> (a.x / b, a.y / b, a.z / b, a.w / b); }

        template < typename T >
	    inline bool operator == (const vector4<T>& a, const vector4<T>& b)						
            { return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w)); }
	    template < typename T >
        inline bool operator != (const vector4<T>& a, const vector4<T>& b)						
            { return ((a.x != b.x) && (a.y != b.y) && (a.z != b.z) && (a.w != b.w)); }
	    template < typename T >
        inline bool operator <= (const vector4<T>& a, const vector4<T>& b)						
            { return ((a.x <= b.x) && (a.y <= b.y) && (a.z <= b.z) && (a.w <= b.w)); }
	    template < typename T >
        inline bool operator >= (const vector4<T>& a, const vector4<T>& b)						
            { return ((a.x >= b.x) && (a.y >= b.y) && (a.z >= b.z) && (a.w >= b.w)); }
            
	    template < typename T >
        inline bool operator < (const vector4<T>& a, const vector4<T>& b)							
            { return ((a.x < b.x) && (a.y < b.y) && (a.z < b.z) && (a.w < b.w)); }
	    template < typename T >
        inline bool operator > (const vector4<T>& a, const vector4<T>& b)							
            { return ((a.x > b.x) && (a.y > b.y) && (a.z > b.z) && (a.w > b.w)); }
        template < typename T >
        inline T lenghtSq(const vector4<T>& v)									
            { return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }

        template < typename T >
	    inline T lenght(const vector4<T>& v)									
            { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
        template < typename T >
	    inline vector4<T> normalize(const vector4<T>& v)									
            { return v / (T)sqrt(double(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w)); }
        template < typename T >
	    inline vector4<T> normalizex(const vector4<T>& v)								
            { return v / (T)(sqrt(double(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w)) + 0.0001); }

        template < typename T >
	    inline vector4<T> cross(const vector4<T>& v1, vector4<T>& v2)						
            { return vector4<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x, v1.w * v2.w); }
	    template < typename T >
        inline T dot(const vector4<T>& v1, const vector4<T>& v2)					
            { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w; }
	    template < typename T >
        inline T angle(const vector4<T>& v1, const vector4<T>& v2)				
            { return (T)(acos(double((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w)) /
                        sqrt((double)((v1.x * v1.x + v1.y * v1.y + v1.z * v1.z + v1.w * v1.w)) * T((v2.x * v2.x + v2.y * v2.y + v2.z * v2.z + v2.w * v2.w))))); }
	    template < typename T >
        inline vector4<T> interpolate_coords(const vector4<T>& v1, const vector4<T>& v2, const float p)								
            { return v1 + p * (v2 - v1); }
	    template < typename T >
        inline vector4<T> interpolate_normal(const vector4<T>& v1, const vector4<T>& v2, const float p)								
            { return normalize(v1 + p * (v2 - v1)); }
	    template < typename T >
        inline bool nearequal(const vector4<T>& v1, vector4<T>& v2, const vector2<T>& epsilon)							
            { return ( abs(float(v1.x - v2.x )) <= epsilon && 
                ( abs(float(v1.y - v2.y)) <= epsilon) && (abs(float(v1.z - v2.z)) <= epsilon) && (abs(float(v1.w - v2.w)) <= epsilon)); }
   
        template <typename T>
        inline vector4<T> _min(const vector4<T>& c1, const vector4<T>& c2)
            {return vector4<T>(utb::min<T>(c1.x, c2.x), utb::min<T>(c1.y, c2.y), utb::min<T>(c1.z, c2.z), utb::min<T>(c1.w, c2.w));}
        template <typename T>
        inline vector4<T> _max(const vector4<T>& c1, const vector4<T>& c2)
            {return vector4<T>(utb::max<T>(c1.x, c2.x), utb::max<T>(c1.y, c2.y), utb::max<T>(c1.z, c2.z));}
	    template <typename T>
        inline vector4<T> scale(const vector4<T>& v, const float s)
            {return vector4<T>(v.x * s, v.y*s, v.z*s, v.w*s);}

        using vec4f = vector4 <float>  ;
        using vec4d = vector4 <double>;
    }
}

#endif