#ifndef  __UT_BUFFER_H__
#define __UT_BUFFER_H__


#include "utconfig.h"

#include <cassert>

#include "uttypetraits.h"
#include "utalgorithm.h"
#include "utoptional.h"

namespace utb {

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
		using iterator = pointer;
		using const_iterator = const value_type*;

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
		iterator begin() 			{ return TRAWBUFFER; }

		/**
		 * @brief Get the iterator to the beginning of the buffer.
		 * @return The iterator to the beginning of the buffer.
		 */
		const_iterator begin() const { return TRAWBUFFER; }

		/**
		 * @brief Get the iterator to end of the buffer.
		 * @return The iterator to end of the buffer.
		 */
		iterator end() 				{ return TRAWBUFFER + m_sUsed; }

		/**
		 * @brief Get the iterator to end of the buffer.
		 * @return The iterator to end of the buffer.
		 */
		const_iterator end() const 	{ return TRAWBUFFER + m_sUsed; }


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

		constexpr value_type at(size_type index) const {
			assert (index < m_sUsed);
			return TRAWBUFFER[index];
		}

		constexpr value_type at(size_type index) {
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