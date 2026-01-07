#ifndef __UTATOMIC_GCC_PLATFORM_H__
#define __UTATOMIC_GCC_PLATFORM_H__

#include "../utconfig.h"
#if UTB_CONFIG_ENABLE_ATOMIC == UTB_YES

#include "../utalgorithm.h"
#include "../uttypetraits.h"

#include "utatomic_flags.h"

#ifdef __GCC_ATOMIC_BOOL_LOCK_FREE
#define	ATOMIC_BOOL_LOCK_FREE		__GCC_ATOMIC_BOOL_LOCK_FREE
#endif
#ifdef __GCC_ATOMIC_CHAR_LOCK_FREE
#define	ATOMIC_CHAR_LOCK_FREE		__GCC_ATOMIC_CHAR_LOCK_FREE
#endif
#ifdef __GCC_ATOMIC_CHAR16_T_LOCK_FREE
#define	ATOMIC_CHAR16_T_LOCK_FREE	__GCC_ATOMIC_CHAR16_T_LOCK_FREE
#endif
#ifdef __GCC_ATOMIC_CHAR32_T_LOCK_FREE
#define	ATOMIC_CHAR32_T_LOCK_FREE	__GCC_ATOMIC_CHAR32_T_LOCK_FREE
#endif
#ifdef __GCC_ATOMIC_WCHAR_T_LOCK_FREE
#define	ATOMIC_WCHAR_T_LOCK_FREE	__GCC_ATOMIC_WCHAR_T_LOCK_FREE
#endif
#ifdef __GCC_ATOMIC_SHORT_LOCK_FREE
#define	ATOMIC_SHORT_LOCK_FREE		__GCC_ATOMIC_SHORT_LOCK_FREE
#endif
#ifdef __GCC_ATOMIC_INT_LOCK_FREE
#define	ATOMIC_INT_LOCK_FREE		__GCC_ATOMIC_INT_LOCK_FREE
#endif
#ifdef __GCC_ATOMIC_LONG_LOCK_FREE
#define	ATOMIC_LONG_LOCK_FREE		__GCC_ATOMIC_LONG_LOCK_FREE
#endif
#ifdef __GCC_ATOMIC_LLONG_LOCK_FREE
#define	ATOMIC_LLONG_LOCK_FREE		__GCC_ATOMIC_LLONG_LOCK_FREE
#endif
#ifdef __GCC_ATOMIC_POINTER_LOCK_FREE
#define	ATOMIC_POINTER_LOCK_FREE	__GCC_ATOMIC_POINTER_LOCK_FREE
#endif

namespace utb {
    namespace atomic {
        /**
         *  @brief Generic atomic type, primary class template.
         *  @tparam T  Type to be made atomic, must be trivally copyable.
         */
        template <typename T>
        struct gcc_atomic_type {
            static constexpr bool is_always_lock_free  = __atomic_always_lock_free(sizeof(T), 0);

            using value_type = T;
            using volatile_pointer = volatile T*;
            using difference_type = T;


            static void store (volatile_pointer obj, value_type v, memory_order order = memory_order::SeqCst)
                { __atomic_store_n (obj, v, static_cast<int>(order)); }

            static value_type load (volatile_pointer obj, memory_order order = memory_order::SeqCst)
                { return __atomic_load_n (obj, static_cast<int>(order)); }

            static value_type exchange (volatile_pointer obj, value_type v, memory_order order = memory_order::SeqCst)
                { return __atomic_exchange_n (obj, v, static_cast<int>(order)); }

            static bool compare_exchange_n (volatile_pointer obj,value_type& expected, value_type& desired, bool b,
                                    memory_order order = memory_order::SeqCst)
                { return __atomic_compare_exchange_n (obj, &expected, desired, b,
                                                    order, static_cast<int>(order)); }

            static bool compare_exchange(volatile_pointer obj,value_type& expected, value_type& desired, int i, memory_order order = memory_order::SeqCst)
                { return _atomic_compare_exchange (obj, &expected, &desired, i, order, static_cast<int>(order)); }

            


            static value_type fetch_add (volatile_pointer obj, value_type v, memory_order order = memory_order::SeqCst )
                { return __atomic_fetch_add (obj, v, static_cast<int>(order)); }

            static value_type fetch_sub (volatile_pointer obj, value_type v, memory_order order = memory_order::SeqCst )
                { return __atomic_fetch_sub (obj, v, static_cast<int>(order)); }

            static value_type fetch_and (volatile_pointer obj, value_type v, memory_order order = memory_order::SeqCst )
                { return __atomic_fetch_and (obj, v, static_cast<int>(order)); }

            static value_type fetch_or (volatile_pointer obj, value_type v, memory_order order = memory_order::SeqCst )
                { return __atomic_fetch_or (obj, v, static_cast<int>(order)); }

            static value_type fetch_xor (volatile_pointer obj, value_type v, memory_order order = memory_order::SeqCst )
                { return __atomic_fetch_xor (obj, v, static_cast<int>(order)); }

            static value_type add_fetch (volatile_pointer obj,value_type v, memory_order order = memory_order::SeqCst )
                { return __atomic_add_fetch (obj, v, static_cast<int>(order)); }

            static value_type sub_fetch (volatile_pointer obj,value_type v, memory_order order = memory_order::SeqCst )
                { return __atomic_sub_fetch (obj, v, static_cast<int>(order)); }

            static value_type and_fetch (volatile_pointer obj,value_type v, memory_order order = memory_order::SeqCst )
                { return __atomic_and_fetch (obj, v, static_cast<int>(order)); }

            static value_type or_fetch (volatile_pointer obj,value_type v, memory_order order = memory_order::SeqCst )
                { return __atomic_or_fetch (obj, v, static_cast<int>(order)); }

            static value_type xor_fetch (volatile_pointer obj,value_type v, memory_order order = memory_order::SeqCst )
                { return __atomic_xor_fetch (obj, v, static_cast<int>(order)); }

            static bool is_lock_free(volatile_pointer obj)
                { return __atomic_is_lock_free (sizeof(value_type), obj); }
        };

    } // namespace atomic
}

#endif
#endif