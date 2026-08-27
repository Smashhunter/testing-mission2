project(programm2)	

set(SOURCE_FILES
    src/server-socket.cpp
    src/server.cpp
)

add_executable(programm2
    main.cpp
    ${SOURCE_FILES}
)

target_include_directories(programm2 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(programm2 PRIVATE my_lib)

target_compile_definitions(programm2 PRIVATE
    PROJECT_NAME_STR="${PROJECT_NAME}"
    SOCKET_PATH="${SERVER_PATH}"
)
