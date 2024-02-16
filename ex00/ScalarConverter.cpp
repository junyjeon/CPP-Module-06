#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

char ScalarConverter::toChar(const std::string &str)
{
    // 변환이 말이 안되거나, 오버플로우가 발생하는 경우 ImpossibleException 예외를 던진다.
    if (str.length() != 1 || !isascii(str[0]))
        throw ImpossibleException();
    // char로의 변환이 표시할 수 없는 문자인 경우 NonDisplayableException 예외를 던진다.
    int ascii = static_cast<int>(str[0]);
    if (str.length() == 1 && isprint(ascii) && !isdigit(ascii))
        return str[0];
    else if (!isprint(ascii))
        throw NonDisplayableException();
}

int ScalarConverter::toInt(const std::string &str)
{
    // 변환이 말이 안되거나, 오버플로우가 발생하는 경우 ImpossibleException 예외를 던진다.
    // 예시: 0, -42, 42
    int num = std::stoi(str);
    if (!isdigit(str[0]) || num < std::numeric_limits<int>::min() || std::numeric_limits<int>::max() < num)
        throw ImpossibleException();
    return num;
}

float ScalarConverter::toFloat(const std::string &str)
{
    // 변환이 말이 안되거나, 오버플로우가 발생하는 경우 ImpossibleException 예외를 던진다.
    // 0.0f, -4.2f, 4.2f
    // -inff, +inf, nanf
}

double ScalarConverter::toDouble(const std::string &str)
{
    // 변환이 말이 안되거나, 오버플로우가 발생하는 경우 ImpossibleException 예외를 던진다.
    // 0.0, -4.2, 4.2
    // -inf, +inf, nan
}

void ScalarConverter::convert(const std::string &str)
{
    try
    {
        std::cout << "char: " << toChar(str) << std::endl;
    }
    catch (const NonDisplayableException &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (const ImpossibleException &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        std::cout << "int: " << toInt(str) << std::endl;
    }
    catch (const NonDisplayableException &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (const ImpossibleException &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        std::cout << "float: " << toFloat(str) << std::endl;
    }
    catch (const NonDisplayableException &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (const ImpossibleException &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        std::cout << "double: " << toDouble(str) << std::endl;
    }
    catch (const NonDisplayableException &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (const ImpossibleException &e)
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
