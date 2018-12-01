#!/bin/bash

## Managing default directories, args etc...

ORIGIN=$(pwd)
CMAKE_BUILD_DIR="bin"
EXEC_NAME="prog"

function build_for_config
{
  mkdir -p ${ORIGIN}/${CMAKE_BUILD_DIR}/$1
  cd ${ORIGIN}/${CMAKE_BUILD_DIR}/$1
  cmake -DCMAKE_BUILD_TYPE=$1 -G Ninja ${ORIGIN}
  ninja
  objdump -dC ${EXEC_NAME} > ${EXEC_NAME}.asm
}

## BUILD

build_for_config Release
build_for_config Debug
