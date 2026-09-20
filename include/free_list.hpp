#pragma once
#include "block.hpp"

struct FreeListNode
{
    FreeListNode* next;
    FreeListNode* prev;
};

struct FreeList
{
    BlockHeader* head;
};
