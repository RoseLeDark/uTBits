/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
#ifndef __UT_PAIR_H__
#define __UT_PAIR_H__

#include "utebo.h"
#include "utalgorithm.h"

namespace utb {

    template <typename T, typename U, typename = void>
	class pair  {
        using self_type = pair<T, U>;

		using first_type  		 		= typename type_traits<T>::value_type;
		using pointer_first 	 		= typename type_traits<T>::pointer;
		using reference_first 	 		= typename type_traits<T>::reference;
		using const_reference_first  	= typename type_traits<T>::const_reference;

		using second_type   		 	= typename type_traits<U>::value_type;
		using pointer_second 	 		= typename type_traits<U>::pointer;
		using reference_second  	 	= typename type_traits<U>::reference;
		using const_reference_second   	= typename type_traits<U>::const_reference;

		using storage_first 			= ebo_storage<T, 0>;
		using storage_second			= ebo_storage<U, 1>;


		constexpr pair() = default;
		explicit  pair(const_reference_first f) noexcept
			: m_first(f) { }

		explicit pair(const_reference_second s) noexcept
			: m_second(s) { }

		constexpr pair(const_reference_first f, const_reference_second s) noexcept
			: m_first(f), m_second(s) { }

		constexpr pair(const self_type& other) noexcept
				: pair(other.first(), other.second() ) { }


				  reference_first 		 first()  noexcept 		 { return m_first.get(); }
		constexpr const_reference_first  first()  const noexcept { return m_first.get(); }

				  reference_second 		 second() noexcept 		 { return m_second.get(); }
		constexpr const_reference_second second() const noexcept { return m_second.get(); }

		void swap(self_type& o) {
			utb::swap(m_first,  o.m_first);
			utb::swap(m_second, o.m_second);
		}
	private:
		storage_first  	m_first;
		storage_second  m_second;
    };

	template <typename T, typename U, typename = void>
	pair<T, U> make_pair(const T& a, const U& b) {
		return pair<T, U>(a, b);
	}

	template <typename ForwardIterator, typename TComp>
	inline constexpr pair<ForwardIterator,ForwardIterator>  
	equal_range (ForwardIterator first, ForwardIterator last, const TComp& value) {

		pair<ForwardIterator, ForwardIterator> rv;

		rv.second = rv.first = utb::lower_bound (first, last, value);
		while (rv.second != last && !(value < *(rv.second)))
			++ rv.second;
		return rv;
	}

	template <typename T, typename U>
	struct is_pod< pair<T, U> > {
		enum {
			value = ( (is_pod<T>::value || is_fundamental<T>::value) &&
					  (is_pod<U>::value || is_fundamental<U>::value) )
		};
	};
}
#endif