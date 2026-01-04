#ifndef _UT_STACK_H_
#define _UT_STACK_H_

#include "utconfig.h"

#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

namespace utb {
     /**
         * A simple template for a Stack

         */
        template<typename TType>
        class basic_stack {
        public:
            using basic_type_t = TType;

            /**
             * This constructor use a given address as buffer
             * @param nSize The size of the stack (The last position [addr+(nSize)] )
             * @param addr The first buffer or adress to use as stack
             */
            basic_stack(size_t nSize, basic_type_t* addr) {
                internal_create(nSize, addr, 0); }

            /**
             * This constructor use a given address as buffer
             * @param nSize The size of the stack (The last position [addr+(nSize)] )
             * @param addr The first buffer or adress to use as stack
             * @param offset The offset, when start position in the buffer not address 0 is
             */
            basic_stack(size_t nSize, basic_type_t* addr, int offset) {
                internal_create(nSize, addr, offset); }

            /**
             *  Add an item to the stack
             *
             *  @param item The item you are adding.
             *  @return - 0 the item was added
             *          - 1 the stack is full
             */
            int push(basic_type_t item) {
                int _ret = 1;

                if(m_iCurrent < m_iLast - 1) {
                    m_iCurrent++;
                    m_ulAdrr[m_iCurrent] = item;
                    _ret = 0;
                }
                return _ret;
            }
            /**
             * Pop an item from the stack
             * @param item Where the item you are removing will be returned to.
             * @return  - 0 the item was removed
             *          - 2 the given item was null
             *          - 1 the stack is empty
             */
            int pop(basic_type_t* item) {
                if(item == NULL) return 2;

                if(count() > 0 ) {
                    basic_type_t x = m_ulAdrr[m_iCurrent];
                    m_iCurrent--;
                    *item = x;
                    return 0;
                }
                return 1;
            }
            /**
             * get the current obj from the stack, this will not remove it
             *
             * @param item Where the item you are getting will be returned to.
             * @return  - 0 the item was removed
             *          - 2 the given item was null
             *          - 1 the stack is empty
             */
            int peek(basic_type_t* item) {
                if(item == NULL) return 2;

                if(count() > 0 ) {
                    basic_type_t x = m_ulAdrr[m_iCurrent];
                    *item = x;
                    return 0;
                }
                return 1;
            }
            /**
             * Reset the stack, will remove all objects in the stack
             */
            void reset() {
                internal_reset();
            }

            /**
             * Get the count of the stack
             * @return The count of the stack
             */
            int count()     { return m_iCurrent + 1; }
            /**
             * Get the size of the stack
             * @return The size of the stack.
             */
            int size()      { return m_ulSize; }

            /**
             *  Is the stack empty?
             *  @return true the stack is empty and false when not
             */
            bool is_empty() { return (m_iCurrent == -1); }
            /**
             *  Is the stack full?
             *  @return true the stack is full and false when not
             */
            bool is_full()  { return (m_iCurrent == (m_iLast - 1) ); }

            /**
             * How many empty spaves are currently left in the stack.
             */
            int get_left()  { return m_ulSize - (m_iCurrent + 1); }
        private:
            /**
             * the internal creating function for the stack
             * @param nSize The size of the stack (The last position [addr+(nSize)] )
             * @param addr The first buffer or adress to use as stack
             * @param offset The offset, when start position in the buffer not address 0 is
             */
            void internal_create(size_t nSize, basic_type_t* addr, int offset) {
                m_ulAdrr = (addr);
                m_ulSize = (nSize - offset);

                m_iFirst = (offset - 1);
                m_iCurrent = (m_iFirst);
                m_iLast = (nSize);
            }
            /**
             * The internal reset function
             */
            void internal_reset() {
                while(!is_empty())
                    pop();
                m_iCurrent = m_iFirst;
            }
        private:
            basic_type_t *m_ulAdrr;
            size_t m_ulSize;
            size_t m_iFirst;
            size_t m_iLast;
            size_t m_iCurrent;
        };

        template<typename T>
        using stack = basic_stack<T>;
}


#endif