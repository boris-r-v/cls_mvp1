cmake_minimum_required(VERSION 3.21)

project(CLS_mvp_1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include(CPM)
include(ProtobufGenerateGrpc)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_DIR} (Version ${gRPC_VERSION})")


#Redis libs
find_library(HIREDIS_LIB hiredis)
find_library(REDIS_PLUS_PLUS_LIB redis++)
find_package(Threads REQUIRED)

# Proto file
add_library(hw_grpc_proto OBJECT proto/CLS.proto)
target_include_directories(hw_grpc_proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(hw_grpc_proto PUBLIC gRPC::grpc++)
protobuf_generate_cpp_grpc(TARGET hw_grpc_proto)

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
include_directories("cls_core")
include_directories("cls_bl")
include_directories (${CMAKE_BINARY_DIR}/proto)


file(GLOB sources "cls_core/*.h" "cls_core/*.cpp" "cls_core/*.hpp" "main.cpp" "cls_bl/*.h" "cls_bl/*.cpp")

# Targets greeter_[async_](client|server)
add_executable(cls_server ${sources})
target_link_libraries(cls_server
    hw_grpc_proto
    ${HIREDIS_LIB}
    ${REDIS_PLUS_PLUS_LIB} )


foreach(_target
    set_sync_one
    set_async
   )
  add_executable(${_target} "${_target}.cpp")
  target_link_libraries(${_target}
  hw_grpc_proto
  ${HIREDIS_LIB}
  ${REDIS_PLUS_PLUS_LIB} )
endforeach()


