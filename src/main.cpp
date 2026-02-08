#include "encryptx/engine.h"
#include "encryptx/errors.h"

#include <iostream>
#include <memory>

#include <chrono>
#include <filesystem>

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
                 "  encryptx encrypt [--chunk-size N] <input> <output>\n"
                 "  encryptx decrypt [--chunk-size N] <input> <output>\n"
                 "\n"
                 "Options:\n"
                 "  --chunk-size N   Chunk size in MB (default: 4)\n";
}

void progress_bar(uint64_t done, uint64_t total)
{
    int percent = static_cast<int>((done * 100) / total);
    std::cout << "\rProgress: " << percent << "%";
    std::cout.flush();
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
            auto start = std::chrono::high_resolution_clock::now();

            engine.encrypt_file(input, output, progress_bar);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            double seconds = elapsed.count();
            double fileMB =
                std::filesystem::file_size(input) / (1024.0 * 1024.0);
            double throughput = fileMB / seconds;

            std::cout << "\nEncryption completed successfully\n";
            std::cout << "Time: " << seconds << " sec\n";
            std::cout << "Throughput: " << throughput << " MB/s\n";
        }
        else if (command == "decrypt")
        {
            engine.decrypt_file(input, output, progress_bar);
            std::cout << "\nDecryption completed successfully\n";
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
