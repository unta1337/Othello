#!/bin/bash

SOURCE_PREFIX="./src/"
BUILD_PREFIX="./.build/"

CFLAGS="-Wall -Wextra"
INCLUDE_PATH="./include"

set -e

if ! [ $1 ]
then
    echo "No subcommand provided"
elif [ $1 == "build" ]
then
    mkdir -p $BUILD_PREFIX

    gcc $CFLAGS -o "${BUILD_PREFIX}main" \
                   "${SOURCE_PREFIX}main.c" \
                   "${SOURCE_PREFIX}board.c" \
                   "${SOURCE_PREFIX}consoleutil.c" \
                -I $INCLUDE_PATH
elif [ $1 == "run" ]
then
    ${BUILD_PREFIX}main
elif [ $1 == "clean" ]
then
    rm -rf ${BUILD_PREFIX}
fi
