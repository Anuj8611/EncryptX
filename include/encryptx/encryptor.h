#pragma once
#include <cstddef>
#include <cstdint>

namespace encryptx
{

    class Encryptor
    {
    public:
        virtual ~Encryptor() = default;

        virtual void encrypt(uint8_t *data, size_t len) = 0;
        virtual void decrypt(uint8_t *data, size_t len) = 0;
    };

}
