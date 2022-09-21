cmake_minimum_required(VERSION 3.15)

project(fort_grpc)

enable_language(Fortran C)
include(FortranCInterface)
FortranCInterface_VERIFY(CXX)

FortranCInterface_HEADER(
    fc_mangle.h
    SYMBOLS multiple
)

include(../../cpp/cmake/common.cmake)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
# Proto file
get_filename_component(proto_name "mathcalc.proto" ABSOLUTE)
get_filename_component(proto_path "${proto_name}" DIRECTORY)

# Generated source
set(proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/mathcalc.pb.cc")
set(proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/mathcalc.pb.h")
set(grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/mathcalc.grpc.pb.cc")
set(grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/mathcalc.grpc.pb.h")

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

set(fsrv_srcs 
    ${CMAKE_CURRENT_SOURCE_DIR}/calc_mod.f90 
    ${CMAKE_CURRENT_SOURCE_DIR}/calc_utils.f90
    ${CMAKE_CURRENT_SOURCE_DIR}/services_interface.f90
    ${CMAKE_CURRENT_SOURCE_DIR}/server.f90
    ${CMAKE_CURRENT_SOURCE_DIR}/services.cxx
)

add_executable(fserver ${fsrv_srcs})
target_link_libraries(fserver
    PUBLIC
        server_wrap
)

add_executable(client client.cxx)
target_link_libraries(client server_wrap)