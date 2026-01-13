/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
#ifndef __UTRAY_H__
#define __UTRAY_H__

#include "utconfig.h"
#include "utvector3.h"

namespace utb {
    namespace math {
         template<typename T>
	    class ray
        {
        public:
            using self_type = ray<T>;
            using value_type = T;
            using pointer = T* ;

            ray (vector3<value_type> position, vector3<value_type> direction) : m_position(position), m_directon(direction) {}
	        ray(const ray<value_type>& other) : m_position(other.m_position), m_directon(other.m_directon) {}
            ray(ray<value_type>&& other) noexcept : m_position(utb::move(other.m_position)), m_directon(utb::move(other.m_directon)) {}

    

            void reset(const vector3<value_type>& position, const vector3<value_type>& direction) {
                m_position = position;
                m_directon = direction;
            }
            void clear() {
                m_position = vector3<value_type>(0);
                m_directon = vector3<value_type>(0);
            }
            void zero() {
                m_position = vector3<value_type>(0);
                m_directon = vector3<value_type>(0);
            }
            void set(const vector3<value_type>& position, const vector3<value_type>& direction) {
                m_position = position;
                m_directon = direction;
            }
            void set_position(const vector3<value_type>& position) {
                m_position = position;
            }
            void set_direction(const vector3<value_type>& direction) {
                m_directon = direction;
            }

            vector3<value_type> get_position() const {
                return m_position;
            }
            vector3<value_type> get_direction() const {
                return m_directon;
            }

            ray clone() const {
                return ray<value_type>(m_position, m_directon);
            }

            ray swap(ray<value_type>& other) noexcept {
                if (this != &other) {
                    utb::swap(m_position, other.m_position);
                    utb::swap(m_directon, other.m_directon);
                }
                return *this;
            }

            ray & operator = (const ray<value_type>& other) {
                if (this != &other) {
                    m_position = other.m_position;
                    m_directon = other.m_directon;
                }
                return *this;
            }
            ray & operator = (ray<value_type>&& other) noexcept {
                if (this != &other) {
                    m_position = utb::move(other.m_position);
                    m_directon = utb::move(other.m_directon);
                }
                return *this;
            }

            bool operator == (const ray<value_type>& other) const {
                return (m_position == other.m_position) && (m_directon == other.m_directon);
            }
            bool operator != (const ray<value_type>& other) const {
                return !(*this == other);
            }
        private:
            vector3<T> m_position;
            vector3<T> m_directon;
        };
    }
}

#endif // __UTRAY_H__