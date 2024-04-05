#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <grpcpp/grpcpp.h>

#include <CLS.pb.h>
#include <CLS.grpc.pb.h>

class CreateBalanceRpcClient{
	std::unique_ptr<cls_gen::CounterRPC::Stub> stub_;
    public:
	CreateBalanceRpcClient( std::shared_ptr<grpc::Channel> chanel ): stub_ (cls_gen::CounterRPC::NewStub(chanel)) {}

	int64_t create( int _id ){
	    cls_gen::BusinessRequest request;
		request.set_clientrequestid(123465);
		request.mutable_context()->mutable_clientendpoint()->set_sourcecontextid( 32 );
		request.mutable_context()->mutable_clientendpoint()->set_clientsessionid( 32 );
		request.mutable_context()->set_traceid("123465");
	    request.mutable_createbalance()->set_templateid ( _id );
		request.mutable_createbalance()->set_count(1);
		request.set_handlerid(654321);

		cls_gen::BusinessResponse reply;
	    grpc::ClientContext context;
	    grpc::Status status = stub_ -> CreateBalanceCall( &context, request, &reply );

	    if ( status.ok() ) return reply.clientrequestid();
	    else std::cout << "RPC failed" << std::endl;
	    return 0;
	}
};

int main(int argc, char** argv){
/*
	if (argc != 2){
		std::cerr << "Usage: sync_create counter_id" << std::endl;
		return 1;
	}
*/
	CreateBalanceRpcClient md( grpc::CreateChannel("127.0.0.1:5678", grpc::InsecureChannelCredentials()));
	std::cout << "Create balanceInfo clientrequestid:<" << md.create( 1 ) << ">\n";

    return 0;
}
