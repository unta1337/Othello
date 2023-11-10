#!/bin/bash

SOURCE_PREFIX="./src/"
BUILD_PREFIX="./.build/"

CFLAGS="-Wall -Wextra"
INCLUDE_PATH="./include"

function print_usage {
    echo "Usage:"
    echo "    ./build.sh <subcommand>"
    echo ""
    echo "<subcommand>:"
    echo "    build: build project"
    echo "    run:   run project"
    echo "    clean: remove generated files"
}

set -e

if ! [ $1 ]
then
    echo "Error: No subcommand provided"
    echo ""

    print_usage
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
else
    echo "Error: Unknown subcommand \"${1}\""
    echo ""

    print_usage
fi
