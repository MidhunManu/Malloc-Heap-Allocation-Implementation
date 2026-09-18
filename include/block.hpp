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

struct BlockPlayload
{
    
};

struct Block
{
    BlockHeader header;
    BlockPlayload payload;    
};
