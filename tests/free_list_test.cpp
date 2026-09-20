#include <gtest/gtest.h>
#include "../include/heap.hpp"
#include "../include/free_list.hpp"
#include "../include/block.hpp"

namespace {
   Heap heap = createHeap();
   BlockHeader* blk1 = unwrap(createBlock(heap.memory, 32));
   BlockHeader* blk2 = unwrap(createBlock(reinterpret_cast<std::byte*>(getNextBlock(blk1)), 64));
   BlockHeader* blk3 = unwrap(createBlock(reinterpret_cast<std::byte*>(getNextBlock(blk2)), 16));

   FreeList list{};
}

TEST(FREE_LIST_TEST, HEAD_PREV_EQ_NULL)
{
    auto* link1 = reinterpret_cast<FreeListNode*>(blk2);

    auto* links = link1;

    EXPECT_EQ(links->prev, nullptr);
}

TEST(FREE_LIST_TEST, ALL_BLOCK_IN_FREE_LIST_ARE_FREE)
{
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

TEST(FREE_LIST_TEST, ALLOCATE_MEMORY)
{
    insertAtHead(list, blk3);
    insertAtHead(list, blk2);
    insertAtHead(list, blk1);

    void* payload_allocation = unwrap(allocate(list, 32));
    auto* header = reinterpret_cast<BlockHeader*>(
        reinterpret_cast<std::byte*>(payload_allocation) - sizeof(BlockHeader)
    );

    EXPECT_EQ(header, blk1);
    EXPECT_EQ(header->state, BlockState::ALLOCATED);
    EXPECT_EQ(header->size, 32);
    EXPECT_EQ(list.head, blk2);
}
