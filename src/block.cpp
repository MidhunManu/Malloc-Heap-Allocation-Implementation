#include <cstdlib>
#include <iostream>
#include "../include/block.hpp"
#include "../include/config.hpp"

std::expected<BlockHeader*, AllocatorError> createBlock(std::byte* memory, std::size_t size)
{
    if ((size + sizeof(BlockHeader*) > HeapConfig::capacity))
    {
        return std::unexpected(AllocatorError::OutOFMemory);
    }
    auto* header = reinterpret_cast<BlockHeader*>(memory);
    header->size = size;
    header->state = BlockState::FREE;

    return header;
}

std::byte* getPlayload(BlockHeader* header)
{
    return reinterpret_cast<std::byte*> (header) + sizeof(BlockHeader);
}

BlockHeader* getNextBlock(BlockHeader* header)
{
    auto* next = reinterpret_cast<std::byte*>(header)
                + sizeof(BlockHeader) 
                + header->size;
    
    return reinterpret_cast<BlockHeader*>(next);
}
