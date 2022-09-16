
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "keyvalueunary.grpc.pb.h"

#include "utils.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

// Implementation of the service. We have to implement all of the
// service's methods - these will be invoked by the runing gRPC server.
extern "C"
{
    void runserver_();
    void RunServer();
}

class KeyValServiceImpl final : public keyvalueunary::KeyValueUnary::Service {
    public:
    Status GetValue(ServerContext* context, 
    const keyvalueunary::GetValueRequest* request,
    keyvalueunary::GetValueReply* reply) override {
        std::lock_guard<std::mutex> lock(db_mutex_);

        auto it = dict_.find(request->key());
        if ( it == dict_.end() ) {
            std::string v = std::to_string(get_operates());
            reply->set_value(v);
        } else {
            reply->set_value(it->second);
        }
        return Status::OK;
    }

    Status SetValue(ServerContext* context, 
    const keyvalueunary::SetValueRequest* request, 
    keyvalueunary::SetValueReply* reply) override {
        std::lock_guard<std::mutex> lock(db_mutex_);

        dict_[request->key()] = request->value();
        reply->set_value(request->value());

        rise_operates(1);
        return Status::OK;
    } 

    Status CountValue(ServerContext* context, 
    const keyvalueunary::CountValueRequest* request,
    keyvalueunary::CountValueReply* reply) override {
        std::lock_guard<std::mutex> lock(db_mutex_);

        auto it = dict_.find(request->key());
        if ( it == dict_.end() ) {
            reply->set_count(-1);
        } else {
            reply->set_count(it->second.size());
        }
        return Status::OK;
    }

    private:
    // dict in server
    std::map<std::string, std::string> dict_;
    // Mutex serializing access to the map
    std::mutex db_mutex_;
};

void runserver_()
{
    RunServer();
}

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  KeyValServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}