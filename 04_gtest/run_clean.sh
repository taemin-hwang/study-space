#!/bin/bash

dir_name="./opt/"
if [ -d $dir_name ]
    then rm -rf $dir_name
fi

pushd build
find . ! \( -name "run_cmake.sh" -o -name "test" \) -delete
popd
