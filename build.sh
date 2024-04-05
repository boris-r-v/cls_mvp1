#!/bin/bash


export CC=/usr/local/gcc-13.2/bin/gcc
export CXX=/usr/local/gcc-13.2/bin/g++

rm -rf build
mkdir -p build && cd build
cmake  .. && cmake --build . -j 8

