#include "encryptx/engine.h"
#include "encryptx/config.h"

#include <fstream>
#include <vector>

namespace encryptx
{

    EncryptEngine::EncryptEngine(std::unique_ptr<Encryptor> enc)
        : encryptor_(std::move(enc)) {}

    void EncryptEngine::encrypt_file(const std::string &input,
                                     const std::string &output)
    {

        std::ifstream in(input, std::ios::binary);
        std::ofstream out(output, std::ios::binary);

        std::vector<uint8_t> buffer(DEFAULT_CHUNK_SIZE);

        while (true)
        {
            in.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
            std::streamsize bytes = in.gcount();
            if (bytes == 0)
                break;

            encryptor_->encrypt(buffer.data(), bytes);
            out.write(reinterpret_cast<char *>(buffer.data()), bytes);
        }
    }

} // namespace encryptx
