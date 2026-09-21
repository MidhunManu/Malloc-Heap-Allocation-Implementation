#pragma once
#include <cstddef>

namespace HeapConfig
{
    constexpr std::size_t capacity = 4096;
    constexpr std::size_t min_free_block_size = 17;
}
