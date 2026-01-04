#ifndef __UT_VOID_H__
#define __UT_VOID_H__

#include "utconfig.h"

namespace utb {
    /**
	 * @brief A dummy class with value-type semantics, mostly useful as a template argument.
	 */
	class basic_void_type {
	public:
		/**
		 * @brief Construct the void type.
		 */
		basic_void_type();

		/**
		 * @brief Creates the Void from another Void.
		 * @note Do nothing.
		 */
		basic_void_type(const basic_void_type& other) noexcept;
		/**
		 * @brief Deconstrut the void type.
		 */
		 ~basic_void_type();

		/**
		 * @brief Assigns another void.
		 */
		basic_void_type& operator = (const basic_void_type& v) noexcept;
		/**
		 * @brief Will return always true due to Voids having no members.
		 */
		bool operator ==(const basic_void_type& v) const noexcept;
		/**
		 * @brief Will return always false due to Voids having no members.
		 */
		bool operator !=(const basic_void_type& v) const noexcept;
	};

	template <class ...ts>
	struct make_void { using type = basic_void_type; };

    template <class ...ts>
    using void_t = typename make_void<ts ...>::type;

}
#endif