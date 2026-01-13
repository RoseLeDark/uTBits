/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
#ifndef __UTCONFIG_H__
#define __UTCONFIG_H__

#define UTB_YES 1
#define UTB_NO  0

#define UTB_ENABLE 1
#define UTB_DISABLE 0

#define UTB_SIZE_TYPE_16 16
#define UTB_SIZE_TYPE_32 32 
#define UTB_SIZE_TYPE_64 64
#define UTB_SIZE_TYPE_AUTO 0

/// ---------- Configuration Options ----------
#ifndef UTB_MAX_MAP_ENTRYS
#define UTB_MAX_MAP_ENTRYS 16
#endif

#ifndef UTB_SIZE_TYPE 
#define UTB_SIZE_TYPE UTB_SIZE_TYPE_AUTO
#endif

#ifndef UTB_CONFIG_DEFAULT_STACK_SIZE
#define UTB_CONFIG_DEFAULT_STACK_SIZE UTB_SIZE_TYPE_AUTO
#endif

#ifndef UTB_CONFIG_ENABLE_ATOMIC
#define UTB_CONFIG_ENABLE_ATOMIC UTB_YES
#endif

#ifndef UTB_CONFIG_BASIC_HASHMUL_VAL
	/// Basic value for struct::hash as basic hash calculate @see utb::hash
	#define UTB_CONFIG_BASIC_HASHMUL_VAL 2149645487U
#endif // MN_THREAD_CONFIG_BASIC_HASHMUL_VAL


/// ---- DO NOT EDIT BELOW THIS LINE ----
#if UTB_SIZE_TYPE == UTB_SIZE_TYPE_AUTO
#undef UTB_SIZE_TYPE
    #if __SIZEOF_POINTER__ == 2
        using index_type = unsigned short;        // 16-bit MCU
        #define UTB_SIZE_TYPE UTB_SIZE_TYPE_16
    #elif __SIZEOF_POINTER__ == 4
        using index_type = unsigned int;          // 32-bit system
        #define UTB_SIZE_TYPE UTB_SIZE_TYPE_32
    #elif __SIZEOF_POINTER__ == 8
        using index_type = unsigned long long;    // 64-bit system
        #define UTB_SIZE_TYPE UTB_SIZE_TYPE_64
    #else
        #error "Unknown pointer size — cannot auto-detect UTB_SIZE_TYPE"
    #endif

#else

    #if UTB_SIZE_TYPE == UTB_SIZE_TYPE_16
        using index_type = unsigned short;
    #elif UTB_SIZE_TYPE == UTB_SIZE_TYPE_32
        using index_type = unsigned int;
    #elif UTB_SIZE_TYPE == UTB_SIZE_TYPE_64
        using index_type = unsigned long long;
    #else
        #error "UTB_SIZE_TYPE is not valid"
    #endif

    
#endif

#if UTB_CONFIG_DEFAULT_STACK_SIZE == UTB_SIZE_TYPE_AUTO
    #undef UTB_CONFIG_DEFAULT_STACK_SIZE
    #if __SIZEOF_POINTER__ == 2
        #define UTB_CONFIG_DEFAULT_STACK_SIZE 16                  // 16-bit MCU
    #elif __SIZEOF_POINTER__ == 4
        #define UTB_CONFIG_DEFAULT_STACK_SIZE 32         // 32-bit system
    #elif __SIZEOF_POINTER__ == 8
        #define UTB_CONFIG_DEFAULT_STACK_SIZE 64               // 64-bit system
    #else
        #error "Unknown default stack size — cannot auto-detect UTB_CONFIG_DEFAULT_STACK_SIZE"
    #endif  
#endif




static_assert(sizeof(index_type) * 8 == UTB_SIZE_TYPE,
              "index_type size does not match UTB_SIZE_TYPE");
namespace utb {
    using size_t = index_type;

   /*#if UTB_CONFIG_ENABLE_ATOMIC == UTB_YES
        #if USE_STD_ATOMIC == UTB_YES
            template<typename T>
            using atomic_t = std::atomic<T>;
        #elif USE_UTB_ATOMIC == UTB_YES
            #include "utatomic.h"
            template<typename T>
            using atomic_t = utb::atomic<T>;
        #endif
    #endif*/
}

#endif