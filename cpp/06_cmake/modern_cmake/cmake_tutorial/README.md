
## Relationship between the 3 packages
MyApplication --depends--> MyLibraries --depends--> SomeLibraries

## Access a CMake project from another CMake project
In general, there are three ways to access a CMake project from another Cmake project
1) subdirectory
2) exported build directories
3) importing prebuild package which is already installed

In this post, we will select third option.
Hence, the three packages are not in the same CMake tree.

## CMAKE_INSTALL_PREFIX
cmake -DCMAKE_INSTALL_PREFIX=${PWD}/out/ ..
