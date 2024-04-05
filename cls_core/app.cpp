#include <iostream>
#include <app.h>
#include <grpc_server.h>
#include <redis_pool.h>
#include <logger.h>
#include <cls_config.h>

void cls_core::Main::run(int argc, char** argv){
    if ( 2 != argc ){
        std::cout << "Usage: cls_server config.xml\n";
        return;
    }

    cls_core::config& cfg = cls_core::config::instance().load( argv[1] );

    cls_core::logger::set_severity( cfg.get<int>("cls.debug.level") );
    cls_core::redis_pool::instance().add_conn( cfg.get<std::string>("cls.redis.conn1.ip"), cfg.get<size_t>("cls.redis.conn1.port") );
    
    gRPC::ServerImpl server_;
    server_.run( cfg.get<std::string>( "cls.grpc.business_endpoint") );
}