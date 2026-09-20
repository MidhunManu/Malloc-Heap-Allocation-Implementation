#pragma once

struct BlockHeader;

struct FreeListNode
{
    FreeListNode* next;
    FreeListNode* prev;
};

struct FreeList
{
    BlockHeader* head;
};

void clearList(FreeList& list);
void insertAtHead(FreeList& list, BlockHeader* head);
void updateHeadPrev(FreeList& list, BlockHeader* block);
void removeHead(FreeList& list);
void removeNode(FreeList& list, BlockHeader* block);
void removeTail(FreeListNode& list);
