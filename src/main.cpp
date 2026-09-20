#include <iostream>
#include <format>
#include "../include/heap.hpp"
#include "../include/block.hpp"
#include "../include/free_list.hpp"

int main(int argc, char const *argv[])
{
    Heap heap = createHeap();

    BlockHeader* block1 = unwrap(createBlock(heap.memory, 64));
    auto* block2_memory = reinterpret_cast<std::byte*>(block1) + sizeof(BlockHeader) + block1->size;
    BlockHeader* block2 = unwrap(createBlock(block2_memory, 64));

    FreeList free_List{};
    free_List.head = block1;

    auto* link1 = reinterpret_cast<FreeListNode*>(getPlayload(block1));
    auto* link2 = reinterpret_cast<FreeListNode*>(getPlayload(block2));

    link1->next = link2;
    link1->prev = nullptr;

    link2->next = nullptr;
    link2->prev = link1;

    auto* links = link1;

    while(links != nullptr)
    {
        auto* header = reinterpret_cast<BlockHeader*>(
            reinterpret_cast<std::byte*>(links) - sizeof(FreeListNode)
        );

        std::cout << header->size << "\n";
        links = links->next;
    }

    #ifdef DEBUG
        std::cout << std::format("block size: {}\n", block1->size);
        std::cout << std::format("block state: {}\n", static_cast<int>(block1->state));
        std::cout << std::format("Heap Address: {}\n", static_cast<void*>(heap.memory));
        // std::cout << std::format("Payload Address: {}\n", static_cast<void*>(payload));
    #endif

    destroyHeap(heap);
    return 0;
}
