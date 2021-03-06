#if !defined FROZEN_META_STRING_TO_STRING_HPP_INCLUDED
#define      FROZEN_META_STRING_TO_STRING_HPP_INCLUDED

#include "./basic_string.hpp"

namespace frozen {
namespace meta {

namespace detail {

    template< class CharT,
            class Int,
            Int Value,
            class Acc = basic_string<CharT>,
            bool = (Value < 10) >
    struct to_string_from_integer;

    template< class CharT,
            class Int,
            Int Value,
            CharT... Chars >
    struct to_string_from_integer< CharT, Int, Value, basic_string<CharT, Chars...>, false >
            : to_string_from_integer< CharT, Int, Value / 10, basic_string< CharT, Value % 10 + '0', Chars... > >{};

    template< class CharT,
            class Int,
            Int Value,
            CharT... Chars >
    struct to_string_from_integer< CharT, Int, Value, basic_string<CharT, Chars...>, true >{
        typedef basic_string< CharT, Value + '0', Chars... > type;
    };

} // namespace detail

template<class CharT, class T, T Value, class = void>
struct to_basic_string;

template<class CharT, class Int, Int Value>
struct to_basic_string<CharT, Int, Value, typename std::enable_if<std::is_integral<Int>::value>::type>
     : detail::to_string_from_integer<CharT, Int, Value>
{};

template<class Int, Int Value>
using to_string = typename to_basic_string<char, Int, Value>::type;

template<class Int, Int Value>
using to_wstring = typename to_basic_string<wchar_t, Int, Value>::type;

template<class Int, Int Value>
using to_u16string = typename to_basic_string<char16_t, Int, Value>::type;

template<class Int, Int Value>
using to_u32string = typename to_basic_string<char32_t, Int, Value>::type;

} // namespace meta
} // namespace frozen

#define FROZEN_TO_STRING(INT) \
    typename frozen::meta::to_string<typename std::decay<decltype(INT)>::type, INT>

#define FROZEN_TO_WSTRING(INT) \
    typename frozen::meta::to_wstring<typename std::decay<decltype(INT)>::type, INT>

#define FROZEN_TO_U16STRING(INT) \
    typename frozen::meta::to_u16string<typename std::decay<decltype(INT)>::type, INT>

#define FROZEN_TO_U32STRING(INT) \
    typename frozen::meta::to_u32string<typename std::decay<decltype(INT)>::type, INT>

#endif    // FROZEN_META_STRING_TO_STRING_HPP_INCLUDED
