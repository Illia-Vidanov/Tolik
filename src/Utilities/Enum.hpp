#ifndef TOLIK_UTILITIES_ENUM_HPP
#define TOLIK_UTILITIES_ENUM_HPP

#include <type_traits>
#include <iostream>

#include "Setup.hpp"

namespace Tolik
{
namespace detail
{
  template<typename T> constexpr bool IsEnumOrArithmetic = std::is_enum_v<T> || std::is_arithmetic_v<T>;
}

template<typename T, std::enable_if_t<!detail::IsEnumOrArithmetic<T>, bool> = true> inline constexpr T ToUnderlying(T value)
{
  static_assert(false, "Can't cast to underlying type non enum");
  return value;
}

template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, bool> = true> inline constexpr T ToUnderlying(T value) { return value; }
template<typename T> inline constexpr std::underlying_type_t<T> ToUnderlying(T value) { return static_cast<std::underlying_type_t<T>>(value); }

template<typename T, bool = std::is_enum_v<T>> struct GetUnderlyingTypeIfExists { using type = T; };
template<typename T> struct GetUnderlyingTypeIfExists<T, true> { using type = std::underlying_type_t<T>; };
template<typename T> using HelperGetUnderlyingTypeIfExists = typename GetUnderlyingTypeIfExists<T>::type;

// TODO: SFINAE if defenition of operator between T and U exists

template<typename T, typename U, typename std::enable_if_t<detail::IsEnumOrArithmetic<T> && detail::IsEnumOrArithmetic<U>, bool> = true> inline constexpr T operator|(T value1, U value2) 
{return static_cast<T>(ToUnderlying(value1) | ToUnderlying(value2)); }
template<typename T, typename U, typename std::enable_if_t<detail::IsEnumOrArithmetic<T> && detail::IsEnumOrArithmetic<U>, bool> = true> inline constexpr T operator&(T value1, U value2) 
{ return static_cast<T>(ToUnderlying(value1) & ToUnderlying(value2)); }
template<typename T, typename U, typename std::enable_if_t<detail::IsEnumOrArithmetic<T> && detail::IsEnumOrArithmetic<U>, bool> = true> inline constexpr T operator^(T value1, U value2) 
{ return static_cast<T>(ToUnderlying(value1) ^ ToUnderlying(value2)); }

template<typename T, typename U, typename std::enable_if_t<detail::IsEnumOrArithmetic<T> && detail::IsEnumOrArithmetic<U>, bool> = true> inline constexpr bool operator==(T value1, U value2) 
{ return ToUnderlying(value1) == ToUnderlying(value2); }
template<typename T, typename U, typename std::enable_if_t<detail::IsEnumOrArithmetic<T> && detail::IsEnumOrArithmetic<U>, bool> = true> inline constexpr bool operator!=(T value1, U value2) 
{ return ToUnderlying(value1) != ToUnderlying(value2); }
template<typename T, typename U, typename std::enable_if_t<detail::IsEnumOrArithmetic<T> && detail::IsEnumOrArithmetic<U>, bool> = true> inline constexpr bool operator<(T value1, U value2) 
{ return ToUnderlying(value1) < ToUnderlying(value2); }
template<typename T, typename U, typename std::enable_if_t<detail::IsEnumOrArithmetic<T> && detail::IsEnumOrArithmetic<U>, bool> = true> inline constexpr bool operator>(T value1, U value2) 
{ return ToUnderlying(value1) > ToUnderlying(value2); }

template<typename T, typename U, typename std::enable_if_t<detail::IsEnumOrArithmetic<T> && detail::IsEnumOrArithmetic<U>, bool> = true> inline constexpr T &operator|=(T &value1, U value2)
{ value1 = static_cast<T>(ToUnderlying(value1) | ToUnderlying(value2)); return value1; }
template<typename T, typename U, typename std::enable_if_t<detail::IsEnumOrArithmetic<T> && detail::IsEnumOrArithmetic<U>, bool> = true> inline constexpr T &operator&=(T &value1, U value2)
{ value1 = static_cast<T>(ToUnderlying(value1) & ToUnderlying(value2)); return value1; }
template<typename T, typename U, typename std::enable_if_t<detail::IsEnumOrArithmetic<T> && detail::IsEnumOrArithmetic<U>, bool> = true> inline constexpr T &operator^=(T &value1, U value2)
{ value1 = static_cast<T>(ToUnderlying(value1) ^ ToUnderlying(value2)); return value1; }

template<typename T, typename std::enable_if_t<std::is_enum_v<T>, bool> = true> inline std::ostream& operator<<(std::ostream& os, T self)
{
  return os << static_cast<std::underlying_type_t<T>>(self);
}
} // Tolik

#endif // TOLIK_UTILITIES_ENUM_HPP