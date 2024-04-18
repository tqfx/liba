cmake_minimum_required(VERSION 2.8.12...4.0)

project(main C)

find_package(liba CONFIG REQUIRED)

if(TARGET alib)
  add_executable(main-static main.c)
  target_link_libraries(main-static PRIVATE alib)
endif()

if(TARGET liba)
  add_executable(main-shared main.c)
  target_link_libraries(main-shared PRIVATE liba)
endif()
