pushd build
cmake -DCMAKE_INSTALL_BINDIR=${PWD}/.. ..
make
make install
popd
