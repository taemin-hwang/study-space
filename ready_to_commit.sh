# rename *.cpp to *.cc
find . -name "*.cpp" -exec bash -c 'mv "$1" "${1%.cpp}".cc' - '{}' \;

# remove a.out
find . -iname a.out -type f -exec rm -f {} \;
