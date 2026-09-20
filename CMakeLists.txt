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
    src/free_list.cpp
)

add_executable(allocator ${SOURCE_FILES})

target_include_directories(allocator PRIVATE include)

if(DEBUG)
    target_compile_definitions(allocator PRIVATE DEBUG)
endif()

# -------------------------
# GoogleTest
# -------------------------

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)


# -------------------------
# Tests
# -------------------------

add_executable(allocator_tests
    tests/test_heap.cpp
    tests/free_list_test.cpp
    src/heap.cpp
    src/block.cpp
    src/free_list.cpp
)

target_include_directories(allocator_tests PRIVATE include)

target_link_libraries(allocator_tests
    PRIVATE
    GTest::gtest_main
)
