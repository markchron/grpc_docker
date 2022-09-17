
# Windows & Docker

## Install WSL2 Linux Kernel
Check [windows version minimum requirement](https://docs.microsoft.com/en-us/windows/wsl/install#update-to-wsl-2)

To check your windows version and build number, select Windows logo key + R, type `winver`, select `OK`. 
You can update to the latest Windows version by selecting `Start > Settings > Windows Update > Check for updates`. 
If you already install WSL, check its version by open PowerShell or command prompt and run `wsl --list --verbose`.

* Update from WSL to WSL2 on Windows 10
  - Download this [WSL2 kernel update](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi) (required) 
  - Double-click the __wsl_update_x64.msi__ file and apply the update
  - Open __Start__
  - Search for __PowerShell__, run it as _administrator_.
  - Type the following command to set Windows Subsystem for Linux 2 your default architecture for new distros you'll install and press __Enter__: `wsl --set-default-version 2`
  - Type the following command to get a list of all the distros installed on your device and press __Enter__ `wsl -l -v`
  - Type the following command to convert the distro from WSL1 to WSL2 `wsl --set-version DISTRO_NAME 2` Make sure `DISTRO_NAME` is replaced by actual name of the linux distribution, for example `Ubuntu`
  - Check current wsl version by `wsl --list --verbose`

## [Install Docker Desktop on Windows](https://docs.docker.com/desktop/install/windows-install/)

	

# Package
CMake has `find_package` command


## Clone the repository (including submodules)
[`RELEASE_TAG_HERE`](https://github.com/grpc/grpc/releases)
`$ git clone --recurse-submodules -b RELEASE_TAG_HERE --depth 1 --shallow-submodules https://github.com/grpc/grpc`

## Build and install gRPC and Protocol Buffers.
The following commands build and locally install gRPC and Protocol Buffers:
```
$ cd grpc
$ mkdir -p cmake/build
$ pushd cmake/build
$ cmake -DgRPC_INSTALL=ON \
-DgRPC_BUILD_TESTS=OFF \
-DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
../..
$ make -j
$ make install
$ popd
```
It is strongly recommend to install gRPC __locally__, by set `CMAKE_INSTALL_PREFIX`, because there is no easy way to uninstall gRPC after you've installed it globally.
## Build the example
The example code is part of the `grpc` repo source
```
$ cd examples/cpp/helloword
$ mkdir -p cmake/build
$ pushd cmake/build
$ cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
$ make -j
```

# docker build

The following command build docker image on terminal. 

`docker build --no-cache --pull --force-rm -t markchron/protoc:cxx -f protoc.dockerfile .`


## Dockerfile sample with protocolbuffer
protoc.dockerfile 
```
RUN apt-get update \
&& apt-get install unzip -y \
&& wget -q -O protobuf-cpp-3.21.5.tar.gz \
https://github.com/protocolbuffers/protobuf/releases/download/v21.5/protobuf-cpp-3.21.5.tar.gz \
&& tar xzvf protobuf-cpp-3.21.5.tar.gz \
&& move path/to/protoc /usr/local/bin/protoc \
&& rm protobuf-cpp-3.21.5.tar.gz

WORKDIR /path/to/example
```
