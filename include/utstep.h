#ifndef __UTB_STEP_H__
#define __UTB_STEP_H__

#include <assert.h>
#include "utconfig.h"

#include "utlimits.h"

namespace utb {

    /// @brief A class that iterates through a range with a fixed step size.
    /// @tparam T The numeric type for start, step, and end values.
    template<typename T>
    class step {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference_type = T&;
        using const_reference_type = const T&;
        using self_type = step<T>;

        /// @brief Constructs a step iterator with start, step size, and optional end value.
        /// @param start The starting value.
        /// @param step The step size (must be positive; defaults to 1 if <= 0).
        /// @param end The end value (defaults to the maximum value of type T).
        constexpr step(value_type start, value_type step, value_type end = utb::numeric_limits<T>::max() )
            : m_vStart(start), m_vValue(start), m_vStep(step), m_vEnd(end) { 
                if(m_vStep <= 0) m_vStep  = 1;

        }

        /// @brief Returns the start value.
        constexpr value_type start()    { return m_vStart; }
        /// @brief Returns the end value.
        constexpr value_type end()      { return m_vEnd; }
        /// @brief Returns the current value.
        constexpr value_type value()    { return m_vValue; }
        /// @brief Resets the current value to the start value.
        constexpr void       reset()    { m_vValue = m_vStart; }

        /// @brief Increments the current value by the step size.
        constexpr self_type& operator++() {  m_vValue += m_vStep;  return *this;  }
        /// @brief Decrements the current value by the step size (clamped to start value).
        constexpr self_type& operator--() {  m_vValue -= m_vStep; if(m_vValue < m_vStart) m_vValue = m_vStart; return *this;  }

        /// @brief Conversion operator to bool. Returns true if the current value is within range.
        constexpr operator bool() const {
            return  (m_vValue <= m_vEnd);
        }

    protected:
        value_type m_vStart;
        value_type m_vValue;
        value_type m_vStep;
        value_type m_vEnd;
    };

    
    /// @brief An extended step iterator that allows dynamic modification of the step size.
    /// @tparam T The numeric type for start, step, and end values.
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
        
        /// @brief Constructs an extended step iterator with start, step size, and optional end value.
        /// @param start The starting value.
        /// @param step The step size.
        /// @param end The end value (defaults to the maximum value of type T).
        constexpr xstep(value_type start, value_type step, value_type end = numeric_limits<T>::max)
            : base_type(start, step, end) { }
        
        /// @brief Sets a new step size and advances the current value.
        /// @param stp The new step size.
        /// @return Reference to this object.
        constexpr self_type& step(const value_type stp) { m_vStep = stp; return step(); }
        /// @brief Advances the current value by the step size (clamped to end value).
        /// @return Reference to this object.
        constexpr self_type& step() { m_vValue += m_vStep; if(m_vValue > m_vEnd) m_vValue = m_vEnd; return *this; }

    };
}
#endif