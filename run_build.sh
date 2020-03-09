pushd build
cmake -DCMAKE_INSTALL_BINDIR=${PWD} CMakeLists.txt
make
make install
