#pragma once
#include <expected>
#include <iostream>

enum class AllocatorError
{
    None,
    OutOFMemory,
    InvalidSize,
    InvalidArgument,
    NoFitFound,
};

template <typename T, typename E>
T unwrap(std::expected<T, E> result)
{
    if (!result)
    {
        std::cout << "Allocator Error"
                  << static_cast<int>(result.error())
                  << "\n";

        exit(static_cast<int>(result.error()));
    }
    return *result;
}
