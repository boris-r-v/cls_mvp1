#include <grpc_server.h>
#include <callers.h>
#include <cls_control_rpc.h>
#include <logger.h>

#include <thread>

using namespace cls_core::gRPC;

ServerImpl::~ServerImpl(){
    server_ -> Shutdown();
    cq_ -> Shutdown();
}

void ServerImpl::run(){
    std::string server_address ("0.0.0.0:5678" );
    LOG_INFO << "CLS-server bind on: <" << server_address <<">";

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service_);     // Register "service_" as the instance through which we'll communicate with clients. In this case it corresponds to an *asynchronous* service.
    builder.RegisterService(&service_control_);

    cq_ = builder.AddCompletionQueue();     // Get hold of the completion queue used for the asynchronous communication with the gRPC runtime.

    server_ = builder.BuildAndStart();       // Finally assemble the server.
    isWorking = true;                       // allo service infinite loop in Handle Rpcs
    HandleRpcs();                           // Proceed to the server's main loop.
}

void ServerImpl::HandleRpcs(){
    LOG_TRACE << "HandleRpcs thread_id<"<< std::this_thread::get_id() <<">";
    new cls_bl::SetBalanceInfo(&service_, cq_.get() );
    new cls_bl::CreateBalance(&service_, cq_.get() );
    new cls_core::SetLogSeverity(&service_control_, cq_.get() );
    void* tag; 
    bool ok;
    while (isWorking) {

        GPR_ASSERT(cq_->Next(&tag, &ok));
        GPR_ASSERT(ok);

        static_cast<CallerBase*>(tag)->Proceed();   
    }
}

void ServerImpl::stop(){
    isWorking = false;
}