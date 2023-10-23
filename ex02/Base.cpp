#include "Base.hpp"

Base::~Base() {}

Base *generate()
{
    srand(time(NULL));
    int i = rand() % 3;
    if (i == 0)
        return new A;
    else if (i == 1)
        return new B;
    else
        return new C;
}

void identify(Base *p)
{
    dynamic_cast<A *>(p);
}

void identify(Base &p)
{
}
