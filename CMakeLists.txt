cmake_minimum_required(VERSION 4.0)
project(DSA C)

set(CMAKE_C_STANDARD 11)

add_library(DSA STATIC
        primer.c
        array.c
        linked_list.c)
