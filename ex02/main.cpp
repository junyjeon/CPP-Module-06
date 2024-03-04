#include "Base.hpp"

int main() {
    Base* obj = generate();
    std::cout << "identify by pointer: ";
    identify(obj);
    std::cout << std::endl;

    std::cout << "identify by reference: ";
    identify(*obj);
    std::cout << std::endl;

    delete obj;
    return 0;
}