#include <callers.h>
#include <template.h>
#include <logger.h>

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
                std::string key ("counterTemplate:");
                key += std::to_string(request_.templateid());
                key += ":0:0";   //FIX ME разобраться как взять актуальную версию шаблона на текущую дату или дату из запроса на создание счетчика

                LOG_TRACE << "cls_bl::CreateBalance::Proceed() " << key ;
                auto counter = co_await redis_ -> hgetall<std::unordered_map<std::string, std::string>>( key );
                for (const auto &ele : counter )
                        LOG_TRACE <<"TemplateValue: <" << ele.first << ">\t<" << ele.second << ">" ;                        
                
                /*Populate counter data*/
                counter["dateFrom"] = "some value";
                counter["dateTo"] = "some value";
                counter["value"] = "some value";
                counter["reservedValue"] = "some value";
                counter["isPeriodic"] = "some value";
                counter["metaVersion"] = "some value";
                counter["modifyTS"] = "some value";
                counter["templateVersion"] = "some value";
                counter["templateId"] = "some value";
                counter["activationCodeId"] = "some value";
                counter["classificstionAttrs"] = "some attr1,aome attr2, some attr3, some attr4, etc";
                counter["owner"] = "some value";
                counter["profileId"] = "some value";
                counter["flags"] = "some flag";
                counter["occurOnReserve"] = "some value";
                counter["occurOnCommit"] = "some value";
                counter["occurOnEOS"] = "some value";
                counter["occurOnGet"] = "some value";
                counter["occurOnLifeCycle"] = "some value";
                counter["initValue"] = "some value";
                counter["IRPAamount"] = "some value";
                counter["valueHistoryDateFrom"] = "some value";
                counter["valueHistory"] = "some value";
                counter["numBussinesAttrs"] = "3";
                counter["bussinesAttr1"] = "some attr";
                counter["bussinesAttr2"] = "some attr";
                counter["bussinesAttr3"] = "some attr";
                counter["numAutoRefils"] = "4";
                counter["autoRefil1"] = "some refil";
                counter["autoRefil2"] = "some refil";
                counter["autoRefil3"] = "some refil";
                counter["autoRefil4"] = "some refil";
                key = "counter_id_seq";
                co_await redis_ -> command<long long>("incr", key);
                std::string counter_id = "counter:";
                counter_id += co_await redis_ -> command<std::string>("get", key);
                LOG_TRACE <<"new counter have id: <" << counter_id << ">";

                auto val = co_await redis_ -> hset(counter_id, counter.begin(), counter.end() );



                reply_.mutable_complinfo()->set_id(100);
                status_ = Status::FINISH;
                responder_.Finish(reply_, grpc::Status::OK, this);                
        }
        else{
                delete this;
        }
        co_return;
}       


