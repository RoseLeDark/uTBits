/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
#ifndef __UTWEAK_PTR_H__
#define __UTWEAK_PTR_H__ 

#include "uttypes.h"
#include "utconfig.h"
#include "utatomic.h"

#include "utshared_ptr.h"

namespace utb {

    template <typename T, typename TRefType >
    class basic_weak_ptr {
    public:
        using value_type = T;
        using element_type = T;
        using reference = T&;
        using const_value_type = const value_type;
        using pointer = value_type*;
        using count_type = TRefType;


        using self_type = basic_weak_ptr<value_type, count_type>;
        using shared_type = basic_shared_ptr<value_type, count_type>;


        explicit basic_weak_ptr(value_type pValue = 0)
            : m_ptr(pValue), m_ref(1)  { }

        basic_weak_ptr( const self_type& r )
            : m_ptr(r.m_ptr), m_ref(r.m_ref)  { }

        basic_weak_ptr( shared_type& pShrd) : m_ptr(pShrd.get()), m_ref( pShrd.ref() ) {}

        template<class U, typename YRefType = count_type>
        basic_weak_ptr( const basic_weak_ptr<U, YRefType>& r )
            : m_ptr(r.m_ptr), m_ref(r.m_ref)  { }

        template<class U, typename YRefType = count_type>
        basic_weak_ptr( const basic_shared_ptr<U, YRefType>& pShrd) : m_ptr(pShrd.get()), m_ref(pShrd.ref() ) {}

        shared_type lock()                          { return shared_type(m_ptr); }
        bool expired()                              { return m_ref.get() == 0; }
        void reset()                                { self_type(0).swap(*this); }

        count_type use_count()                  	{ return m_ref.get(); }

        void swap(self_type& other) {
            utb::swap<pointer>(m_ptr, other.m_ptr);
            utb::swap<count_type >(m_ref, other.m_ref);
        }
        template<class Y, typename YRefType = count_type>
        bool owner_before( const basic_weak_ptr<Y, YRefType> & rhs ) {
            return m_ref < rhs.m_ref;
        }
        template<class Y, typename YRefType = count_type>
        bool owner_before( const basic_shared_ptr<Y, YRefType> & rhs ) {
            return m_ref < rhs.ref();
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

        operator bool() { return m_ptr != 0; }

        self_type& operator=( const self_type& r ) {
            m_ptr = r.m_ptr;
            m_ref = r.m_ref;
            return *this;
        }
    private:
        pointer m_ptr;
        count_type m_ref;
    };

    #if UTB_ATOMIC == 1
        template <typename T>
        using weak_ptr = basic_weak_ptr< T, utb::atomic::atomic_size_t>;
    #else
        template <typename T>
        using weak_ptr = basic_weak_ptr< T, utb::size_t>;
    #endif

    template<typename T, typename... Args >
    inline weak_ptr<T>  make_weak(Args&&... args) {
        return weak_ptr<T>(new T (utb::forward<Args>(args)...) );
    }
}

#endif // __TWEAK_PTR_H__