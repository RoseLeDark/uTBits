
/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
#ifndef __UTB_HISTORY_H__
#define __UTB_HISTORY_H__

#include "utconfig.h"
#include "uttypetraits.h"
#include "utalgorithm.h"

namespace utb {
    template<typename T, utb::size_t N, bool IsIntegral = utb::is_integral<T>::value>
    class history;

    template<typename T, utb::size_t N>
    class history<T, N, true> {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference_type = T&;
        using const_reference_type = const T&;
        using self_type = history<T, N, true>;
        using size_type = utb::size_t;

        constexpr history() : 
            m_vMin(utb::numeric_limits<T>::max()), 
            m_vMax(utb::numeric_limits<T>::min())   { 

            utb::fill(m_data, m_data + N, 0);
        }

        constexpr void push(const_reference_type v) {
                // Array nach rechts schieben
            for (size_type i = N - 1; i > 0; --i)
                m_data[i] = m_data[i - 1];

            // Neuer Wert an Position 0
            m_data[0] = v;

            // Min/Max aktualisieren
            if ( v < m_vMin) m_vMin = v;
            if ( v > m_vMax) m_vMax = v;
        }

        // Neuester Wert
        constexpr const_reference_type current() const {
            return m_data[0];
        }

        // Wert davor
        constexpr const_reference_type latest() const {
            return m_data[1];
        }

        // Ältester Wert
        constexpr const_reference_type oldest() const {
            return m_data[N - 1];
        }

        constexpr value_type min() const { return m_vMin; }
        constexpr value_type max() const { return m_vMax; }

        constexpr value_type average() const {
            value_type sum = 0;

            for (size_type i = 0; i < N; ++i) {
                sum += m_data[i];
            }
            return sum / N;
        }

        constexpr const_reference_type operator[](size_type i) const {
            return m_data[i];
        }

    private:
        value_type m_data[N];
        value_type m_vMin;
        value_type m_vMax;
    };

    template<typename T, utb::size_t N>
    class history<T, N, false> {
    public:
         using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference_type = T&;
        using const_reference_type = const T&;
        using self_type = history<T, N, false>;
        using size_type = utb::size_t;

        constexpr history()  { }

        constexpr void push(const_reference_type v) {
                // Array nach rechts schieben
            for (size_type i = N - 1; i > 0; --i)
                m_data[i] = m_data[i - 1];

            // Neuer Wert an Position 0
            m_data[0] = v;
        }

        constexpr size_type size() const { return m_count; }

        // Neuester Wert
        constexpr const_reference_type current() const {
            return m_data[0];
        }

        // Wert davor
        constexpr const_reference_type lastest() const {
            return m_data[1];
        }

        // Ältester Wert
        constexpr const_reference_type oldest() const {
            return m_data[m_count - 1];
        }

        constexpr const_reference_type operator[](size_type i) const {
            return m_data[i];
        }

    private:
        value_type m_data[N];
    };
}

#endif