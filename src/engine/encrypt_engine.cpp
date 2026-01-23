#include "encryptx/engine.h"
#include "encryptx/checksum.h"
#include "encryptx/chunk_format.h"
#include "encryptx/config.h"
#include "encryptx/errors.h"

#include <fstream>
#include <vector>
#include <cstring>

namespace encryptx
{

    EncryptEngine::EncryptEngine(std::unique_ptr<Encryptor> enc)
        : encryptor_(std::move(enc)) {}

    void EncryptEngine::encrypt_file(const std::string &input,
                                     const std::string &output)
    {
        std::ifstream in(input, std::ios::binary);
        if (!in)
            throw IOError("Failed to open input file: " + input);

        std::ofstream out(output, std::ios::binary);
        if (!out)
            throw IOError("Failed to open output file: " + output);

        // ---- write placeholder file header ----
        FileHeader fileHeader{};
        std::memcpy(fileHeader.magic, "ENCXv1", 6);
        fileHeader.chunk_size = DEFAULT_CHUNK_SIZE;
        fileHeader.total_chunks = 0;

        out.write(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));

        std::vector<uint8_t> buffer(DEFAULT_CHUNK_SIZE);
        uint64_t chunkIndex = 0;

        while (true)
        {
            in.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
            std::streamsize bytes = in.gcount();
            if (bytes == 0)
                break;

            ChunkHeader ch{};
            ch.index = chunkIndex;
            ch.data_size = static_cast<uint32_t>(bytes);

            encryptor_->encrypt(buffer.data(), bytes);
            uint32_t checksum = crc32(buffer.data(), bytes);

            out.write(reinterpret_cast<char *>(&ch), sizeof(ch));
            out.write(reinterpret_cast<char *>(buffer.data()), bytes);
            out.write(reinterpret_cast<char *>(&checksum), sizeof(checksum));

            chunkIndex++;
        }

        // ---- PATCH total_chunks ----
        fileHeader.total_chunks = chunkIndex;
        out.seekp(0);
        out.write(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
    }

} // namespace encryptx
