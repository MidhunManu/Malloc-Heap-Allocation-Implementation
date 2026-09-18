#pragma once
#include <cstddef>

enum class BlockState
{
    FREE,
    ALLOCATED,
};

struct BlockHeader
{
    std::size_t size;
    BlockState state;
};

BlockHeader* createBlock(std::byte* memory, std::size_t payload_size);
std::byte* getPlayload(BlockHeader* header);
BlockHeader* getNextBlock(BlockHeader* header);
