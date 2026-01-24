#include "encryptx/engine.h"
#include "encryptx/errors.h"

#include <iostream>
#include <memory>

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
        encrypt(data, len); // XOR is symmetric
    }

private:
    uint8_t key_;
};

void print_usage()
{
    std::cout << "Usage:\n"
              << "  encryptx encrypt <input> <output>\n"
              << "  encryptx decrypt <input> <output>\n";
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        print_usage();
        return 1;
    }

    std::string command = argv[1];
    std::string input = argv[2];
    std::string output = argv[3];

    try
    {
        auto enc = std::make_unique<XOREncryptor>(0xAA);
        EncryptEngine engine(std::move(enc));

        if (command == "encrypt")
        {
            engine.encrypt_file(input, output);
            std::cout << "Encryption completed successfully\n";
        }
        else if (command == "decrypt")
        {
            engine.decrypt_file(input, output);
            std::cout << "Decryption completed successfully\n";
        }
        else
        {

            print_usage();
            return 1;
        }
    }
    catch (const EncryptXError &e)
    {
        std::cerr << "EncryptX error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
