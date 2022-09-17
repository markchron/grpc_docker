#include <string>

#include <grpcpp/grpcpp.h>
#include "mathcalc.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using mathcalc::MathCalc;
using mathcalc::MathRequest;
using mathcalc::MathReply;

class MathCalcClient {
    public:
    MathCalcClient(std::shared_ptr<Channel> channel) 
    : stub_(MathCalc::NewStub(channel)) {}

    int sendRequest(int a, int b) {
        MathRequest request;
        request.set_a(a);
        request.set_b(b);
        
        ClientContext context;
        MathReply reply;
        Status status = stub_ -> sendRequest(&context,request, &reply);

        if (status.ok()) {
            return reply.result();
        } else {
            std::cout << status.error_code() << ": " <<status.error_message() << std::endl;
            return -1;
        }
    }

    private:
    std::unique_ptr<MathCalc::Stub> stub_;
};

int main() {
    std::string address("0.0.0.0:50051");

    MathCalcClient client (
        grpc::CreateChannel(address, grpc::InsecureChannelCredentials())
    );
    int a = 5, b= 10;
    std::cout <<"After operate "<< a <<" @ " << b << " = "<< client.sendRequest(a, b) <<std::endl;
    return 0;
}