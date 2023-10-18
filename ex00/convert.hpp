#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <cctype>
#include <cmath>

class ScalarConverter
{
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter &);
    ScalarConverter &operator=(const ScalarConverter &);
    ~ScalarConverter();

public:
    static char convertToChar(const std::string &);
    static int convertToInt(const std::string &);
    static float convertToFloat(const std::string &);
    static double convertToDouble(const std::string &);
};

#endif
