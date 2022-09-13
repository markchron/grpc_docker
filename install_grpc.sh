#!/usr/bin/bash
git clone --recurse-submodules -b v1.48.1 --depth 1 --shallow-submodules https://github.com/grpc/grpc
mkdir -p opt
mkdir -p cmake/build
pushd cmake/build
cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=./opt ../..
make -j 
make install
popd