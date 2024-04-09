# CMackeLists.txt for Utf8
#
# © 2024 by Hatem Nabli


cmake_minimum_required(VERSION 3.8)
set(this Utf8)

set(Headers 
    include/Utf8/Utf8.hpp
)

set(Sources 
    src/Utf8.cpp
)

add_library(${this} STATIC ${Sources} ${Headers})
set_target_properties(${this} PROPERTIES 
    FOLDER Libraries
)

target_include_directories(${this} PUBLIC include)

add_subdirectory(test)