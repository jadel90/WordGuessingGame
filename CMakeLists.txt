cmake_minimum_required(VERSION 3.29)
project(Assignment_1z)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_1z
    main.c
    utils.c
    utils.h
    word_list.txt)
