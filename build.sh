rm -rf ./build
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug  \
      -DCMAKE_INSTALL_PREFIX=../output ../

make& make install