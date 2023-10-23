#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <exception>
#include <sstream>
#include <limits>

class ScalarConverter
{
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter &);
    ScalarConverter &operator=(const ScalarConverter &);
    ~ScalarConverter();

public:
    static void convert(const std::string &);

    static char ToChar(const std::string &);
    static int ToInt(const std::string &);
    static float ToFloat(const std::string &);
    static double ToDouble(const std::string &);

    class NonDisplayableException : public std::exception
    {
    public:
        const char *what() const throw();
    };

    class ImpossibleException : public std::exception
    {
    public:
        const char *what() const throw();
    };
};

#endif
