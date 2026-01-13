/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
#ifndef __UT_MAP__
#define __UT_MAP__

#include "utpair.h"
#include "utvector.h"

namespace utb {
    /**
     * @brief  Lightweight c++11 dictionary map implementation.
     *
     * @tparam TKey The type for the key.
     * @tparam TValue The type for the value.
     * @tparam TMapSize The Max Entry of this map
     */
    template <class TKey, class TValue, utb::size_t TMapSize = UTB_MAX_MAP_ENTRYS>
    class light_map {
    public:
        using mapped_type = TValue;
        using key_type = TKey;

        using value_type = pair<TKey, TValue>;
        using reference = pair<TKey, TValue>&;
        using pointer = pair<TKey, TValue>*;
        using const_reference = const pair<TKey, TValue>&;
        using const_pointer = const pair<TKey, TValue>*;

        using difference_type = ptrdiff_t;
        using size_type = utb::size_t;

        using iterator = TValue*;
        using const_iterator = const TValue*;

        using self_type = light_map < TKey, TValue, TMapSize>;

        light_map(const size_type start_size = UTB_MAX_MAP_ENTRYS) noexcept
            :  m_ayKeyValue(start_size) { }

        ~light_map() {
            m_ayKeyValue.clear();
        }


        void clear() {
            m_ayKeyValue.clear();
        }

        template< class... Args >
        utb::pair<iterator, bool> assign(const key_type& key, Args && ... args) {
            value_type _value(key, utb::forward<Args>(args)...);

            return assign(_value);
        }

        utb::pair<iterator, bool> assign(const value_type& vValue) {
            utb::pair<iterator, bool> _ret(vValue.seconde, false);

            for(typename TContainer::iterator it = m_ayKeyValue.begin();
                        it != m_ayKeyValue.end(); it++) {
                value_type _pair = *it;

                if(_pair.first == vValue.first) {
                    m_ayKeyValue.erase(it);
                    m_ayKeyValue.insert(vValue);
                    _ret->second = true;
                }
            }
            return _ret;
        }

        /**
         * @brief Inserts a new element into the container constructed in-place with the given args if there is no
         * 		element with the key in the container.
         * @param key The key to emplace.
         * @param args arguments to forward to the constructor of the element.
         *
         * @return Returns a pair consisting of an iterator to the inserted element,
         *	and a bool denoting whether the insertion took place (true if insertion happened and false if not).
            */
        template< class... Args >
        utb::pair<iterator, bool> emplace(const key_type& key, Args && ... args) {
            value_type _value = value_type(key, utb::forward<Args>(args)...);

            return insert(_value);
        }

        /**
         * @brief Inserts value.
         * @param value The element value to insert.
         * @return  Returns a pair consisting of an iterator to the inserted element (or to the element that
                    prevented the insertion) and a bool denoting whether the insertion took place.
            */
        utb::pair<iterator, bool> insert( const value_type& value ) {
            utb::pair<iterator, bool> result(&value, false);

            if(find(value.first) == nullptr) {
                m_ayKeyValue.push_back(value);
                result.second = find(value.first) != nullptr;
            }

            return result;
        }

        template< class... Args >
        void insert_or_assign(const key_type& key, Args && ... args) {
            value_type _value(key, utb::forward<Args>(args)...);

            auto iter = find(key);
            if(iter == nullptr)
                insert(_value);
            else
                assign(_value);

        }

        /**
         * @brief insert key_type key with mapped_type value.
         * @return
         *	 - True: The key doesn't exist, the data is added to the map
            *	 - False: The key already exists, no change is made
            */
        bool insert(const key_type& key, const mapped_type& value) {
            return insert(value_type(key, value)).second;
        }

        /**
         * @brief insert key_type key with mapped_type value.
         * @return
         *	 - True: The key doesn't exist, the data is added to the map
            *	 - False: The key already exists, no change is made
            */
        bool insert(key_type&& key, mapped_type&& value) {
            return insert(value_type( utb::forward(key), utb::forward(value)) ).second;
        }




        /**
         * @brief Removes specified elements from the container.
         * @param pos Iterator to the element to remove.
         * @return Return the the last removed iterator.
         */
        iterator erase( const_iterator pos ) {
            return m_ayKeyValue.erase(pos);
        }

        /**
         * @brief Removes specified elements from the container.
         * @param first The start of the range of elements to remove.
         * @param last The end of the range of elements to remove.
         * @return Return the the last removed iterator.
         */
        iterator erase( const_iterator first, const_iterator last ) {
            return m_ayKeyValue.erase(first, last);
        }
        /**
         * @brief Removes the element with the key equivalent to tKey.
         * @param tKey value of the elements to remove.
         * @return Number of elements removed (0 or 1).
         */
        size_type erase( const key_type& tKey ) {
            if(empty()) return 0;

            for(typename TContainer::iterator it = m_ayKeyValue.begin();
                        it != m_ayKeyValue.end(); it++) {
                value_type _pair = *it;

                if(_pair.first == tKey) {
                    utb::destruct<TContainer::iterator>(it);
                    return 1;
                }
            }

            return 0;
        }
        /**
         * @brief Finds an element with key equivalent to key.
         * @param tKey 	The key value of the element to search for.
         * @return The associerte value with this key, when not exist then return the end();
         */
        iterator find(const key_type& tKey) noexcept {
            if(empty()) return nullptr;

            for(typename TContainer::iterator it = m_ayKeyValue.begin();
                        it != m_ayKeyValue.end(); it++) {
                value_type _pair = *it;

                if(_pair.first == tKey) {
                    return &(_pair.second);
                }
            }

            return nullptr;
        }
        /**
         * @brief Finds an element with key equivalent to key.
         * @param tKey 	The key value of the element to search for.
         * @return The associerte value with this key, when not exist then return the
         * setted alternative value.
         */
        const_iterator find(const key_type& tKey) const noexcept {
            if(empty()) return nullptr;

            for(typename TContainer::iterator it = m_ayKeyValue.begin();
                        it != m_ayKeyValue.end(); it++) {
                value_type _pair = *it;

                if(_pair.first == tKey) {
                    return &(_pair.second);
                }
            }

            return nullptr;
        }

        /**
         * @brief Is the map empty.
         * @return If true then is the map empty and if false then not.
         */
        constexpr bool empty() const noexcept {
            return m_ayKeyValue.is_empty();
        }

        /**
         * @brief Get the number of map-members.
         * @return The number of map entries.
         */
        constexpr size_type size() const noexcept {
            return m_ayKeyValue.get_used();
        }

        /**
         * @brief Returns the number of elements with key key.
         * @param key Value of the elements to count.
         * @return Number of elements with key that compares equivalent to key, which is either 1 or 0.
         */
        size_type count( const key_type& key ) const {
            return (find(key) != nullptr) ? 1 : 0;
        }


        /**
         * @brief Exchanges the contents of the container with those of other.
         * @param other Container to exchange the contents with.
         */
        void swap( self_type& other ) {
            swap(m_ayKeyValue, other.m_ayKeyValue);
        }

        /**
         * @brief Read value of map for given key.
         * @param tKey The key.
         * @return The associerte value with this key, when not exist then return the
         * setted alternative value.
         */
        iterator operator[](const key_type& tKey) noexcept {
            return find(tKey);
        }
        /**
         * @brief Read value of map for given key.
         * @param tKey The key.
         * @return The associerte value with this key, when not exist then return the
         * setted alternative value.
         */
        const_iterator operator[](const key_type& tKey) const noexcept {
            return find(tKey);
        }
    private:
        vector<TPairType, TMapSize> m_ayKeyValue;
    };

    /**
     * @brief A standard map container for storing a fixed size pairs.
     * @tparam TKey The type for the key.
     * @tparam TValue The type for the value.
     */
    template <class TKey, class TValue>
    using map = light_map< TKey, TValue , UTB_MAX_MAP_ENTRYS>;

    template <class TKey, class TValue, int TMapSize>
    using mapn = light_map< TKey, TValue , TMapSize>;
}

#endif