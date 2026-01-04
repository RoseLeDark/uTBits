#ifndef __UT_MATH_H__
#define __UT_MATH_H__

#include "utconfig.h"
#include "utalgorithm.h"

namespace utb {
    namespace math {
        template <typename T>
        inline T factorial(T p) {
            if ( p == 0 || p == 1 ) return 1;
            else if ( p < 0 ) return 0;

            T f = 1;
            for(; p > 1; p--) f *= p;
              
            return f;
        }
        template <typename T>
        inline T barycentric(T value1, T value2, T value3, T amount1, T amount2)  {
                return value1 + (value2 - value1) * amount1 + (value3 - value1) * amount2;
        }

        template <typename T>
        inline T catmullrom(T value1, T value2, T value3, T value4, T amount) {
                float amountSq = amount * amount;
                float amountCube = amountSq * amount;
                return (( T(2.0) * value2 +
                (-value1 + value3) * amount +
                ((T)2.0 * value1 - (T)5.0 * value2 + (T)4.0 * value3 - value4) * amountSq +
                ((T)3.0 * value2 - (T)3.0 * value3 - value1 + value4) * amountCube) * (T)0.5);
        }
	    template <typename T>	
        inline T clamp (T value, T min, T max) {
                return utb::min<T> (utb::max<T> (min, value), max);
        }
        template <typename T>	
        inline T hermite (T value1, T tangent1, T value2, T tangent2, T amount) {
                T s = amount;
                T s2 = s * s;
                T s3 = s2 * s;
                T h1 =  2 * s3 - 3 * s2 + 1;
                T h2 = -2 * s3 + 3 * s2;
                T h3 =      s3 - 2 * s2 + s;
                T h4 =      s3 -     s2;
                return value1 * h1 + value2 * h2 + tangent1 * h3 + tangent2 * h4;
        }

        template <typename T>	
        inline T Lerp (T value1, T value2, T amount)
        {
            return value1 + (value2 - value1) * amount;
        }
        template <typename T>	
        inline T SmoothStep (T value1, T value2, T amount)
        {
            amount = amount * amount * ((T)3 - (T)2 * amount);
            return value1 + (value2 - value1) * amount;
        }
        template <typename T>
        inline T degrees (T radians)
        {
            return radians * (180/ PI);
        }
        template <typename T>
        inline float radians (float degrees)
        {
            return degrees * (PI / 180);
        }
    }
}

#endif