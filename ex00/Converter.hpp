#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <iostream>
#include <sstream>
#include <exception>

class Converter
{
private:
    Converter();
    Converter(const Converter &);
    Converter &operator=(const Converter &);
    ~Converter();

public:
    static void convert(const std::string &);

    static char ToChar(const std::string &);
    static int ToInt(const std::string &);
    static float ToFloat(const std::string &);
    static double ToDouble(const std::string &);

    class NonDisplayableException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };

    class ImpossibleException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };
};

#endif