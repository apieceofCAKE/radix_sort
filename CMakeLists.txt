cmake_minimum_required(VERSION 3.14)
project(radix_sort_v2 C)

set(CMAKE_C_STANDARD 99)

add_executable(radix_sort_v2 main.c)

target_link_libraries(radix_sort_v2 m)
