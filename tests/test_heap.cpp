#include <gtest/gtest.h>
#include "../include/heap.hpp"
#include "../include/config.hpp"

TEST(HeapTest, CreateHeapTest)
{
    Heap heap = createHeap();
    EXPECT_NE(heap.memory, nullptr);
    EXPECT_EQ(heap.capacity, HeapConfig::capacity);
    destroyHeap(heap);
    EXPECT_EQ(heap.memory, nullptr);
    EXPECT_EQ(heap.capacity, 0);
}
