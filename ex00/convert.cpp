#include "convert.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
    *this = other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
    return *this;
}

ScalarConverter::~ScalarConverter() {}

char ScalarConverter::convertToChar(const std::string &literal)
{
    if (literal.length() == 1 && !std::isdigit(literal[0]))
        return literal[0];
    int num = std::stoi(literal);
    if (!isprint(num))
        throw std::invalid_argument("impossible");
    return static_cast<char>(num);
}

int ScalarConverter::convertToInt(const std::string &literal)
{
    try
    {
        return std::stoi(literal);
    }
    catch (std::invalid_argument &e)
    {
        throw std::invalid_argument("impossible");
    }
    catch (std::out_of_range &e)
    {
        throw std::invalid_argument("impossible");
    }
}

float ScalarConverter::convertToFloat(const std::string &literal)
{
    if (literal == "-inff" || literal == "+inff" || literal == "nanf")
        return std::stof(literal);
    return std::stof(literal);
}

double ScalarConverter::convertToDouble(const std::string &literal)
{
    if (literal == "-inf" || literal == "+inf" || literal == "nan")
        return std::stod(literal);
    return std::stod(literal);
}
