#pragma once

#include <algorithm>
#include <boost/config/suffix.hpp>

namespace sak {

	template<typename Function, std::size_t... N>
	BOOST_FORCEINLINE void unroll_impl( std::index_sequence<N...> const&, Function&& F) {
	    bool dummy[] =  { ((std::forward<Function>(F)(std::integral_constant<std::size_t, N>{})),true)... };
	    (void)(dummy);
	}

	/**
	 * @brief      Inline lambda arbitrary unroller. Unroll factor is passed as a parameter template, the unroll factor of each instance is then passed as an argument wrapped in an integral constant.
	 *
	 * @param[in]  <unnamed>  Unroll index
	 *
	 * @tparam     N          Unroll factor
	 * @tparam     Function   Lambda
	 */
	template<int N, typename Function>
	BOOST_FORCEINLINE void unroll(Function&& F) {
	  unroll_impl(std::make_index_sequence<N>{}, std::forward<Function>(F));
	}

}