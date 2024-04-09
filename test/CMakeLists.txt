# CMakeLists.txt for UriTests
#
# © 2024 by Hatem Nabli

cmake_minimum_required(VERSION 3.8)
set(this Utf8Tests)

set(Sources 
    src/Utf8Tests.cpp
)

add_executable(${this} ${Sources})
set_target_properties(${this} PROPERTIES 
    FOLDER Tests
)

target_include_directories(${this} PRIVATE ..)

target_link_libraries(${this} PUBLIC 
    gtest_main 
    Utf8
)

add_test(
    NAME ${this} 
    COMMAND ${this}
)