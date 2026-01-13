/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
#ifndef __UT_NODE_H__
#define __UT_NODE_H__

#include "utconfig.h"

namespace utb {
    template <class TNODE>
        class basic_node_itarrator {
        public:
            using value_type = typename TNODE::value_type;
            using pointer = value_type*;
            using reference = value_type&;
            using self_type = basic_node_itarrator<TNODE>;
            using difference_type = ptrdiff_t;
            using node_type = TNODE;

            basic_node_itarrator() : m_pNode(NULL) { }
            basic_node_itarrator(node_type _pNode) : m_pNode(_pNode) { }
            basic_node_itarrator(const self_type& _pOther ) : m_pNode(_pOther.m_pNode) { }

            self_type& operator ++ () {
                if(m_pNode) m_pNode = m_pNode->Next;
                return *this;
            }
            self_type& operator -- () {
                if(m_pNode) m_pNode = m_pNode->Prev;
                return *this;
            }

            reference operator*() const { return m_pNode->get(); }
            pointer operator->() const { return &m_pNode->get(); }

            self_type operator++(int) {
                self_type copy(*this); ++(*this); return copy; }

            self_type operator--(int) {
                self_type copy(*this); --(*this); return copy; }

            bool operator == (const self_type& rhs) const {
                return rhs.m_pNode == m_pNode; }

            bool operator != (const self_type& rhs) const {
                return !(rhs == *this); }
        private:
            node_type m_pNode;
        };

        template <class TNODE>
        class basic_node_itarrator_res {
        public:
           // using iterator_category = bidirectional_iterator_tag;
            using value_type = typename TNODE::value_type;
            using pointer = value_type*;
            using reference = value_type&;
            using self_type = basic_node_itarrator_res<TNODE>;
            using difference_type = ptrdiff_t;
            using node_type = TNODE;

            basic_node_itarrator_res() : m_pNode(NULL) { }
            basic_node_itarrator_res(node_type _pNode) : m_pNode(_pNode) { }
            basic_node_itarrator_res(const self_type& _pOther ) : m_pNode(_pOther.m_pNode) { }

            self_type& operator ++ () {
                if(m_pNode) m_pNode = m_pNode->Prev;
                return *this;
            }
            self_type& operator -- () {
                if(m_pNode) m_pNode = m_pNode->Next;
                return *this;
            }

            reference operator*() const { return m_pNode->get(); }
            pointer operator->() const { return &m_pNode->get(); }

            self_type operator++(int) {
                self_type copy(*this); ++(*this); return copy; }

            self_type operator--(int) {
                self_type copy(*this); --(*this); return copy; }

            bool operator == (const self_type& rhs) const {
                return rhs.m_pNode == m_pNode; }

            bool operator != (const self_type& rhs) const {
                return !(rhs == *this); }
        private:
            node_type m_pNode;
        };

        template <typename T>
        class basic_node {
        public:
            //using iterator_category = bidirectional_iterator_tag;
            using self_type = basic_node<T>;
            using value_type = T;
            using pointer = value_type*;
            using const_pointer = const pointer;
            using reference = value_type&;
            using const_reference = const reference;

            using iterator = basic_node_itarrator<self_type>;
            using const_iterator = const basic_node_itarrator<const self_type>;

            using reverse_iterator = basic_node_itarrator_res<self_type>;
            using const_reverse_iterator = const basic_node_itarrator_res<const self_type>;
            /**
             * @brief Construct a new base node object
             */
            explicit basic_node(value_type value )
                : Next(0), Prev(0), m_tValue(value) { }

            basic_node(self_type* _pNext, self_type* _pPrev)
                : Next(_pNext), Prev(_pPrev), m_tValue( value_type() ) { }
            basic_node(const self_type& _pOther)
                : Next(_pOther.Next), Prev(_pOther.Prev), m_tValue(_pOther.m_tValue) { }

            iterator            begin()         { return iterator( root() ); }
            reverse_iterator    rbegin()        { return reverse_iterator( last() ); }
            const_iterator      cbegin() const  { return const_iterator( root() ); }

            iterator            end()           { return iterator( last() ); }
            reverse_iterator    rend()          { return reverse_iterator( root() ); }
            const_iterator      cend() const    { return const_iterator( last() ); }

            self_type*   root() {
                return (Prev != 0) ? Prev->root() : this;
            }
            const self_type* root() const {
                return (Prev != 0) ? Prev->root() : this;
            }
            self_type*   last() {
                return (Next != 0) ? Next->last() : this;
            }
            const self_type* last() const {
                return (Next != 0) ? Next->last() : this;
            }

            /**
             * @brief Inserts this standalone node before the node pNext in pNext's .
             */
            void insert(self_type* pNext) {
                Next = pNext;
                Prev = pNext->Prev;
                pNext->Prev->Next = this;
                pNext->Prev = this;
            }
            /**
             * @brief Removes this node from the  it's in.
             */
            void remove() {
                Next->Prev = Prev;
                Prev->Next = Next;
            }

            bool is() const { return this != Next; }

            /**
             * @brief Removes [pFirst,pLast) from the  it's in and inserts it before this in this node's .
             */
            void splice(self_type* first, self_type* last) {
                last->Prev->Next  = this;
                first->Prev->Next = last;
                this->Prev->Next  = first;

                self_type* pTemp = this->Prev;
                this->Prev  = last->Prev;
                last->Prev  = first->Prev;
                first->Prev = pTemp;
            }
            /**
             * @brief Reverses the order of nodes in the circular  this node is a part of.
             */
            void reverse() {
                self_type*  pNode = this;

                do {
                    if(pNode != NULL) {
                        self_type* pTemp = pNode->Next;
                        pNode->Next = pNode->Prev;
                        pNode->Prev = pTemp;
                        pNode         = pNode->Prev;
                    }
                } while(pNode != this);
            }
            /**
             * @brief Add a range of elements
             */
            void insert_range(self_type*  pFirst, self_type*  pFinal) {
                Prev->Next = pFirst; pFirst->Prev = Prev;
                Prev       = pFinal; pFinal->Next = this;
            }
            void swap(self_type& other) {
                const basic_node temp(this);
                this = other; other = temp;

                if(this.Next == &other) this.Next = this.Prev = this;
                else this.Next->Prev = this.Prev->Next = this;

                if(other.Next == this) other.Next = other.Prev = &other;
                else other.Next->Prev = other.Prev->Next = &other;

            }
            /**
             * @brief remove a range of elements
             */
            static void remove_range(self_type* pFirst, self_type* pFinal) {
                pFinal->Next->Prev = pFirst->Prev;
                pFirst->Prev->Next = pFinal->Next;
            }

            value_type get() { return m_tValue; }

            bool operator == (const self_type& rhs) const {
                if( rhs.Next != Next) return false;
                if( rhs.Prev != Prev) return false;
                return (rhs.m_tValue == m_tValue);
            }

            bool operator != (const self_type& rhs) const {
                return !(rhs == *this);
            }

            /**
             * @brief The pointer to the next node
             */
            self_type*  Next;
            /**
             * @brief The pointer to the prev node
             */
            self_type*  Prev;
        private:
            value_type m_tValue;
        };


        template <typename T>
        inline void swap(basic_node<T>& a, basic_node<T>& b) {
            a.swap(b);
        }
        
        template<typename T>
        using node = basic_node<T>;
}



#endif