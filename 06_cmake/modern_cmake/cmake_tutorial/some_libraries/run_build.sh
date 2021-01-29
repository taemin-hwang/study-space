
pushd build
cmake -DCMAKE_INSTALL_PREFIX=${WORKING_DIR}/out/ ..
make install
popd
