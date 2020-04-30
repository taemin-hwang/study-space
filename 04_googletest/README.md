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


## enable/disable test
vim run_build.sh
- change ENABLE_TEST to ON/OFF

## report
./run_test.sh

### precondition
junit2html
- pip install junit2html

### report xml
<test file> --gtest_output=xml:result.xml
- test-googletest --gtest_output=xml:result.xml

### convert xml to html
junit2html result.xml output.html
