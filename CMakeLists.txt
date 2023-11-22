cmake_minimum_required(VERSION 3.26)
project(cppproj2)

set(CMAKE_CXX_STANDARD 17)

add_executable(cppproj2 main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "F:\\SFML\\lib\\cmake\\SFML")

target_link_libraries(cppproj2 sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.6.1 REQUIRED graphics network audio window system)