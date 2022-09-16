#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <grpcpp/grpcpp.h>

#include "keyvalueunary.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;


using keyvalueunary::KeyValueUnary;

class KeyValueUnaryClient {
    public:
    KeyValueUnaryClient(std::shared_ptr<Channel> channel) 
    : stub_(KeyValueUnary::NewStub(channel)) {}

    //
    std::string GetValue(const std::string &key) {
        ClientContext context;
        keyvalueunary::GetValueRequest request;
        request.set_key(key);
        keyvalueunary::GetValueReply reply;

        Status status = stub_ ->GetValue(&context, request, &reply);

        if (status.ok()) {
            return reply.value();
        } else {
            std::cout << status.error_code() << ": "<< status.error_message() << std::endl;
            return "RPC failed GetValue";
        }
    }

    void SetValue(const std::string& key, const std::string& value) {
        ClientContext context;
        keyvalueunary::SetValueRequest request;
        request.set_key(key);
        request.set_value(value);

        keyvalueunary::SetValueReply reply;
        Status status = stub_->SetValue(&context, request, &reply);
        if (status.ok()) {
          //  std::cout << reply.value() << std::endl;
        } else {
            std::cout << "SetValue error: " << status.error_code() <<": " << status.error_message()<<std::endl;
        }
        return;
    }

    int CountValue(const std::string& key) {
        ClientContext context;

        keyvalueunary::CountValueRequest request;
        request.set_key(key);
        keyvalueunary::CountValueReply reply;
        Status status = stub_ ->CountValue(&context, request, &reply);

        
        if (status.ok()) {
            return reply.count();
        } else {
            std::cout << "CountValue" << status.error_code() <<": " << status.error_message() << std::endl;
            return 0;
        }
    }

    private:
    std::unique_ptr<KeyValueUnary::Stub> stub_;
};

int main(int argc, char** argv) {

  std::string target_str;
  std::string arg_str("--target");
  if (argc > 1) {
    std::string arg_val = argv[1];
    size_t start_pos = arg_val.find(arg_str);
    if (start_pos != std::string::npos) {
      start_pos += arg_str.size();
      if (arg_val[start_pos] == '=') {
        target_str = arg_val.substr(start_pos + 1);
      } else {
        std::cout << "The only correct argument syntax is --target="
                  << std::endl;
        return 0;
      }
    } else {
      std::cout << "The only acceptable argument is --target=" << std::endl;
      return 0;
    }
  } else {
    target_str = "localhost:50051";
  }


  KeyValueUnaryClient client(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

  client.SetValue("foo", "bar");
  client.SetValue("baz", "anacoda is here");

  std::cout << "operate in utils_mod = " << client.GetValue("func") << std::endl;
  std::cout << "GetValue(foo) = " << client.GetValue("foo") << std::endl;
  std::cout << "Count(baz) = " << client.CountValue("baz")<<std::endl;
  return 0;
}