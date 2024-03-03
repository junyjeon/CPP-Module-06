#include "Serializer.hpp"
#include <iostream>
#include <cassert>

int main() {
    Data *originalData = new Data();
    originalData->dataLength = 3;
    originalData->payload = new uint8_t[3];
    originalData->payload[0] = 1;
    originalData->payload[1] = 2;
    originalData->payload[2] = 3;

    // originalData
    std::cout << "originalData: " << originalData << std::endl;
    std::cout << "originalData->dataLength: " << static_cast<int>(originalData->dataLength) << std::endl;
    std::cout << "originalData->payload: ";
    for (size_t i = 0; i < originalData->dataLength; ++i) {
        std::cout << static_cast<int>(originalData->payload[i]) << " ";
    }
    std::cout << std::endl;

    // serialize
    uintptr_t serializedData = Serializer::serialize(originalData);
    std::cout << "serializedData: " << serializedData << std::endl;
    // serializedData의 payload를 출력하는 건, uintptr_t 타입이므로 끝 주소에 \0이 없어서 출력이 안됨.
    // reinterpret_cast<Data *>(serializedData)->payload 이거. 그럼 어떻게 해야하죠 선생님. 헬프

    // deserialize
    Data *deserializedData = Serializer::deserialize(serializedData);
    std::cout << "deserializedData: " << deserializedData << std::endl;
    std::cout << "deserializedData->dataLength: " << static_cast<int>(deserializedData->dataLength) << std::endl;
    // deserializedData의 payload 내용 출력
    std::cout << "deserializedData->payload: ";
    for (size_t i = 0; i < deserializedData->dataLength; ++i) {
        std::cout << static_cast<int>(deserializedData->payload[i]) << " ";
    }
    std::cout << std::endl;

    // 내용 비교
    bool isEqual = originalData->dataLength == deserializedData->dataLength && // 데이터의 길이 비교
                   std::memcmp(originalData->payload, deserializedData->payload, originalData->dataLength) == 0; // 데이터 비교
    // assert(조건) 조건이 false이면 프로그램 종료
    assert(isEqual);

    // 메모리 해제
    delete[] originalData->payload;
    delete originalData;
    delete[] deserializedData->payload;
    delete deserializedData;

    return 0;
}