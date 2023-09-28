cmake_minimum_required(VERSION 3.23)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # seems to work with CLion - if you run into problems, try an older version of catch2 v3
)
FetchContent_MakeAvailable(Catch2)


include_directories(src)
include_directories(test-unit)

add_executable(Project1
        src/main.cpp
        src/avl.h
        )

add_executable(Testing
        test-unit/test.cpp
        )

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)
