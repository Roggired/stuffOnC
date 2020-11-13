cmake_minimum_required(VERSION 3.15)
project(stepik_cource C)

set(CMAKE_C_STANDARD 99)

add_executable(stepik_cource src/main.c src/tree/tree.h src/tree/tree.c src/tree/list.h src/tree/list.c src/tree/tree_writer.h src/tree/tree_writer.c)