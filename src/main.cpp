#include "encryptx/engine.h"
#include <memory>
#include <iostream>

using namespace encryptx;

class XOREncryptor : public Encryptor
{
public:
    explicit XOREncryptor(uint8_t key) : key_(key) {}

    void encrypt(uint8_t *data, size_t len) override
    {
        for (size_t i = 0; i < len; ++i)
            data[i] ^= key_;
    }

    void decrypt(uint8_t *data, size_t len) override
    {
        encrypt(data, len);
    }

private:
    uint8_t key_;
};

int main()
{
    auto enc = std::make_unique<XOREncryptor>(0xAA);
    EncryptEngine engine(std::move(enc));

    engine.encrypt_file("img.jpg", "img.enc");
    engine.decrypt_file("img.enc", "img_out.jpg");

    std::cout << "Done\n";
}
