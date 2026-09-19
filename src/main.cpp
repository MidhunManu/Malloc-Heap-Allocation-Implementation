#include <iostream>
#include <format>
#include "../include/heap.hpp"
#include "../include/block.hpp"

int main(int argc, char const *argv[])
{
    Heap heap = createHeap();
    BlockHeader* block = createBlock(heap.memory, 128);
    std::byte* payload = getPlayload(block);

    #ifdef DEBUG
        std::cout << std::format("block size: {}\n", block->size);
        std::cout << std::format("block state: {}\n", static_cast<int>(block->state));
        std::cout << std::format("Heap Address: {}\n", static_cast<void*>(heap.memory));
        std::cout << std::format("Payload Address: {}\n", static_cast<void*>(payload));
    #endif

    destroyHeap(heap);
    return 0;
}
