#include <iostream>
#include <app.h>
#include <grpc_server.h>
#include <redis_pool.h>
#include <logger.h>

void cls_core::Main::run(int argc, char** argv){
    if ( argc == 1 ) std::cout <<"Usage cls_server [number_of_redis_connections] (default: 1 - better choise)\n";
    if (argc == 2) cls_core::redis_pool::instance().get( atoi(argv[1]) );

    logging::core::get()->set_filter( logging::trivial::severity >= logging::trivial::trace );


    gRPC::ServerImpl server_;
    server_.run();
}