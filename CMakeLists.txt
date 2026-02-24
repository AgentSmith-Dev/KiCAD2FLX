cmake_minimum_required(VERSION 3.16)
project(KiCAD2FLX LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(KiCAD2FLX
  src/main.cpp
  src/PosFile.cpp
  src/PosLine.cpp
  src/PackageMapFile.cpp
)

target_include_directories(KiCAD2FLX PRIVATE src)

enable_testing()
add_subdirectory(test)
