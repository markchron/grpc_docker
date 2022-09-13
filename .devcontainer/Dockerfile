FROM ubuntu:focal

# switching to a non-root user
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

ENV DEBIAN_FRONTEND=noninteractive
RUN
RUN apt-get update \
 && apt-get install -y \
 build-essential autoconf git pkg-config \
 automake libtool curl cmake make g++ unzip \
 && groupadd --gid ${USER_GID} ${USERNAME} \
 && useradd -s /bin/bash --uid ${USER_UID} --gid ${USER_GID} -m ${USERNAME} \
 # [可选] 添加sudo命令
 && apt-get install -y sudo \
 # 将新创建的非root用户添加到sudoers
 && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
 && chmod 0440 /etc/sudoers.d/$USERNAME \
 && apt-get autoremove -y \
 && apt-get clean -y \
 && rm -rf /var/lib/apt/lists/*

#ENV GRPC_RELEASE_TAG v1.48.1
#RUN git clone --recurse-submodules -b ${GRPC_RELEASE_TAG} \
#--depth 1 --shalow-submodules https://github.com/grpc/grpc \
#&& mkdir -p /home/vscode/opt \
#&& mkdir -p cmake/build \
#&& pushd cmake/build \
#&& cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/home/vscode/opt ../.. \
#&& make -j \
#&& make install \
#&& popd

# Switch back to dialog for any adhoc use of apt-get
ENV DEBIAN_FRONTEND=