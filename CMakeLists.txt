cmake_minimum_required(VERSION 3.20)
project(Bdot C)

set(CMAKE_C_STANDARD 99)

add_executable(Bdot main.c bdot.c bdot.h)
