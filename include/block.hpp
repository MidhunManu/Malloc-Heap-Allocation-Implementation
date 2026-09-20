#pragma once
#include <cstddef>
#include <expected>
#include "error_codes.hpp"

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

std::expected<BlockHeader*, AllocatorError> createBlock(std::byte* memory, std::size_t payload_size);
std::byte* getPlayload(BlockHeader* header);
BlockHeader* getNextBlock(BlockHeader* header);
std::expected<void*, AllocatorError> allocate(FreeList& free_list, std::size_t size);
void deallocate(BlockHeader* headeer);
