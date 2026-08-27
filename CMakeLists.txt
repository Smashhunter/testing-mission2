cmake_minimum_required(VERSION 3.15)

project(testing-mission VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(SERVER_PATH "/tmp/my_app.sock" CACHE STRING "Socket file path for IPC communication")

include_directories(${WORKING_DIRECTORY}/lib)

add_subdirectory(lib)
add_subdirectory(programm1)
add_subdirectory(programm2)
