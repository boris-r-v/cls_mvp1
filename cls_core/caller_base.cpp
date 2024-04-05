#include <caller_base.h>

cls_core::CallerBase::CallerBase( cls_gen::CounterRPC::AsyncService* service, grpc::ServerCompletionQueue* cq )
        :service_( service )
        ,cq_( cq )
        ,status_( Status::PROCESS )
        ,redis_(cls_core::redis_pool::instance().get()) 
{}

cls_core::ControlCallerBase::ControlCallerBase( cls_gen::ControlRPC::AsyncService* service, grpc::ServerCompletionQueue* cq )
        :service_( service )
        ,cq_( cq )
        ,status_( Status::PROCESS )
        ,redis_(cls_core::redis_pool::instance().get()) 
{}