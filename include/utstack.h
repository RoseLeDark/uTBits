#ifndef _UT_STACK_H_
#define _UT_STACK_H_

#include "utconfig.h"

#include "utoptional.h"
#include "utbuffer.h"
#include "uttypetraits.h"
#include "utalgorithm.h"
#include "utfast_addr.h"

namespace utb {
     /**
         * A simple template for a Stack

         */
        template<typename TValueType, utb::size_t TSize>
        class basic_stack {
        public:
            using self_type = basic_stack<TValueType, TSize>;
            using value_type = TValueType;
            using size_type = utb::size_t;

            basic_stack() = default;
            ~basic_stack() = default;
            /**
             * @brief Push a value onto the stack.
             * @param value The value to push.
             */
            bool push(const_reference value) {  
                if(full()) return false;
                return m_buffer.write(value) != 0; 
            }
            /**
             * @brief Pop a value from the stack.
             * @return The popped value.
             */
            utb::optional<value_type> pop() { 
                if(empty()) return utb::optional<value_type>();
                value_type value =  m_buffer.read();
                m_buffer--; 
                return utb::optional<value_type>(value); 
            } 
            /**
             * @brief Check if the stack is empty.
             * @return true if the stack is empty, false otherwise.
             */
            constexpr bool empty() const noexcept { return m_buffer.used() == 0; }

            /**
             * @brief Check if the stack is full.
             * @return true if the stack is full, false otherwise.
             */ 
            constexpr bool full() const noexcept { return m_buffer.is_full(); }

            /**
             * @brief Get the current size of the stack.
             * @return The current size of the stack.
             */
            constexpr size_type size() const noexcept { return m_buffer.used(); }

        private:
            value_type m_rawBuffer[TSize];
            utb::buffer<value_type, m_rawBuffer, TSize> m_buffer;
        };

        template<typename TValueType, utb::size_t TSize = UTB_CONFIG_DEFAULT_STACK_SIZE>
        using stack = basic_stack<TValueType, TSize>;
}


#endif