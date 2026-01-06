#ifndef  __UT_BUFFER_H__
#define __UT_BUFFER_H__


#include "utconfig.h"

#include <cassert>

#include "uttypetraits.h"
#include "utalgorithm.h"
#include "utoptional.h"

namespace utb {

	template<typename TYPE>
	class buffer_iterator {
		static_assert(TSIZE > 0, "Size must be greater than zero.");	
	public:
		using self_type = buffer_iterator<TYPE>;
		using value_type = TYPE;
		using pointer = value_type*;
		using reference = value_type&;
		using size_type = utb::size_t;
		using const_reference = const value_type&;
		using const_pointer = const value_type*;
		using iterator_category = random_access_iterator_tag ;
		using difference_type = ptrdiff_t;
		using iterator = pointer;
		using const_iterator = const value_type*;

		explicit buffer_iterator(pointer& pBuffer, size_type sSize , size_type iStartPosition = 0) 
			: m_iCurrentPosition(iStartPosition), m_pBuffer(pBuffer), m_sMaxSize(sSize) { }

		~buffer_iterator() = default;

		constexpr bool	operator== (const self_type& iter) const {
			for(utb::size_t i = m_iCurrentPosition; i < m_sMaxSize; ++i) {
				if (m_pBuffer[i] != iter.m_pBuffer[i]) {
					return false;
				}
			}
			return m_iCurrentPosition == iter.m_iCurrentPosition && m_sMaxSize == iter.m_sMaxSize;
		}

		constexpr bool	operator< (const self_type& iter) const
			{ return m_itr < iter.m_itr; }

		constexpr reference_type	operator* () const { return (*m_pBuffer[m_iCurrentPosition]); }
		constexpr pointer			operator-> () const { return &*m_pBuffer[m_iCurrentPosition]; }

		constexpr self_type&	operator++ () { if(m_iCurrentPosition < m_sMaxSize) ++m_iCurrentPosition;  return *this; }
		constexpr self_type&	operator-- () { if(m_iCurrentPosition > 0) --m_iCurrentPosition; return *this; }

		constexpr self_type		operator++ (int) { if(m_iCurrentPosition < m_sMaxSize) ++m_iCurrentPosition;  return *this; }
		constexpr self_type		operator-- (int) { if(m_iCurrentPosition > 0) --m_iCurrentPosition; return *this; }

		constexpr self_type&	operator+= (utb::size_t n) { 
			m_iCurrentPosition += n; 
			if (m_iCurrentPosition > m_sMaxSize) {
				m_iCurrentPosition = m_sMaxSize;
			}
			return *this;
		}

		constexpr self_type&	operator-= (utb::size_t n) { 
			if (n > m_iCurrentPosition) {
				m_iCurrentPosition = 0;
			} else {
				 m_iCurrentPosition -= n;
			}
			return *this;
		}

		constexpr self_type		operator + (utb::size_t n) const {
			self_type iter = *this;
			iter.m_iCurrentPosition += n;
			if (iter.m_iCurrentPosition > m_sMaxSize) {
				iter.m_iCurrentPosition = m_sMaxSize;
			}
			return iter;
		}

		constexpr self_type		operator- (utb::size_t n) const {
			self_type iter = *this;
			iter.m_iCurrentPosition += n;
			if (iter.m_iCurrentPosition > m_sMaxSize) {
				iter.m_iCurrentPosition = m_sMaxSize;
			}
			return iter;
		}

		constexpr reference_type 	operator[] (utb::size_t n) const { assert(n < m_sMaxSize); return m_pBuffer[n]; }
		constexpr difference_type	operator- (const self_type& i) const { return m_iCurrentPosition - i.m_iCurrentPosition; }

	private:
		size_type   m_iCurrentPosition;
		size_type   m_sMaxSize;
		pointer& 	m_pBuffer;
	};
	template<typename TYPE, TYPE* TRAWBUFFER, utb::size_t TSIZE>
	class buffer {
		static_assert(TSIZE > 0, "Size must be greater than zero.");
		static_assert(TSIZE <= utb::size_t(sizeof(TYPE*) / sizeof(TYPE)), "Buffer view out of bounds.");
		static_assert(utb::is_pointer<TYPE*>::value, "TYPE must be a pointer type.");
	public:
		using self_type = buffer<TYPE, TRAWBUFFER, TSIZE>;
		using value_type = TYPE;
		using pointer = value_type*;
		using reference = value_type&;
		using size_type = utb::size_t;
        using move_type = value_type&&;

		using const_reference = const value_type&;
		using const_pointer = const value_type*;

		using iterator_category = random_access_iterator_tag ;
		using difference_type = ptrdiff_t;
		using iterator = buffer_iterator<TYPE, TSIZE>;
		using const_iterator = const buffer_iterator<TYPE, TSIZE>;

		buffer() : m_sUsed(0) { }
		buffer(const self_type& other) = delete;
		buffer(self_type&& other) noexcept = delete;
		~buffer() = default;

		self_type& operator=(const self_type&) = delete;
		self_type& operator=(self_type&&) = delete;



		/**
		 * @brief Get the iterator to the beginning of the buffer.
		 * @return The iterator to the beginning of the buffer.
		 */
		iterator begin() 			{ return iterator(TRAWBUFFER, m_sUsed, 0); }

		/**
		 * @brief Get the iterator to the beginning of the buffer.
		 * @return The iterator to the beginning of the buffer.
		 */
		const_iterator begin() const { return const_iterator(TRAWBUFFER, m_sUsed, 0); }

		/**
		 * @brief Get the iterator to end of the buffer.
		 * @return The iterator to end of the buffer.
		 */
		iterator end() 				{ return iterator(&TRAWBUFFER[m_sUsed], m_sUsed, m_sUsed); }

		/**
		 * @brief Get the iterator to end of the buffer.
		 * @return The iterator to end of the buffer.
		 */
		const_iterator end() const 	{ return const_iterator(&TRAWBUFFER[m_sUsed], m_sUsed, m_sUsed); }


		utb::size_t write(const_reference value) {
			if (m_sUsed >= TSIZE) return 0;

			TRAWBUFFER[m_sUsed++] = value;
			return 1;
		}
		value_type read() {
			assert (m_sUsed > 0);

			value_type value = TRAWBUFFER[0];
			utb::move(TRAWBUFFER + 1, TRAWBUFFER + m_sUsed, TRAWBUFFER);
			return value;
		}

		utb::size_t assign(const_pointer pBuffer, size_type size) {
			if ( size > TSIZE) return 0;

			utb::copy(pBuffer, pBuffer + size, TRAWBUFFER + m_sUsed);
			m_sUsed += size;
			return size;
		}
		
		void emplace_back(const_reference value) {
			assert (m_sUsed < TSIZE);
			TRAWBUFFER[m_sUsed++] = value;
		}

		pointer data() noexcept {
			return TRAWBUFFER;
		}
		const_pointer data() const noexcept {
			return TRAWBUFFER;
		} 

		/**
		 * @brief Clear the used content.
		 */
		void clear() {
			m_sUsed = 0;
		}
		/**
		 * @brief Is the given buffer equal with this?
		 * @param other Reference to the comparing buffer
		 * @return true The given buffer is equal with this, false when not.
		 */
		constexpr bool is_equal (const buffer& other) const noexcept{
			if (m_sUsed != other.m_sUsed) {
				return false;
			}
			return utb::equal(begin(), end(), other.begin());
		}

		constexpr reference at(size_type index) const {
			assert (index < m_sUsed);
			return TRAWBUFFER[index];
		}

		constexpr reference at(size_type index) {
			assert (index < m_sUsed);
			return TRAWBUFFER[index];
		}

		/**
		 * @brief Get the capacity of the buffer in elements.
		 * @return The capacity of the buffer in elements.
		 */
		constexpr size_type capacity() const noexcept		{ return TSIZE - m_sUsed; }
		
		/**
		 * @brief is the buffer  empty?
		 * @return If true then is the buffer empty and if false then not.
		 */
		constexpr bool is_empty() const noexcept			{ return m_sUsed == 0; }

		/**
		 * @brief Get the free memory size in elements.
		 * @return The free memory size in elements.
		 */
		constexpr size_type free() const noexcept 		{ return TSIZE - m_sUsed; }

		/**
		 * @brief Get the free memory size in bytes.
		 * @return The free memory size in bytes.
		 */
		constexpr size_type free_bytes() const noexcept { return (TSIZE - m_sUsed) * sizeof(value_type); }

		/**
		 * @brief is the buffer  full?
		 * @return If true then is the buffer full and if false then not.
		 */
		constexpr bool is_full() const noexcept				{ return m_sUsed == TSIZE; }
		/**
		 * @brief Get the allocated memory size in elements.
		 * @return The allocated memory size in elements.
		 */
		constexpr size_type size() const noexcept 		{ return TSIZE; }

		/**
		 * @brief Get the allocated memory size in bytes.
		 * @return The allocated memory size in bytes.
		 */
		constexpr size_type bytes() const noexcept { return TSIZE * sizeof(value_type); }

		/**
		 * @brief Get the used size of the buffer in elements.
		 * @return The used size of the buffer in elements.
		 */
		constexpr size_type used() const noexcept		{ return m_sUsed; }

		/**
		 * @brief Get the used size of the buffer in bytes.
		 * @return The used size of the buffer in bytes.
		 */
		constexpr size_type used_bytes() const noexcept { return m_sUsed * sizeof(value_type); }

		/**
		 * @brief Compare operator.
		 */
		bool operator == (const buffer& other) const {
			return is_equal(other);
		}
		/**
		 * @brief Not compare operator.
		 */
		bool operator != (const buffer& other) const {
			return !(is_equal(other));
		}


		reference operator [] (size_type index) {
			assert (index < m_sUsed);
			return TRAWBUFFER[index];
		}

		const_reference operator [] (size_type index) const {
			assert (index < m_sUsed);
			return TRAWBUFFER[index];
		}

		self_type& operator ++() {
			assert (m_sUsed < TSIZE);
			++m_sUsed;
			return *this;
		}
		self_type& operator --() {
			assert (m_sUsed > 0);
			--m_sUsed;
			return *this;
		}
	private:
		size_type    m_sUsed;
	};
}

#endif