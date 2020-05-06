#!/bin/bash

working_dir=${PWD}/

pushd build
cmake -DCMAKE_INSTALL_BINDIR=${PWD}/.. -DENABLE_TEST=ON -DWORKING_DIR=$working_dir ..
make
make install
popd
