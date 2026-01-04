#ifndef __UT_VECTOR2_H__
#define __UT_VECTOR2_H__

#include "utconfig.h"
#include "utalgorithm.h"

#include <math.h>

namespace utb {
    namespace math {

        template < typename T >
        class vector2 {
        public:
            using value_type = T;
            using self_type = vector2<T> ;
            using pointer = T* ;
                
            union  {
                struct {
                    value_type x;
                    value_type y;
                };
                value_type c[2];
            };
            
                
                
            vector2() 														{}
	        vector2(value_type _x, value_type _y) : x(_x), y(_y)	{}
	        vector2(value_type _f) : x(_f), y(_f)			{}
            vector2(const vector2& vec) : x(vec.x), y(vec.y)	{}
            vector2(const pointer lpvec) : x(lpvec[0]), y(lpvec[1])	{}

            operator pointer ()		{ return (pointer)(c); }
            operator void* ()		{ return (void*)(c); }
                
            self_type& operator =  (const self_type& v)	{ 
                x = v.x; y = v.y; return *this; }

            self_type& operator += (const self_type& v)	{
                x += v.x; y += v.y; return *this; }

            self_type& operator -= (const self_type& v) { 
                x -= v.x; y -= v.y; return *this; }

            self_type& operator *= (const self_type& v) { 
                x *= v.x; y *= v.y; return *this; }

            self_type& operator /= (const self_type& v)	{ 
                x /= v.x; y /= v.y; return *this; }


            self_type& operator /= (const value_type& f)	{ 
                x /= f; y /= f; return *this; }

            self_type& operator *= (const value_type& f)	{ 
                x *= f; y *= f; return *this; }
	    };
        
        template < typename T >
        inline vector2<T> operator + (const vector2<T>& a, const vector2<T>& b)	
            { return vector2<T>(a.x + b.x, a.y + b.y); }

	    template < typename T >
        inline vector2<T> operator - (const vector2<T>& a, const vector2<T>& b)	
            { return vector2<T>(a.x - b.x, a.y - b.y); }

	    template < typename T >
        inline vector2<T> operator * (const vector2<T>& a, const vector2<T>& b)	
            { return vector2<T>(a.x * b.x, a.y * b.y); }

	    template < typename T >
        inline vector2<T> operator / (const vector2<T>& a, const vector2<T>& b)
            { return vector2<T>(a.x / b.x, a.y / b.y); }

	    template < typename T >
        inline vector2<T> operator + (const float& f, const vector2<T>& b)		
            { return vector2<T>(f + b.x, f + b.y); }

	    template < typename T >
        inline vector2<T> operator - (const float& f, const vector2<T>& b)		
            { return vector2<T>(f - b.x, f - b.y); }

	    template < typename T >
        inline vector2<T> operator * (const float& f, const vector2<T>& b)		
            { return vector2<T>(f * b.x, f * b.y); }

	    template < typename T >
        inline vector2<T> operator / (const float& f, const vector2<T>& b)		
            { return vector2<T>(f / b.x, f / b.y); }

	    template < typename T >
        inline vector2<T> operator - (const vector2<T>& a, const float& f)		
            { return vector2<T>(a.x - f, a.y - f); }

	    template < typename T >
        inline vector2<T> operator / (const vector2<T>& a, const float& f)		
            { return vector2<T>(a.x / f, a.y / f); }

        template < typename T >
	    inline bool operator == (const vector2<T>& a, const vector2<T>& b)		
            { return ((a.x == b.x) && (a.y == b.y)); }

        template < typename T >
        inline bool operator != (const vector2<T>& a, const vector2<T>& b)		
            { return ((a.x != b.x) && (a.y != b.y)); }

	    template < typename T >
        inline bool operator <= (const vector2<T>& a, const vector2<T>& b)		
            { return ((a.x <= b.x) && (a.y <= b.y)); }

	    template < typename T >
        inline bool operator >= (const vector2<T>& a, const vector2<T>& b)		
            { return ((a.x >= b.x) && (a.y >= b.y)); }

	    template < typename T >
        inline bool operator <  (const vector2<T>& a, const vector2<T>& b)		
            { return ((a.x < b.x) && (a.y < b.x)); }

	    template < typename T >
        inline bool operator >  (const vector2<T>& a, const vector2<T>& b)		
            { return ((a.x > b.x) && (a.y > b.y)); }
        
        template < typename T >
        inline T	 lenght(const  vector2<T>& v)									
            { return (T)(v.x * v.x + v.y * v.y ); }

	    template < typename T >
        inline T	 lenghtSq(const vector2<T>& v)									
            { return (T)sqrt(v.x * v.x + v.y * v.y ); }

	    template < typename T >
        inline vector2<T> normalize(const vector2<T>& v)									
            { return v / (T)sqrt(v.x * v.x + v.y * v.y ); }

	    template < typename T >
        inline vector2<T> normalizeEx(const vector2<T>& v)								
            { return v / (T)sqrt((v.x * v.x + v.y * v.y ) + 0.0001f); }

        template < typename T >
	    inline T dot(const vector2<T>& v1, const vector2<T>& v2)					
            { return (T)(v1.x * v2.x + v1.y * v2.y);}

        template < typename T >
	    inline T angle(const vector2<T>& v1, const vector2<T>& v2)  { 
            return (T)acos((v1.x * v2.x + v1.y * v2.y ) /
	               (T)sqrt((v1.x * v1.x + v1.y * v1.y ) * (v2.x * v2.x + v2.y * v2.y))); 
        }

        template < typename T >
	    inline vector2<T> interpolate_coords(const vector2<T>& v1, const vector2<T>& v2, const T p)								
            { return v1 + p * (v2 - v1); }

        template < typename T >
	    inline vector2<T> interpolate_normal(const vector2<T>& v1, const vector2<T>& v2, const T p)								
            { return normalize(v1 + p * (v2 - v1)); }

        template < typename T >
	    inline bool nearEqual(const vector2<T>& v1, vector2<T>& v2, const vector2<T>& epsilon)							
            { return (( abs((T)(v1.x - v2.x )) <= epsilon) && (utb::abs((T)(v1.y - v2.y)) <= epsilon)); }

        template <typename T>
        inline vector2<T> _min(const vector2<T>& c1, const vector2<T>& c2)
            {return vector2<T>(utb::min<T>(c1.x, c2.x), utb::min<T>(c1.y, c2.y));}

	    template <typename T>
        inline vector2<T> _max(const vector2<T>& c1, const vector2<T>& c2)
            {return vector2<T>(utb::max<T>(c1.x, c2.x), utb::max<T>(c1.y, c2.y));}

        template <typename T>
        inline vector2<T> scale(const vector2<T>& v, const float s)
            {return vector2<T>(v.x * s, v.y*s);}

        using vec2f = vector2<float>  ;
        using vec2d = vector2<double>;
    }
}

#endif