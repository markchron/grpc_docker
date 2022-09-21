#include <memory>
#include <string>
#include <thread>

#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>

#include "helloworld.grpc.pb.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;

class ServerImpl final {
    public:
    ~ServerImpl() {
        server_->Shutdown();
        // always shutdown the completion queue after the server.
        cq_ ->Shutdown();
    }

    void Run(const char* server_address) {
        ServerBuilder builder;
        // Listen on the given address without any authentication mechanism.
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        // Register 'service_' as the instance through which we'll communicate with client.
        // In this case it corresponds to an *asynchronous* service.
        builder.RegisterService(&service_);
        // Get hold of the completion queue used for the asynchronous communication
        // with the gRPC runtime.
        cq_ = builder.AddCompletionQueue();
        // Finally assemble the server.
        server_ = builder.BuildAndStart();

        std::cout << "Aysnchonous server listening on " << server_address << std::endl;

        // Proceed to the server's main loop
        HandleRpcs();
    }

    private:
    // Class encompasing the state and logic needed to server a request
    class CallData {
        public:
        // Take in the 'service' instance (in this case, representing an asynchronous server)
        // and the complete queue 'cq' used for asynchronous communication with gRPC runtime.
        CallData(helloworld::Greeter::AsyncService* service,
        ServerCompletionQueue* cq): 
        service_(service), 
        cq_(cq), 
        responder_(&ctx_),
        status_(CREATE) {
            // Invoke the serving logic right away
            Proceed();
        }

        void Proceed() {
            if (status_ == CREATE) {
                // Make this instance progress to the PROCESS state
                status_ = PROCESS;

                // As part of the initial CREATE state, we *request* that 
                // the system start processing SayHello requests. In this request,
                // 'this' acts are the tag uniquely identifying the request (so that
                // different CallData instances are serve different requests concurrently),
                // in this case, the memory address of this CallData instance.
                service_->RequestSayHello(&ctx_, &request_, &responder_, cq_, cq_, this);
            } else if (status_ == PROCESS) {
                // Spawn a new CallData instance to serve new clients while we process
                // the one for this CallData. The instance will deallocate itself as part
                // of its FINISH state.
                new CallData(service_, cq_);

                // The actual processing.
                ProcessRequest();
                // And we are done!

                // Let the gRPC runtime know we've finished, using the memory address
                // of this instance as the uniquely identifying tag for the event.
                status_ = FINISH;
                responder_.Finish(reply_, Status::OK, this);

            } else {
                GPR_ASSERT(status_ == FINISH);
                // Once in the FINISH state, deallocate ourselfs(CallData).
                delete this;
            }
        }

        private:

        void ProcessRequest(){
            // The actual processing.
            //-----------------------
            std::string prefix("Hello from Async ");
            reply_.set_message(prefix + request_.name() );
        }
        // The means of communication with the gRPC runtime for an asynchronous server.
        helloworld::Greeter::AsyncService* service_;
        // The producer-consumer queue where for asynchronous server notifications
        ServerCompletionQueue* cq_;
        // Context for the rpc, allowing to tweak aspects of it such as the use of 
        // compression, authentication, as well as to send metadata back to the client.
        ServerContext ctx_;

        // What we get from the client
        helloworld::HelloRequest request_;
        // what we send back to the client
        helloworld::HelloReply reply_;

        // The means to get back to the client
        ServerAsyncResponseWriter<helloworld::HelloReply> responder_;

        // a tiny state machine
        enum CallStatus {CREATE, PROCESS, FINISH};
        CallStatus status_;// The current serving state
    };

    // This can be run in multiple threads if needed.
    void HandleRpcs() {
        // Spawn a new CallData instance for a new client
        new CallData(& service_, cq_.get());

        void * tag; //uniquely identifies a request
        bool ok;
        while (true) {
            // Block waiting to read the next event from the completion queue.
            // The event is uniquely identified by its tag, which in this case is
            // the memory address of a CallData instance.
            // The return value of Next should always be checked. 
            // This return value tells us whether there is any kind of event or cq_
            // is shutting down.
            GPR_ASSERT(cq_->Next(&tag, &ok));
            GPR_ASSERT(ok);

            static_cast<CallData*> (tag)-> Proceed();
        }
    }


    // For asynchronous 
    std::unique_ptr<ServerCompletionQueue> cq_;
    std::unique_ptr<Server> server_;
    //
    helloworld::Greeter::AsyncService service_;
};

extern "C" {
    void RunServer(const char* address);
}

void RunServer(const char* address) {
    ServerImpl server;
    server.Run(address);
}