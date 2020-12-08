cmake_minimum_required(VERSION 3.10)

project(perkolacje)

set(proj_headers include/union_find.h include/Perkolacja.h )
set(proj_sources src/Perkolacja.cpp)
add_executable(${PROJECT_NAME} main.cpp ${proj_sources} ${proj_headers})
target_include_directories(${PROJECT_NAME} PUBLIC include/)

