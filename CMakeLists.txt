cmake_minimum_required(VERSION 3.15)
project(stepik_cource C)

set(CMAKE_C_STANDARD 99)

add_executable(stepik_cource src/main.c src/graph/graph.h src/graph/graph.c src/graph/list.h src/graph/list.c src/graph/graph_writer.h src/graph/graph_writer.c)