#include "Converter.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./convert <literal>" << std::endl;
        return 1;
    }

    std::string literal = argv[1];
    Converter::convert(literal);

    return 0;
}