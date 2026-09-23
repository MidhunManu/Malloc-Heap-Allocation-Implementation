#include "../include/free_list.hpp"
#include <cstddef>
#include "../include/free_list.hpp"
#include "../include/block.hpp"

void clearList(FreeList& list)
{
    BlockHeader* current = list.head;
    while(current != nullptr)
    {
        auto* links = reinterpret_cast<FreeListNode*>(getPlayload(current));
        FreeListNode* next = links->next;

        links->next = nullptr;
        links->prev = nullptr;

        if (next != nullptr)
        {
            current = reinterpret_cast<BlockHeader*>(
                reinterpret_cast<std::byte*>(next) - sizeof(BlockHeader)
            );
        }
        else
        {
            current = nullptr;
        }
    }
    list.head = nullptr;
}

void insertAtHead(FreeList& list, BlockHeader* head)
{
    FreeListNode* newNode = reinterpret_cast<FreeListNode*>(getPlayload(head));

    if (list.head == nullptr)
    {
        newNode->next = nullptr;
        newNode->prev = nullptr;
        list.head = head;
        return;
    }

    BlockHeader* current = list.head;
    FreeListNode* currentNode = reinterpret_cast<FreeListNode*>(getPlayload(current));
    newNode->next = currentNode;
    newNode->prev = nullptr;

    currentNode->prev = newNode;
    list.head = head;
}

void updateHeadPrev(FreeList& list, BlockHeader* block)
{
    BlockHeader* currentHead = list.head;
    auto* currentNode = reinterpret_cast<FreeListNode*>(getPlayload(currentHead));
    auto blockNode = reinterpret_cast<FreeListNode*>(getPlayload(block));
    currentNode->prev = blockNode;
    blockNode->next = currentNode;
}

void removeHead(FreeList& list)
{
    if (list.head == nullptr)
    {
        return;
    }

    auto* currentNode = reinterpret_cast<FreeListNode*>(getPlayload(list.head));
    if (currentNode->next == nullptr)
    {
        list.head = nullptr;
        return;
    }

    auto* nextNode = currentNode->next;
    list.head = reinterpret_cast<BlockHeader*>(
        reinterpret_cast<std::byte*>(nextNode) - sizeof(FreeListNode)
    );
}

void removeNode(FreeList& list, BlockHeader* block)
{
    if (block->state != BlockState::FREE)
    {
        return;
    }

    auto* node = reinterpret_cast<FreeListNode*>(getPlayload(block));
    if (node->prev != nullptr)
    {
        node->prev->next = node->next;
    }
    else
    {
        if (node->next != nullptr)
        {
            list.head = reinterpret_cast<BlockHeader*>(
                reinterpret_cast<std::byte*>(node->next) - sizeof(FreeListNode)
            );
        }
        else
        {
            list.head = nullptr;
        }
    }

    if (node->next != nullptr)
    {
        node->next->prev = node->prev;
    }

    node->prev = nullptr;
    node->next = nullptr;
}

void deleteNode(FreeList& list, BlockHeader* block)
{
    removeNode(list, block);
    delete block;
}

void removeTail(FreeList& list)
{
    if (list.head == nullptr)
    {
        return;
    }

    auto* node = reinterpret_cast<FreeListNode*>(getPlayload(list.head));

    while(node->next != nullptr)
    {
        node = node->next;
    }

    auto* block = reinterpret_cast<BlockHeader*>(
        reinterpret_cast<std::byte*>(node) - sizeof(FreeListNode)
    );

    removeNode(list, block);
}
