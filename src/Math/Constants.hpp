#ifndef TOLIK_MATH_CONSTANTS_HPP
#define TOLIK_MATH_CONSTANTS_HPP

#include "Setup.hpp"

namespace Tolik
{
using DefFloatType = float;
using DefIntType = int;
using DefUIntType = uint32_t;

constexpr inline DefFloatType kPI = static_cast<DefFloatType>(3.141592);
constexpr inline DefFloatType kHalfPI = kPI / static_cast<DefFloatType>(2);
constexpr inline DefFloatType kElipson = static_cast<DefFloatType>(0.000001);
} // Tolik

#endif // TOLIK_MATH_CONSTANTS_HPP