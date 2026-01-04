#ifndef __UT_TYPETRAITS_H__
#define __UT_TYPETRAITS_H__

#include "uttypes.h"

namespace utb {

    template <typename T>
	struct type_traits {
		using value_type = T;
		using const_type = const T;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;
	};

	template <typename T>
	struct type_traits<T&> {
		using value_type = T;
		using const_type = const T;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;
	};

	template <typename T>
	struct type_traits<const T> {
		using value_type = T;
		using const_type = const T;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;
	};

	template <typename T>
	struct type_traits<const T&> {
		using value_type = T;
		using const_type = const T;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;
	};

	template <typename T>
	struct type_traits<volatile T&> {
		using value_type = T;
		using const_type = const T;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;
	};

	template <typename T>
	struct type_traits<const volatile T&> {
		using value_type = T;
		using const_type = const T;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;
	};

	template <typename T>
	struct type_traits<T*> {
		using value_type = T*;
		using const_type = const T*;
		using reference = T*&;
		using const_reference = const T*&;
		using pointer = T*;
		using const_pointer = const T*;
	};

	template <typename T, size_t N>
	struct type_traits<T [N]> {
	private:
		typedef T array_type[N];
	public:
	   	using value_type = T*;
	  	using const_type = const T*;
		using reference = array_type&;
		using const_reference = const array_type&;
		using pointer = T*;
		using const_pointer = const T*;
	};

	template <typename T, size_t N>
	struct type_traits<const T [N]> {
	private:
		typedef const T array_type[N];
	public:
	   	using value_type = const T*;
	  	using const_type = const T*;
		using reference = array_type&;
		using const_reference = const array_type&;
		using pointer = T*;
		using const_pointer = const T*;
	};

    template<class T, T v> struct integral_constant {
        enum { value = v  };
    };

    using  true_type = integral_constant<bool, true>;
    using false_type =  integral_constant<bool, false> ;

    template<typename>
    struct is_const : public false_type { };

    template<typename T>
    struct is_const<T const>  : public true_type { };

	/// is_volatile
	template<typename>
	struct is_volatile : public false_type { };

	template<typename T>
	struct is_volatile<T volatile> : public true_type { };



	/// is_empty
	template<typename T>
	struct is_empty : public integral_constant<bool, __is_empty(T)> { };


    template<typename T>
    struct is_enum : public integral_constant<bool, __is_enum(T)> { };

    template<typename T>
    struct is_union : public integral_constant<bool, __is_union(T)> { };

    template<typename T>
    struct is_class : public integral_constant<bool, __is_class(T)> { };

    template<typename>
    struct is_function;

    template<typename>
    struct is_function : public false_type { };

    template<typename T, typename... Args>
    struct is_function<T(Args...)> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args...) &> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args...) &&> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args......)> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args......) &> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args......) &&> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args...) const> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args...) const &> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args...) const &&> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args......) const> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args......) const &> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args......) const &&> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args...) volatile> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args...) volatile &> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args...) volatile &&> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args......) volatile> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args......) volatile &> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args......) volatile &&> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args...) const volatile> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args...) const volatile &> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args...) const volatile &&> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args......) const volatile> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args......) const volatile &> : public true_type { };

	template<typename T, typename... Args>
	struct is_function<T(Args......) const volatile &&> : public true_type { };

    template<typename T>
    struct is_abstract : public integral_constant<bool, __is_abstract(T)> { };

    template<typename T>
    struct is_polymorphic : public integral_constant<bool, __is_polymorphic(T)> { };

    template<typename T>
    struct is_literal_type : public integral_constant<bool, __is_literal_type(T)> { };

    template<typename T>
    struct is_pod : public integral_constant<bool, __is_pod(T)> { };

    /// is_trivial
	template<typename T>
	struct is_trivial : public integral_constant<bool, __is_trivial(T)> { };

	// is_trivially_copyable
  	template<typename T>
    struct is_trivially_copyable : public integral_constant<bool, __is_trivially_copyable(T)>  { };

	/// is_standard_layout
	template<typename T>
	struct is_standard_layout : public integral_constant<bool, __is_standard_layout(T)> { };

	template<typename T>
    struct is_bind_expression  : public false_type { };

	template<typename T>
    struct is_placeholder  : public integral_constant<int, 0> { };


	template<typename T>
    struct is_integral : public integral_constant<bool, false> { };

	template<class T>
    struct is_integral<const T> : public is_integral<T> { };

    template<class T>
    struct is_integral<volatile T> : public is_integral<T> { };

    template<class T>
    struct is_integral<const volatile T> : public is_integral<T> { };



    template<typename T>
    struct is_rational : public integral_constant<bool, false> { };

	template<class T>
    struct is_rational<const T> : public is_rational<T> { };

    template<class T>
    struct is_rational<volatile T> : public is_rational<T> { };

    template<class T>
    struct is_rational<const volatile T> : public is_rational<T> { };

    template<typename T>
    struct is_void : public integral_constant<bool, false> { };

    template<class T>
    struct is_void<const T> : public is_void<T> { };

    template<class T>
    struct is_void<volatile T> : public is_void<T> { };

    template<class T>
    struct is_void<const volatile T> : public is_void<T> { };

    template<typename T>
    struct is_floating_point : public integral_constant<bool, false> { };

    template<>
    struct is_floating_point<float> : public integral_constant<bool, true> { };

    template<>
    struct is_floating_point<double> : public integral_constant<bool, true> { };

	template <>
	struct is_floating_point<long double> : public integral_constant<bool, true> { };

	template <typename T>
	struct is_floating_point<const T> : is_floating_point<T> {};

	template <typename T>
	struct is_floating_point<volatile T> : is_floating_point<T> {};

	template <typename T>
	struct is_floating_point<const volatile T> : is_floating_point<T> {};

	 /// is_lvalue_reference
  	template<typename>
    struct is_lvalue_reference : public false_type { };

  	template<typename T>
    struct is_lvalue_reference<T&> : public true_type { };


    /// is_rvalue_reference
  	template<typename>
    struct is_rvalue_reference : public false_type { };

  	template<typename T>
    struct is_rvalue_reference<T&&> : public true_type { };

    template<typename T>
    struct is_pointer
    	: public integral_constant<bool, false> { };

    template<typename T>
    struct is_pointer<T*>
    	: public integral_constant<bool, true> { };

    template<typename T>
    struct is_fundamental
    	: public integral_constant<bool, is_integral<T>::value || is_rational<T>::value> { };

    template<typename T>
    struct has_trivial_constructor
    	: public integral_constant<bool, is_fundamental<T>::value | is_pointer<T>::value | is_pod<T>::value> { };

    template<typename T>
    struct has_trivial_copy
    	: public integral_constant<bool, is_fundamental<T>::value | is_pointer<T>::value | is_pod<T>::value> { };

    template<typename T>
    struct has_trivial_assign
    	: public integral_constant<bool, is_fundamental<T>::value | is_pointer<T>::value | is_pod<T>::value> { };

    template<typename T>
    struct has_trivial_destructor
    	: public integral_constant<bool, is_fundamental<T>::value || is_pointer<T>::value || is_pod<T>::value> { };

	template<typename T>
	struct is_reference
		: public integral_constant<bool, is_lvalue_reference<T>::value | is_rvalue_reference<T>::value> { };

	/// is_arithmetic
	template<typename T>
	struct is_arithmetic
		: public integral_constant< bool, !(is_integral<T>::value | is_floating_point<T>::value) > { };

	/// is_object
	template<typename T>
	struct is_object
		: public integral_constant< bool, ! (is_function<T>::value |  is_reference<T>::value |
											is_void<T>::value) > { };

	/// is_signed
	template <typename T>
	struct is_signed : false_type {};

	template <>
	struct is_signed<char> : integral_constant<bool, (char(255) < 0)> {};

	template <>
	struct is_signed<signed char> : true_type {};

	template <>
	struct is_signed<short> : true_type {};

	template <>
	struct is_signed<int> : true_type {};

	template <>
	struct is_signed<long> : true_type {};

	template <>
	struct is_signed<long long> : true_type {};

	template <>
	struct is_signed<float> : true_type {};

	template <>
	struct is_signed<double> : true_type {};

	template <>
	struct is_signed<long double> : true_type {};

	template <typename T>
	struct is_signed<const T> : is_signed<T> {};

	template <typename T>
	struct is_signed<volatile T> : is_signed<T> {};

	template <typename T>
	struct is_signed<const volatile T> : is_signed<T> {};


	/// is_unsigned
	template <typename T>
	struct is_unsigned : false_type {};

	template <>
	struct is_unsigned<bool> : true_type {};

	template <>
	struct is_unsigned<char> : integral_constant<bool, (char(255) > 0)> {};

	template <>
	struct is_unsigned<unsigned char> : true_type {};

	template <>
	struct is_unsigned<unsigned short> : true_type {};

	template <>
	struct is_unsigned<unsigned int> : true_type {};

	template <>
	struct is_unsigned<unsigned long> : true_type {};

	template <>
	struct is_unsigned<unsigned long long> : true_type {};

	template <typename T>
	struct is_unsigned<const T> : is_unsigned<T> {};

	template <typename T>
	struct is_unsigned<volatile T> : is_unsigned<T> {};

	template <typename T>
	struct is_unsigned<const volatile T> : is_unsigned<T> {};

	template<typename>
	struct is_member_pointer;



	/// is_compound
	template<typename T>
	struct is_compound
	: public integral_constant<bool, !is_fundamental<T>::value> { };


    template<typename T>
    struct has_cheap_compare : public integral_constant<bool, has_trivial_copy<T>::value && sizeof(T) <= 4 > { };


    template<size_t size, size_t align = alignof(void *)>
	struct aligned_storage {
		struct type { alignas(align) unsigned char data[size]; };
	};

    template<size_t size, size_t align = alignof(void *)>
    using aligned_storage_t = typename aligned_storage<size, align>::type;


	template<> struct is_integral<int8_t> : public integral_constant<bool, true> { };
    template<> struct is_integral<uint8_t> : public integral_constant<bool, true> { };
    template<> struct is_integral<int16_t> : public integral_constant<bool, true> { };
    template<> struct is_integral<uint16_t> : public integral_constant<bool, true> { };
    template<> struct is_integral<int32_t> : public integral_constant<bool, true> { };
    template<> struct is_integral<uint32_t> : public integral_constant<bool, true> { };
    template<> struct is_integral<int64_t> : public integral_constant<bool, true> { };
    template<> struct is_integral<uint64_t> : public integral_constant<bool, true> { };
    template<> struct is_integral<wchar_t> : public integral_constant<bool, true> { };
    template<> struct is_integral<bool> : public integral_constant<bool, true> { };

    template<> struct is_void<void> : public integral_constant<bool, true> { };
    template<> struct is_void<const void> : public integral_constant<bool, true> { };
    template<> struct is_void<volatile void> : public integral_constant<bool, true> { };
    template<> struct is_void<const volatile void> : public integral_constant<bool, true> { };

    template<> struct is_void<float> : public integral_constant<bool, true> { };
    template<> struct is_void<double> : public integral_constant<bool, true> { };
    template<> struct is_void<long double> : public integral_constant<bool, true> { };
}

#endif