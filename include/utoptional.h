#ifndef __UT_OPTIONAL_H__
#define __UT_OPTIONAL_H__

#include "utconfig.h"
#include "uttypes.h"
#include "uttypetraits.h"
#include "utvoid.h"
#include "utalgorithm.h"
#include "utfunctional.h"


namespace utb {

    struct nullopt_t { };

    template< typename T>
	class basic_optional {
	public:
		using value_type = T;
		using const_value_type = const T;
		using reference = T&;
		using const_reference = const T&;
		using move_type = T&&;
		using const_move_type = const T&&;

		using pointer = T*;
		using const_pointer = const T*;

		using self_type = basic_optional<T>;


		basic_optional() noexcept
    		: m_bHasValue( false), m_tValue() { }

		explicit basic_optional(const_value_type& value)
			: m_bHasValue( true), m_tValue( value) { }

		basic_optional(const self_type& other)
			: m_bHasValue( other.m_bHasValue), m_tValue(other.m_tValue) { }

		basic_optional(const self_type&& other) noexcept
			: m_bHasValue( utb::move(other.m_bHasValue)), m_tValue( utb::move(other.m_tValue)) { }


		template< typename... Args>
		constexpr explicit basic_optional(Args&&... args)
			: m_bHasValue( true), m_tValue( value_type( utb::forward<Args>(args)...))  {}

		template< typename U = value_type >
    	constexpr explicit basic_optional( U && value)
			: m_bHasValue( true), m_tValue( utb::forward<U>( value)) { }

		~basic_optional() { reset(); }

		/**
    	 * @brief Resets the basic_optional.
    	 */
    	void reset() noexcept {
        	if ( has_value() & utb::is_class<T>::value))
                	m_tValue.~value_type();

        	m_bHasValue = false;
    	}
    	/**
    	 * @brief Clears the basic_optional.
    	 */
    	void clear() {
			m_bHasValue = false;
		}

		/**
		 * @brief Assigns a value to the basic_otional.
		 */
    	self_type& assign(const_value_type& value)
		{
			m_tValue = value;
			m_bHasValue = true;
			return *this;
		}

		/**
		 * @brief Moves a value into the basic_otional.
		 */
		self_type& assign(move_type value) {
			m_tValue = utb::move(value);
			m_bHasValue = true;
			return *this;
		}

		/**
		 * @brief Assigns another basic_otional.
		 */
		self_type& assign(const self_type& other) {
			self_type tmp(other);
			swap(tmp);
			return *this;
		}
		/**
    	 * @brief Swap this basic_optional with a other.
    	 */
		void swap( self_type& other) {
			utb::swap(m_bHasValue, other.m_bHasValue);
			utb::swap(m_tValue, other.m_tValue);
    	}

    	/**
    	 * @brief Have this basic_optional a value?
    	 * @return True when this basic_optional hald any vaule and false when not.
    	 */
		constexpr bool has_value() const noexcept {
        	return m_bHasValue;
		}
		/**
		 * @brief Returns the basic_optional's value.
		 */
		reference value() {
    		assert( has_value());
    		return m_tValue;
    	}
    	/**
		 * @brief Returns the basic_optional's value.
		 */
		const_reference value() const {
    		assert( has_value());
    		return m_tValue;
    	}
    	/**
		 * @brief Returns the basic_optional's value, or the given default value
		 *	when this basic_optional no value have.
		 */
		constexpr value_type value_or(const value_type value) const {
			return has_value() ? m_tValue : static_cast<value_type>( value);
		}
		/**
		 * @brief Returns the basic_optional's value, or the given default value
		 *	when this basic_optional no value have.
		 */
    	template< typename U >
		constexpr value_type value_or(const U& value) const {
			return has_value() ? m_tValue : static_cast<value_type>( value);
		}

		/**
    	 * @brief Assigns another basic_otional.
    	 */
		self_type& operator = (const self_type& other) noexcept {
			return assign(value);
    	}

    	/**
    	 * @brief Assigns another basic_otional.
    	 */
    	self_type& operator = ( self_type&& other) noexcept {
    		return assign(value);
    	}

		/**
    	 * @brief Get the given value as pointer.
    	 */
		constexpr const_pointer operator ->() const {
			return m_tValue;
		}

		/**
    	 * @brief
    	 */
		pointer operator ->() {
			return m_tValue;
		}

		/**
    	 * @brief
    	 */
		constexpr const_reference operator *() const  {
			return m_tValue;
		}

		/**
    	 * @brief
    	 */
		reference operator *() {
			return m_tValue;
		}

    	/**
    	 * @brief Convert this basic_optional to boolean.
    	 * @return True when this basic_optional hald any vaule and false when not.
    	 */
    	explicit operator bool() const noexcept {
        	return m_bHasValue;
    	}
	private:
		/**
    	 * @brief Flag whether or not has this basic_optianel a value.
    	 */
		bool m_bHasValue;
		/**
    	 * @brief A saved / cached copy of the value.
    	 */
    	value_type m_tValue;
	};

	template <typename T>
	inline void swap(basic_optional<T>& a, basic_optional<T>& b) {
		a.swap(b);
	}


	template< typename T, typename U >
	inline constexpr bool operator == (const basic_optional<T>& x, const basic_optional<U>& y) {
		return bool(x) != bool(y) ? false : !bool( x) ? true : *x == *y;
	}

	template< typename T, typename U >
	inline constexpr bool operator != (const basic_optional<T>& x, const basic_optional<U>& y) {
		return !(x.value() == y.value());
	}

	template< typename T, typename U >
	inline constexpr bool operator < (const basic_optional<T>& x, const basic_optional<U>& y) {
		return (!y) ? false : (!x) ? true : *x < *y;
	}

	template< typename T, typename U >
	inline constexpr bool operator > (const basic_optional<T>& x, const basic_optional<U>& y) {
		return (y.value() < x.value());
	}

	template< typename T, typename U >
	inline constexpr bool operator <= (const basic_optional<T>& x, const basic_optional<U>& y) {
		return !(y.value() < x.value());
	}

	template< typename T, typename U >
	inline constexpr bool operator >= (const basic_optional<T>& x, const basic_optional<U>& y) {
		return !(x.value() < y.value());
	}

	// Comparison with nullopt

	template< typename T >
	inline constexpr bool operator == (const basic_optional<T>& x, nullopt_t) noexcept {
		return (!x);
	}

	template< typename T >
	inline constexpr bool operator == (nullopt_t, const basic_optional<T>& x) noexcept {
		return (!x);
	}

	template< typename T >
	inline constexpr bool operator != (const basic_optional<T>& x, nullopt_t) noexcept {
		return bool(x);
	}

	template< typename T >
	inline constexpr bool operator != (nullopt_t, const basic_optional<T>& x) noexcept {
		return bool(x);
	}

	template< typename T >
	inline constexpr bool operator < (const basic_optional<T>&, nullopt_t) noexcept {
		return false;
	}

	template< typename T >
	inline constexpr bool operator < (nullopt_t, const basic_optional<T>& x) noexcept {
		return bool(x);
	}

	template< typename T >
	inline constexpr bool operator <= (const basic_optional<T>& x, nullopt_t) noexcept {
		return (!x);
	}

	template< typename T >
	inline constexpr bool operator <= (nullopt_t, const basic_optional<T>&) noexcept {
		return true;
	}

	template< typename T >
	inline constexpr bool operator > (const basic_optional<T>& x, nullopt_t) noexcept {
		return bool(x);
	}

	template< typename T >
	inline constexpr bool operator > (nullopt_t, const basic_optional<T>&) noexcept
	{
		return false;
	}

	template< typename T >
	inline constexpr bool operator >= (const basic_optional<T>&, nullopt_t) noexcept {
		return true;
	}

	template< typename T >
	inline constexpr bool operator >= (nullopt_t, const basic_optional<T>& x) noexcept {
		return (!x);
	}

	template< typename T, typename U >
	inline constexpr bool operator == (const basic_optional<T>& x, const U& v) {
		return bool(x) ? *x == v : false;
	}

	template< typename T, typename U >
	inline constexpr bool operator == (const U& v, const basic_optional<T>& x) {
		return bool(x) ? v == *x : false;
	}

	template< typename T, typename U >
	inline constexpr bool operator != (const basic_optional<T>& x, const U& v) {
		return bool(x) ? *x != v : true;
	}

	template< typename T, typename U >
	inline constexpr bool operator != (const U& v, const basic_optional<T>& x) {
		return bool(x) ? v != *x : true;
	}

	template< typename T, typename U >
	inline constexpr bool operator < (const basic_optional<T>& x, const U& v) {
		return bool(x) ? *x < v : true;
	}

	template< typename T, typename U >
	inline constexpr bool operator < (const U& v, const basic_optional<T>& x) {
		return bool(x) ? v < *x : false;
	}

	template< typename T, typename U >
	inline constexpr bool operator <= (const basic_optional<T>& x, const U& v) {
		return bool(x) ? *x <= v : true;
	}

	template< typename T, typename U >
	inline constexpr bool operator<=(const U& v, const basic_optional<T>& x) {
		return bool(x) ? v <= *x : false;
	}

	template< typename T, typename U>
	inline constexpr bool operator>(const basic_optional<T>& x, const U& v) {
		return bool(x) ? *x > v : false;
	}

	template< typename T, typename U>
	inline constexpr bool operator>(const U& v, const basic_optional<T>& x) {
		return bool(x) ? v > *x : true;
	}

	template< typename T, typename U>
	inline constexpr bool operator>=(const basic_optional<T>& x, const U& v) {
		return bool(x) ? *x >= v : false;
	}

	template< typename T, typename U>
	inline constexpr bool operator >= (const U& v, const basic_optional<T>& x) {
		return bool(x) ? v >= *x : true;
	}

	template< typename T >
	constexpr basic_optional<typename utb::decay<T>::type> make_optional( T && value ) {
		return basic_optional<typename utb::decay<T>::type>( utb::forward<T>( value ) );
	}

	template< typename T, typename...Args >
	constexpr basic_optional<T> make_optional( Args&&... args ) {
		return basic_optional<T>(utb::forward<Args>(args)...);
	}
#if 0
	template< class T >
	struct hash<basic_optional<T>> {
		utb::size_t operator()( const basic_optional<T>& opt ) const noexcept {
			return bool(opt) ? hash<T>()(*opt) : 0;
		}
	};
#endif // 0

	template <typename T>
	using optional = basic_optional<T>;

	static constexpr nullopt_t nullopt = nullopt_t{};

}

#endif