cmake_minimum_required(VERSION 3.00)
project(Wizard Wars)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_Wars_COMPILER CPP)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/cmake_modules")
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIRECTORY}/source/*.cpp)

find_package(Allegro)
find_package(Boost)
find_package(Asio)

add_executable(game ${SOURCE_FILES})