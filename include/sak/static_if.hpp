#pragma once

#include <utility>
#include <boost/config/suffix.hpp>

namespace sak {
	template<bool B>
	class static_if{
		public:
			template<typename Function>
			BOOST_FORCEINLINE static void exec(Function&& F){}
	};

	template<>
	class static_if<true> {
		public:
			template<typename Function>
			BOOST_FORCEINLINE static void exec(Function&& F){ F(); }
	};
};
