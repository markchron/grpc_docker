Docker container with gRPC

Provide environment to build c++ and python application with gRPC.
# Build Container
Open folder by VS Code, then open project by `Remote-Container: Open in a Container` by `Command Palette`.

Or build image by the following command
```
docker build --no-cache --pull --force-rm -t vsc-grpc -f .devcontainer/Dockerfile .
```

# Quick start
## Hello
Compile C++ application
```
cd examples/cpp/helloworld
mkdir -p cmake/build
cd cmake/build
cmake -DCMAKE_INSTALL_PREFIX=$gRPC_HOME ../..
make -j
```
Run the server by `./greeter_server`, then client by `./greeter_client`. 

The Python plugin and related code can be installed with `pip`. 
Make sure you have the Python gRPC packages installed in the environment where it's run. 
```
$ sudo apt-get install python3-pip
$ python3 -m pip install grpcio grpcio-tools
$ cd examples/python/helloworld
$ python3 greeter_client.py
```

The other combination is start up service by `python greeter_server.py` and run client by `./greeter_client` built in C++. 


