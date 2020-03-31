#!/bin/bash

dir_name="./var/"
if [ ! -d $dir_name ]
    then mkdir $dir_name
fi

pushd build
cmake -DCMAKE_INSTALL_BINDIR=${PWD}/.. CMakeLists.txt
make
make install
popd
