#include <string>

#include <grpcpp/grpcpp.h>
#include "mathcalc.grpc.pb.h"

#include "calc_utils.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using mathcalc::MathCalc;
using mathcalc::MathRequest;
using mathcalc::MathReply;

class MathServiceImp final : public MathCalc::Service {
    Status sendRequest(
        ServerContext * context,
        const MathRequest *request,
        MathReply * reply
    ) override {
        int a = request->a();
        int b = request->b();
        int c = a * b;
        multiple(a, b, c);
        reply->set_result(c);

        return Status::OK;
    }  
};

extern "C" {
    void RunServer();
    Server* CreateServerPtr(const char *);
//    std::unique_ptr<Server> CreateServerPtr(const char *);
    void InitialServer(Server*);
}

void RunServer() {
    std::string server_address("0.0.0.0:50051");

    MathServiceImp service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << server_address << std::endl;

    server->Wait();
}

// void RunServer_() {
//     RunServer();
// }

Server* CreateServerPtr(const char *server_address) {
    MathServiceImp service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> _server(builder.BuildAndStart());
//    _server->Wait();
    _server->Start();

    Server * server = _server.get();
   return server;
}

void InitialServer(Server* server) {
    server->Wait();
}

void DeleteServerPtr(Server* server){
    delete server;
}