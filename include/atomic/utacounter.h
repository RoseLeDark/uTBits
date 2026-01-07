#ifndef __UTATOMIC_COUNTER_H__
#define __UTATOMIC_COUNTER_H__

#include "../utatomic.h"
#include "../uttypes.h"
#if UTB_CONFIG_ENABLE_ATOMIC == UTB_YES


namespace utb {
    namespace atomic {

        template <typename TCOUNTERTYPE = uint32_t>
        class atomic_counter  {
        public:
            using value_type = TCOUNTERTYPE;
            /**
             * @brief Construct a new atomic_counter and initializes it to zero.
             */
            atomic_counter() : m_atomicCount(0) { }
            /**
             * @brief Construct a new atomic_counter and initializes it with the given
             * value.
             * @param value The start value for this the counter.
             */
            atomic_counter(const value_type& value) : m_atomicCount(value) { }
            /**
             * @brief Construct a new atomic_counter from a other atomic_counter.
             * @param other The other counter from copyed it.
             */
            atomic_counter(const atomic_counter& other) : m_atomicCount(other.m_atomicCount.load()) { }

            /**
             * @brief Converts the atomic_counter to value_type.
             */
            inline operator value_type () const 			{ return m_atomicCount.load(); }
            /**
             * @brief Get the value of the counter.
             * @return The value of the counter.
             */
            inline value_type value() const					{ return m_atomicCount.load(); }

            /**
             * @brief Increments the counter.
             * @return The result of the increment.
             */
            inline value_type operator ++ ()				{ return ++m_atomicCount; }
            /**
             * @brief Decrements the counter.
             * @return The result of the decrement.
             */
            inline value_type operator -- ()				{ return --m_atomicCount; }

            /**
             * @brief Increments the counter.
             * @return The previous value.
             */
            inline value_type operator ++ (int) 			{ return m_atomicCount++; }
            /**
             * @brief Decrements the counter.
             * @return The previous value.
             */
            inline value_type operator -- (int) 			{ return m_atomicCount--; }
            /**
             * @brief If the counter zero?
             * @return If true the counter is zero and if false otherwise.
             */
            inline bool operator ! () const					{ return m_atomicCount.load() == 0; }
            /**
             * @brief Assigns the value of another atomic_counter.
             */
            atomic_counter& operator = (const atomic_counter& other);
            /**
             * @brief Assigns a value to the counter.
             * @param value The value for assigns the counter.
             */
            atomic_counter& operator = (const value_type& value);
        private:
            atomic_t<value_type>	m_atomicCount;
        };
    }
}

#endif // UTB_CONFIG_ENABLE_ATOMIC
#endif // __UTATOMIC_COUNTER_H__
