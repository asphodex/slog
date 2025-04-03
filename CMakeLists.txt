cmake_minimum_required(VERSION 3.30)
project(slog)

set(CMAKE_CXX_STANDARD 26)

add_executable(slog main.cpp
        include/slog.h)
