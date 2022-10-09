cmake_minimum_required(VERSION 3.10)

project(Project2)

aux_source_directory(./src DIR_SRCS)

include_directories(include)

add_executable(cal ${DIR_SRCS})