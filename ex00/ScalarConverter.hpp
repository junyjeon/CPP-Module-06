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

    static char toChar(const std::string &);
    static int toInt(const std::string &);
    static float toFloat(const std::string &);
    static double toDouble(const std::string &);
public:
    ~ScalarConverter();
    static void convert(const std::string &);

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
