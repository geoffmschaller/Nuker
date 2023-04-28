cmake_minimum_required(VERSION 3.25)
project(Nuker C)

set(CMAKE_C_STANDARD 23)

add_executable(Nuker src/main.c includes/main.h src/main.c)
