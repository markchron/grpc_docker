FROM ubuntu:focal

## switching to a non-root user
#ARG USERNAME=vscode
#ARG USER_UID=1000
#ARG USER_GID=$USER_UID

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
 && apt-get install -y build-essential autoconf libtool pkg-config git cmake curl g++ unzip make \
 #&& groupadd --gid ${USER_GID} ${USERNAME} \
 #&& useradd -s /bin/bash --uid ${USER_UID} --gid ${USER_GID} -m ${USERNAME} \
 #&& apt-get install -y sudo \
 #&& echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
 #&& chmod 0440 /etc/sudoers.d/$USERNAME \
 && apt-get autoremove -y \
 && apt-get clean -y

ENV GRPC_RELEASE_TAG v1.48.1
RUN git clone --recurse-submodules -b ${GRPC_RELEASE_TAG} --depth 1 --shallow-submodules https://github.com/grpc/grpc /var/local/git/grpc \
 && mkdir -p /var/local/git/grpc/cmake/build \
 && cd /var/local/git/grpc/cmake/build \
 && cmake \
 -DBUILD_SHARED_LIBS=ON \
 -DCMAKE_INSTALL_PREFIX=/var/local/opt \
 -DCMAKE_BUILD_TYPE=Release \
 -DgRPC_INSTALL=ON \
 -DgRPC_BUILD_TESTS=OFF \
 ../.. \
 && cmake --build . --target plugins \
 && cmake --build . --target install
 
# Switch back to dialog for any adhoc use of apt-get
ENV DEBIAN_FRONTEND=
