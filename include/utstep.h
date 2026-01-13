#ifndef __UTB_STEP_H__
#define __UTB_STEP_H__

#include <assert.h>
#include "utconfig.h"

#include "utlimits.h"

namespace utb {

    template<typename T>
    class step {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference_type = T&;
        using const_reference_type = const T&;
        using self_type = step<T>;

        constexpr step(value_type start, value_type step, value_type end = utb::numeric_limits<T>::max() )
            : m_vStart(start), m_vValue(start), m_vStep(step), m_vEnd(end) { 
                if(m_vStep <= 0) m_vStep  = 1;

        }

        constexpr value_type start()    { return m_vStart; }
        constexpr value_type end()      { return m_vEnd; }
        constexpr value_type value()    { return m_vValue; }
        constexpr void       reset()    { m_vValue = m_vStart; }

        constexpr self_type& operator++() {  m_vValue += m_vStep;  return *this;  }
        constexpr self_type& operator--() {  m_vValue -= m_vStep; if(m_vValue < m_vStart) m_vValue = m_vStart; return *this;  }

        constexpr operator bool() const {
            return  (m_vValue <= m_vEnd);
        }

    protected:
        value_type m_vStart;
        value_type m_vValue;
        value_type m_vStep;
        value_type m_vEnd;
    };

    
    template<typename T>
    class xstep : step<T> {
    public:
        using base_type = step<T>;
        using self_type = xstep<T>;
        using value_type = typename base_type::value_type;
        using pointer = typename base_type::pointer;
        using const_pointer = typename base_type::const_pointer;
        using reference_type = typename base_type::reference_type;
        using const_reference_type = typename base_type::const_reference_type;
        
        constexpr xstep(value_type start, value_type step, value_type end = numeric_limits<T>::max)
            : base_type(start, step, end) { }
        
        constexpr self_type& step(const value_type stp) { m_vStep = stp; return step(); }
        constexpr self_type& step() { m_vValue += m_vStep; if(m_vValue > m_vEnd) m_vValue = m_vEnd; return *this; }

    };
}
#endif