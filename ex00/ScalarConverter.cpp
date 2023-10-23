#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

char ScalarConverter::ToChar(const std::string &str)
{
    if (str == "-inf" || str == "+inf" || str == "nan")
        throw ImpossibleException();
    if (isprint(str[0]))

        if (str.length() == 1 && !isdigit(str[0]))
            return str[0];
    return static_cast<char>(std::atoi(str.c_str()));
}

int ScalarConverter::ToInt(const std::string &str)
{
    if (str == "-inf" || str == "+inf" || str == "nan")
        throw ImpossibleException();
    if (str.length() == 1 && !isdigit(str[0]))
        return static_cast<int>(str[0]);
}

float ScalarConverter::ToFloat(const std::string &str)
{
    if (str == "-inf" || str == "+inf" || str == "nan")
        std::cout << "float: " << str << "f" << std::endl;
    if (str.length() == 1 && !isdigit(str[0]))
        return static_cast<float>(str[0]);
}

double ScalarConverter::ToDouble(const std::string &str)
{
    if (str == "-inf" || str == "+inf" || str == "nan")
        std::cout << "double: " << str << std::endl;
    if (str.length() == 1 && !isdigit(str[0]))
        return static_cast<float>(str[0]);
}

void ScalarConverter::convert(const std::string &str)
{
    int flag = false;
    void *endptr = NULL;

    if (str.length() == 1 && !isdigit(str[0]))
    {
        std::cout << "char: " << str[0] << std::endl;
        std::cout << "int: " << static_cast<int>(str[0]) << std::endl;
        std::cout << "float: " << static_cast<float>(str[0]) << ".0f" << std::endl;
        std::cout << "double: " << static_cast<double>(str[0]) << ".0" << std::endl;
        return;
    }

    if (str == "-inf" || str == "+inf" || str == "nan")
    {
        std::cout << "char: " << ScalarConverter::ToChar(str) << std::endl;
        std::cout << "int: " << ScalarConverter::ToInt(str) << std::endl;
        std::cout << "float: " << str << ".0f" << std::endl;
        std::cout << "double: " << str << ".0" << std::endl;
        return;
    }

    try
    {
        std::cout << "char: " << ScalarConverter::ToChar(str) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        std::cout << "int: " << ScalarConverter::ToChar(str) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        std::cout << "float: " << ScalarConverter::ToChar(str) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        std::cout << "double: " << ScalarConverter::ToChar(str) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

const char *ScalarConverter::NonDisplayableException::what() const throw()
{
    return "Non displayable";
}

const char *ScalarConverter::ImpossibleException::what() const throw()
{
    return "impossible";
}
