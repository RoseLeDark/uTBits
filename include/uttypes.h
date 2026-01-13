/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
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