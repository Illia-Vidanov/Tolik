#ifndef TOLIK_ALGORITHMS_POLINDROMES_HPP
#define TOLIK_ALGORITHMS_POLINDROMES_HPP

#include <functional>
#include <utility>

#include "gcem.hpp"

#include "Setup.hpp"
#include "Math/Constants.hpp"
#include "Math/Utils.hpp"
#include "Utilities/Type.hpp"

namespace Tolik
{
namespace polindrome
{
template<typename T = uint8_t>
struct DigitRange
{
	constexpr DigitRange() {}
	constexpr DigitRange(T min, T max) : min(min), max(max) {}
	T min = 0;
	T max = 0;
};

// Get all palindromes possible fitting in this data type
template<typename Functor>
constexpr inline void GetAllPalindromes(Functor callback);

// Get polindromse in digit range first - includive, second - exclusive
template<typename T, typename Functor>
constexpr inline void GetPalindromesDigitCount(const DigitRange<T> &digitCountRange, Functor callback);

// Get palindromes whose digits doesn't overflow set ranges { {2, 6}, {3, 7}, {1, 8}, {2, 5} } = max 4664; min 2332
// First number inclusive last exclusive
template<typename Functor>
constexpr inline void GetPalindromesDigitRange(const std::vector<DigitRange> &ranges, Functor callback);

//template<typename T>
//constexpr bool IsPolindrome(T number);

//template<typename T>
//constexpr DefUIntType GetIndexOfPolindrome(T polindrome);

//template<typename T = DefUIntType>
//constexpr T GetPolindromeWithIndex(DefUIntType index);

//template<typename T = DefUIntType>
//constexpr inline T GetPolindromeCountInNDigitNumber(DefUIntType numberDigits) 
//{ return 9 * gcem::pow(10, gcem::ceil(numberDigits / 2.0) - 1); }

//template<typename T>
//constexpr inline DefUIntType GetCountOfDigitsFromPolindromeIndex(T polindromeIndex)
//{ return gcem::ceil(2 * gcem::log10(polindromeIndex / 9.0) + 2); }


namespace detail
{
// Same as GetPalindromes(const std::vector<DigitRange> &ranges) but with valid ranges, that means half the amount of ranges that polindrome needs
template<typename Functor>
constexpr inline void GetPalindromesFromValidRanges(const std::vector<DigitRange> &validRanges, bool odd, Functor callback);

// Create valid ranges from given numbers.
// Both values are inclusive
// In this case min = 0
// Example: 235 = { {0, 3}, {0, 4}, {0, 6} }
template<typename T>
constexpr inline auto GetValidRangesFromNumber(T max) -> std::vector<DigitRange>;

// Create valid ranges from given numbers.
// Both values are inclusive
// Example: (121, 235) { {1, 3}, {2, 4}, {1, 6} }
template<typename T, typename U>
constexpr inline auto GetValidRangesFromNumber(T min, U max) -> std::vector<DigitRange>;

// Convert ranges from full to half size, because polindrome needs only them
// Example: { {1, 3}, {2, 4}, {1, 6}, {2, 3}, {2, 3} } = { {2, 3}, {2, 3}, {1, 6} }
// Same as:
// for(std::size_t i = 0; i < validRangesCount; i++)
//	validRanges[i] = DigitRange(std::max(ranges[i].min, ranges[ranges.size() - i - 1].min), std::min(ranges[i].max, ranges[ranges.size() - i - 1].max));
constexpr inline auto GetValidRanges(const std::vector<DigitRange> &ranges) -> std::vector<DigitRange>;

template<typename ReturnType, typename U, typename Functor>
constexpr void IteratePalindromes(ReturnType &number, U digit, U totalDigits, Functor callback);

// Get palindromes with digits in number ranging.
// digit is used for recursive iteration
// totalDigits in this case also indicates if the number is odd
// Example: { {1, 3}, {2, 4} } totalDigits = 3
// Equals: 121 131 222 232
template<typename ReturnType, typename U, typename Functor>
constexpr void IteratePalindromesRanging(ReturnType &number, U digit, U totalDigits, const std::vector<DigitRange> &validRanges, Functor callback);

// Get needed difference to get next polindrome
// totalDigits is used to add offset
// same as: (10^digit + 1) * (totalDigits - digit) / 2;
template<typename T, typename U>
constexpr inline T GetDiff(U digit, U totalDigits);
} // detail



template<typename Functor>
constexpr void GetAllPalindromes(Functor callback)
{
	using ReturnType = typename FunctorTraits<Functor>::arg<0>::type;
	ReturnType number = ReturnType(0);
	callback(number);

	static_assert(std::numeric_limits<ReturnType>::is_specialized, "Need to know std::numeric_limits<T> in order to get all palindromes from this type");

	for(uint32_t digit = 1; digit < std::numeric_limits<ReturnType>::digits10 + 1; digit++)
	{
		detail::IteratePalindromes(number, digit, digit, callback);
        number = 0;
	}

	detail::IteratePalindromesRanging(number, std::numeric_limits<ReturnType>::digits10 + 1, std::numeric_limits<ReturnType>::digits10 + 1, GetValidRangesFromNumber(std::numeric_limits<ReturnType>::max()), callback);
}

template<typename T, typename Functor>
constexpr void GetPalindromesDigitCount(const DigitRange<T> &digitCountRange, Functor callback)
{
    using ReturnType = typename FunctorTraits<Functor>::arg<0>::type;
    ReturnType number = ReturnType(0);
	if(0 < digitRange.first && 1 < digitRange.second)
		callback(number);

	// With c++20 I could have written std::is_constant_evaluated to avoid logging in constexpr variant
    if(std::numeric_limits<ReturnType>::is_specialized && std::numeric_limits<ReturnType>::digits10 < digitRange.second)
        std::cout << "Number might overflow"; // TODO: Use logger
    
    bool odd = true;
    for(T digit = digitRange.first; digit < digitRange.second; digit = digit + U(1))
    {
        IteratePalindromes(number, digit, digit, odd, callback);
        
        odd = !odd;
        number = 0;
    }
}

template<typename Functor>
constexpr void GetPalindromesDigitRange(const std::vector<DigitRange> &ranges, Functor callback)
{
	using ReturnType = typename FunctorTraits<Functor>::arg<0>::type;
	ReturnType number = ReturnType(0);
	if(ranges.size() == 1)
		callback(number);

	IteratePalindromesRanging(number, ranges.size(), ranges.size(), GetValidRanges(ranges), callback);
}


namespace detail
{
template<typename Functor>
constexpr void GetPalindromesFromValidRanges(const std::vector<DigitRange> &ranges, bool odd, Functor &&callback)
{
	using ReturnType = typename FunctorTraits<Functor>::arg<0>::type;
	ReturnType number = ReturnType(0);
	if(ranges.size() == 1 && odd)
		callback(number);

	std::size_t totalDigits = ranges.size() * 2 - odd;
	IteratePalindromesRanging(number, totalDigits, totalDigits, ranges, callback);
}

template<typename T>
auto GetValidRangesFromNumber(T max) -> std::vector<DigitRange>
{
	const std::size_t n = NumberDigits(max);
	const std::size_t validRangesCount = (n + 1) / 2;
	ranges_t validRanges(validRangesCount);

	for(std::size_t i = 0; i < validRangesCount; i++)
		validRanges[i] = std::pair<uint8_t, uint8_t>(0, std::min(GetDigit(max, i), GetDigit(max, n - i - 1)) + 1);

	return validRanges;
}

template<typename T, typename U>
constexpr T GetDiff(U digit, U totalDigits)
{
	if constexpr(!std::is_arithmetic_v<T>)
        return (IntegralPower(T(10), digit) + T(1)) * (totalDigits - digit) / U(2);
    else
    {
        static const uint32_t maxDigits = std::numeric_limits<T>::digits10 + 1;
        static const T lookup[21] = { 0, 1, 11, 101, maxDigits > 3 ? 1001 : 0,
                                      maxDigits > 4 ? (gcem::pow(10, 4) + 1) : 0,   maxDigits > 5 ? (gcem::pow(10, 5) + 1) : 0,   maxDigits > 6 ? (gcem::pow(10, 6) + 1) : 0,   maxDigits > 7 ? (gcem::pow(10, 7) + 1) : 0,
                                      maxDigits > 8 ? (gcem::pow(10, 8) + 1) : 0,   maxDigits > 9 ? (gcem::pow(10, 9) + 1) : 0,   maxDigits > 10 ? (gcem::pow(10, 10) + 1) : 0, maxDigits > 11 ? (gcem::pow(10, 11) + 1) : 0, 
                                      maxDigits > 12 ? (gcem::pow(10, 12) + 1) : 0, maxDigits > 13 ? (gcem::pow(10, 13) + 1) : 0, maxDigits > 14 ? (gcem::pow(10, 14) + 1) : 0, maxDigits > 15 ? (gcem::pow(10, 15) + 1) : 0,
                                      maxDigits > 16 ? (gcem::pow(10, 16) + 1) : 0, maxDigits > 17 ? (gcem::pow(10, 17) + 1) : 0, maxDigits > 18 ? (gcem::pow(10, 18) + 1) : 0, maxDigits > 19 ? (gcem::pow(10, 19) + 1) : 0 };
        return lookup[digit] * std::pow(T(10), (totalDigits - digit) / U(2));
    }
}
} // detail
} // polindrome



template<typename T, typename U>
Palindromes::ranges_t Palindromes::GetValidRangesFromNumber(T min, U max)
{
	const std::size_t n = NumberDigits(max);
	const std::size_t validRangesCount = (n + 1) / 2;
	ranges_t validRanges(validRangesCount);

	for(std::size_t i = 0; i < validRangesCount; i++)
		validRanges[i] = std::pair<uint8_t, uint8_t>(std::max(GetDigit(min, i), GetDigit(min, n - i - 1)), std::min(GetDigit(max, i), GetDigit(max, n - i - 1)) + 1);

	return validRanges;
}

Palindromes::ranges_t Palindromes::GetValidRanges(const ranges_t &ranges)
{
	const std::size_t validRangesCount = (ranges.size() + 1) / 2;
	ranges_t validRanges(validRangesCount);

	for(std::size_t i = 0; i < validRangesCount; i++)
		validRanges[i] = std::pair<uint8_t, uint8_t>(std::max(ranges[i].first, ranges[ranges.size() - i - 1].first), std::min(ranges[i].second, ranges[ranges.size() - i - 1].second));

	return validRanges;
}

template<typename ReturnType, typename U, typename Functor>
constexpr void Palindromes::IteratePalindromes(ReturnType &number, U digit, U totalDigits, Functor&& callback)
{
    ReturnType diff = GetDiff<ReturnType>(digit, totalDigits);

    for(uint8_t i = 0; i < 9; i++)
    {
        number = number + diff;
        callback(number);
        if(U(2) < digit)
            IteratePalindromes(number, digit - U(2), totalDigits, callback);
    }

    number = number - diff * ReturnType(9);
}

template<typename ReturnType, typename U, typename Functor>
constexpr void Palindromes::IteratePalindromesRanging(ReturnType &number, U digit, U totalDigits, const ranges_t &validRanges, Functor&& callback)
{
	const DigitRange &validRange = validRanges[(totalDigits - digit) / U(2)];

    ReturnType diff = GetDiff<ReturnType>(digit, totalDigits);

	if(digit == totalDigits && (validRange.first + 2) < validRange.second)
	{
		number = number + diff * std::max<uint8_t>(1, validRange.first);
		callback(number);
	}

	for(uint8_t i = validRange.first + 1 + (digit == totalDigits); i < validRange.second; i++)
	{
		if(U(2) < digit)
			IteratePalindromesRanging(number, digit - U(2), totalDigits, validRanges, callback);
		
		number = number + diff;
		callback(number);
	}

	if(U(2) < digit)
		IteratePalindromesRanging(number, digit - U(2), totalDigits, validRanges, callback);

	number = number - diff * (validRange.second - validRange.first - 1 + (digit == totalDigits));
}
}

#endif