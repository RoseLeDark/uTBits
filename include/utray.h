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