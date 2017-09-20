#pragma once

#include <utility>
#include <boost/config/suffix.hpp>

namespace sak
{
	/**
	 * @brief      Class for static if.
	 *
	 * @tparam     B     Whatever
	 */
	template<bool B>
	class static_if
	{
		public:
			template<typename Function>
			BOOST_FORCEINLINE static void exec(Function&& F){}
	};

	/**
	 * @brief      Class for static if.
	 */	
	template<>
	class static_if<true>
	{
		public:
			template<typename Function>
			BOOST_FORCEINLINE static void exec(Function&& F)
      {
        std::forward<Function>(F)();
      }
	};
};
