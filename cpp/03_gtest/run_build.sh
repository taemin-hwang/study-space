#!/bin/bash

working_dir=${PWD}/

if [ ! -d $working_dir/build ]
    then mkdir $working_dir/build
fi

pushd build
cmake -DCMAKE_INSTALL_BINDIR=${PWD}/.. -DENABLE_TEST=ON -DWORKING_DIR=$working_dir ..
make
make install
popd
