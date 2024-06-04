#ifndef TOLIK_MATH_UTILS_HPP
#define TOLIK_MATH_UTILS_HPP

#include <type_traits>
#include <cmath>

#include "Setup.hpp"

#include "gcem.hpp"

#include "Math/Constants.hpp"

namespace Tolik
{
// If type is custom it's better to leave it as is
template<typename T>
using ReturnFloatType = std::conditional_t<!std::is_floating_point_v<T> && !std::is_arithmetic_v<T>, DefFloatType, T>;


template<typename T>
constexpr inline ReturnFloatType<T> DegreesToRadians(T degrees)
{ return degrees * (PI / 180); }

template<typename T>
constexpr inline ReturnFloatType<T> RadiansToDegrees(T radians)
{ return radians * (180 / PI); }


template<typename T, typename U>
constexpr inline bool AreSame(T t, U u)
{ return gcem::abs(t - u) < Elipson; }


namespace Detail
{
// https://en.wikipedia.org/wiki/Exponentiation_by_squaring

template<typename T, typename U>
constexpr ReturnFloatType<T> IntegralPowerIterate(T base, U exp)
{
    if(exp == 1)
        return base;
    
    if(exp % 2 == 0)
        return IntegralPowerIterate(base * base, exp / 2);
    //                                      rounds to 0 automatically
    return base * IntegralPowerIterate(base * base, exp / 2);
}


template<typename T, typename U, std::enable_if_t<std::is_arithmetic_v<T>, bool> = true>
constexpr inline ReturnFloatType<T> IntegralPowerImpl(T base, U exp) { return std::pow(base, exp); }

// It's probably worth to take into account that special type might be signed
template<typename T, typename U, std::enable_if_t<!std::is_arithmetic_v<T>, bool> = true>
constexpr inline T IntegralPowerImpl(T base, U exp)
{
    if(exp < 0)
        return T(1) / IntegralPowerImpl(base, -exp);
    if(exp == 0)
        return 1;
    
    return IntegralPowerIterate(base, exp);
}
}

// Function to power unknown type.
// If it's normalt type std::pow is used.
// In other case power algorithm is used, that uses only operators '=' '*' '/' '=='
template<typename T, typename U>
constexpr inline ReturnFloatType<T> IntegralPower(T base, U exp)
{
    return Detail::IntegralPowerImpl(base, exp);
}


// Gets digit at index from number
// If index is invalid 0 returned
// Indexing starts at 0 and equals the same as (x / 10^index) % 10
template<typename T = uint8_t, typename U, typename V>
constexpr inline T GetDigit(U u, V index)
{
    // We might get "signal SIGFPE, Arithmetic exception." if we skip this line
    if(index < 0)
        return 0;
    return U(u / IntegralPower(U(10), index)) % U(10);
}


namespace Detail
{
template <typename T>
constexpr inline DefUIntType NumberDigitsImpl(T t)
{
    if(t < T(0))
        return NumberDigitsImpl(-t);
    DefUIntType digits = 0;
    while(T(0) < t)
    {
        digits++;
        t = t / 10;
    }
    return digits;
}

template<>
inline DefUIntType NumberDigitsImpl<char>(char t)
{
    if(t < 0)
        return NumberDigitsImpl<char>(-t);
    
    static const char x[128] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
    return x[static_cast<unsigned char>(t)];
}
template<>
inline DefUIntType NumberDigitsImpl<unsigned char>(unsigned char t)
{
    static const unsigned char x[256] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
    return x[t];
}

template<>
constexpr inline DefUIntType NumberDigitsImpl<short>(short t)
{
    if(t < 0)
        return NumberDigitsImpl<short>(-t);
    
    if(t >= 100)
    {
        if(t >= 1000)
        {
            if(t > 10000)
                return 5;
            return 4;
        }
        return 3;
    }
    else
    {
        if(t >= 10)
            return 2;
        return 1;
    }
}
template<>
constexpr inline DefUIntType NumberDigitsImpl<unsigned short>(unsigned short t)
{
    if(t >= 100)
    {
        if(t >= 1000)
        {
            if(t > 10000)
                return 5;
            return 4;
        }
        return 3;
    }
    else
    {
        if(t >= 10)
            return 2;
        return 1;
    }
}

template<>
constexpr inline DefUIntType NumberDigitsImpl<int>(int t)
{
    if(t < 0) return NumberDigitsImpl<int>(-t);

    if(t >= 100000)
    {
        if(t >= 10000000)
        {
            if(t >= 100000000)
            {
                if(t > 1000000000)
                    return 10;
                return 9;
            }
            return 8;
        }
        if(t >= 1000000)
            return 7;
        return 6;
    }
    if(t >= 100)
    {
        if(t >= 1000)
        {
            if(t >= 10000)
                return 5;
            return 4;
        }
        return 3;
    }
    if(t >= 10)
        return 2;
    return 1;
}

template<>
constexpr inline DefUIntType NumberDigitsImpl<unsigned int>(unsigned int t)
{
    if(t >= 100000)
    {
        if(t >= 10000000)
        {
            if(t >= 100000000)
            {
                if(t > 1000000000)
                    return 10;
                return 9;
            }
            return 8;
        }
        if(t >= 1000000)
            return 7;
        return 6;
    }
    if(t >= 100)
    {
        if(t >= 1000)
        {
            if(t >= 10000)
                return 5;
            return 4;
        }
        return 3;
    }
    if(t >= 10)
        return 2;
    return 1;
}

template<>
constexpr inline DefUIntType NumberDigitsImpl<long long>(long long t)
{
    if(t < 0)
        return NumberDigitsImpl<long long>(-t);

    if(t >= 10000000000)
    {
        if(t >= 100000000000000)
        {
            if(t >= 10000000000000000)
            {
                if(t >= 100000000000000000)
                {
                    if(t >= 1000000000000000000)
                        return 19;
                    return 18;
                }
                return 17;
            }
            if(t >= 1000000000000000)
                return 16;
            return 15;
        } 
        if(t >= 1000000000000)
        {
            if(t >= 10000000000000)
                return 14;
            return 13;
        }
        if(t >= 100000000000)
            return 12;
        return 11;
    }
    if(t >= 100000)
    {
        if(t >= 10000000)
        {
            if(t >= 100000000)
            {
                if(t >= 1000000000)
                    return 10;
                return 9;
            }
            return 8;
        }
        if (t >= 1000000)
            return 7;
        return 6;
    }
    if(t >= 100)
    {
        if(t >= 1000)
        {
            if(t >= 10000)
                return 5;
            return 4;
        }
        return 3;
    }
    if(t >= 10)
        return 2;
    return 1;
}
template<>
constexpr inline DefUIntType NumberDigitsImpl<unsigned long long>(unsigned long long t)
{
    if(t >= 10000000000)
    {
        if(t >= 1000000000000000)
        {
            if(t >= 100000000000000000)
            {
                if(t >= 1000000000000000000)
                {
                    if(t >= 10000000000000000000u)
                        return 20;
                    return 19;
                }
                return 18;
            }
            if(t >= 10000000000000000)
                return 17;
            return 16;
        } 
        if(t >= 1000000000000)
        {
            if(t >= 10000000000000)
            {
                if(t > 100000000000000)
                    return 15;
                return 14;
            }
            return 13;
        }
        if(t >= 100000000000)
            return 12;
        return 11;
    }
    if(t >= 100000)
    {
        if(t >= 10000000)
        {
            if(t >= 100000000)
            {
                if(t >= 1000000000)
                    return 10;
                return 9;
            }
            return 8;
        }
        if (t >= 1000000)
            return 7;
        return 6;
    }
    if(t >= 100)
    {
        if(t >= 1000)
        {
            if(t >= 10000)
                return 5;
            return 4;
        }
        return 3;
    }
    if(t >= 10)
        return 2;
    return 1;
}
}

// Get number of whole digits in any type
template<typename U = DefUIntType, typename T>
constexpr inline U NumberDigits(T t)
{
    return t == 0 ? 0 : static_cast<U>(Detail::NumberDigitsImpl(t));
}
}


#endif