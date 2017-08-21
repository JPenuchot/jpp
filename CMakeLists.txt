cmake_minimum_required(VERSION 2.8.9)
project(Main)

#	Adding compiler optimizations

#SET(CMAKE_C_COMPILER /usr/bin/clang)
#SET(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14 -mavx2 -mfma")

#	Ckecking for packages

find_package(Boost REQUIRED)

#	Adding includes

include_directories(
	"include/"
	${Boost_LIBRARY_DIR}
)

#	Linking libraries

#link_directories(${Boost_INCLUDE_DIRS})
#link_libraries(${Boost_LIBRARIES})

#	Adding sources

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(sak ${SOURCES})
