#include <callers.h>
#include <template.h>

cls_bl::CreateBalance::CreateBalance(cls_gen::CounterRPC::AsyncService* _as, grpc::ServerCompletionQueue* _cq ):
        CallerBase(_as, _cq),
        responder_(&ctx_)
{
        service_->RequestCreateBalanceCall(&ctx_, &request_, &responder_, cq_, cq_,this);
}

cls_core::Task cls_bl::CreateBalance::Proceed() {
        if( Status::PROCESS == status_){
                //new GetBalanceTechnicalInfo(service_, cq_, redis_ );
                new CreateBalance(service_, cq_ );

                /*Оперделяем какой шаблон использовать*/              
                std::string templateId ("counterTemplate:");
                templateId += std::to_string(request_.templateid());
                templateId += ":0:0";   //FIX ME разобраться как взять актуальную версию шаблона на текущую дату или дату из запроса на создание счетчика

std::cout << "cls_bl::CreateBalance::Proceed() " << templateId << "\n";

                auto counter_template = co_await redis_ -> hgetall<std::unordered_map<std::string, std::string>>( templateId );

                for (const auto &ele : counter_template )
                        std::cout<<"HDETALL: <" << ele.first << ">\t<" << ele.second << ">" << std::endl;                        
                
                reply_.mutable_complinfo()->set_id(100);

                status_ = Status::FINISH;
                responder_.Finish(reply_, grpc::Status::OK, this);                
        }
        else{
                delete this;
        }
        co_return;
}       


