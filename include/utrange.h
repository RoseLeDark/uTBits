#ifndef __UTB_RANGE_H__
#define __UTB_RANGE_H__

#include <assert.h>
#include "utconfig.h"


namespace utb {
    namespace internal {
        template <typename T, T TSTART, T TEND, bool TNEG, T TSTEP> 
        class basic_range {
            static_assert(TEND >= TSTART, "TEND must be greeter then as TSTART");
            static_assert(TSTEP != 0, "TSTEP must not be zero");
            static_assert(((TEND - TSTART) % TSTEP) == 0,  "TEND is not reachable with given TSTART and TSTEP");

            static constexpr T COUNT =  (TEND == TSTART) ? 2 :  ((TEND - TSTART) / TSTEP + 1);
        public:
            using value_type = T;
            using pointer = T*;
            using const_pointer = const T*;
            using reference_type = T&;
            using const_reference_type = const T&;
            using self_type = basic_range<T, TSTART, TEND, TNEG, TSTEP>;
             
            constexpr basic_range() noexcept : m_iPosition(0) {
                    initial_range();
            }
            
            constexpr value_type count() noexcept   { return COUNT; }

            constexpr value_type start()    { return TSTART; }
            constexpr value_type end()      { return m_nRange[COUNT - 1]; }
            constexpr value_type value()    { return m_nRange[m_iPosition]; }

            constexpr void       reset()    { m_iPosition = 0; }
            constexpr value_type position() { return m_iPosition; }
            constexpr void       position(const value_type i) { m_iPosition = (i >= COUNT)  COUNT - 1 : i;  }

            operator value_type      () const                           
                { return m_nRange[m_iPosition]; }
            constexpr reference_type operator[] (utb::size_t n) const 
                { return m_nRange[n]; }
            constexpr self_type&	 operator++ () 
                { m_iPosition++; if(m_iPosition >= COUNT) m_iPosition = COUNT - 1; return *this; }
            constexpr self_type&	 operator-- () 
                { m_iPosition--; if(m_iPosition <= 0 ) m_iPosition = 0; return *this; }

            operator bool () { return m_iPosition != COUNT-1; }
        private:
            void initial_range() {
                 if((TEND == TSTART)) {
                    m_nRange[0] = TSTART;
                    m_nRange[1] = TEND;
                } else {

                    value_type  BASE = TNEG ? -TSTART : TSTART;
                    value_type  STEP = TNEG ? -TSTEP  : TSTEP;


                    for (value_type i = 0; i < COUNT; ++i)
                        m_nRange[i] = BASE + i * STEP;

                }
            }
        private:
            value_type m_iPosition;
            value_type m_nRange[ COUNT ];
        };
    }
    template <typename T, T TSTART, T TEND, T TSTEP> 
    using rangex = internal::basic_range<T, TSTART, TEND, false, TSTEP>;

    template <unsigned int TSTART, unsigned int TEND, unsigned int TSTEP> 
    using range = internal::basic_range<unsigned int, TSTART, TEND, false, TSTEP>;

    template <typename T, T TSTART, T TEND, T TSTEP> 
    using nrangex = internal::basic_range<T, TSTART, TEND, true, TSTEP>;

    template <unsigned int TSTART, unsigned int TEND, unsigned int TSTEP> 
    using nrange = internal::basic_range<unsigned int, TSTART, TEND, true, TSTEP>;
}


#endif