#include <cls_control_rpc.h>
#include <logger.h>

cls_core::SetLogSeverity::SetLogSeverity(cls_gen::ControlRPC::AsyncService* _as, grpc::ServerCompletionQueue* _cq ):
        ControlCallerBase(_as, _cq),
        responder_(&ctx_)
{
        service_->RequestSetLogSeverity(&ctx_, &request_, &responder_, cq_, cq_,this);
}

cls_core::Task cls_core::SetLogSeverity::Proceed() {
        if( Status::PROCESS == status_){
            new SetLogSeverity(service_, cq_ );

            reply_.set_status(cls_gen::ResponceEnum::ok);

            switch(request_.level()){
                case cls_gen::SeverityEnum::trace:
                    cls_core::logger::set_severity_trace();
                    break;
                case cls_gen::SeverityEnum::debug:
                    cls_core::logger::set_severity_debug();
                    break;
                case cls_gen::SeverityEnum::info:
                    cls_core::logger::set_severity_info();
                    break;
                case cls_gen::SeverityEnum::warning:
                    cls_core::logger::set_severity_warning();
                    break;
                case cls_gen::SeverityEnum::error:
                    cls_core::logger::set_severity_error();
                    break;
                case cls_gen::SeverityEnum::fatal:
                    cls_core::logger::set_severity_fatal();
                    break;
                default:
                    LOG_FATAL << "Unknown severity log level code: <" << request_.level() <<">";
                    cls_core::logger::set_severity_error();
                    reply_.set_status(cls_gen::ResponceEnum::fail);
                    reply_.set_message("wrong severity level");
            }
            status_ = Status::FINISH;
            responder_.Finish(reply_, grpc::Status::OK, this);                
    }
        else{
                delete this;
        }        
        co_return ;
}       
