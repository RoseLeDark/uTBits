#ifndef __UT_FUNCTIONAL_H_
#define __UT_FUNCTIONAL_H_

#include "utfunctional.h"
#include "utalignment.h"

/// @brief Utility namespace for the uTBits library.
namespace utb {
    /// @brief Lightweight, non-allocating function wrapper.
    ///
    /// This class template provides a small-object-optimized callable wrapper
    /// similar in spirit to std::function but intended for embedded/low-overhead
    /// use. It stores callable objects inside an internal buffer of fixed
    /// size to avoid heap allocations.
    /// @tparam Sig Function signature (return type and argument types).
    /// @tparam sz Size of the internal buffer in bytes for small-object optimization.
    /// @tparam algn Alignment requirement for the internal buffer.
    template <class Sig, utb::size_t sz, utb::size_t algn>
    class light_function_base;

	template <class TSIG, class... Args, utb::size_t sz, utb::size_t algn>
    class light_function_base<TSIG(Args...), sz, algn> {
        /// @brief Type-erased vtable storing operations for the contained callable.
        ///
        /// The vtable provides three operations: move the stored object, destroy
        /// the stored object, and invoke the stored callable with the given
        /// arguments.
        struct vtable_t {
            /// @brief Move the stored object from src to dest (placement-new).
            void (*mover)(void *src, void *dest);

            /// @brief Destroy the stored object in-place.
            void (*destroyer)(void *);

            /// @brief Invoke the stored callable and return the result.
            TSIG (*invoke)(void const *t, Args &&...args);

            /// @brief Obtain a vtable instance for a specific callable type T.
            ///
            /// The returned pointer is valid for the lifetime of the program.
            template <class T> static vtable_t const *get() {
                static const vtable_t table = {
                    [](void *src, void *dest) { new (dest) T(utb::move(*static_cast<T *>(src))); },
                    [](void *t) { static_cast<T *>(t)->~T(); },
                    [](void const *t, Args &&...args) -> TSIG {
                        return (*static_cast<T const *>(t))(utb::forward<Args>(args)...);
                    }
                };
                return &table;
            }
        };
	public:
        /// @brief The return type of the wrapped callable.
        using return_type = TSIG;

        /// @brief Default-construct an empty wrapper (no callable stored).
        light_function_base() { }

        /// @brief Copy-construct from another wrapper.
        light_function_base(const light_function_base &o)
            : table(o.table), data(o.data) { }

        /// @brief Move-construct from another wrapper.
        light_function_base(light_function_base &&o)
            : table(o.table) {
            if (table) table->mover(&o.data, &data);
        }

        /// @brief Construct from any callable object compatible with the signature.
        ///
        /// The callable is stored in-place in the internal buffer. SFINAE is used
        /// to prevent accidental construction from another light_function_base and
        /// to ensure the callable's return type is convertible to TSIG.
        template <class F, class dF = decay_t<F>, enable_if_t<!is_same<dF, light_function_base>{}> * = nullptr,
                  enable_if_t<is_convertible<res_of_t<dF &(Args...)>, TSIG>{}> * = nullptr>
        light_function_base(F &&f) : table(vtable_t::template get<dF>()) {
            static_assert(sizeof(dF) <= sz, "object too large");
            static_assert(alignof(dF) <= algn, "object too aligned");
            new (&data) dF(forward<F>(f));
        }

        /// @brief Destroy the stored callable, if any.
        ~light_function_base() {
            if (table) table->destroyer(&data);
        }

        /// @brief Copy-assignment.
        light_function_base &operator=(const light_function_base &o) {
            this->~light_function_base();
            new (this) light_function_base(move(o));
            return *this;
        }

        /// @brief Move-assignment.
        light_function_base &operator=(light_function_base &&o) {
            this->~light_function_base();
            new (this) light_function_base(move(o));
            return *this;
        }

        /// @brief True if a callable is stored.
        explicit operator bool() const {
            return table;
        }

        /// @brief Invoke the stored callable with the given arguments.
        /// @note Behavior is undefined if no callable is stored.
        return_type operator()(Args... args) const {
            return table->invoke(&data, utb::forward<Args>(args)...);
        }
	private:
		vtable_t const *table = nullptr;
        aligned_storage_t<sz, algn> data;
    };

    template <class TSIG, class... Args, utb::size_t sz, utb::size_t algn>
    inline bool operator==(const light_function_base<TSIG(Args...), sz, algn> &__f, nullptr_t) {
        return !static_cast<bool>(__f);
    }


    template <class TSIG, class... Args, utb::size_t sz, utb::size_t algn>
    inline bool operator==(nullptr_t, const light_function_base<TSIG(Args...), sz, algn> &__f) {
        return !static_cast<bool>(__f);
    }

    template <class TSIG, class... Args, utb::size_t sz, utb::size_t algn>
    inline bool operator!=(const light_function_base<TSIG(Args...), sz, algn> &__f, nullptr_t) {
        return static_cast<bool>(__f);
    }

    template <class TSIG, class... Args, utb::size_t sz, utb::size_t algn>
    inline bool operator!=(nullptr_t, const light_function_base<TSIG(Args...), sz, algn> &__f) {
        return static_cast<bool>(__f);
    }

    template <class TSIG>
    using function = light_function_base<TSIG, sizeof(void *) * 4, alignof(void *)>;
}

#endif