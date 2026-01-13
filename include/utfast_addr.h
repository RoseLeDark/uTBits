#ifndef __UTFAST_TYPE_H__
#define __UTFAST_TYPE_H__

#include "uttypes.h"
#include "utfunctional.h"
/// @brief 
namespace utb {
    namespace detail {
        /**
         * @brief Leichtgewichtige Wrapper-Klasse für ein einzelnes Bit.
         *
         * Verwaltet ein einzelnes Bit (als bit-field) und bietet
         * grundlegende Operatoren zum Zuweisen, Vergleichen und Umschalten (flip).
         */
        class base_fastbit {
        public:
            unsigned char bit : 1;

            base_fastbit()  { bit = 0; }
            explicit base_fastbit(unsigned char b) { bit = b ? 1 : 0; }
            base_fastbit(const base_fastbit& b) { bit = b.bit; }
            
            base_fastbit& operator = (const base_fastbit& other) {
                bit = other.bit; 
            }
            base_fastbit& operator = (const bool& v) {
                bit = v ? 1 : 0; 
            }

            bool operator == (const base_fastbit& other) {
                return bit == other.bit;
            }
            bool operator != (const base_fastbit& other) {
                return bit != other.bit;
            }

            operator bool() { return bit == 1; }
            /**
             * Flip the bit from 0 to 1 or from 0 to 1
             */
            void flip() { bit = (bit ==1) ? 0 : 1; }
        };
    }

    
    /**
     * @brief View für ein Register oder einen Wert als Ganzes und als Bit-Feld.
     *
     * Ermöglicht den Zugriff auf denselben Speicherbereich als Wert (TVALUE)
     * oder als Array einzelner Bits (TBiteType bits[TBits]). Nützlich für
     * bitweise Manipulationen und direkte Adress-Views.
     *
     * @tparam TVALUE  Basistyp des dargestellten Werts (z.B. uint32_t).
     * @tparam TBits   Anzahl der Bits im View (Standard: sizeof(TVALUE)*8).
     * @tparam TBiteType Typ für einzelne Bits (Standard: utb::detail::base_fastbit).
     */
    template <typename TVALUE, utb::size_t TBits, typename TBiteType = detail::base_fastbit>
    class fast_register_view {
        union {
            TVALUE value;
            TBiteType bits[TBits];
        };
    public:
        using self_type = fast_register_view<TVALUE, TBits, TBiteType>;
        using value_type = TVALUE;
        using size_type = TVALUE;
        using bit_type = TBiteType;
        using pointer = TVALUE*;
        using const_pointer = const TVALUE*;
        using reference = TVALUE&;
        using const_reference = const TVALUE&;
        using iterator = bit_type*;
        using const_iterator = const bit_type*;
        using bit = bool;

        fast_register_view() = default;
        explicit fast_register_view(value_type vvalue) : value(vvalue) { }
        fast_register_view(const self_type& other) : value(other.value) { }

        size_type size() { return TBits;  }

        size_type num_zeros() {
            unsigned int zeros = 0;
            for(int i = 0; i < TBits; i++)
                if(bits[i] == 0) zeros++;
            return zeros;
        }
        size_type num_ones() {
            return TBits - num_zeros();
        }

        void set(size_type pos, bit_type p) {
            if(p < TBits)  bits[pos].bit = p;
        }

        self_type& flip() {
            for(size_type i = 0; i < TBits; i++)
                bits[i].flip();
            return *this;
        }

        self_type& flip(size_type p) {
            if(p < TBits) bits[p].flip();

            return *this;
        }

        bit& get(const size_type p) {  return bits[p];  }
        bit& operator [] (const size_type p) {  return bits[p];  }

        value_type& get_value() { return value; }
        uint32_t  operator () () { return value; }

        self_type& operator = (value_type& v) {  value = v; return *this; }
        self_type& operator = (self_type& other) { value = other.value; return *this; }

        bool operator == (self_type& other) { return value == other.value; }
        bool operator != (self_type& other) { return value != other.value;  }

        bool operator <= (self_type& other) { return value <= other.value;  }
        bool operator >= (self_type& other) { return value >= other.value;  }
        bool operator < (self_type& other)  {  return value < other.value;  }
        bool operator > (self_type& other)  {  return value > other.value;  }

        self_type& operator += (self_type& other) { value += other.value; return *this;  }
        self_type& operator -= (self_type& other) { value -= other.value; return *this; }
        self_type& operator *= (self_type& other) { value *= other.value; return *this; }
        self_type& operator &= (self_type& other) { value &= other.value; return *this; }
        self_type& operator |= (self_type& other) { value |= other.value; return *this;  }
        self_type& operator ^= (self_type& other) { value ^= other.value; return *this; }
        self_type& operator <<= (self_type& other) { value <<= other.value; return *this; }
        self_type& operator >>= (self_type& other) { value >>= other.value; return *this; }
        self_type& operator /= (self_type& other) { value /= other.value; return *this; }

        self_type& operator += (value_type& v) { value += v; return *this; }
        self_type& operator -= (value_type& v) { value -= v; return *this; }
        self_type& operator *= (value_type& v) { value *= v; return *this; }
        self_type& operator /= (value_type& v) { value /= v; return *this; }
        self_type& operator <<= (value_type& v) { value <<= v; return *this; }
        self_type& operator >>= (value_type& v) { value >>= v; return *this; }

        self_type& operator - ( const self_type& rhs) { return self_type(*this) -= rhs; }
        self_type& operator + ( const self_type& rhs) { return self_type(*this) += rhs; }
        self_type& operator * ( const self_type& rhs) {  return self_type(*this) *= rhs; }
        self_type& operator / ( const self_type& rhs) { return self_type(*this) /= rhs; }
        self_type& operator << ( const self_type& rhs) { return self_type(*this) <<= rhs; }
        self_type& operator >> ( const self_type& rhs) { return self_type(*this) >>= rhs; }

        self_type& operator ++ () { value++; return *this;  }
        self_type& operator -- () { value--; return *this; }
        self_type& operator ~ () { value = ~value; return *this; }

        self_type& operator | ( const self_type& rhs) {
            self_type result = self_type(*this);
            result.value |= rhs.value;
            return result;
        }
        self_type& operator ^ ( const self_type& rhs) {
            self_type result = self_type(*this);
            result.value ^= rhs.value;
            return result;
        }
        self_type& operator & ( const self_type& rhs) {
            self_type result = self_type(*this);
            result.value &= rhs.value;
            return result;
        }
        self_type& operator ~ () {
            self_type result = self_type(*this);
            result.value = ~result.value;
            return result;
        }
    };
    /**
     * @brief Alias für eine schnelle Adress-/Register-View.
     *
     * Standardmäßig entspricht TBits der Wortbreite von TVALUE in Bits.
     */
    template <typename TVALUE, utb::size_t TBits = sizeof(TVALUE) * 8, typename TBiteType = detail::base_fastbit>
    using fast_addr_t = fast_register_view<TVALUE, TBits, TBiteType>;

    /**
     * @brief Erzeugt eine View auf eine gegebene Speicheradresse.
     *
     * Vorsicht: Die Funktion gibt einen rohen Zeiger zurück und übernimmt
     * keine Speicher- oder Alignment-Prüfungen. Der Aufrufer ist verantwortlich
     * für die Gültigkeit der Adresse.
     *
     * @param address Numerische Adresse, auf die die View zeigen soll.
     * @return Zeiger auf fast_addr_t an der angegebenen Adresse.
     */
    template <typename TVALUE, utb::size_t TBits = sizeof(TVALUE) * 8, typename TBiteType = detail::base_fastbit>
    fast_addr_t<TVALUE, TBits, TBiteType>*  create_fast_view(uintptr_t address) {
        return reinterpret_cast<fast_addr_t<TVALUE, TBits, TBiteType>*>(address);
    }

    /// @name Typ-Aliasse für häufige Wortbreiten
    ///@{
    using byte              = fast_addr_t<unsigned char>;   // 8 Bit
    using word              = fast_addr_t<uint16_t>;        // 16 Bit
    using dword             = fast_addr_t<uint32_t>;        // 32 Bit
    using qword             = fast_addr_t<uint64_t>;        // 64 Bit
    ///@}

    using fsize_t           = fast_addr_t<utb::size_t>;
    using ffloat_t          = fast_addr_t<float>;
    using fdouble_t         = fast_addr_t<double>;

    using fint8_t           = fast_addr_t<int8_t>;
    using fint16_t          = fast_addr_t<int16_t>;
    using fint32_t          = fast_addr_t<int32_t>;
    using fint64_t          = fast_addr_t<int64_t>;

    using fuint8_t          = fast_addr_t<uint8_t>;
    using fuint16_t         = fast_addr_t<uint16_t>;
    using fuint32_t         = fast_addr_t<uint32_t>;
    using fuint64_t         = fast_addr_t<uint64_t>;

}

#endif