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
}

#endif