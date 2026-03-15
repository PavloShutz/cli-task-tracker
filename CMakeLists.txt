cmake_minimum_required(VERSION 3.31.3)
project(CLITaskTracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

set(SOURCES 
    src/main.cpp
    src/task.cpp
    src/ui.cpp
    src/utility.cpp)
add_executable(task-cli ${SOURCES})

target_include_directories(task-cli
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(task-cli PRIVATE nlohmann_json::nlohmann_json)