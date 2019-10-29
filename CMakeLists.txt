# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.1)

# project name
project(lucia)

# creates the variable EXEC and sets it to hello
set(EXEC lucia)

set(CMAKE_BUILD_TYPE Release)

# set the C++11 standard
set(CMAKE_CXX_STANDARD 11)

# I../includes
include_directories(src)

find_package(ASSIMP REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIRS})

# puts all .cpp files inside src to the SOURCES variable
file(GLOB_RECURSE SOURCES src/*.cpp)


# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(${EXEC} ${SOURCES})