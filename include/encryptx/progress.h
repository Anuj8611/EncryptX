#pragma once
#include <cstdint>

namespace encryptx
{

    // processed_bytes, total_bytes
    using ProgressCallback = void (*)(uint64_t, uint64_t);

}
