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
    if (size > HeapConfig::capacity || size <= 0)
    {
        return std::unexpected(AllocatorError::InvalidSize);
    }

    auto* head = free_list.head;
    auto* headNode = reinterpret_cast<FreeListNode*>(getPlayload(head));

    auto* curr = headNode;

    while (curr != nullptr)
    {
        auto* header = reinterpret_cast<BlockHeader*>(
            reinterpret_cast<std::byte*>(curr) - sizeof(FreeListNode)
        );

        if (header->size >= size)
        {
            removeNode(free_list, header);
            header->state = BlockState::ALLOCATED;
            auto* payload = reinterpret_cast<std::byte*>(getPlayload(header));
            return payload;
        }
        curr = curr->next;
    }

    return std::unexpected(AllocatorError::NoFitFound);
}

void deallocate(BlockHeader* headeer)
{

}
