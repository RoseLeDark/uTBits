#ifndef __UTEBO_STORAGE_H__
#define __UTEBO_STORAGE_H__

#include "utconfig.h"
#include "uttypes.h"
#include "utfunctional.h"

namespace utb {
    template <typename T, int TAG = 0, typename = void>
	class ebo_storage {
	public:
		using value_type = T;
	  	using const_type = const T;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;

		constexpr ebo_storage() = default;

		template<typename U>
		constexpr ebo_storage(U&& u) noexcept : m_iItem(utb::forward(u) ) {}

				  		reference get() noexcept 		{ return m_iItem; }
		constexpr const_reference get() const noexcept 	{ return m_iItem; }

		ebo_storage& operator=( const ebo_storage& other ) = default;
        ebo_storage& operator=( ebo_storage&& other ) = default;
	private:
		T m_iItem;
	};

	template <typename T, int TAG>
	class ebo_storage<T, TAG, utb::enable_if_t<utb::is_class<T>::value>> : private T {
		using base_type = T;
	public:
		using value_type = T;
	  	using const_type = const T;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;

		using base_type::T;

		constexpr ebo_storage() = default;
		constexpr ebo_storage(const_reference type)  : base_type(type) { }
		constexpr ebo_storage(const T&& type) 		 : base_type(utb::move(type)) { }

				  reference 	  get() noexcept 		{ return *this; }
		constexpr const_reference get() const noexcept 	{ return *this; }
	};

}
#endif