#!/usr/bin/bash
mkdir -p opt
gRPC_HOME=`pwd`/opt
if [ -d "grpc" ]; then
  echo "grpc does exist."
else
  git clone --recurse-submodules -b v1.48.1 --depth 1 --shallow-submodules https://github.com/grpc/grpc
fi

mkdir -p grpc/cmake/build
pushd grpc/cmake/build
cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$gRPC_HOME ../..
make -j
make install
popd
