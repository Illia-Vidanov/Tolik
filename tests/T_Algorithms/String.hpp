#ifndef TOLIK_T_ALGORITHMS_STRING_HPP
#define TOLIK_T_ALGORITHMS_STRING_HPP

#include <cassert>

#include "Algorithms/String.hpp"

void TestString()
{
    assert(Tolik::SplitString("12  34 56", " ")[0] == "12");
    assert(Tolik::SplitString("12  34 56", " ")[1] == "34");
    assert(Tolik::SplitString("  12 34 56", " ")[0] == "12");

    assert(Tolik::SplitString("12 34  56", " ")[2] == "56");
    assert(Tolik::SplitString("12 34 56  ", " ")[2] == "56");

    assert(Tolik::SplitString("12 34 56", " ").size() == 3);
    assert(Tolik::SplitString("12 34 56  ", " ").size() == 3);
    assert(Tolik::SplitString("  12 34 56  ", " ").size() == 3);
}

#endif