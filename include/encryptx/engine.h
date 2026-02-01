#pragma once

#include <memory>
#include <string>

#include "encryptor.h"
#include "encryptx/progress.h"

namespace encryptx
{

    class EncryptEngine
    {
    public:
        explicit EncryptEngine(std::unique_ptr<Encryptor> encryptor);

        void encrypt_file(const std::string &input,
                          const std::string &output,
                          ProgressCallback cb = nullptr);

        void decrypt_file(const std::string &input,
                          const std::string &output,
                          ProgressCallback cb = nullptr);

    private:
        std::unique_ptr<Encryptor> encryptor_;
    };

} // namespace encryptx
