#pragma once

#include <algorithm>
#include <boost/config/suffix.hpp>

namespace sak {

	template<typename Function, std::size_t... N>
	BOOST_FORCEINLINE void unroll_impl( std::index_sequence<N...> const&, Function&& F) {
	    bool dummy[] =  { ((std::forward<Function>(F)(std::integral_constant<std::size_t, N>{})),true)... };
	    (void)(dummy);
	}

	template<int N, typename Function>
	BOOST_FORCEINLINE void unroll(Function&& F) {
	  unroll_impl(std::make_index_sequence<N>{}, std::forward<Function>(F));
	}

}