#!/bin/bash

working_dir=${PWD}/

dir_name="./var/"
if [ ! -d $dir_name ]
    then mkdir $dir_name
fi

pushd build
cmake -DCMAKE_INSTALL_BINDIR=${PWD}/.. -DENABLE_TEST=OFF -DWORKING_DIR=$working_dir ..
make
make install
popd
