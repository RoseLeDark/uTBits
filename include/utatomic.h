#ifndef __UTB_ATOMIC_PRIMARY_TYPES_H__
#define __UTB_ATOMIC_PRIMARY_TYPES_H__

#include "utconfig.h"
#include "atomic/utatomic_types.h"

#if UTB_ATOMIC == 1
namespace utb {
    namespace atomic {
        template <typename TAtomicType, TAtomicType TTrue = true, TAtomicType TFalse = false>
        class basic_atomic_flag  {
        public:
            using flag_type = TAtomicType;
            using reference = TAtomicType&;

            constexpr basic_atomic_flag() noexcept
                : m_bFlag(0) { }

            constexpr basic_atomic_flag(const flag_type& flag) noexcept
                : m_bFlag(flag) { }

            basic_atomic_flag(const basic_atomic_flag&) noexcept = delete;

            reference operator=(const reference)          noexcept = delete;
            reference operator=(const reference) volatile noexcept = delete;

            void clear(memory_order order = memory_order::SeqCst) noexcept {
                m_bFlag.store(TFalse, order);
            }
            flag_type test_and_set(memory_order order = memory_order::SeqCst) noexcept {
                return m_bFlag.exchange(TTrue, order);
            }
            flag_type test(memory_order order = memory_order::SeqCst) const {
                return m_bFlag.load(order);
            }
        private:
            _atomic<flag_type> m_bFlag;
        };

        using atomic_flag = basic_atomic_flag<bool>;

         // Signad basic types
        using atomic_bool           = base_atomic<bool>;
        using atomic_char	        = base_atomic<char>;
        using atomic_schar	        = base_atomic<signed char>;
        using atomic_short	        = base_atomic<short>;
        using atomic_int	        = base_atomic<int>;
        using atomic_long	        = base_atomic<long>;
        using atomic_int_least8_t	= base_atomic<int_least8_t>;
        using atomic_int_least16_t	= base_atomic<int_least16_t>;
        using atomic_int_least32_t	= base_atomic<int_least32_t>;
        using atomic_int_least64_t	= base_atomic<int_least64_t>;
        using atomic_int_fast8_t	= base_atomic<int_fast8_t>;
        using atomic_int_fast16_t	= base_atomic<int_fast16_t>;
        using atomic_int_fast32_t	= base_atomic<int_fast32_t>;
        using atomic_int_fast64_t	= base_atomic<int_fast64_t>;
        using atomic_int8_t         = base_atomic<int8_t>;
        using atomic_int16_t        = base_atomic<int16_t>;
        using atomic_int32_t        = base_atomic<int32_t>;
        using atomic_int64_t        = base_atomic<int64_t>;

        // unsigned types
        using atomic_uchar	        = base_atomic<unsigned char>;
        using atomic_ushort	        = base_atomic<unsigned short>;
        using atomic_uint	        = base_atomic<unsigned int>;
        using atomic_ulong	        = base_atomic<unsigned long>;
        using atomic_uint_least8_t	= base_atomic<uint_least8_t>;
        using atomic_uint_least16_t	= base_atomic<uint_least16_t>;
        using atomic_uint_least32_t	= base_atomic<uint_least32_t>;
        using atomic_uint_least64_t	= base_atomic<uint_least64_t>;
        using atomic_uint_fast8_t	= base_atomic<uint_fast8_t>;
        using atomic_uint_fast16_t	= base_atomic<uint_fast16_t>;
        using atomic_uint_fast32_t	= base_atomic<uint_fast32_t>;
        using atomic_uint_fast64_t	= base_atomic<uint_fast64_t>;
        using atomic_uint8_t        = base_atomic<uint8_t>;
        using atomic_uint16_t       = base_atomic<uint16_t>;
        using atomic_uint32_t       = base_atomic<uint32_t>;
        using atomic_uint64_t       = base_atomic<uint64_t>;


        // Spzial types
        using atomic_intptr_t	    = base_atomic<intptr_t>;
        using atomic_uintptr_t	    = base_atomic<uintptr_t>;
        using atomic_size_t	        = base_atomic<size_t>;
        using atomic_ptrdiff_t	    = base_atomic<ptrdiff_t>;
        using atomic_intmax_t	    = base_atomic<intmax_t>;
        using atomic_uintmax_t	    = base_atomic<uintmax_t>;
        using atomic_char16_t   	= base_atomic<char16_t>;
        using atomic_char32_t	    = base_atomic<char32_t>;
        using atomic_wchar_t	    = base_atomic<wchar_t>;
        using atomic_sig_t          = base_atomic<int>;

        template <typename T>
        using atomic_t = base_atomic<T>;
    }
}
#endif // UTB_CONFIG_ENABLE_ATOMIC
#endif // __UTATOMIC_PRIMARY_TYPES_H__