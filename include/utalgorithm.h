#ifndef __UTF_ALGORITHMEN_H__
#define __UTF_ALGORITHMEN_H__

#include "uttypes.h"
#include "uttypetraits.h"
#include "utiterator.h"

#include <climits>

namespace utb {

    inline utb::size_t nlz_base(uint64_t x) {
		 unsigned long long value = x;
		 return sizeof(value) * CHAR_BIT - __builtin_clzll(value);
	}
	inline utb::size_t nlz(uint64_t x) {
		return nlz_base(x) - 1;
	}

    template<int TVal> struct int_to_type {
	    enum { value = TVal };
	};

	template <typename T>
	struct type_to_type {
		using orig_type = T;
	};

	template <bool flag, typename T, typename U>
	struct select {
		using result = T;
	};

	template <typename T, typename U>
	struct select<false, T, U> {
		using result = U;
	};

    namespace internal {

        template<typename T>
        void copy_n(const T* first, utb::size_t n, T* result, utb::int_to_type<false>) {
            const T* last = first + n;

            while (first != last) {
                switch (n & 0x3) {
                    case 0: *result++ = *first++;
                    case 3: *result++ = *first++;
                    case 2: *result++ = *first++;
                    case 1: *result++ = *first++;
                }
            }
        }

        template<typename T>
        void copy_n(const T* first, utb::size_t n, T* result, utb::int_to_type<true>) {
            assert(result >= first + n || result < first);
            memcpy(result, first, n * sizeof(T));
        }

        template<typename T>
        void copy(const T* first, const T* last, T* result, utb::int_to_type<false>) {
            T* localResult = result;
            while (first != last)
                *localResult++ = *first++;
        }
        template<typename T>
        void copy(const T* first, const T* last, T* result, utb::int_to_type<true>) {
            const utb::size_t n = reinterpret_cast<const char*>(last) - reinterpret_cast<const char*>(first);
            memcpy(result, first, n);
        }

        template<typename T>
        inline void move_n(const T* from, utb::size_t n, T* result, utb::int_to_type<false>) {
            for (int i = int(n) - 1; i >= 0; --i)
                    result[i] = from[i];
        }

        template<typename T>
        inline void move_n(const T* first, utb::size_t n, T* result, utb::int_to_type<true>) {
            memmove(result, first, n * sizeof(T));
        }

        template<typename T>
        inline void move(const T* first, const T* last, T* result, utb::int_to_type<false>) {
            result += (last - first);
            while (--last >= first)
                    *(--result) = *last;
        }
        template<typename T>
        inline  void move(const T* first, const T* last, T* result, utb::int_to_type<true>) {
            const utb::size_t n = reinterpret_cast<uintptr_t>(last) - reinterpret_cast<uintptr_t>(first);
            memmove(result, first, n);
        }


        template<typename T>
        void copy_construct_n(const T* first, utb::size_t n, T* result, utb::int_to_type<false>) {
            for (utb::size_t i = 0; i < n; ++i)
                new (result + i) T(first[i]);
        }

        template<typename T>
        void copy_construct_n(const T* first, utb::size_t n, T* result, utb::int_to_type<true>) {
            assert(result >= first + n || result < first);
            memcpy(result, first, n * sizeof(T));
        }

        template<typename T>
        void destruct_n(T* first, utb::size_t n, utb::int_to_type<false>) {
            sizeof(first);
            for (utb::size_t i = 0; i < n; ++i)
                    (first + i)->~T();
        }

        template<typename T>
        inline void destruct_n(T*, utb::size_t, utb::int_to_type<true>) {
            // Nothing to do, no destructor needed.
        }

        template<typename T>
        void destruct(T* mem, utb::int_to_type<false>) {
            sizeof(mem);
            mem->~T();
        }

        template<typename T>
        inline void destruct(T*, utb::int_to_type<true>) {
             // Nothing to do, no destructor needed.
        }

        template<typename T>
        void construct(T* mem, utb::int_to_type<false>) {
            new (mem) T();
        }

        template<typename T>
        inline void construct(T*, utb::int_to_type<true>) {
            // Nothing to do
        }

        template<typename T>
        inline void copy_construct(T* mem, const T& orig, utb::int_to_type<false>) {
            new (mem) T(orig);
        }

        template<typename T>
        inline void copy_construct(T* mem, const T& orig, utb::int_to_type<true>) {
            mem[0] = orig;
        }

        template<typename T>
        void construct_n(T* to, utb::size_t count, utb::int_to_type<false>) {
            sizeof(to);
            for (utb::size_t i = 0; i < count; ++i)
                    new (to + i) T();
        }

        template<typename T>
        inline void construct_n(T*, int, utb::int_to_type<true>) {
            // trivial ctor, nothing to do.
        }

        template<class TIter, class TPred>
        void test_ordering(TIter first, TIter last, const TPred& pred) {
        	sizeof(first); sizeof(last); sizeof(pred);
        }

        template<typename T1, typename T2, class TPred>
        inline bool debug_pred(const TPred& pred, const T1& a, const T2& b) {
         	return pred(a, b);
        }

		struct in_place_type_tag {};
		struct in_place_index_tag {};

		struct in_place_type {};
    } // Intarnal

    template<typename T>
    struct less {
        bool operator()(const T& lhs, const T& rhs) const noexcept {
            return lhs < rhs;
        }
	};
	template<typename T>
    struct greater {
        bool operator()(const T& lhs, const T& rhs) const noexcept {
            return lhs > rhs;
        }
	};
	template<typename T>
    struct equal_to {
        bool operator()(const T& lhs, const T& rhs) const noexcept {
            return lhs == rhs;
        }
	};
	template<typename T>
	struct not_equal_to {
        bool operator()(const T& lhs, const T& rhs) const noexcept {
            return lhs != rhs;
        }
	};


	template<typename T>
	struct greater_equal  {
		bool operator()(const T& lhs, const T& rhs) const noexcept {
            return lhs >= rhs;
        }
	};

	template<typename T>
	struct less_equal  {
		bool operator()(const T& lhs, const T& rhs) const noexcept {
            return lhs <= rhs;
        }
	};

	template<typename T>
	struct negate  {
		T operator()(const T& a) const noexcept {
            return -a;
        }
	};

	template<typename T>
	struct plus  {
		T operator()(const T& a, const T& b) const noexcept {
            return a + b;
        }
	};

	template<typename T>
	struct minus  {
		T operator()(const T& a, const T& b) const noexcept {
            return a - b;
        }
	};

	template<typename T>
	struct multiplies  {
		T operator()(const T& a, const T& b) const noexcept {
            return a * b;
        }
	};

	template<typename T>
	struct divides {
		T operator()(const T& a, const T& b) const noexcept {
            return a / b;
        }
	};

	template<typename T>
	struct modulus {
		T operator()(const T& a, const T& b) const noexcept {
            return a % b;
        }
	};



	template<typename T>
    T nexthigher(T k) noexcept  {
		k--;
		for (unsigned int i=1; i< sizeof(T) * 8; i <<= 1)
			k |= (k >> i);
		return k+1;
	}


	template <typename T>
	struct inc {
		using value_type = T;
		value_type operator()(value_type x) const { return ++x; }
	};

	template <typename T>
	struct dec {
		using value_type = T;
		value_type operator()(value_type x) const { return --x; }
	};

	template <typename T, typename R>
	inline R _reinterpret_cast(T* p) {
		return static_cast<R>(static_cast<void*>(p));
	}

	template <typename T, typename R>
	inline const R _const_reinterpret_cast(const T* p) {
		return static_cast<const R>(static_cast<const void*>(p));
	}

    inline utb::size_t popcount (uint32_t v)	{ return __builtin_popcount (v); }



    template<typename T>
    inline void  copy_construct(T* mem, const T& orig) {
	        internal::copy_construct(mem, orig, utb::int_to_type <utb::has_trivial_copy<T>::value> ());
	}

	

	template<typename T>
    inline void construct(T* mem) {
	        internal::construct(mem, utb::int_to_type<utb::has_trivial_constructor<T>::value>());
	}


	template<typename T>
    inline void destruct(T* mem) {
	        internal::destruct(mem, utb::int_to_type<utb::has_trivial_destructor<T>::value>());
	}

    template<typename T>
    void copy_n(const T* src, utb::size_t n, T* dest) {
	        internal::copy_n(src, n, dest, utb::int_to_type<utb::has_trivial_copy<T>::value>());
	}

	template<typename T>
    void copy(const T* src, const T* last, T* dest) {
	        internal::copy(src, last, dest, utb::int_to_type<utb::has_trivial_copy<T>::value>());
	}

	template<typename T>
    void copy_construct_n(T* src, utb::size_t n, T* dest) {
	        internal::copy_construct_n(src, n, dest, utb::int_to_type<utb::has_trivial_copy<T>::value>());
	}

	template<typename T>
    void move_n(const T* from, utb::size_t n, T* dest) {
        assert(from != dest || n == 0);

        if (dest + n >= from && dest < from + n) {
            internal::move_n(from, n, dest, utb::int_to_type<utb::has_trivial_copy<T>::value>());
        } else {
            internal::copy_n(from, n, dest, utb::int_to_type<utb::has_trivial_copy<T>::value>());
        }
	}

	template<typename T>
    inline void move(const T* src, const T* last, T* dest) {
        assert(src != dest || src == last);
        const utb::size_t n = reinterpret_cast<uintptr_t>(last) - reinterpret_cast<uintptr_t>(src);
        const unsigned char* destEnd = reinterpret_cast<const unsigned char*>(dest) + n;

        if (destEnd >= reinterpret_cast<const unsigned char*>(src) && dest < last) {
            internal::move(src, last, dest, utb::int_to_type<utb::has_trivial_copy<T>::value>());
        } else {
            internal::copy(src, last, dest, utb::int_to_type<utb::has_trivial_copy<T>::value>());
        }
	}

    template<typename T>
    inline void  copy_construct(T* mem, const T&& orig) {
	        internal::copy_construct(mem, utb::move<T>(orig), utb::int_to_type <utb::has_trivial_copy<T>::value> ());
	}

	template <typename T>
	inline T* copy_backward (const T* first, const T* last, T* result) noexcept {
		const utb::size_t nBytes (utb::distance (first, last));
		memmove (advance_ptr(result,-nBytes), first, nBytes);
	}

	template <class TIter, class TFn>
    TFn foreach(TIter src, TIter last, TFn fn) {
        while (src!=last)  {
            fn (*src); ++src;
        }
        return (fn);
	}

	template<typename T>
    void construct_n(T* src, utb::size_t n) {
	    internal::construct_n(src, n, utb::int_to_type<utb::has_trivial_constructor<T>::value>());
	}
	template<typename T>
    void destruct_n(T* src, utb::size_t n) {
	    internal::destruct_n(src, n, utb::int_to_type<utb::has_trivial_destructor<T>::value>());
	}
    template<typename T>
    inline void fill(T* src, T* last, const T& val) {
        while (src != last) {
            *src = val; src = src + 1;
        }
	}

	template<typename T>
    inline void fill_n(T* src, utb::size_t n, const T& val) {
        T* last = src + n;
        while (src != last) {
            switch (n & 0x7) {
                case 0: *src = val; ++src;
                case 7: *src = val; ++src;
                case 6: *src = val; ++src;
                case 5: *src = val; ++src;
                case 4: *src = val; ++src;
                case 3: *src = val; ++src;
                case 2: *src = val; ++src;
                case 1: *src = val; ++src;
            }
        }
	}


	template <class TIter, class TPred = utb::less<TIter> >
	constexpr TIter lower_bound (TIter first, TIter last, const TPred& value) {
		TIter mid;
		while (first != last) {

			mid = first + utb::size_t(utb::distance (first,last))/2;
			if (value < *mid) first = mid + 1;
			else last = mid;
		}
		return last;
	}

	template <class TIter, typename T, class TPred = utb::less<TIter> >
    constexpr TIter lower_bound(TIter src, TIter last, const T& val, const TPred& pred) {
	        internal::test_ordering(src, last, pred);
	        int dist(0);
	        dist = distance(src, last);

	        while (dist > 0) {
                const int halfDist = dist >> 1;
                TIter mid = src;
                advance(mid, halfDist);
                if (internal::debug_pred(pred, *mid, val))
                        src = ++mid, dist -= halfDist + 1;
                else
                        dist = halfDist;
	        }
	        return src;
	}


	template <class TIter, class TPred = utb::less<TIter> >
	constexpr TIter upper_bound (TIter first, TIter last, const TPred& value) {
		TIter mid;
		while (first != last) {

			mid = first + utb::size_t(utb::distance (first,last))/2;
			if (value < *mid) last = mid;
			else first = mid + 1;
		}
		return last;
	}

	template <class TIter, typename T, class TPred = utb::less<TIter>>
    constexpr TIter upper_bound(TIter src, TIter last, const T& val, const TPred& pred) {
	        internal::test_ordering(src, last, pred);
	        int dist(0);
	        dist = distance(src, last);

	        while (dist > 0) {
                const int halfDist = dist >> 1;
                TIter mid = src;
                advance(mid, halfDist);
                if (!internal::debug_pred(pred, val, *mid))
                    src = ++mid, dist -= halfDist + 1;
                else
                    dist = halfDist;
	        }
	        return src;
	}

	template <typename TIter, typename TComp>
	inline constexpr bool binary_search (TIter first, TIter last, const TComp& value) {
		TIter found = utb::lower_bound (first, last, value);
		return found != last && !(value < *found);
	}




	template <class TIter, typename T>
    TIter find(TIter src, TIter last, const T& val) {
        while (src != last) {
            if ((*src) == val) return src;
            ++src;
        }
        return last;
	}

	template <class TIter, typename T, class TPred = utb::less<TIter>>
    TIter find_if(TIter src, TIter last, const T& val, const TPred& pred) {
        while (src != last) {
            if (pred(*src, val))
                    return src;
            ++src;
        }
        return last;
	}

	template <class TIter, typename T>
    void accumulate(TIter src, TIter last, T& dest) {
        while (src != last)  {
            dest += *src; ++src;
        }
	}
    #undef abs

	template<typename T>
    T abs(const T& t) {
	    return t >= T(0) ? t : -t;
	}
    template<int>
	inline int abs(const int& x) {
        const int y = x >> 31;
        return (x ^ y) - y;
	}
    template<short>
	inline short abs(const short& x) {
        const short y = x >> 15;
        return (x ^ y) - y;
	}

    template<typename T>
    inline bool is_range(const T ch, const T min, const T max) { return (ch >= min && ch <= max); }

    inline bool islower(char ch) { return is_range<char>(ch, 0x61, 0x7A); }

    inline bool isupper(char ch) { return is_range<char>(ch, 0x41, 0x5A); }

    inline bool isalpha(char ch) { return (isupper(ch) ||  islower(ch) ); }

    inline bool isdigit(char ch) { return is_range<char>(ch, 0x30,  0x39); }

    inline bool iscntrl(char ch) { return is_range<char>(ch, 0x00,  0x1F) || ch == 0x7F; }

    inline bool isspace(char ch) { return is_range<char>(ch, 0x09,  0x0D) || ch == 0x20; }

    inline bool isblank(char ch) { return ch == 0x09 || ch == 0x20; }

    inline bool isgraph(char ch) { return is_range<char>(ch, 0x21,  0x7E); }

    inline bool isprint(char ch) { return  (isgraph(ch)  || ch == 0x20 ); }

    inline bool isxdigit(char ch){ return isdigit(ch) || is_range<char>(ch, 0x41,  0x46) || is_range<char>(ch, 0x61,  0x66);   }

    inline bool isalnum(char ch)  { return isdigit(ch) || isalpha(ch); }

    inline char hex2char(char ch) {
        return ( isdigit(ch) ) ?  ch - 48 :  ( islower(ch) ) ?  ch - 87 :
               ( isupper(ch) ) ?  ch - 55 :  0;
    }


	template<typename T>
    inline T max(const T x, const T y) {
	    return x > y ? x : y;
	}

	template<typename T>
    inline T min(const T x, const T y) {
	    return x < y ? x : y;
	}

	template <typename TAssignable>
    void swap(TAssignable& a, TAssignable& b) {
        TAssignable tmp = utb::move(a);

        a = utb::move(b);
        b = utb::move(tmp);
	}

	template <typename TAssignable, utb::size_t N>
    inline void swap(TAssignable (&x)[N], TAssignable (&y)[N]) {
      for (utb::size_t i = 0; i < N; i++)
			utb::swap(x[i], y[i]);
    }

	template <typename fIt1, typename fIt2 >
    inline void iter_swap(fIt1 a, fIt2 b) {
      utb::swap(*a, *b);
    }

	template <typename fIt1, typename fIt2 >
    fIt2 swap_ranges(fIt1 a, fIt1 b, fIt2 c) {
		for (; a != b; ++a, ++c)
			utb::iter_swap(*a, *c);
		return c;
    }

    template <typename TRandomAccessIterator, typename TRandFunc>
	void random_shuffle (TRandomAccessIterator first, TRandomAccessIterator last, const TRandFunc& func) {
		for (; first != last; ++ first)
			utb::iter_swap (first, first + (func() % distance (first, last)));
	}
}
#endif