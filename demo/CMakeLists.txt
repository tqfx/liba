cmake_minimum_required(VERSION 3.12...4.0)

project(main C)

find_package(liba CONFIG REQUIRED)

add_executable(main-static main.c)
target_link_libraries(main-static PRIVATE alib)

add_executable(main-shared main.c)
target_link_libraries(main-shared PRIVATE liba)

add_executable(main-object main.c)
target_link_libraries(main-object PRIVATE liba.o)
