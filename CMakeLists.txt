cmake_minimum_required(VERSION 3.15)
project(Kipp)

set(CMAKE_CXX_STANDARD 17)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

include_directories(include)

add_subdirectory(src)

target_link_libraries(Kipp stdc++fs)