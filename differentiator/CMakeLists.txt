cmake_minimum_required(VERSION 3.15)
project(differentiator)

set(CMAKE_CXX_STANDARD 17)

add_executable(differentiator diff_header.h DSL.h commands.h diff.cpp simple.cpp equation_creator.cpp
        tree_header.h tree.cpp tree_dot.cpp diff_reader.cpp DSL.h commands.h diff_main.cpp latex.cpp equation_creator_rec.cpp)