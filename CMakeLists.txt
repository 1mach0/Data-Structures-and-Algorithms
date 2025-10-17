cmake_minimum_required(VERSION 4.0)
project(DSA C)

set(CMAKE_C_STANDARD 11)

add_library(DSA STATIC library.c
        primer.c)
