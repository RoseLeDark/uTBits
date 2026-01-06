#ifndef __UTF_ALIGNMENT_H__
#define __UTF_ALIGNMENT_H__

#include "uttypes.h"
#include "utalgorithm.h"
#include "utfunctional.h"
#include "uttypetraits.h"

namespace utb {
    using max_align_t 	= uintptr_t;
    using nullptr_t 	= decltype(nullptr);
    using addrof_null_t = nullptr_t ;

    const utb::size_t default_alignment = alignof(void*);
	constexpr utb::size_t max_alignment = alignof(max_align_t);

    namespace detail {

        template<typename T>
	    struct alignof_helper {
	        char    x;
	        T 		y;
	    };

        struct __attribute__ ((aligned (1)))  aligned1 	{  uint8_t member; };
		struct __attribute__ ((aligned (2)))  aligned2 	{ uint16_t member; };
		struct __attribute__ ((aligned (4)))  aligned4 	{ uint32_t member; };
		struct __attribute__ ((aligned (8)))  aligned8 	{ uint64_t member; } ;
		struct __attribute__ ((aligned (16))) aligned16 { uint64_t member[2]; } ;
        struct __attribute__ ((aligned (32))) aligned32 { uint64_t member[4]; } ;
		struct __attribute__ ((aligned (64))) aligned64 { uint64_t member[8]; } ;



        template<utb::size_t N> struct type_with_alignment {
	        typedef char err_invalid_alignment[N > 0 ? -1 : 1];
	    };

        template<> struct type_with_alignment<1> { aligned1 type; };
        template<> struct type_with_alignment<2> { aligned2 type; };
        template<> struct type_with_alignment<4> { aligned4 type; };
        template<> struct type_with_alignment<8> { aligned8 type; };
        template<> struct type_with_alignment<16> { aligned16 type; };
        template<> struct type_with_alignment<32> { aligned32 type; };
        template<> struct type_with_alignment<64> { aligned64 type; };

        union max_align {
			char c;
			short s;
			int i;
			long l;
			long long ll;
			float f;
			double d;
        };
    }

    template<> struct is_pod<detail::aligned1> : public true_type{};
	template<> struct is_pod<detail::aligned2> : public true_type{};
	template<> struct is_pod<detail::aligned4> : public true_type{};
	template<> struct is_pod<detail::aligned8> : public true_type{};
	template<> struct is_pod<detail::aligned16> : public true_type{};
	template<> struct is_pod<detail::aligned32> : public true_type{};
	template<> struct is_pod<detail::aligned64> : public true_type{};


    template<typename T>
	struct alignment_of {
	    enum { res = offsetof(detail::alignof_helper<T>, y) };
	};
	template<> struct alignment_of<void> {
		enum { res = 0  };
	};

	template<> struct alignment_of<void const> {
		enum { res = 0  };
	};

	template<> struct alignment_of<void const volatile> {
		enum { res = 0  };
	};

	template<> struct alignment_of<void volatile> {
		enum { res = 0  };
	};


	template <utb::size_t Target, bool check>  struct long_double_alignment{ using type = long double; };
	template <utb::size_t Target> struct long_double_alignment<Target, false> {
		using type = detail::max_align; };

	template <utb::size_t Target, bool check> struct double_alignment{ using type = double; };
    template <utb::size_t Target> struct double_alignment<Target, false> {
    	using type = typename long_double_alignment<Target, alignment_of<long double>::res >= Target>::type; };

	template <utb::size_t Target, bool check> struct long_long_alignment{  using type = long long; };
	template <utb::size_t Target> struct long_long_alignment<Target, false> {
    	using type = typename  double_alignment<Target, alignment_of<double>::res >= Target>::type; };

	template <utb::size_t Target, bool check> struct long_alignment{ using type = long; };
	template <utb::size_t Target> struct long_alignment<Target, false> {
		using type = typename long_long_alignment<Target, alignment_of<long long>::res >= Target>::type; };

	template <utb::size_t Target, bool check> struct int_alignment{ using type = int; };
	template <utb::size_t Target> struct int_alignment<Target, false>{
		using type = typename long_alignment<Target, alignment_of<long>::res >= Target>::type; };

	template <utb::size_t Target, bool check> struct short_alignment{ using type = short; };
	template <utb::size_t Target> struct short_alignment<Target, false>{
		using type = typename int_alignment<Target, alignment_of<int>::res >= Target>::type; };

	template <utb::size_t Target, bool check> struct char_alignment{ using type = char; };
	template <utb::size_t Target> struct char_alignment<Target, false>{
		using type = typename short_alignment<Target, alignment_of<short>::res >= Target>::type; };

    template<typename T>
	struct aligned_as {
	    using res = typename detail::type_with_alignment<alignment_of<T>::res>;
	};

	template <class integral>
	constexpr bool is_aligned(integral x, utb::size_t a) noexcept {
		return (x & (integral(a) - 1)) == 0u;
	}
	inline bool is_aligned(const volatile void* p, utb::size_t a) {
	  return is_aligned(reinterpret_cast<uintptr_t>(p), a);
	}

	template <class integral>
	constexpr integral align_up(integral x, utb::size_t a) noexcept {
		return integral((x + (integral(a) - 1)) & ~integral(a-1));
	}
	template <class pointer>
	pointer align_up_ptr(pointer p, utb::size_t a) {
	  	return reinterpret_cast<pointer>(align_up(reinterpret_cast<uintptr_t>(p), a));
	}

	template <class integral>
	constexpr integral align_down(integral x, utb::size_t a) noexcept {
		return integral(x & ~integral(a-1));
	}
	template <class pointer>
	pointer align_down_ptr(pointer p, utb::size_t a) {
	  	return reinterpret_cast<pointer>(align_down(reinterpret_cast<uintptr_t>(p), a));
	}


	/**
	 * @brief is a valid alignment, i.e. a power of two not zero
	 */
	constexpr bool is_aligvalid(utb::size_t alignment) noexcept {
		return alignment && (alignment & (alignment - 1)) == 0u;
	}

	// returns the offset needed to align ptr for given alignment
	inline utb::size_t alig_offset(void* address, utb::size_t alignment) noexcept {
		if(!is_aligvalid(alignment)) return 0;

		auto _isaligned = reinterpret_cast<uintptr_t>(address) & (alignment - 1);
		return _isaligned != 0 ? (alignment - _isaligned) : 0;
	}

	inline utb::size_t alignment_for(const utb::size_t size) noexcept {
		if(size >= max_alignment) return max_alignment;

		return (utb::size_t(1) << nlz(size) );
	}
}

#endif