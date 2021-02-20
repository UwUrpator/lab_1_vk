cmake_minimum_required(VERSION 3.15)
project(array C)

set(CMAKE_C_STANDARD 99)

add_executable(run_arr main.c menu.c testarr.c array.c cmpint.c cmpstr.c demofun.c intio.c strio.c)