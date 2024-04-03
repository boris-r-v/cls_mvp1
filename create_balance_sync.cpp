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
	    cls_gen::CreateBalance request;
	    request.set_templateid ( _id );
		request.set_count(1);

		
		cls_gen::BalanceCompletionInfo reply;
	    grpc::ClientContext context;
	    grpc::Status status = stub_ -> CreateBalanceCall( &context, request, &reply );

	    if ( status.ok() ) return reply.complinfo().id();
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
	std::cout << "Create balanceInfo id:<" << md.create( 1 ) << ">\n";

    return 0;
}
