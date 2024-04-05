#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <grpcpp/grpcpp.h>

#include <CLS_srv.pb.h>
#include <CLS_srv.grpc.pb.h>

class RpcClient{
	std::unique_ptr<cls_gen::ControlRPC::Stub> stub_;
    public:
	RpcClient( std::shared_ptr<grpc::Channel> chanel ): stub_ (cls_gen::ControlRPC::NewStub(chanel)) {}

	int64_t send( int id ){
	    cls_gen::SetSeverityRequest request;
		request.set_level( (cls_gen::SeverityEnum)id );

		
		cls_gen::ControlResponce reply;
	    grpc::ClientContext context;
	    grpc::Status status = stub_ -> SetLogSeverity( &context, request, &reply );

	    if ( status.ok() ) return reply.status();
	    else std::cout << "RPC failed" << std::endl;
	    return 0;
	}
};

int main(int argc, char** argv){

	if (argc != 2){
		std::cerr << "Usage: "<< argv[0] << " severity_level" << std::endl;
		return 1;
	}

	RpcClient md( grpc::CreateChannel("127.0.0.1:5678", grpc::InsecureChannelCredentials()));
	std::cout << "Create balanceInfo id:<" << md.send( atoi( argv[1] ) ) << ">\n";

    return 0;
}
