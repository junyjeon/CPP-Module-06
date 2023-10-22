#include "Serializer.hpp"

int main()
{
    Data *originalData = new Data();
    originalData->name = "Jun";

    std::cout << "Original data value: " << originalData->name << std::endl;

    // serialize
    uintptr_t serializedData = Serializer::serialize(originalData);
    std::cout << "Serialized data: " << serializedData << std::endl;

    // deserialize
    Data *deserializedData = Serializer::deserialize(serializedData);
    std::cout << "Deserialized data value: " << deserializedData->name << std::endl;

    assert(originalData == deserializedData);

    delete originalData;

    return 0;
}