/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
#ifndef __UT_ENDIANESS_H__
#define __UT_ENDIANESS_H__

#include "utconfig.h"


namespace utb {
    
    template<class T = void>
    struct endian  {
        static constexpr unsigned int little = __ORDER_LITTLE_ENDIAN__;
        static constexpr unsigned int big = __ORDER_LITTLE_ENDIAN__;

        static constexpr unsigned int native()  {  
            const unsigned int i = 0xFFFF0000;
            return (*reinterpret_cast<const unsigned char*>(&i) == 0) ? little : big; 
        }
    };
}

#endif