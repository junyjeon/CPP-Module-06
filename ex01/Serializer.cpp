#include "Serializer.hpp"

Serializer::Serializer() {}

Serializer::Serializer(const Serializer &other)
{
    *this = other;
}

Serializer &Serializer::operator=(const Serializer &other)
{
    (void)other;
    return *this;
}

Serializer::~Serializer() {}

// uintptr_t is 포인터를 저장 할 수 있는 unsigned int 타입
uintptr_t Serializer::serialize(Data* ptr) {
    if (ptr == NULL)
        return 0;
    size_t totalSize = sizeof(uint8_t) + ptr->dataLength;
    uint8_t* buffer = new uint8_t[totalSize];
    
    buffer[0] = ptr->dataLength;

    // memcpy(복사할 위치, 복사할 데이터, 복사할 데이터 길이)
    memcpy(buffer + sizeof(uint8_t), ptr->payload, ptr->dataLength);

    //딱 payload 길이 만큼만 복사.
    return reinterpret_cast<uintptr_t>(buffer);
}
// re interpret cast 포인터 타입을 다른 포인터로 타입 변환
// char * -> int * -> float * -> void * -> int * -> Data * 이런식으로 같은 바이트를 가지고 있는 포인터 타입으로 변환 가능.
// 메모리 주소는 같음.
// 포인터를 저장한 unsigned int 타입을 Data 구조체 포인터 타입으로 변환

Data *Serializer::deserialize(uintptr_t raw) {
    uint8_t* buffer = reinterpret_cast<uint8_t*>(raw);

    Data* data = new Data();

    // buffer에서 데이터 길이 정보를 읽음
    data->dataLength = *buffer;

    // 데이터 길이만큼 메모리를 할당하고, payload 데이터를 복사
    data->payload = new uint8_t[data->dataLength];
    memcpy(data->payload, buffer + sizeof(uint8_t), data->dataLength);

    delete[] buffer;
    return data;
}

//Data * -> 32bit. uintptr_t -> 32bit.