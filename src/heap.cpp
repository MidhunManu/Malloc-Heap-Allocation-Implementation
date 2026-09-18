#include "../include/heap.hpp"
#include "../include/config.hpp"

struct Heap createHeap()
{
    Heap heap;
    heap.memory = new std::byte[HeapConfig::capacity];
    heap.capacity = HeapConfig::capacity;

    return heap;
}

void destroyHeap(Heap& heap)
{
    delete[] heap.memory;
    heap.memory = nullptr;
    heap.capacity = 0;
}
