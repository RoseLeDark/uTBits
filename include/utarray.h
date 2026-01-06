#ifndef __UT_ARRAY_H__
#define __UT_ARRAY_H__

#include "utconfig.h"

# include <cassert>
# include <typeinfo>

#include "utalgorithm.h"
#include "utfunctional.h"
#include "uttypetraits.h"

namespace utb {
    template<typename T, utb::size_t N>
    class basic_fixed_array {
    public:
        using self_type = basic_fixed_array<T, N>;

        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;

        using size_type = utb::size_t;
        using difference_type = ptrdiff_t;

        basic_fixed_array() { if(is_pointer<T>::value) fill(nullptr); else fill(T()); }
        basic_fixed_array(const value_type& val) 	{ fill(val); }
        basic_fixed_array(const self_type& other) {
            memcpy(m_nData, other.m_nData, sizeof(m_nData));
        }


        iterator  		begin() noexcept 			{ return &m_nData[0]; }
        constexpr const_iterator 	begin() const noexcept
            { return (m_nData[0]); }

        iterator  		end() noexcept 				{ return (m_nData[N-1]); }
        constexpr const_iterator 	end() const noexcept
            { return (m_nData[N-1]); }

        reference 		front() noexcept 			{ return (m_nData[0]); }
        const_reference front() const noexcept		{ return (m_nData[0]); }

        reference 		back() noexcept 			{ return (m_nData[N-1]); }
        const_reference back() const noexcept 		{ return (m_nData[N-1]); }

        size_type 		size() const noexcept 		{ return N; }

        reference 		at(size_type pos) 			{ return m_nData[pos]; }
        const_reference at(size_type pos) const 	{ return m_nData[pos]; }

        void fill(const value_type& val) {
            for (size_type i = 0; i < N; ++i) {
                m_nData[i] = val;
            }
        }

        void swap(self_type& other) noexcept  {
            swap_ranges(begin(), end(), other.begin());
        }

        reference operator[](size_type pos) noexcept {
            return m_nData[pos];
        }

        constexpr const_reference operator[](size_type pos) const noexcept {
            return m_nData[pos];
        }

        bool is_equal(const self_type& other) {
            return utb::equal(begin(), end(), other.begin());
        }

    private:
        value_type m_nData[N];
    };

    // Array comparisons.
    template<typename T, utb::size_t N>
    inline bool  operator == (const basic_fixed_array<T, N>& a, const basic_fixed_array<T, N>& b) {
        return a.is_equal(b);
    }

    template<typename T, utb::size_t N>
    inline bool  operator != (const basic_fixed_array<T, N>& a, const basic_fixed_array<T, N>& b) {
        return !(a.is_equal(b));
    }


    template<typename T, utb::size_t N>
    inline bool  operator < (const basic_fixed_array<T, N>& a, const basic_fixed_array<T, N>& b) {
        for(int i = 0; i<N; i++)
            if(a[i] >= b[i]) return false;
        return true;
    }

    template<typename T, utb::size_t N>
    inline bool  operator <= (const basic_fixed_array<T, N>& a, const basic_fixed_array<T, N>& b) {
        for(int i = 0; i<N; i++)
            if(a[i] > b[i]) return false;
        return true;
    }

    template<typename T, utb::size_t N>
    inline bool  operator > (const basic_fixed_array<T, N>& a, const basic_fixed_array<T, N>& b) {
        for(int i = 0; i<N; i++)
            if(a[i] <= b[i]) return false;
        return true;
    }

    template<typename T, utb::size_t N>
    inline bool  operator >= (const basic_fixed_array<T, N>& a, const basic_fixed_array<T, N>& b) {
        for(int i = 0; i<N; i++)
            if(a[i] < b[i]) return false;
        return true;
    }

    template<typename T, utb::size_t N>
    inline void swap (basic_fixed_array<T, N>& a, basic_fixed_array<T, N>& b) {
        a.swap(b);
    }

    template<typename T, utb::size_t N>
    inline void fill (basic_fixed_array<T, N>& a, const int val) {
        a.fill(val);
    }

    template<typename T, utb::size_t N>
    inline void zero (basic_fixed_array<T, N>& a) {
        a.fill(0);
    }

    template<typename T, utb::size_t N>
    using array = basic_fixed_array<T, N>;
}

#endif