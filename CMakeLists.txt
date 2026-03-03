cmake_minimum_required(VERSION 3.31.3)
project(CLITaskTracker LANGUAGES CXX)

set(SOURCES src/main.cpp)

add_executable(task-cli ${SOURCES})