project(programm1)

set(SOURCE_FILES
    src/app.cpp
    src/thread-safe-buffer.cpp
)

add_executable(programm1
    main.cpp
    ${SOURCE_FILES}
)

target_include_directories(programm1 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(programm1 PRIVATE my_lib)

target_compile_definitions(programm1 PRIVATE
    PROJECT_NAME_STR="${PROJECT_NAME}"
)
