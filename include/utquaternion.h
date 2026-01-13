#ifndef __UTQUATERNION_H__
#define __UTQUATERNION_H__

#include "utvector4.h"
#include "utvector3.h"
#include "utalgorithm.h"
#include "utmap.h"
#include "utfunctional.h"

#include <cfloat>

namespace utb {
    /// @brief Mathematical utilities namespace
    namespace math {
        /// @brief Quaternion class for 3D rotations and orientations
        /// @tparam T Scalar type (float, double, etc.)
        template <typename T>
        class quaternion {
        public:
            using value_type = T;
            using self_type = quaternion<T>;
            using pointer = T* ;
            using const_pointer = const T* ;

            union
            {
                struct {
                    value_type x;
                    value_type y;
                    value_type z;
                    value_type s;
                }
		        float qu[4];
            };

            quaternion() : vec(vector4<value_type>(0.0f))	{}

            quaternion(value_type fs, value_type x, value_type y, value_type z) 
                : x(x), y(y), z(z), s(fs)	{}
            quaternion(const vector3<value_type> &axis);
            quaternion(float *pfs)  
                : x(pfs[1]), y(pfs[2]), z(pfs[3]), s(pfs[0]))	{}

            quaternion(const self_type& q) : x(q.x), y(q.y), z(q.z), s(q.s)	{}
            quaternion(self_type&& q) : x(utb::move(q.x)), y(utb::move(q.y)), z(utb::move(q.z)), s(utb::move(q.s))	{}

            float s() const { return s; }
            vector3<value_type> v() const { return vector3<value_type>(x, y, z); }

            operator pointer ()		{ return (pointer)(qu); }
            operator const_pointer () const	{ return (float*)qu; }

            self_type& operator =  (const self_type& q)	{ 
                vec = q.vec;  return *this; 
            }
            self_type& operator += (const self_type& q)	{
                vec += q.vec;  return *this; 
            }
            self_type& operator -= (const self_type& q)	{
                vec -= q.vec;  return *this; 
            }
            self_type& operator -= (const self_type& q)		{
                vec -= q.vec;  return *this; 
            }
            self_type& operator *= (const self_type& b) {
                s = ((s * b.s) - (x * b.x) - (y * b.y) - (z * b.z));
                x = ((s * b.x) + (x * b.s) + (y * b.z) - (z * b.y));
                y = ((s * b.y) - (x * b.z) + (y * b.s) + (z * b.x));
                z = ((s * b.z) + (x * b.y) - (y * b.x) + (z * b.s));
                return *this;
            }
            self_type& operator *= (const value_type f)    { 
                vec *= f;  return *this; 
            }
            self_type& operator /= (const self_type& q)    {
                vec /= q.vec;  return *this; 
            }
            self_type& operator /= (const value_type f)    { 
                vec /= f;  return *this; 
            }
            
            bool operator == (const self_type& q) const {
                return vec == q.vec;
            }
            bool operator != (const self_type& q) const {
                return !(*this == q);
            }
            bool operator < (const self_type& q) const {
                return (x < q.x) && (y < q.y) && (z < q.z) && (s < q.s);
            }
            bool operator > (const self_type& q) const {
                return (x > q.x) && (y > q.y) && (z > q.z) && (s > q.s);
            }
            bool operator <= (const self_type& q) const {
                return (x <= q.x) && (y <= q.y) && (z <= q.z) && (s <= q.s);
            }
            bool operator >= (const self_type& q) const {
                return (x >= q.x) && (y >= q.y) && (z >= q.z) && (s >= q.s);
            }
        };

        template <typename T> 
	    inline quaternion<T> identy() { return quaternion<T>(1.0f, 0.0f, 0.0f, 0.0f); }

        template <typename T> 
	    inline T lenght(const quaternion<T>& v)											
            { return (T)sqrt((double)(v.v.w * v.v.w + v.v.x * v.v.x + v.v.y * v.v.y + v.v.z * v.v.z)); }

	    template <typename T> 
        inline T lenghtSq(const quaternion<T>& v)										
            { return (v.v.w * v.v.w + (T)v.v.x * (T)v.v.x + (T)v.v.y * (T)v.v.y + (T)v.v.z * (T)v.v.z); }

        template <typename T>
        inline quaternion<T> invert(const quaternion<T> &q)  {  
            T temp = lenghtSq(q); quaternion<T> tq = q;  tq.v.w /= temp; tq.v.x /= -temp; tq.v.y /= -temp; tq.v.z /= -temp; return q; 
        }
        
        template <typename T>
        inline quaternion<T> exp(const quaternion<T>& v) {
            T Mul;
            quaternion<T> temp = v;
            T Length = lenght(temp.v);

            if (Length > 1.0e-4) Mul = sin(Length)/Length;
            else Mul = 1.0;

            temp.v.w = cos(Length); // Scalar part

            // Vector part
            temp.v.x *= Mul; 
            temp.v.y *= Mul;
            temp.v.z *= Mul;
            return temp;
        }
        template <typename T>
        inline quaternion<T> log(const quaternion<T>& v){
            T Length;
	        quaternion<T> temp = v;

            Length = lenght(temp.v);
            Length = atan(Length/temp.v.w);

            temp.v.w = 0.0;

            temp.v.x *= Length;
            temp.v.y *= Length;
            temp.v.z *= Length;

            return temp;
        }
        template <typename T>
        inline quaternion<T> normalize(const quaternion<T>& v) {
            T norme = lenght(v);
	        quaternion<T> temp = v;

            if (norme == 0.0) {
                temp.v.w = 1.0;
                temp.v.x = 0.0;
                temp.v.y = 0.0;
                temp.v.z = 0.0;
            } else {
                float recip = 1.0/norme;

                temp.v.w *= recip;
                temp.v.x *= recip;
                temp.v.y *= recip;
                temp.v.z *= recip;
            }
            return temp;
        }
        template <typename T>
        inline quaternion<T> conjugate(const quaternion<T>& v) {
            quaternion<T> temp = v;

            temp.v.w = -temp.v.w;
            temp.v.x = -temp.v.x;
            temp.v.y = -temp.v.y;
            temp.v.z = -temp.v.z;

            return temp;
        }
        template <typename T>
        inline quaternion<T> pow(const quaternion<T>& v, const T exp){
            if (fabs(v.s) > .9999)
                return v;
            
            T   alpha = acos(v.s);
            T   newAlpha = alpha * exp;
            quaternion<T> result;
            result.v.w = cos(newAlpha);

            float   mult = sin(newAlpha) / sin(alpha);
            result.v.x = (float)v.v.x * mult;
            result.v.y = (float)v.v.y * mult;
            result.v.z = (float)v.v.z * mult;

            return result;
        }
        template <typename T>
        inline T dot(const quaternion<T> &a, const quaternion<T> &b) {
            return a.v.w*b.v.w + a.v.x*b.v.x + a.v.y*b.v.y + a.v.z*b.v.z;
        }

        template <typename T>
        inline quaternion<T> power(const quaternion<T>& qu, T degree) {
                if ( degree == 0 ) return quaternion<T>((T)1.0, 0, 0, 0);
                quaternion<T> tmp_qu = qu ;

                for ( float f = 1 ; f < abs(degree) ; f++ )
                        tmp_qu *= qu ;

                if ( degree < 0 )
                    return ( 1.0f / tmp_qu );

                return tmp_qu ;
        }

        template <typename T>
        inline quaternion<T> sin(const quaternion<T> &q) {
            quaternion<T> s;

            for( float n = 0; n < 6.0f; n++ )
		    s += pow( -1.0f ,n ) * (power( q , 2.0f * n + 1.0f ) ) /
                        ( utb::factorial<T>( 2.0f * n + 1.0f ) );

            return s ;
        }

        template <typename T>
        inline quaternion<T> cos(const quaternion<T> &q) {
            quaternion<T> s;

            for( T n = 1.0f; n <= 6.0f; n++ )
		        s += pow( -1.0f ,n ) * power( q , 2.0f * n ) /
                        factorial<T>( 2.0f * n ) ;

            return s ;
        }

         template <typename T>
        inline quaternion<T> tan(const quaternion<T> &q) {
            if ( lenghtSq(q) == 0.0 ) return quaternion<T>(1, 0, 0, 0) ;
            return sin( q ) / cos( q ) ;
        }
        template <typename T>
        inline quaternion<T> ctan(const quaternion<T> &q)
        {
            if ( lenghtSq(q) == 0 ) return quaternion<T>(1.0, 0.0, 0.0, 0.0) ;
            return cos( q ) / sin( q ) ;
        }

        template <typename T>
        inline quaternion<T> operator * (const quaternion<T>& a,const quaternion<T>& b) {
            quaternion<T> q;
            q.v.w =   ((a.v.w * b.v.w) - (a.v.x * b.v.x) - (a.v.y * b.v.y) - (a.v.z * b.v.z)); // Scalar part
            q.v.x = ((a.v.w * b.v.x) + (a.v.x * b.v.w) + (a.v.y * b.v.y) - (a.v.z * b.v.y)); // Vector part x
            q.v.y = ((a.v.w * b.v.y) - (a.v.x * b.v.z) + (a.v.y * b.v.w) + (a.v.z * b.v.x)); // Vector part y
            q.v.z = ((a.v.w * b.v.z) + (a.v.x * b.v.y) - (a.v.y * b.v.x) + (a.v.z * b.v.w)); // Vector part z
            return q;
        } 

        template <typename T>
        inline quaternion<T> quaternion_fromaxis(const float angle, vector3<T> axis)
        {
            T omega, s = lenght(axis), c;
            vector3<T> vt = axis;
            quaternion<T>  _ret;

            if (fabs(s) > FLT_EPSILON) {
                c = 1.0f/s;
                vt *= c;

                omega = -0.5f * angle;
                s = (T)sin(omega);

                quaternion<T> temp(cos(omega), s*vt.x, s*vt.y, s*vt.z);
                return normalize(temp);
            } 
            quaternion<T> temp(1.0, vector3<T>(0.0f));
            return normalize(temp);
        }

        template <typename T> 
        quaternion<T>::quaternion(const vector3<value_type> &axis) {
            value_type cos_z_2 = (value_type)cos(0.5*axis.z);
            value_type cos_y_2 = (value_type)cos(0.5*axis.y);
            value_type cos_x_2 = (value_type)cos(0.5*axis.x);

            value_type sin_z_2 = (value_type)sin(0.5*axis.z);
            value_type sin_y_2 = (value_type)sin(0.5*axis.y);
            value_type sin_x_2 = (value_type)sin(0.5*axis.x);

            // and now compute quaternion
            v.w  = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
            v.x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
            v.y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
            v.z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
        }


        using quatf = quaternion<float>;
        using quatd = quaternion<double>;
        using quati = quaternion<int>;
        using quats = quaternion<short>;
    }
}

#endif // __UTQUATERNION_H__