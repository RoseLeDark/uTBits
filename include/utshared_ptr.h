/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
#ifndef __UTSHARED_PTR_H__
#define __UTSHARED_PTR_H__ 

#include "uttypes.h"
#include "utconfig.h"
#include "utatomic.h"
#include "utfunctional.h"

namespace utb {

    template < typename T, typename TRefType >
    class basic_shared_ptr   {
    public:
        using value_type = T;
        using element_type = T;
        using reference = T&;
        using const_value_type = const value_type;
        using pointer = value_type*;
        using ref_type = TRefType;

        using self_type = basic_shared_ptr<value_type, ref_type>;


        explicit basic_shared_ptr(pointer ptr )
            : m_ref(1), m_ptr(ptr)  { }

        basic_shared_ptr(const self_type& sp) {
            assert( (++m_ref != 0) );
            m_ptr = sp.m_ptr;
        }

        ~basic_shared_ptr() {
            if (--m_ref == 0) delete m_ptr;
        }

        pointer release() {
            pointer __px = this->get();
            if (--m_ref == 0) delete m_ptr;

            return __px;
        }
        void reset( pointer pValue = 0)
            { self_type(pValue).swap(*this); }

        ref_type ref() {
            return m_ref;
        }
        void swap(self_type& b) {
            utb::swap<pointer>(m_ptr, b.m_ptr);
            utb::swap<ref_type >(m_ref, b.m_ref);
        }

        pointer get() const {
            return static_cast<T*>(m_ptr);
        }

        pointer operator->() const {
            assert(get() != 0);
            return this->get();
        }
        const_value_type& operator*() {
            assert(get() != 0);
            return *this->get();
        }
        operator bool() {
            return m_ptr != 0;
        }

        self_type& operator = (self_type& sp) {
            release();
            m_ptr = sp.m_ptr;
            m_ref = sp.m_ref;
            return *this;
        }
    private:
        ref_type m_ref;
        pointer m_ptr;
    };

    #if UTB_ATOMIC == 1
        template <typename T>
        using shared_ptr = basic_shared_ptr< T, utb::atomic::atomic_size_t>;
    #else
        template <typename T>
        using shared_ptr = basic_shared_ptr< T, utb::size_t>;
    #endif

    template<typename T, typename... Args >
    inline shared_ptr<T>  make_shared(Args&&... args) {
        return shared_ptr<T>(new T (utb::forward<Args>(args)...) );
    }
}

#endif // __UTSHARED_PTR_H__