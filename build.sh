#!/bin/bash

## Managing default directories, args etc...

ORIGIN=$(pwd)

DEFAULT_CMAKE_BUILD_DIR=".build"
DEFAULT_OUTPUT_DIR="bin"

CMAKE_BUILD_DIR=${1}
OUTPUT_DIR=${2}

if [ -z "${CMAKE_BUILD_DIR}" ]; then
	CMAKE_BUILD_DIR=${DEFAULT_CMAKE_BUILD_DIR}
fi

if [ -z "${OUTPUT_DIR}" ]; then
	OUTPUT_DIR=${DEFAULT_OUTPUT_DIR}
fi

## Making sure directories are there

if [ ! -d "$CMAKE_BUILD_DIR" ]; then
  mkdir ${CMAKE_BUILD_DIR}
fi

if [ ! -d "$OUTPUT_DIR" ]; then
  mkdir ${OUTPUT_DIR}
fi



cd ${CMAKE_BUILD_DIR}
cmake ..
make

objdump -dC prog > prog.asm

mv prog ${ORIGIN}/${OUTPUT_DIR}
mv prog.asm ${ORIGIN}/${OUTPUT_DIR}
