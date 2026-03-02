cmake_minimum_required(VERSION 4.1)
project(Theater C)

set(CMAKE_C_STANDARD 11)

add_executable(Theater
        sala.c
        sala.h
        test_sala.c)
