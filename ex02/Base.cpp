#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base() {}

Base *generate()
{
    srand(time(NULL)); // srand()함수로 컴퓨터의 현재 시간(time(NULL))을 seed(초기값)으로 설정
    switch (rand() % 3)
    {
        case 0: return new A();
        case 1: return new B();
        case 2: return new C();
    }
    return NULL;
}

// typeinfo(타입 정보를 알아내는 헤더) 금지. -> dynamic_cast를 사용하여 타입을 알아낼 수 있음.
// 포인터 dynamic_cast가 반환에 실패하면 nullptr를 반환.
void identify(Base* p) {
    if (dynamic_cast<A*>(p)) std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p)) std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p)) std::cout << "C" << std::endl;
}

// 레퍼런스 dynamic_cast가 반환에 실패하면 std::bad_cast 예외를 던짐.
void identify(Base& p) {
    if (dynamic_cast<A*>(&p)) std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(&p)) std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(&p)) std::cout << "C" << std::endl;
}