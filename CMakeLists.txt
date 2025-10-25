cmake_minimum_required(VERSION 4.0)
project(DSA C)

set(CMAKE_C_STANDARD 11)

add_library(DSA STATIC
        0_primer.c
        1_array.c
        2_linked_list.c
        3_stack_as_array.c
        4_stack_as_linked_list.c
        5_expression_parsing.c
        6_queue.c
        7_binary_search.c
        9_hash_table.c
        8_sort.c
        10_bst.c
        11_avl.c
        12_btree.c)
