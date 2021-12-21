#!/bin/bash

working_dir=${PWD}/

mkdir -p build

pushd build
cmake ..
make
popd
