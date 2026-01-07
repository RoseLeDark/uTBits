#ifndef __UTATOMIC_PRIMARY_TYPES_H__
#define __UTATOMIC_PRIMARY_TYPES_H__

#include "../utconfig.h"
#if UTB_CONFIG_ENABLE_ATOMIC == UTB_YES

 #if defined(__GNUC__) || defined(__clang__) || defined(__xlc__)
    #include "utatomic_gcc.h"
    #define UTB_ATOMIC 1
#else
#error Unsupported compiler / system.
#endif

namespace utb {
    namespace atomic {

       

    #if UTB_ATOMIC == 1
        template <typename T>
        struct base_atomic  {
            static constexpr bool is_always_lock_free  = ATOMIC_BOOL_LOCK_FREE == 2;

            using value_type = T;
            using difference_type = T;
            using arch_atomic_type = gcc_atomic_type<value_type>;
            using self_type = base_atomic<T>;

            base_atomic()  = default;
            ~base_atomic()  = default;

            base_atomic(const self_type&) = delete;
            base_atomic& operator=(const self_type&) = delete;
            base_atomic& operator=(const self_type&) volatile = delete;

            constexpr base_atomic(value_type value)  : m_vtValue(value) { }

            value_type get() { return m_vtValue; }

            void store (value_type v, memory_order order = memory_order::SeqCst)
                {   arch_atomic_type::store(&m_vtValue, v, order); }

            value_type load (memory_order order = memory_order::SeqCst) const
                { return arch_atomic_type::load(&m_vtValue, order); }

            value_type exchange (value_type v, memory_order order = memory_order::SeqCst)
                { return arch_atomic_type::exchange(&m_vtValue, v, order); }

            bool compare_exchange_strong(value_type& expected, value_type& desired, memory_order order = memory_order::SeqCst)
                { return arch_atomic_type::compare_exchange (&m_vtValue, &expected, &desired, 0, order, static_cast<int>(order)); }

            bool compare_exchange_weak(value_type& expected, value_type& desired, memory_order order = memory_order::SeqCst)
                { return arch_atomic_type::compare_exchange (&m_vtValue, &expected, &desired, 1, order, static_cast<int>(order)); }

            bool compare_exchange_t (value_type& expected, value_type& desired,  memory_order order = memory_order::SeqCst)
                { return arch_atomic_type::compare_exchange_n(&m_vtValue,expected, desired, true, order); }

            bool compare_exchange_f (value_type& expected, value_type& desired, memory_order order = memory_order::SeqCst)
                { return arch_atomic_type::compare_exchange_n(&m_vtValue,expected, desired, false, order); }

            value_type fetch_add (value_type v, memory_order order = memory_order::SeqCst )
                { return arch_atomic_type::fetch_add (&m_vtValue,v, order); }

            value_type fetch_sub (value_type v, memory_order order = memory_order::SeqCst )
                { return arch_atomic_type::fetch_sub (v, order); }

            value_type fetch_and (value_type v, memory_order order = memory_order::SeqCst )
                { return arch_atomic_type::fetch_and (&m_vtValue,v, order); }

            value_type fetch_or (value_type v, memory_order order = memory_order::SeqCst )
                { return arch_atomic_type::fetch_or (&m_vtValue, v, order); }

            value_type fetch_xor (value_type v, memory_order order = memory_order::SeqCst )
                { return arch_atomic_type::fetch_xor (&m_vtValue, v, order); }

            value_type add_fetch (value_type v, memory_order order = memory_order::SeqCst )
                { return arch_atomic_type::add_fetch (&m_vtValue, v, order); }

            value_type sub_fetch (value_type v, memory_order order = memory_order::SeqCst )
                { return arch_atomic_type::sub_fetch (v, order); }

            value_type and_fetch (value_type v, memory_order order = memory_order::SeqCst )
                { return arch_atomic_type::and_fetch (&m_vtValue, v, order); }

            value_type or_fetch (value_type v, memory_order order = memory_order::SeqCst )
                { return arch_atomic_type::or_fetch (v, order); }

            value_type xor_fetch (value_type v, memory_order order = memory_order::SeqCst )
                { return arch_atomic_type::xor_fetch (&m_vtValue, v, order); }

            bool is_lock_free() const
                { return arch_atomic_type::is_lock_free(&m_vtValue); }

            bool is_lock_free() const volatile
                { return arch_atomic_type::is_lock_free(); }

            inline operator value_type() const	         { return arch_atomic_type::load(&m_vtValue); }
            inline operator value_type() const volatile  { return arch_atomic_type::load(&m_vtValue); }

            inline value_type operator ++ (int)          { return arch_atomic_type::add_fetch (&m_vtValue, 1); }
            inline value_type operator -- (int)          { return arch_atomic_type::sub_fetch (&m_vtValue, 1); }
            inline value_type operator ++ ()             { return arch_atomic_type::add_fetch (&m_vtValue, 1); }
            inline value_type operator -- ()             { return arch_atomic_type::sub_fetch (&m_vtValue, 1); }

            inline value_type operator ++ (int) volatile { return arch_atomic_type::add_fetch (&m_vtValue, 1); }
            inline value_type operator -- (int) volatile { return arch_atomic_type::sub_fetch (&m_vtValue, 1); }
            inline value_type operator ++ ()    volatile { return arch_atomic_type::add_fetch (&m_vtValue, 1); }
            inline value_type operator -- ()    volatile { return arch_atomic_type::sub_fetch (&m_vtValue, 1); }
            inline value_type operator += (value_type v) { return arch_atomic_type::add_fetch (&m_vtValue, v); }
            inline value_type operator -= (value_type v) { return arch_atomic_type::sub_fetch (&m_vtValue, v); }
            inline value_type operator &= (value_type v) { return arch_atomic_type::and_fetch (&m_vtValue, v); }
            inline value_type operator |= (value_type v) { return  arch_atomic_type::or_fetch (&m_vtValue, v); }
            inline value_type operator ^= (value_type v) { return arch_atomic_type::xor_fetch (&m_vtValue, v); }      
            inline value_type operator  = (value_type v) { arch_atomic_type::store(&m_vtValue, v); return v; }
            inline value_type operator  = (value_type v) volatile { arch_atomic_type::store(&m_vtValue, v); return v; }

        private:
            volatile value_type m_vtValue;
        };
        
        template<typename T>
        struct base_atomic<T*> {
            static constexpr bool is_always_lock_free  = ATOMIC_POINTER_LOCK_FREE == 2;

            using value_type = T*;
            using arch_atomic_type = gcc_atomic_type<value_type>;
            using pointer = T*;
            using self_type = base_atomic<T*>;
            using difference_type = ptrdiff_t;

            base_atomic() = default;
            ~base_atomic() = default;

            constexpr base_atomic(pointer value) : m_vtValue(value) { }

            inline operator pointer() const	         { return arch_atomic_type::load(&m_vtValue); }
            inline operator pointer() const volatile  { return arch_atomic_type::load(&m_vtValue); }
        private:
            volatile pointer m_vtValue;
        };
    #endif // UTB_ATOMIC == 1             
    } // namespace atomic
}
#endif // UTB_CONFIG_ENABLE_ATOMIC
#endif // __UTATOMIC_FLAGS_H__