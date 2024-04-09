#ifndef _caller_base_define_
#define _caller_base_define_


#include <grpcpp/grpcpp.h>
#include <CLS.grpc.pb.h>
#include <CLS_srv.grpc.pb.h>
#include <redis_pool.h>
#include <coro_task.h>

namespace cls_core
{
    class CallerBase{
        public:
            CallerBase(cls_gen::CounterRPC::AsyncService*, grpc::ServerCompletionQueue*);
            ~CallerBase()=default;
            virtual Task<void> Proceed() = 0;

        protected:
            
            enum class Status { CREATE, PROCESS, FINISH };
            cls_gen::CounterRPC::AsyncService* service_;
            grpc::ServerCompletionQueue* cq_;
            grpc::ServerContext ctx_;
            Status status_; 
            redis_t redis_;
    };

    class ControlCallerBase{
        public:
            ControlCallerBase(cls_gen::ControlRPC::AsyncService*, grpc::ServerCompletionQueue*);
            ~ControlCallerBase()=default;
            virtual Task<void> Proceed() = 0;

        protected:
            
            enum class Status { CREATE, PROCESS, FINISH };
            cls_gen::ControlRPC::AsyncService* service_;
            grpc::ServerCompletionQueue* cq_;
            grpc::ServerContext ctx_;
            Status status_; 
            redis_t redis_;
    };


} // namespace cls_core

#endif // _caller_base_define_