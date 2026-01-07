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