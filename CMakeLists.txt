cmake_minimum_required(VERSION 3.10)
project(Behachka_Semerka C)

set(CMAKE_C_STANDARD 99)


find_package(Threads REQUIRED)

# Задание 1
add_executable(ex1 ex1.c)
target_link_libraries(ex1 Threads::Threads)

# Задание 2
add_executable(ex2 ex2.c)
target_link_libraries(ex2 Threads::Threads)
