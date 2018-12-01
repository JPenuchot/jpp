cmake_minimum_required(VERSION 2.8.9)
project(prog)

# Adding compiler optimizations

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -march=native \
  -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

find_package(Boost REQUIRED)

# Adding includes


include_directories("include/")
include_directories(${Boost_INCLUDE_DIRS})

# Adding sources

file(GLOB_RECURSE SOURCES "example/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
