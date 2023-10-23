#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

char ScalarConverter::ToChar(const std::string &str)
{
    if (str == "-inf" || str == "inf" || str == "+inf" || str == "-nan" || str == "nan" || str == "+nan")
        throw ImpossibleException();
    if (str.length() != 1)
    {
        char *endptr;
        double d = strtod(str.c_str(), &endptr);
        if (str.c_str() == endptr)
            throw ImpossibleException();
        if (d < std::numeric_limits<char>::min() || std::numeric_limits<char>::max() < d)
            throw NonDisplayableException();
        return static_cast<char>(d);
    }
    char c = str[0];
    if (!isprint(static_cast<unsigned char>(c)))
        throw NonDisplayableException();
    return c;
}

int ScalarConverter::ToInt(const std::string &str)
{
    if (str == "-inf" || str == "inf" || str == "+inf" || str == "-nan" || str == "nan" || str == "+nan")
        throw ImpossibleException();
    if (str.length() != 1)
    {
        char *endptr;
        double d = strtod(str.c_str(), &endptr);
        if (str.c_str() == endptr)
            throw ImpossibleException();
        if (d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
            throw NonDisplayableException();
        return static_cast<int>(d);
    }
    int i = static_cast<int>(str[0]);
    if (!isprint(static_cast<int>(i)))
        throw NonDisplayableException();
    return i;
}

float ScalarConverter::ToFloat(const std::string &str)
{
    if (str == "-inf" || str == "inf" || str == "+inf" || str == "-nan" || str == "nan" || str == "+nan")
        throw NonDisplayableException();
    if (str == "-inf" || str == "+inf" || str == "nan") //- +
        std::cout << "float: " << str << "f" << std::endl;
}

double ScalarConverter::ToDouble(const std::string &str)
{
    if (str == "-inf" || str == "+inf" || str == "nan")
        std::cout << "double: " << str << std::endl;
}

void ScalarConverter::convert(const std::string &str)
{
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

    // non displayable characters shouldn’t be used as inputs. and output infor message.

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
