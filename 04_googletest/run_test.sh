#!/bin/bash

working_dir=${PWD}/
opt_dir="$working_dir/opt/"
date_=$(date "+%Y-%m-%d")
time_=$(date "+_%H-%M")

if [ ! -d $opt_dir ]
    then ./run_build.sh
fi

pushd $opt_dir
./test-googletest --gtest_output=xml:result.xml
junit2html result.xml gtest_$date_$time_.html
find . -name "result.xml" -delete
popd
