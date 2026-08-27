project(my_lib VERSION 1.0.0 LANGUAGES CXX)

set(SOURCE_LIB 
	src/lib.cpp
	src/socket.cpp
	src/client-socket.cpp
)

add_library(my_lib SHARED ${SOURCE_LIB})

target_include_directories(my_lib PUBLIC
	include/
)
