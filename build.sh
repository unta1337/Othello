#!/bin/bash

SOURCE_PREFIX="./src/"
BUILD_PREFIX="./build/"

CFLAGS="-Wall -Wextra"
INCLUDE_PATH="./include"

set -xe

mkdir -p $BUILD_PREFIX

gcc $CFLAGS -o "${BUILD_PREFIX}main" \
               "${SOURCE_PREFIX}main.c" \
               "${SOURCE_PREFIX}board.c" \
            -I $INCLUDE_PATH
