#pragma once
#include <cstddef>

struct Heap
{
    std::byte* memory;
    std::size_t capacity;
};

struct Heap createHeap(Heap& heap);
void destroyHeap();
