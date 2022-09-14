
# Setup a virtualenv
## Linux
```
$ sudo apt-get install python3-venv # if needed
$ python3 -m venv .grenv
$ source .grenv/bin/activate
```
## macOS
```
$ python3 -m venv .grenv
$ source .grenv/bin/activate
$ python3 -m pip install --upgrade pip
```

Or try the following (not test yet)
```
python -m pip install virtualenv
virtualenv venv
source venv/bin/activate
python -m pip install --upgrade pip
```
## Window
```
PS C:\Users\Mark\...\gRPC> python -m venv .grenv
PS C:\Users\Mark\...\gRPC> /path/to/.grenv/Scripts/Activate.ps1
PS C:\Users\Mark\...\gRPC> Set-ExecutionPolicy Unrestricted -Scope Process
```

# Example
```
# Install gRPC
$ python3 -m pip install grpcio
# Install gRPC tools
$ python3 -m pip install grpcio-tools
# Clone the repository to get the example code:
$ git clone -b v1.46.3 --depth 1 --shallow-submodules https://github.com/grpc/grpc
# Navigate to the "hello, world" Python example:
$ cd grpc/examples/python/helloworld
```


From the `examples/python/helloworld` directory, Run a gRPC application
```
# Run the server:
$ python greeter_server.py
```
From another terminal, 
#run the client:
$ python greeter_client.py
```
Congratulations! You’ve just run a client-server application with gRPC.

