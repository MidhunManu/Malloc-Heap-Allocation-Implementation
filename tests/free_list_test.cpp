#include <gtest/gtest.h>
#include "../include/heap.hpp"
#include "../include/free_list.hpp"

namespace {
   Heap heap = createHeap();
   BlockHeader* blk1 = unwrap(createBlock(heap.memory, 32));
   auto* blk2_memory = reinterpret_cast<std::byte*>(blk1) + blk1->size;
   BlockHeader* blk2 = unwrap(createBlock(blk2_memory, 32));
   auto* blk3_memory = reinterpret_cast<std::byte*>(blk2) + blk2->size;
   BlockHeader* blk3 = unwrap(createBlock(blk3_memory, 32));
}

TEST(FREE_LIST_TEST, HEAD_PREV_EQ_NULL)
{
    auto* link1 = reinterpret_cast<FreeListNode*>(blk1);

    auto* links = link1;

    EXPECT_EQ(links->prev, nullptr);
}

TEST(FREE_LIST_TEST, ALL_BLOCK_IN_FREE_LIST_ARE_FREE)
{
    FreeList list{};
    insertAtHead(list, blk1);
    insertAtHead(list, blk2);
    insertAtHead(list, blk3);

    auto* node = reinterpret_cast<FreeListNode*>(getPlayload(list.head));
    while(node != nullptr)
    {
        auto* header = reinterpret_cast<BlockHeader*>(
            reinterpret_cast<std::byte*>(node) - sizeof(FreeListNode)
        );
        EXPECT_EQ(header->state, BlockState::FREE);
        node = node->next;
    }
}
