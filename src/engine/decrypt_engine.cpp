#include "encryptx/engine.h"
#include "encryptx/chunk_format.h"
#include "encryptx/checksum.h"
#include "encryptx/errors.h"

#include <fstream>
#include <vector>
#include <cstring>

namespace encryptx
{

    void EncryptEngine::decrypt_file(const std::string &input,
                                     const std::string &output)
    {
        // ---- open encrypted file ----
        std::ifstream in(input, std::ios::binary);
        if (!in)
        {
            throw IOError("Failed to open encrypted file: " + input);
        }

        // ---- open output file ----
        std::ofstream out(output, std::ios::binary);
        if (!out)
        {
            throw IOError("Failed to open output file: " + output);
        }

        // ---- read & validate file header ----
        FileHeader fileHeader{};
        in.read(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));

        if (!in)
        {
            throw FormatError("Failed to read file header");
        }

        if (std::memcmp(fileHeader.magic, "ENCXv1", 6) != 0)
        {
            throw FormatError("Invalid EncryptX file (bad magic)");
        }

        // ---- allocate buffer using chunk size from header ----
        std::vector<uint8_t> buffer(fileHeader.chunk_size);

        // ---- process chunks ----
        for (uint64_t i = 0; i < fileHeader.total_chunks; ++i)
        {
            ChunkHeader ch{};
            in.read(reinterpret_cast<char *>(&ch), sizeof(ch));

            if (!in)
            {
                throw FormatError("Failed to read chunk header at index " +
                                  std::to_string(i));
            }

            if (ch.data_size > buffer.size())
            {
                throw FormatError("Invalid chunk size at index " +
                                  std::to_string(ch.index));
            }

            // ---- read encrypted data ----
            in.read(reinterpret_cast<char *>(buffer.data()), ch.data_size);
            if (!in)
            {
                throw CorruptionError("Unexpected EOF while reading chunk data at index " +
                                      std::to_string(ch.index));
            }

            // ---- read stored checksum ----
            uint32_t storedChecksum;
            in.read(reinterpret_cast<char *>(&storedChecksum), sizeof(storedChecksum));
            if (!in)
            {
                throw CorruptionError("Failed to read checksum at chunk " +
                                      std::to_string(ch.index));
            }

            // ---- validate checksum (ON ENCRYPTED DATA) ----
            uint32_t computedChecksum = crc32(buffer.data(), ch.data_size);
            if (computedChecksum != storedChecksum)
            {
                throw CorruptionError("Checksum mismatch at chunk " +
                                      std::to_string(ch.index));
            }

            // ---- decrypt and write ----
            encryptor_->decrypt(buffer.data(), ch.data_size);
            out.write(reinterpret_cast<char *>(buffer.data()), ch.data_size);

            if (!out)
            {
                throw IOError("Failed to write output data at chunk " +
                              std::to_string(ch.index));
            }
        }
    }

} // namespace encryptx
