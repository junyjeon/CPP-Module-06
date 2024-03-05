#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

char ScalarConverter::toChar(const std::string &str)
{
    // 변환이 말이 안되거나, 오버플로우가 발생하는 경우 ImpossibleException
    if (str.compare("nan") == 0)
		throw ImpossibleException();
	long double num;
    std::istringstream iss(str);
    iss >> num;
    if (iss.fail() || !iss.eof() || num < std::numeric_limits<char>::min() || std::numeric_limits<char>::max() < num)
        throw ImpossibleException();
    // 표시할 수 없는 문자인 경우 NonDisplayableException
    else if (!isprint(static_cast<int>(num)))
        throw NonDisplayableException();
    return static_cast<char>(num);
}

int ScalarConverter::toInt(const std::string &str)
{
    // 변환이 말이 안되거나, 오버플로우가 발생하는 경우 ImpossibleException
    // 예시: 0, -42, 42
    if (str.compare("nan") == 0)
		throw ImpossibleException();
	long double num;
    std::istringstream iss(str); // 표준 입력(std::cin)이나 파일로부터 input을 받는 것처럼 처리. (꼼수 느낌)
    iss >> num; // 문자열 str에서 정수로 데이터를 읽어서 num에 저장
    // iss는 공백, +, -, 도 올바르게 처리한다.
    // int num = std::stoi(str); // c++11
    if (iss.fail() || !iss.eof() || num < std::numeric_limits<int>::min() || std::numeric_limits<int>::max() < num) // iss으로 변환 과정에서 int max, min을 넘어가는 경우에도 fail이 발생. eof는 끝까지 읽었을 때 true
        throw ImpossibleException();
    return static_cast<int>(num);
}

float ScalarConverter::toFloat(const std::string &str)
{
    // 변환이 말이 안되거나, 오버플로우가 발생하는 경우 ImpossibleException
    // 0.0f, -4.2f, 4.2f
    // -inff, +inff, nanf
    if (str == "nan") {
        return std::numeric_limits<float>::quiet_NaN();
    } else if (str == "+inf" || str == "inf" || str == "+inff" || str == "inff") {
        return std::numeric_limits<float>::infinity();
    } else if (str == "-inf" || str == "-inff") {
        return -std::numeric_limits<float>::infinity();
    }
    // std::numeric_limits<float>::min() -> 1.17549e-38
    // std::numeric_limits<float>::max() -> 3.40282e+38
    std::istringstream iss(str);
    float num;
    iss >> num;
    if (iss.fail() || !iss.eof())
        throw ImpossibleException();
    if (num < -std::numeric_limits<float>::max() || std::numeric_limits<float>::max() < num)
        throw ImpossibleException();
    return num;
}

double ScalarConverter::toDouble(const std::string &str)
{
    // 변환이 말이 안되거나, 오버플로우가 발생하는 경우 ImpossibleException
    // 0.0, -4.2, 4.2
    // -inf, +inf, nan
    if (str == "nan") {
        return std::numeric_limits<double>::quiet_NaN();
    } else if (str == "+inf" || str == "inf") {
        return std::numeric_limits<double>::infinity();
    } else if (str == "-inf") {
        return -std::numeric_limits<double>::infinity();
    }
    // std::numeric_limits<double>::min() -> 2.22507e-308
    // std::numeric_limits<double>::max() -> 1.79769e+308
    std::istringstream iss(str);
    double num;
    iss >> num;
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

void ScalarConverter::convert(const std::string &originalStr)
{
    std::string str = originalStr;

    if (!str.empty() && str.find("inf") == std::string::npos && str[str.length() - 1] == 'f')
	{
        str = str.substr(0, str.length() - 1);
	}
	
	try
    {
        char res = toChar(str);
        std::cout << "char: '" << res << "'" << std::endl;
    }
    catch (const NonDisplayableException &e)
    {
        std::cerr << "char: " << e.what() << '\n';
    }
    catch (const ImpossibleException &e)
    {
        std::cerr << "char: " << e.what() << '\n';
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
        std::cout << "float: " << std::fixed << std::setprecision(1) << toFloat(str) << "f" << std::endl;
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
        std::cout << "double: " << std::fixed << std::setprecision(1) << toDouble(str) << std::endl;
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
