#ifndef __UT_VECTOR_H__
#define __UT_VECTOR_H__

#include "utconfig.h"
#include "utalgorithm.h"
#include "utalignment.h"

namespace utb {

    /// @brief Fixed-size vector container with in-place storage.
    ///
    /// This container stores up to @p TCapacity elements of type @p T in a
    /// preallocated internal buffer. It provides a subset of std::vector-like
    /// operations but does not perform dynamic memory allocation.
    ///
    /// @tparam T Type of elements stored in the vector.
    /// @tparam TCapacity Maximum number of elements the vector can hold.
    template<typename T, int TCapacity >
    class basic_vector  {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using difference_type = ptrdiff_t;

        using iterator = pointer;
        using const_iterator = const_pointer;

        using size_type = size_t;
        using self_type = basic_vector<T, TCapacity>;

        explicit basic_fixed_vector()
            : m_begin((pointer)&m_data[0]),
                m_end(m_begin),
                m_capacityEnd(m_begin + TCapacity),
                m_max_size(0) { } 

        explicit basic_fixed_vector(size_type initialSize)
            : m_begin((pointer)&m_data[0]),
                m_end(m_begin),
                m_capacityEnd(m_begin + TCapacity),
                m_max_size(TCapacity)  { resize(initialSize); }

        basic_fixed_vector(const pointer first, const pointer last)
            : m_begin((pointer)&m_data[0]),
                m_end(m_begin),
                m_capacityEnd(m_begin + TCapacity),
                m_max_size(TCapacity) { assign(first, last); }

        basic_fixed_vector(const self_type& rhs)
            : m_begin((pointer)&m_data[0]),
                m_end(m_begin),
                m_capacityEnd(m_begin + TCapacity),
                m_max_size(TCapacity) { 
            if(rhs.size() == 0) return;

            utb::copy_construct_n(rhs.m_begin, rhs.size(), m_begin);

            m_end = m_begin + rhs.size();
            assert(invariant());
        }
        iterator  		begin() noexcept 			        { return m_begin; }
        constexpr const_iterator 	begin() const noexcept  { return m_begin; }

        iterator  		end() noexcept 				        { return m_end; }
        constexpr const_iterator 	end() const noexcept    { return m_end; }

        reference 		front() noexcept 			        { return m_begin; }
        const_reference front() const noexcept		        { return m_begin; }

        reference 		back() noexcept 			        { return m_end; }
        const_reference back() const noexcept 		        { return m_end; }

        size_type 		size() const noexcept 		        { return size_type(m_end - m_begin); }

        size_type size() const                              { return size_type(m_end - m_begin); }
        bool empty() const                                  { return m_begin == m_end; }
        bool full() const                                   { return (m_end == m_capacityEnd); }

        size_type capacity()                                { return size_type(m_capacityEnd - m_begin); }

        void push_back(const_reference v) {
            if (full()) return;
            utb::copy_construct(m_end++, v);
        }
        inline void	 push_back (value_type&& v)	{
            if (full()) return;
            utb::copy_construct(m_end++, utb::move(v));
        }

        void push_back() {
            if (full()) return;
            utb::construct(m_end); ++m_end;
        }
        void pop_back() {
            assert(!empty()); --m_end;
            utb::destruct<iterator>(m_end);
        }

        size_type index_of(const reference item, size_type index = 0) const {
            assert(index >= 0 && index < size());
            size_type _pos = npos;

            for ( ; index < size(); ++index) {
                if (m_begin[index] == item) {
                    _pos = index; break;
                }
            }
            return _pos;
        }

        iterator find(const reference item) {
            iterator itEnd = end();

            for (iterator it = begin(); it != itEnd; ++it)
                if (*it == item) { itEnd = it; break; }
            return itEnd;
        }
        bool validate_iterator(const_iterator it) const {
            return it >= begin() && it <= end();
        }

        

        void clear() {
            shrink(0);
            assert(invariant());
        }
        void resize(size_type n) {
            if (n > size()) insert(m_end, n - size(), value_type());
            else shrink(n);
        }

        basic_vector& operator=(const basic_vector& rhs) {
            copy(rhs);
            return *this;
        }
        reference operator[](size_type i) {
            return at(i);
        }

        const reference operator[](size_type i) const {
            return at(i);
        }
        inline void destroy(pointer ptr, size_type n) {
            utb::destruct_n(ptr, n);
        }
        bool invariant() const {
            return m_end >= m_begin;
        }

        void insert(iterator it, size_type n, const reference val) {
            assert(validate_iterator(it));
            assert(invariant());
            insert(size_type(it - m_begin), n, val);
        }

        iterator insert(iterator it, const_reference val) {
            assert(validate_iterator(it));
            assert(invariant());

            const size_type index = (size_type)(it - m_begin);
            if (full()) return;

            utb::construct(m_end);
            
            if (m_end > it) {

                const size_type prevSize = size();
                assert(index <= prevSize);
                const size_type toMove = prevSize - index;

                utb::move_n(it, toMove, it + 1);
            }
            *it = val;
            ++m_end;
            assert(invariant());

            return it;
        }

        void swap( self_type& other ) {
            utb::swap(m_begin, 		other.m_begin);
            utb::swap(m_end, 		other.m_end);
            utb::swap(m_capacityEnd, other.m_capacityEnd);
            utb::swap_n<value_type, TCapacity> (m_data, 	other.m_data);
        }
    private:
        inline void shrink(size_type newSize) {
            assert(newSize <= size());
            const size_type toShrink = size() - newSize;
            utb::destruct_n(m_begin + newSize, toShrink);
            m_end = m_begin + newSize;
        }
    private:
        pointer m_begin;
        pointer m_end;
        value_type m_data[(TCapacity];
        pointer m_capacityEnd;
        size_type  m_max_size;
    };

    template<typename T, int TCapacity>
	using vector =  basic_fixed_vector<T, TCapacity>;
}


#endif