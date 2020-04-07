cmake_minimum_required(VERSION 3.15)
project(language)

set(CMAKE_CXX_STANDARD 17)

add_executable(language lang_header.h lang_commands.h lang_main.cpp lang.cpp
        tree_header.h tree.cpp tree_dot.cpp
        lang_reader.cpp lang_tokenization.cpp
        lang_front_end.cpp lang_middle_end.cpp lang_back_end.cpp lang_front_end_back.cpp
        lang_which_is.cpp)