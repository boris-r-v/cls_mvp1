cmake_minimum_required(VERSION 3.21)
project(CLS_mvp_1)

#set(CMAKE_C_COMPILER /usr/local/gcc-13.2/bin/gcc )
#set(CMAKE_CXX_COMPILER /usr/local/gcc-13.2/bin/g++ )

set(CMAKE_CXX_STANDARD 23)
#add_compile_options(-Wall -Wextra -Wpedantic -std=c++23 )

find_package(Boost 1.84.0 REQUIRED COMPONENTS log headers )
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)
message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS} ")
message(STATUS "Boost library dir: ${Boost_LIBRARY_DIRS} ")
message(STATUS "Link with folowing boost libs: ${Boost_LIBRARIES} ")



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
add_library(hw_grpc_proto OBJECT proto/CLS.proto proto/CLS_srv.proto)
target_include_directories(hw_grpc_proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(hw_grpc_proto PUBLIC gRPC::grpc++)
protobuf_generate_cpp_grpc(TARGET hw_grpc_proto)

# Include generated *.pb.h files
include_directories (${CMAKE_BINARY_DIR}/proto)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
include_directories("cls_core")
include_directories("cls_bl")
include_directories("proto")



file(GLOB sources "proto/*.cpp" "cls_core/*.cpp" "cls_core/*.hpp" "main.cpp" "cls_bl/*.h" "cls_bl/*.cpp")

# Targets cls_server
add_executable(cls_server ${sources})
target_link_libraries(cls_server
    hw_grpc_proto
    ${HIREDIS_LIB}
    ${REDIS_PLUS_PLUS_LIB}
    ${Boost_LIBRARIES}
	)

# Targen some helper
foreach(_target
    set_sync_one
    set_async
    create_balance_sync
    set_severity_level
   )
  add_executable(${_target} "${_target}.cpp")
  target_link_libraries(${_target}
  hw_grpc_proto
  ${HIREDIS_LIB}
  ${REDIS_PLUS_PLUS_LIB} 
  )
endforeach()


