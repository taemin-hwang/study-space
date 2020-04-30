# googletest

## install
git clone https://github.com/google/googletest

gtest$ cd googletest/googletest
googletest/googletest$ mkdir build
googletest/googletest$ cd build/
googletest/googletest/build$ cmake ..
-- Build files have been written to: /home/ubuntu/Desktop/gtest/googletest/googletest/build
googletest/googletest/build$ make
googletest/googletest/build$ sudo make install

NOTE: add_compile_options (--std=c++1y) in CMakeList.txt


## enable google test
vim run_build.sh
- change ENABLE_TEST to ON/OFF
