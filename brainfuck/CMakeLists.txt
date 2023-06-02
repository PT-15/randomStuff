cmake_minimum_required(VERSION 3.7)

project(brainfuck)

set(CMAKE_C_FLAGS "-Wall -Wextra -O2")
#set(CMAKE_C_FLAGS "-Wall -Wextra -g")

#set(CMAKE_VERBOSE_MAKEFILE on)

add_executable(brainfuckInterpreter brainfuckInterpreter.c)
add_executable(ookInterpreter ookInterpreter.c)
add_executable(ookToBrainfuckTranslator ookToBrainfuckTranslator.c)
add_executable(brainfuckToOokTranslator brainfuckToOokTranslator.c)
