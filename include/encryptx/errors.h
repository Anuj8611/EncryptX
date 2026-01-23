#pragma once
#include <stdexcept>
#include <string>

namespace encryptx
{

    // Base class for all EncryptX errors
    class EncryptXError : public std::runtime_error
    {
    public:
        explicit EncryptXError(const std::string &msg)
            : std::runtime_error(msg) {}
    };

    // File I/O related errors
    class IOError : public EncryptXError
    {
    public:
        explicit IOError(const std::string &msg)
            : EncryptXError(msg) {}
    };

    // Invalid file format / header errors
    class FormatError : public EncryptXError
    {
    public:
        explicit FormatError(const std::string &msg)
            : EncryptXError(msg) {}
    };

    // Data corruption / checksum mismatch
    class CorruptionError : public EncryptXError
    {
    public:
        explicit CorruptionError(const std::string &msg)
            : EncryptXError(msg) {}
    };

} // namespace encryptx
