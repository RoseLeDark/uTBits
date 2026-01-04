#ifndef __UTTYPEDEF_H__
#define __UTTYPEDEF_H__

#include <stdint.h>
#include "utconfig.h"
#include <cstddef>

#define offsetof(TYPE, MEMBER) 					__builtin_offsetof (TYPE, MEMBER)

namespace utb {

    namespace math {
		constexpr double pi               = 3.14159265358979;
		constexpr double pi_reciprocal    = 0.31830988618379;
		constexpr double pi_squared       = 9.86960440108936;
		constexpr double e                = 2.71828182845905;
		constexpr double e_reciprocal     = 0.36787944117144;
		constexpr double e_squared        = 7.38905609893065;
		constexpr double root2            = 1.41421356237310;
		constexpr double root2_reciprocal = 0.70710678118655;
		constexpr double euler            = 0.57721566490153;
		constexpr double golden_ratio     = 1.61803398874989;
	}
    
    
}
#endif