#ifndef __UT_FUNCTIONAL_H_
#define __UT_FUNCTIONAL_H_

#include "utfunctional.h"
#include "utalignment.h"

namespace utb {
    template <class Sig, size_t sz, size_t algn>
    class light_function_base;

	template <class TSIG, class... Args, size_t sz, size_t algn>
    class light_function_base<TSIG(Args...), sz, algn> {
        struct vtable_t {
            void (*mover)(void *src, void *dest);

            void (*destroyer)(void *);

            TSIG (*invoke)(void const *t, Args &&...args);

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
		using return_type = TSIG;

        light_function_base() { }
        light_function_base(const light_function_base &o)
            : table(o.table), data(o.data) { }

        light_function_base(light_function_base &&o)
            : table(o.table) {
            if (table) table->mover(&o.data, &data);
        }

        template <class F, class dF = decay_t<F>, enable_if_t<!is_same<dF, light_function_base>{}> * = nullptr,
                  enable_if_t<is_convertible<res_of_t<dF &(Args...)>, TSIG>{}> * = nullptr>
        light_function_base(F &&f) : table(vtable_t::template get<dF>()) {
            static_assert(sizeof(dF) <= sz, "object too large");
            static_assert(alignof(dF) <= algn, "object too aligned");
            new (&data) dF(forward<F>(f));
        }
        ~light_function_base() {
            if (table) table->destroyer(&data);
        }


        light_function_base &operator=(const light_function_base &o) {
            this->~light_function_base();
            new (this) light_function_base(move(o));
            return *this;
        }

        light_function_base &operator=(light_function_base &&o) {
            this->~light_function_base();
            new (this) light_function_base(move(o));
            return *this;
        }

        explicit operator bool() const {
            return table;
        }

        return_type operator()(Args... args) const {
            return table->invoke(&data, utb::forward<Args>(args)...);
        }
	private:
		vtable_t const *table = nullptr;
        aligned_storage_t<sz, algn> data;
    };

    template <class TSIG, class... Args, size_t sz, size_t algn>
    inline bool operator==(const light_function_base<TSIG(Args...), sz, algn> &__f, nullptr_t) {
        return !static_cast<bool>(__f);
    }


    template <class TSIG, class... Args, size_t sz, size_t algn>
    inline bool operator==(nullptr_t, const light_function_base<TSIG(Args...), sz, algn> &__f) {
        return !static_cast<bool>(__f);
    }

    template <class TSIG, class... Args, size_t sz, size_t algn>
    inline bool operator!=(const light_function_base<TSIG(Args...), sz, algn> &__f, nullptr_t) {
        return static_cast<bool>(__f);
    }

    template <class TSIG, class... Args, size_t sz, size_t algn>
    inline bool operator!=(nullptr_t, const light_function_base<TSIG(Args...), sz, algn> &__f) {
        return static_cast<bool>(__f);
    }

    template <class TSIG>
    using function = light_function_base<TSIG, sizeof(void *) * 4, alignof(void *)>;
}

#endif