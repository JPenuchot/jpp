cmake_minimum_required(VERSION 2.8.9)
project(Main)

# Adding compiler optimizations

#SET(CMAKE_C_COMPILER /usr/bin/clang)
#SET(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
  -std=c++14")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
  -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} \
  -O3 -mavx2 -mfma -DNDEBUG")

# Ckecking for packages

find_package(Boost REQUIRED)
find_package(Boost.SIMD REQUIRED)

# Adding includes

include_directories(
  "include/"
  "../include/"
  ${Boost_INCLUDE_DIRS}
  ${Boost.SIMD_INCLUDE_DIRS}
)

# Linking libraries

#link_directories(${Boost_INCLUDE_DIRS})
#link_libraries(${Boost_LIBRARIES})

# Adding sources

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(prog ${SOURCES})
