#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <iostream>
#include <cstring>
#include <cassert>
#include <stdint.h>

struct Data {
    uint8_t dataLength; // 데이터 길이
    uint8_t* payload; // 응답 데이터
};


class Serializer
{
private:
    Serializer();
    Serializer(const Serializer &);
    Serializer &operator=(const Serializer &);

public:
    ~Serializer();
    static uintptr_t serialize(Data *ptr);
    static Data *deserialize(uintptr_t raw);
};

#endif // SERIALIZER_HPP

