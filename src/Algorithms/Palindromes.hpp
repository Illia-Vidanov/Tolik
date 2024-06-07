#ifndef TOLIK_ALGORITHMS_PALINDROMES_HPP
#define TOLIK_ALGORITHMS_PALINDROMES_HPP

#include <functional>
#include <utility>
#include <iostream>

#include "gcem.hpp"

#include "Setup.hpp"
#include "Math/Constants.hpp"
#include "Math/Utils.hpp"
#include "Utilities/Type.hpp"

namespace Tolik
{
namespace palindrome
{
template<typename T>
struct DigitCountRange
{
public:
	constexpr DigitCountRange() {}
	constexpr DigitCountRange(T newMin, T newMax) : min(newMin), max(newMax) {}
	T min = 0;
	T max = 0;
};

struct DigitRange
{
public:
	constexpr DigitRange() {}
	constexpr DigitRange(uint8_t newMin, uint8_t newMax) : min(newMin), max(newMax) {}
	uint8_t min = 0;
	uint8_t max = 0;
};

// Get all palindromes possible fitting in this data type
template<typename Functor>
constexpr inline void GetAllPalindromes(Functor callback);

// Get polindromse in digit range first - includive, second - exclusive
template<typename T, typename Functor>
constexpr inline void GetPalindromesDigitCountRange(const DigitCountRange<T> &digitCountRange, Functor callback);

// Get palindromes whose digits doesn't overflow set ranges { {2, 6}, {3, 7}, {1, 8}, {2, 5} } = max 4664; min 2332
// First number inclusive last exclusive
template<typename Functor>
constexpr inline void GetPalindromesDigitRange(const std::vector<DigitRange> &ranges, Functor callback);

//template<typename T>
//constexpr bool IsPalindrome(T number);

//template<typename T>
//constexpr DefUIntType GetIndexOfPalindrome(T palindrome);

//template<typename T = DefUIntType>
//constexpr T GetPalindromeWithIndex(DefUIntType index);

//template<typename T = DefUIntType>
//constexpr inline T GetPalindromeCountInNDigitNumber(DefUIntType numberDigits) 
//{ return 9 * gcem::pow(10, gcem::ceil(numberDigits / 2.0) - 1); }

//template<typename T>
//constexpr inline DefUIntType GetCountOfDigitsFromPalindromeIndex(T palindromeIndex)
//{ return gcem::ceil(2 * gcem::log10(palindromeIndex / 9.0) + 2); }


namespace detail
{
// Same as GetPalindromes(const std::vector<DigitRange> &ranges) but with valid ranges, that means half the amount of ranges that palindrome needs
template<typename Functor>
constexpr inline void GetPalindromesFromValidRanges(const std::vector<DigitRange> &validRanges, bool odd, Functor callback);

// Create valid ranges from given numbers.
// Both values are inclusive
// In this case min = 0
// Example: 235 = { {0, 3}, {0, 4}, {0, 6} }
template<typename T>
#if __cplusplus >= 202002L
constexpr
#endif
inline auto GetValidRangesFromNumber(T max) -> std::vector<DigitRange>;

// Create valid ranges from given numbers.
// Both values are inclusive
// Example: (121, 235) { {1, 3}, {2, 4}, {1, 6} }
template<typename T, typename U>
#if __cplusplus >= 202002L
constexpr
#endif
inline auto GetValidRangesFromNumber(T min, U max) -> std::vector<DigitRange>;

// Convert ranges from full to half size, because palindrome needs only them
// Example: { {1, 3}, {2, 4}, {1, 6}, {2, 3}, {2, 3} } = { {2, 3}, {2, 3}, {1, 6} }
// Same as:
// for(std::size_t i = 0; i < validRangesCount; i++)
//	validRanges[i] = DigitRange(std::max(ranges[i].min, ranges[ranges.size() - i - 1].min), std::min(ranges[i].max, ranges[ranges.size() - i - 1].max));
// Can be constexpr only from c++20 where constexpr memory allocation is allowed
#if __cplusplus >= 202002L
constexpr
#endif
inline auto GetValidRanges(const std::vector<DigitRange> &ranges) -> std::vector<DigitRange>;

template<typename ReturnType, typename U, typename Functor>
constexpr void IteratePalindromes(ReturnType &number, U digit, U totalDigits, Functor callback);

// Get palindromes with digits in number ranging.
// digit is used for recursive iteration
// totalDigits in this case also indicates if the number is odd
// Example: { {1, 3}, {2, 4} } totalDigits = 3
// Equals: 121 131 222 232
template<typename ReturnType, typename U, typename Functor>
constexpr void IteratePalindromesRanging(ReturnType &number, U digit, U totalDigits, const std::vector<DigitRange> &validRanges, Functor callback);


template<typename T>
constexpr static T kGetDiffLookup[21] =
{
	0, 1, 11, 101, kMaxDigits<T> > 3 ? 1001 : 0,
    kMaxDigits<T> > 4 ?  (gcem::pow(10, 4) + 1) : 0,  kMaxDigits<T> > 5 ?  (gcem::pow(10, 5) + 1) : 0,  kMaxDigits<T> > 6 ?  (gcem::pow(10, 6) + 1) : 0,  kMaxDigits<T> > 7 ?  (gcem::pow(10, 7) + 1) : 0,
    kMaxDigits<T> > 8 ?  (gcem::pow(10, 8) + 1) : 0,  kMaxDigits<T> > 9 ?  (gcem::pow(10, 9) + 1) : 0,  kMaxDigits<T> > 10 ? (gcem::pow(10, 10) + 1) : 0, kMaxDigits<T> > 11 ? (gcem::pow(10, 11) + 1) : 0, 
    kMaxDigits<T> > 12 ? (gcem::pow(10, 12) + 1) : 0, kMaxDigits<T> > 13 ? (gcem::pow(10, 13) + 1) : 0, kMaxDigits<T> > 14 ? (gcem::pow(10, 14) + 1) : 0, kMaxDigits<T> > 15 ? (gcem::pow(10, 15) + 1) : 0,
    kMaxDigits<T> > 16 ? (gcem::pow(10, 16) + 1) : 0, kMaxDigits<T> > 17 ? (gcem::pow(10, 17) + 1) : 0, kMaxDigits<T> > 18 ? (gcem::pow(10, 18) + 1) : 0, kMaxDigits<T> > 19 ? (gcem::pow(10, 19) + 1) : 0
};

// Get needed difference to get next palindrome
// totalDigits is used to add offset
// same as: (10^digit + 1) * (totalDigits - digit) / 2;
template<typename T, typename U>
// static variables in constepxr functions are allowed only from c++20
#if __cplusplus >= 202002L
constexpr
#endif
inline T GetDiff(U digit, U totalDigits);
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

	detail::IteratePalindromesRanging(number, std::numeric_limits<ReturnType>::digits10 + 1, std::numeric_limits<ReturnType>::digits10 + 1, detail::GetValidRangesFromNumber(std::numeric_limits<ReturnType>::max()), callback);
}

template<typename T, typename Functor>
constexpr void GetPalindromesDigitCountRange(const DigitCountRange<T> &digitCountRange, Functor callback)
{
    using ReturnType = typename FunctorTraits<Functor>::arg<0>::type;
    ReturnType number = ReturnType(0);
	if(digitCountRange.min < 2 && 1 < digitCountRange.max)
		callback(number);

	// With c++20 I could have written std::is_constant_evaluated to avoid calling non constexpr function in constexpr variant
    if(std::numeric_limits<ReturnType>::is_specialized && std::numeric_limits<ReturnType>::digits10 < digitCountRange.max)
        std::cout << "Number might overflow"; // TODO: Use logger
    
    for(T digit = digitCountRange.min; digit < digitCountRange.max; digit = digit + T(1))
    {
        detail::IteratePalindromes(number, digit, digit, callback);
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

	detail::IteratePalindromesRanging(number, ranges.size(), ranges.size(), detail::GetValidRanges(ranges), callback);
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
#if __cplusplus >= 202002L
constexpr
#endif
auto GetValidRangesFromNumber(T max) -> std::vector<DigitRange>
{
	const std::size_t n = NumberDigits(max);
	const std::size_t validRangesCount = (n + 1) / 2;
	std::vector<DigitRange> validRanges(validRangesCount);

	for(std::size_t i = 0; i < validRangesCount; i++)
		validRanges[i] = DigitRange(0, std::min(GetDigit(max, i), GetDigit(max, n - i - 1)) + 1);

	return validRanges;
}

template<typename T, typename U>
#if __cplusplus >= 202002L
constexpr
#endif
auto GetValidRangesFromNumber(T min, U max) -> std::vector<DigitRange>
{
	const std::size_t n = NumberDigits(max);
	const std::size_t validRangesCount = (n + 1) / 2;
	std::vector<DigitRange> validRanges(validRangesCount);

	for(std::size_t i = 0; i < validRangesCount; i++)
		validRanges[i] = DigitRange(std::max(GetDigit(min, i), GetDigit(min, n - i - 1)), std::min(GetDigit(max, i), GetDigit(max, n - i - 1)) + 1);

	return validRanges;
}

#if __cplusplus >= 202002L
constexpr
#endif
auto GetValidRanges(const std::vector<DigitRange> &ranges) -> std::vector<DigitRange>
{
	const std::size_t validRangesCount = (ranges.size() + 1) / 2;
	std::vector<DigitRange> validRanges(validRangesCount);

	for(std::size_t i = 0; i < validRangesCount; i++)
		validRanges[i] = DigitRange(std::max(ranges[i].min, ranges[ranges.size() - i - 1].min), std::min(ranges[i].max, ranges[ranges.size() - i - 1].max));

	return validRanges;
}


template<typename ReturnType, typename U, typename Functor>
constexpr void IteratePalindromes(ReturnType &number, U digit, U totalDigits, Functor callback)
{
    ReturnType diff = GetDiff<ReturnType>(digit, totalDigits);

	if(digit == totalDigits)
		number = number + diff;

    for(uint8_t i = 0 + (digit == totalDigits); i < 9; i++)
    {
        if(U(2) < digit)
		{
			IteratePalindromes(number, digit - U(2), totalDigits, callback);
			number = number + diff;
			continue;
		}
		
		callback(number);
		number = number + diff;
    }

	if(U(2) < digit)
		IteratePalindromes(number, digit - U(2), totalDigits, callback);
	else
		callback(number);

    number = number - diff * ReturnType(9);
}

template<typename ReturnType, typename U, typename Functor>
constexpr void IteratePalindromesRanging(ReturnType &number, U digit, U totalDigits, const std::vector<DigitRange> &validRanges, Functor callback)
{
	const DigitRange &validRange = validRanges[(totalDigits - digit) / U(2)];

    ReturnType diff = GetDiff<ReturnType>(digit, totalDigits);

	if(digit == totalDigits)
		number = number + diff * std::max<uint8_t>(1, validRange.min);
	else
		number = number + diff * validRange.min;

	for(uint8_t i = validRange.min + 1 + (digit == totalDigits); i < validRange.max; i++)
	{
		if(U(2) < digit)
		{
			IteratePalindromesRanging(number, digit - U(2), totalDigits, validRanges, callback);
			number = number + diff;
			continue;
		}
		
		callback(number);
		number = number + diff;
	}

	if(U(2) < digit)
		IteratePalindromesRanging(number, digit - U(2), totalDigits, validRanges, callback);
	else
		callback(number);

	number = number - diff * (validRange.max - 1);
}


template<typename T, typename U>
#if __cplusplus >= 202002L
constexpr
#endif
T GetDiff(U digit, U totalDigits)
{
	if constexpr(!std::is_arithmetic_v<T>)
        return (FastPower10(digit) + T(1)) * (totalDigits - digit) / U(2);

    return kGetDiffLookup<T>[digit] * FastPower10((totalDigits - digit) / U(2));
}
} // detail
} // palindrome
} // Tolik

#endif // TOLIK_ALGORITHMS_PALINDROMES_HPP