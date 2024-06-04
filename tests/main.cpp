#include <iostream>
#include <cassert>

#include "T_Algorithms/Palindromes.hpp"
#include "T_Algorithms/String.hpp"
#include "T_Math/Utils.hpp"

int main(int argv, char **args)
{
    TestString();
    TestUtils();
    TestPalindromes();

    std::cout << "\nTest passed!";
    std::cin.ignore();
    return 0;
}