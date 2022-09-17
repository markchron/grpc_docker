
For this example we will be creating a client that sends a request of two numbers to the server, the server will multiply these two numbers and return the result to the client.

 gRPC is dependent on several buffer files that will be built with proto in the background by __PROTOBUF PROTOC__. You should not worry much about what these extra files do, they are simply generated and used by the program however the user never has to interact with them.

`service` creates the link between proto and C++ which will later be invoked in C++ code. `rpc sendRequest(MathRequest) returns (MathReply) {}` denotes a function that accepts a `MathRequest` and returns a `MathReply`. Both `MathRequest` and `MathReply` specify the types as well as content of the messages. The numbers in these requests _do not_ specify their values _only labeling for the proto file generation_. These messages are set by generated code stub in C++ code later. 
