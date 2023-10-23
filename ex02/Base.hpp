#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

class Base
{
public:
    virtual ~Base();

    Base *generate() const;
    
    void identify(Base *p);
    void identify(Base &p);
};

#endif // BASE_HPP
