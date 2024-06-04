#ifndef TOLIK_T_MATH_UTILS_HPP
#define TOLIK_T_MATH_UTILS_HPP

#include "Math/Utils.hpp"

#include <cassert>

using namespace Tolik;

void TestUtils()
{
    assert(NumberDigits(static_cast<char>(9)) == 1);
    assert(NumberDigits(static_cast<char>(99)) == 2);
    assert(NumberDigits(static_cast<char>(10)) == 2);
    assert(NumberDigits(static_cast<char>(100)) == 3);
    assert(NumberDigits(static_cast<unsigned char>(9)) == 1);
    assert(NumberDigits(static_cast<unsigned char>(10)) == 2);
    assert(NumberDigits(static_cast<unsigned char>(99)) == 2);
    assert(NumberDigits(static_cast<unsigned char>(100)) == 3);

    assert(NumberDigits(static_cast<short>(9)) == 1);
    assert(NumberDigits(static_cast<short>(99)) == 2);
    assert(NumberDigits(static_cast<short>(999)) == 3);
    assert(NumberDigits(static_cast<short>(9999)) == 4);
    assert(NumberDigits(static_cast<short>(std::numeric_limits<short>::max())) == 5);

    assert(NumberDigits(static_cast<unsigned short>(9)) == 1);
    assert(NumberDigits(static_cast<unsigned short>(99)) == 2);
    assert(NumberDigits(static_cast<unsigned short>(999)) == 3);
    assert(NumberDigits(static_cast<unsigned short>(9999)) == 4);
    assert(NumberDigits(static_cast<unsigned short>(std::numeric_limits<unsigned short>::max())) == 5);
    
    assert(NumberDigits(static_cast<int>(9)) == 1);
    assert(NumberDigits(static_cast<int>(99)) == 2);
    assert(NumberDigits(static_cast<int>(999)) == 3);
    assert(NumberDigits(static_cast<int>(9999)) == 4);
    assert(NumberDigits(static_cast<int>(99999)) == 5);
    assert(NumberDigits(static_cast<int>(999999)) == 6);
    assert(NumberDigits(static_cast<int>(9999999)) == 7);
    assert(NumberDigits(static_cast<int>(99999999)) == 8);
    assert(NumberDigits(static_cast<int>(999999999)) == 9);
    assert(NumberDigits(static_cast<int>(std::numeric_limits<int>::max())) == 10);

    assert(NumberDigits(static_cast<unsigned int>(9)) == 1);
    assert(NumberDigits(static_cast<unsigned int>(99)) == 2);
    assert(NumberDigits(static_cast<unsigned int>(999)) == 3);
    assert(NumberDigits(static_cast<unsigned int>(9999)) == 4);
    assert(NumberDigits(static_cast<unsigned int>(99999)) == 5);
    assert(NumberDigits(static_cast<unsigned int>(999999)) == 6);
    assert(NumberDigits(static_cast<unsigned int>(9999999)) == 7);
    assert(NumberDigits(static_cast<unsigned int>(99999999)) == 8);
    assert(NumberDigits(static_cast<unsigned int>(999999999)) == 9);
    assert(NumberDigits(static_cast<unsigned int>(std::numeric_limits<unsigned int>::max())) == 10);
    
    assert(NumberDigits(static_cast<long long>(9)) == 1);
    assert(NumberDigits(static_cast<long long>(99)) == 2);
    assert(NumberDigits(static_cast<long long>(999)) == 3);
    assert(NumberDigits(static_cast<long long>(9999)) == 4);
    assert(NumberDigits(static_cast<long long>(99999)) == 5);
    assert(NumberDigits(static_cast<long long>(999999)) == 6);
    assert(NumberDigits(static_cast<long long>(9999999)) == 7);
    assert(NumberDigits(static_cast<long long>(99999999)) == 8);
    assert(NumberDigits(static_cast<long long>(999999999)) == 9);
    assert(NumberDigits(static_cast<long long>(9999999999)) == 10);
    assert(NumberDigits(static_cast<long long>(99999999999)) == 11);
    assert(NumberDigits(static_cast<long long>(999999999999)) == 12);
    assert(NumberDigits(static_cast<long long>(9999999999999)) == 13);
    assert(NumberDigits(static_cast<long long>(99999999999999)) == 14);
    assert(NumberDigits(static_cast<long long>(999999999999999)) == 15);
    assert(NumberDigits(static_cast<long long>(9999999999999999)) == 16);
    assert(NumberDigits(static_cast<long long>(99999999999999999)) == 17);
    assert(NumberDigits(static_cast<long long>(999999999999999999)) == 18);
    assert(NumberDigits(static_cast<long long>(std::numeric_limits<long long>::max())) == 19);

    assert(NumberDigits(static_cast<unsigned long long>(9)) == 1);
    assert(NumberDigits(static_cast<unsigned long long>(99)) == 2);
    assert(NumberDigits(static_cast<unsigned long long>(999)) == 3);
    assert(NumberDigits(static_cast<unsigned long long>(9999)) == 4);
    assert(NumberDigits(static_cast<unsigned long long>(99999)) == 5);
    assert(NumberDigits(static_cast<unsigned long long>(999999)) == 6);
    assert(NumberDigits(static_cast<unsigned long long>(9999999)) == 7);
    assert(NumberDigits(static_cast<unsigned long long>(99999999)) == 8);
    assert(NumberDigits(static_cast<unsigned long long>(999999999)) == 9);
    assert(NumberDigits(static_cast<unsigned long long>(9999999999)) == 10);
    assert(NumberDigits(static_cast<unsigned long long>(99999999999)) == 11);
    assert(NumberDigits(static_cast<unsigned long long>(999999999999)) == 12);
    assert(NumberDigits(static_cast<unsigned long long>(9999999999999)) == 13);
    assert(NumberDigits(static_cast<unsigned long long>(99999999999999)) == 14);
    assert(NumberDigits(static_cast<unsigned long long>(999999999999999)) == 15);
    assert(NumberDigits(static_cast<unsigned long long>(9999999999999999)) == 16);
    assert(NumberDigits(static_cast<unsigned long long>(99999999999999999)) == 17);
    assert(NumberDigits(static_cast<unsigned long long>(999999999999999999)) == 18);
    assert(NumberDigits(static_cast<unsigned long long>(9999999999999999999u)) == 19);
    assert(NumberDigits(static_cast<unsigned long long>(std::numeric_limits<unsigned long long>::max())) == 20);

    assert(IntegralPower(2, 4) == 16);
    assert(IntegralPower(3, 5) == 243);
    assert(AreSame(IntegralPower<float>(2, -4), 0.0625));
    assert(AreSame(IntegralPower<float>(3, -5), 0.004115));

    assert(GetDigit(9876543210, 0) == 0);
    assert(GetDigit(987654321, 0) == 1);
    assert(GetDigit(9876543210, 9) == 9);
    assert(GetDigit(9876543210, 10) == 0);
    assert(GetDigit(9876543210, 100) == 0);
    assert(GetDigit(9876543210, -1) == 0);
    assert(GetDigit(9876543210, -100) == 0);
}

#endif