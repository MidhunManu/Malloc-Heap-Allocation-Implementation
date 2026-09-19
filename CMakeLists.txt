cmake_minimum_required(VERSION 3.20)

project(HeapAllocator 
    VERSION 1.0.0 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
    src/main.cpp
    src/heap.cpp
    src/block.cpp
)

add_executable(allocator ${SOURCE_FILES})

target_include_directories(allocator PRIVATE include)

if(DEBUG)
    target_compile_definitions(allocator PRIVATE DEBUG)
endif()
