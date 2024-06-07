#ifndef TOLIK_MATH_UTILS_HPP
#define TOLIK_MATH_UTILS_HPP

#include <type_traits>
#include <cmath>

#include "gcem.hpp"

#include "Setup.hpp"
#include "Math/Constants.hpp"

namespace Tolik
{
// If type is custom it's better to leave it as is
template<typename T>
using ReturnFloatType = std::conditional_t<std::is_integral_v<T>, DefFloatType, T>;


template<typename T>
constexpr inline ReturnFloatType<T> DegreesToRadians(T degrees)
{ return degrees * (PI / 180); }

template<typename T>
constexpr inline ReturnFloatType<T> RadiansToDegrees(T radians)
{ return radians * (180 / PI); }


template<typename T, typename U>
constexpr inline bool AreSame(T t, U u)
{ return gcem::abs(t - u) < Elipson; }

// Shorthand of writing (std::numeric_limits<T>::digits10 + 1)
template<typename T>
constexpr inline static int kMaxDigits = std::numeric_limits<T>::digits10 + 1;


namespace detail
{
// https://en.wikipedia.org/wiki/Exponentiation_by_squaring

// Exponent here can be only positive, thus unsigned long long
template<typename T, typename U, std::enable_if_t<std::is_convertible_v<U, uint64_t>, bool> = true>
constexpr T IntegralPowerIterate(const T base, const U exp)
{
    // Use cast in case, for example float, or custom defined type, idk
    if(static_cast<uint64_t>(exp) == 1)
        return base;
    
    if(static_cast<uint64_t>(exp) % 2 == 0)
        return IntegralPowerIterate(base * base, static_cast<uint64_t>(exp) / 2);
    //                                      rounds to 0 automatically
    return base * IntegralPowerIterate(base * base, static_cast<uint64_t>(exp) / 2);
}

template<typename T, typename U, std::enable_if_t<!std::is_convertible_v<U, uint64_t>, bool> = true>
constexpr T IntegralPowerIterate(const T base, const U exp)
{
    if(exp < 2)
        return base;

    return base * IntegralPowerIterate(base, exp - 1);
}

template<typename T, typename U, std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<U>, bool> = true>
constexpr inline T IntegralPowerImpl(const T base, const U exp) { return std::pow(base, exp); }

template<typename T, typename U, std::enable_if_t<!std::is_arithmetic_v<T>, bool> = true>
constexpr inline T IntegralPowerImpl(const T base, const U exp)
{
    // Special type might be signed
    if(exp < 0)
        return T(1) / IntegralPowerImpl(base, -exp);
    if(exp == 0)
        return 1;
    
    return IntegralPowerIterate(base, exp);
}
}

// Function to power non-arithemtic type to exponent of non-arithmetic type.
// If it's normal types std::pow is used.
// In other case, power algorithm is used, that uses only operators '=' '*' '/' '== '<'
template<typename T, typename U>
constexpr inline T IntegralPower(const T base, const U exp)
{
    return detail::IntegralPowerImpl(base, exp);
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


namespace detail
{
template<typename T>
constexpr inline T kFastPower10PositiveLookup[] =
{
    1, 10, 100, kMaxDigits<T> > 3 ? 1000 : 0,
    kMaxDigits<T> > 4 ?  gcem::pow<T, T>(10, 4) : 0,  kMaxDigits<T> > 5 ?  gcem::pow<T, T>(10, 5) : 0,  kMaxDigits<T> > 6 ?  gcem::pow<T, T>(10, 6) : 0,  kMaxDigits<T> > 7 ?  gcem::pow<T, T>(10, 7) : 0,
    kMaxDigits<T> > 8 ?  gcem::pow<T, T>(10, 8) : 0,  kMaxDigits<T> > 9 ?  gcem::pow<T, T>(10, 9) : 0,  kMaxDigits<T> > 10 ? gcem::pow<T, T>(10, 10) : 0, kMaxDigits<T> > 11 ? gcem::pow<T, T>(10, 11) : 0, 
    kMaxDigits<T> > 12 ? gcem::pow<T, T>(10, 12) : 0, kMaxDigits<T> > 13 ? gcem::pow<T, T>(10, 13) : 0, kMaxDigits<T> > 14 ? gcem::pow<T, T>(10, 14) : 0, kMaxDigits<T> > 15 ? gcem::pow<T, T>(10, 15) : 0,
    kMaxDigits<T> > 16 ? gcem::pow<T, T>(10, 16) : 0, kMaxDigits<T> > 17 ? gcem::pow<T, T>(10, 17) : 0, kMaxDigits<T> > 18 ? gcem::pow<T, T>(10, 18) : 0, kMaxDigits<T> > 19 ? gcem::pow<T, T>(10, 19) : 0
};

constexpr inline DefFloatType kFastPower10NegativeLookup[] =
{
    static_cast<DefFloatType>(1), static_cast<DefFloatType>(1) / 10, static_cast<DefFloatType>(1) / 100, static_cast<DefFloatType>(1) / 1000,
    static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 4),  static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 5),  static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 6),  static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 7),
    static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 8),  static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 9),  static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 10), static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 11), 
    static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 12), static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 13), static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 14), static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 15),
    static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 16), static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 17), static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 18), static_cast<DefFloatType>(1) / gcem::pow<uint64_t, uint64_t>(10, 19)
};
}

// Function to get power of 10 with lookup
template<typename T = DefIntType, typename U>
#if __cplusplus >= 202002L
constexpr
#endif
inline T FastPower10(U exp)
{
    if constexpr(!std::is_arithmetic_v<T> || !std::is_arithmetic_v<U>)
        return IntegralPower(T(10), exp);
    else if(std::is_signed_v<U>)
    {
        if(exp < U(0))
            return detail::kFastPower10NegativeLookup[-exp];
        else if(U(19) < exp)
            return IntegralPower(T(10), exp);
        else
            return detail::kFastPower10PositiveLookup<T>[exp];
    }

    if(U(19) < exp)
        return IntegralPower(T(10), exp);
    else
        return detail::kFastPower10PositiveLookup<T>[exp];
}


// Get substring from digit
// Same as (digit / 10^first) % 10^last
// first digit inclusive, last exclusive
// Example: first = 1, last = 5, digit = 6543210 => 4321;
//          first = 4, last = 8, digit = -6543210 => 654;
//          first = -10, last = 5, digit = -6543210 => 43210;
template<typename T, typename U>
constexpr inline T GetDigitSubstring(T digit, U first, U last)
{
    // I am not  sure about this line.
    // It might be better to throw an error, but it means we need to check for it anyway, so I would prefer doing it this way
    // If we'll ignore the fact of negative numbers we'll get SIGFPE that is hard to debug
    if(first < 0)
        first = 0;
    if(last < 0)
        return 0;
    if(first >= last)
        return 0;

    return (digit / IntegralPower(10, first)) % IntegralPower(10, last - first);
}


namespace detail
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
// 0 = 0 digits
template<typename U = DefUIntType, typename T>
constexpr inline U NumberDigits(T t)
{
    return t == 0 ? 0 : static_cast<U>(detail::NumberDigitsImpl(t));
}
}


#endif