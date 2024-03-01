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
    return str[0];
}

int ScalarConverter::toInt(const std::string &str)
{
    // 변환이 말이 안되거나, 오버플로우가 발생하는 경우 ImpossibleException 예외를 던진다.
    // 예시: 0, -42, 42
    std::istringstream iss(str); // 표준 입력(std::cin)이나 파일로부터 input을 받는 것처럼 처리. (꼼수 느낌)
    // iss는 공백, +, -, 도 올바르게 처리한다.
    int num;
    iss >> num; // 문자열 str에서 정수로 데이터를 읽어서 num에 저장
    // int num = std::stoi(str); // c++11 이후로는 이렇게 사용해도 된다.
    if (iss.fail() || !iss.eof()) // iss으로 변환 과정에서 int max, min을 넘어가는 경우에도 fail이 발생. eof는 끝까지 읽었을 때 true
        throw ImpossibleException();
    return num;
}

float ScalarConverter::toFloat(const std::string &str)
{
    // 변환이 말이 안되거나, 오버플로우가 발생하는 경우 ImpossibleException 예외를 던진다.
    // 0.0f, -4.2f, 4.2f
    // -inff, +inf, nanf
    // std::numeric_limits<float>::min() -> 1.17549e-38
    // std::numeric_limits<float>::max() -> 3.40282e+38
    std::istringstream iss(str);
    float num;
    iss >> num;
    if (str == "nanf" || str == "+inff" || str == "-inff")
        return std::stof(str);
    if (iss.fail() || !iss.eof())
        throw ImpossibleException();
    if (num < -std::numeric_limits<float>::max() || std::numeric_limits<float>::max() < num)
        throw ImpossibleException();
    return num;
}

double ScalarConverter::toDouble(const std::string &str)
{
    // 변환이 말이 안되거나, 오버플로우가 발생하는 경우 ImpossibleException 예외를 던진다.
    // 0.0, -4.2, 4.2
    // -inf, +inf, nan
    // std::numeric_limits<double>::min() -> 2.22507e-308
    // std::numeric_limits<double>::max() -> 1.79769e+308
    std::istringstream iss(str);
    double num;
    iss >> num;
    if (str == "nan" || str == "+inf" || str == "-inf")
        return std::stod(str);
    if (iss.fail() || !iss.eof())
        throw ImpossibleException();
    // std::numeric_limits<T>::min() -> T가 표현할 수 있는 가장 작은 값. 정수 타입의 경우 가장 작은 음수 값.
    // 예: int의 경우 -2,147,483,648 같은 값
    // 부동 소수점 타입(float, double)의 경우, 0보다 크면서 가장 작은 양수 값.
    // 예: double의 경우 약 2.22507e-308

    // std::numeric_limits<T>::max() -> T가 표현할 수 있는 가장 큰 양수 값.
    // 예: int의 경우 2,147,483,647 같은 값
    // double의 경우 약 1.79769e+308
    if (num < -std::numeric_limits<double>::max() || std::numeric_limits<double>::max() < num)
        throw ImpossibleException();
    return num;
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
