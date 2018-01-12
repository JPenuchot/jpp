#!/bin/bash

## Managing default directories, args etc...

ORIGIN=$(pwd)

DEFAULT_CMAKE_BUILD_DIR="build"
#DEFAULT_OUTPUT_DIR="bin"

CMAKE_BUILD_DIR=${1}
OUTPUT_DIR=${2}

if [ -z "${CMAKE_BUILD_DIR}" ]; then
  CMAKE_BUILD_DIR=${DEFAULT_CMAKE_BUILD_DIR}
fi

## Making sure directories are there

mkdir -p ${CMAKE_BUILD_DIR}
mkdir -p ${CMAKE_BUILD_DIR}/release
mkdir -p ${CMAKE_BUILD_DIR}/debug

cd ${CMAKE_BUILD_DIR}/release
cmake -DCMAKE_BUILD_TYPE=Release ../..
make
objdump -dC prog > prog.asm

cd ../debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
make
objdump -dC prog > prog.asm
