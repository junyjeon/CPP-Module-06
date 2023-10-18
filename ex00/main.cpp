#include "ScalarConverter.hpp"
#include <cassert>
#include <limits>

int main()
{
    // char 테스트
    assert(ScalarConverter::convertToChar("a") == 'a');
    assert(ScalarConverter::convertToChar("0") == 0);

    // int 테스트
    assert(ScalarConverter::convertToInt("42") == 42);
    assert(ScalarConverter::convertToInt("-42") == -42);

    // float 테스트
    assert(ScalarConverter::convertToFloat("4.2f") == 4.2f);
    assert(ScalarConverter::convertToFloat("-4.2f") == -4.2f);
    assert(ScalarConverter::convertToFloat("-inff") == -std::numeric_limits<float>::infinity());
    assert(ScalarConverter::convertToFloat("+inff") == std::numeric_limits<float>::infinity());
    assert(std::isnan(ScalarConverter::convertToFloat("nanf")));

    // double 테스트
    assert(ScalarConverter::convertToDouble("4.2") == 4.2);
    assert(ScalarConverter::convertToDouble("-4.2") == -4.2);
    assert(ScalarConverter::convertToDouble("-inf") == -std::numeric_limits<double>::infinity());
    assert(ScalarConverter::convertToDouble("+inf") == std::numeric_limits<double>::infinity());
    assert(std::isnan(ScalarConverter::convertToDouble("nan")));

    return 0;
}
