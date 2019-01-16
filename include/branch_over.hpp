#pragma once

namespace jpp { // << namespace jpp --------------------------------------------

//using namespace std;

template<typename T, T... Values>
struct value_list {};

template <template F<typename Ft>, typename T, T... Values>
auto branch_over(value_list<T, Values...>)
{
}

} //  << !namespace jpp --------------------------------------------------------
