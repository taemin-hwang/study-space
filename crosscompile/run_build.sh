# !/bin/bash

mkdir -p build

pushd build
  cmake -DCMAKE_TOOLCHAIN_FILE=./etc/toolchain.linux-tegra.cmake ..
  make -j2
popd
