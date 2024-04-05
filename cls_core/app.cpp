#include <iostream>
#include <app.h>
#include <grpc_server.h>
#include <redis_pool.h>
#include <logger.h>

void cls_core::Main::run(int argc, char** argv){
    logger::set_severity_trace();
    if ( argc == 1 ) LOG_INFO <<"Usage: cls_server [number_of_redis_connections] (default: 1 - better choise)";
    if ( argc == 2) cls_core::redis_pool::instance().get( atoi(argv[1]) );
    
    gRPC::ServerImpl server_;
    server_.run();
}