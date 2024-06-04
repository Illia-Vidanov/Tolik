#ifndef TOLIK_T_ALGORITHMS_POLINDROMES_HPP
#define TOLIK_T_ALGORITHMS_POLINDROMES_HPP

#include <cassert>
#include <iostream>
#include <utility>

#include "Algorithms/Palindromes.hpp"

using namespace Tolik;

void callback(short i)
{
    std::cout << static_cast<int>(i) << '\n';
}

void TestPalindromes()
{
    Palindromes::GetPalindromes(callback);
}

#endif