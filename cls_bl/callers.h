#ifndef _callers_h_define_
#define _callers_h_define_

#include <caller_base.h>

/**
 * @brief ����������� ���� ��� �������� ������ ������ ����������
 * ��� ���������� ������ ����������� gRPC ����� �������� ���� ����� ��� ���������, �� �������� 
 * � �� ������ ������� �� ���� ���� ��� ��������� � ������ void ServerImpl::HandleRpcs()
 */
namespace cls_bl
{

    class SetBalanceInfo final: public cls_core::CallerBase {
	    public:
            SetBalanceInfo(cls_gen::CounterRPC::AsyncService*, grpc::ServerCompletionQueue*);
            virtual cls_core::Task<void> Proceed() override;

        private:
            cls_gen::BalanceInfo request_;
            cls_gen::BalanceId reply_;
            grpc::ServerAsyncResponseWriter<cls_gen::BalanceId> responder_;
    };    

    class CreateBalance final: public cls_core::CallerBase {
	    public:
            CreateBalance(cls_gen::CounterRPC::AsyncService*, grpc::ServerCompletionQueue*);
            virtual cls_core::Task<void> Proceed() override;

        private:
            cls_gen::BusinessRequest request_;
            cls_gen::BusinessResponse reply_;
            grpc::ServerAsyncResponseWriter<cls_gen::BusinessResponse> responder_;



	        auto get_templte( std::string key ) -> cls_core::Task<std::unordered_map<std::string, std::string> >;
    };    

} // namespace cls_cmd


#endif //_callers_h_define
    
