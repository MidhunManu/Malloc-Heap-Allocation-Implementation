#include <cstdlib>
#include <iostream>
#include "../include/block.hpp"
#include "../include/config.hpp"
#include "../include/free_list.hpp"
#include "../include/heap.hpp"

std::expected<BlockHeader*, AllocatorError> createBlock(std::byte* memory, std::size_t size)
{
    if (size > HeapConfig::capacity - sizeof(BlockHeader))
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

std::expected<void*, AllocatorError> allocate(FreeList& free_list, std::size_t size)
{
    if (size > HeapConfig::capacity)
    {
        return std::unexpected(AllocatorError::InvalidSize);
    }

    auto* head = free_list.head;
    auto* headNode = reinterpret_cast<FreeListNode*>(getPlayload(head));

    auto* curr = headNode;
    BlockHeader* selectedHeader = nullptr;
    size_t max = 0;
    while (curr != nullptr)
    {
        auto* header = reinterpret_cast<BlockHeader*>(
            reinterpret_cast<std::byte*>(curr) - sizeof(FreeListNode)
        );

        if (header->size > max && header->size >= size)
        {
            max = header->size;
            selectedHeader = header;
        }

        curr = curr->next;
    }

    if (selectedHeader == nullptr)
    {
        return std::unexpected(AllocatorError::NoFitFound);
    }

    removeNode(free_list, selectedHeader);
    selectedHeader->state = BlockState::ALLOCATED;
    auto* payload = reinterpret_cast<std::byte*>(getPlayload(selectedHeader));
    return payload;
}

std::expected<BlockHeader*, AllocatorError> splitBlock(BlockHeader* block, std::size_t size)
{
    if (block->state == BlockState::ALLOCATED)
    {
        return std::unexpected(AllocatorError::InvalidArgument);
    }

    auto* blockEnd = reinterpret_cast<std::byte*>(getPlayload(block)) + block->size;

    size_t remaining = block->size - size - sizeof(BlockHeader) - sizeof(FreeListNode);

    if (remaining < HeapConfig::min_free_block_size)
    {
        return std::unexpected(AllocatorError::InvalidSize);
    }

    auto* newHeaderAddress = blockEnd - size - sizeof(BlockHeader);
    auto* newHeader = reinterpret_cast<BlockHeader*>(newHeaderAddress);
    block->size -= size + sizeof(BlockHeader);
    newHeader->size = size;
    newHeader->state = BlockState::ALLOCATED;

    return newHeader;
}

std::expected<void, AllocatorError> deallocate(FreeList& list, BlockHeader* header)
{
    if (header == nullptr || header->state != BlockState::ALLOCATED)
    {
        return std::unexpected(AllocatorError::InvalidState);
    }

    header->state = BlockState::FREE;
    insertAtHead(list, header);
    return {};
}
