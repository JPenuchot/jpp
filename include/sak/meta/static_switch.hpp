#pragma once

#include <utility>
#include <boost/config/suffix.hpp>

#include "static_if.hpp"

namespace sak
{
  //template< typename T
  //        , T val
  //        , typename Function
  //        >
  //BOOST_FORCEINLINE std::pair< std::integral_constant<T, val>
  //                           , Function&&
  //                           >
  //make_case(Function&& f)
  //{
  //  return std::pair< std::integral_constant<T, val>
  //                  , Function&&
  //                  >
  //                  (0, f);
  //}

  template< typename T
          , typename Function
          , typename ...IC
          , T val
          , std::pair<IC, Function&&> ...Ps
          >
  BOOST_FORCEINLINE void static_switch_impl()
  {
    bool dummy[] =
    {
      (( static_if<std::decay_t<decltype(Ps.first)>::value == val>
        ::exec(std::forward(Ps.second)) ), false)...
    };
  }

  template< typename T
          , typename Function
          , T val
          >
  BOOST_FORCEINLINE void static_switch( static_switch_case<T, Function> Ps... )
  {
    static_switch_impl<T, Function, val, Ps>();
  }
}