pushd build
cmake -DCMAKE_INSTALL_BINDIR=/home/taemin.hwang/project/doipgen/build CMakeLists.txt
make
make install
cp -r opt/doipgen/bin  ../doipgen
