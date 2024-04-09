#pragma once
#include <caller_base.h>

namespace cls_core{

    class SetLogSeverity final: public cls_core::ControlCallerBase {
        public:
            SetLogSeverity(cls_gen::ControlRPC::AsyncService*, grpc::ServerCompletionQueue*);
            virtual cls_core::Task<void> Proceed() override;

        private:
            cls_gen::SetSeverityRequest request_;
            cls_gen::ControlResponce reply_;
            grpc::ServerAsyncResponseWriter<cls_gen::ControlResponce> responder_;
        };    

}