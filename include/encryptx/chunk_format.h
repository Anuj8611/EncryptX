#pragma once
#include <cstdint>

namespace encryptx
{

    struct FileHeader
    {
        char magic[8];
        uint32_t chunk_size;
        uint64_t total_chunks;
    };

    struct ChunkHeader
    {
        uint64_t index;
        uint32_t data_size;
    };

} // namespace encryptx
