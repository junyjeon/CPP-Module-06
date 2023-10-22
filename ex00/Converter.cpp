#include "Converter.hpp"

void Converter::convert(const std::string &str)
{
    try
    {
        std::cout << "char: ";
        char c = ToChar(str);
        std::cout << "'" << c << "'" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        std::cout << "int: ";
        int i = ToInt(str);
        std::cout << i << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        std::cout << "float: ";
        float f = ToFloat(str);
        std::cout << f << "f" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        std::cout << "double: ";
        double d = ToDouble(str);
        std::cout << d << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

char Converter::ToChar(const std::string &str)
{
    int i = ToInt(str);
    if (!isprint(i))
        throw NonDisplayableException();
    return static_cast<char>(i);
}

int Converter::ToInt(const std::string &str)
{
    std::istringstream iss(str);
    int i;
    iss >> i;
    if (iss.fail() || !iss.eof())
        throw ImpossibleException();
    return i;
}

float Converter::ToFloat(const std::string &str)
{
    std::istringstream iss(str);
    float f;
    iss >> f;
    if (iss.fail())
        throw ImpossibleException();
    return f;
}

double Converter::ToDouble(const std::string &str)
{
    std::istringstream iss(str);
    double d;
    iss >> d;
    if (iss.fail())
        throw ImpossibleException();
    return d;
}

const char *Converter::NonDisplayableException::what() const throw()
{
    return "Non displayable";
}

const char *Converter::ImpossibleException::what() const throw()
{
    return "impossible";
}