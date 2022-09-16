cmake_minimum_required(VERSION 3.15)

project(keyvalueunary)

enable_language(Fortran C)
include(FortranCInterface)
FortranCInterface_VERIFY(CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(../../cpp/cmake/common.cmake)

# Proto file
get_filename_component(proto_name "../../protos/keyvalueunary.proto" ABSOLUTE)
get_filename_component(proto_path "${proto_name}" DIRECTORY)

# Generated source
set(proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/keyvalueunary.pb.cc")
set(proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/keyvalueunary.pb.h")
set(grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/keyvalueunary.grpc.pb.cc")
set(grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/keyvalueunary.grpc.pb.h")

add_custom_command(
    OUTPUT "${proto_srcs}" "${proto_hdrs}" "${grpc_srcs}" "${grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
    --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
    -I "${proto_path}"
    --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
    "${proto_name}"
    DEPENDS "${proto_name}"
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(server_wrap SHARED)
target_sources(server_wrap
    PUBLIC
    interface_service.f90
    PRIVATE
    ${proto_srcs}
    ${proto_hdrs} 
    ${grpc_srcs} 
    ${grpc_hdrs}
)
target_link_libraries(server_wrap
    PUBLIC 
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF}
)

FortranCInterface_HEADER(
    fc_mangle.h
    SYMBOLS get_operates rise_operates
)

set(f90_hdrs ${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp)
set(f90_srcs 
    ${CMAKE_CURRENT_SOURCE_DIR}/keyvalue_server.f90 
    ${CMAKE_CURRENT_SOURCE_DIR}/keyvalue_mod.f90
    ${CMAKE_CURRENT_SOURCE_DIR}/keyvalue_utils.f90
    ${CMAKE_CURRENT_SOURCE_DIR}/keyvalue_service.cxx
)

add_executable(keyvalue_server ${f90_srcs})
target_link_libraries(keyvalue_server
    PUBLIC
        server_wrap
)

add_executable(keyvalue_client keyvalue_client.cxx)
target_link_libraries(keyvalue_client server_wrap)