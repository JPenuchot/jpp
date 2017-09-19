cmake_minimum_required(VERSION 2.8.9)
project(Main)

#	Adding compiler optimizations

#SET(CMAKE_C_COMPILER /usr/bin/clang)
#SET(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14 -mavx2 -mfma -DNDEBUG")

#	Ckecking for packages

find_package(Boost REQUIRED)
find_package(Boost.SIMD REQUIRED)

#	Adding includes

include_directories(
	"include/"
	${Boost_INCLUDE_DIRS}
	${Boost.SIMD_INCLUDE_DIRS}
)

#	Linking libraries

#link_directories(${Boost_INCLUDE_DIRS})
#link_libraries(${Boost_LIBRARIES})

#	Adding sources

file(GLOB_RECURSE SOURCES "example/*.cpp")
add_executable(prog ${SOURCES})
