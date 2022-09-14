cmake_minimum_required(VERSION 3.8)

project(HelloWorld)
enable_language(CXX Fortran)

include(FortranCInterface)
# C and Fortran
#FortranCInterface_VERIFY()
# C++ and Fortran
FortranCInterface_VERIFY(CXX)

include(../../cpp/cmake/common.cmake)

# Proto file
get_filename_component(hw_proto "../../protos/helloworld.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
set(cxx_path "${CMAKE_CURRENT_SOURCE_DIR}/../../cpp/helloworld/")
set(hw_proto_srcs "${cxx_path}/helloworld.pb.cc")
set(hw_proto_hdrs "${cxx_path}/helloworld.pb.h")
set(hw_grpc_srcs "${cxx_path}/helloworld.grpc.pb.cc")
set(hw_grpc_hdrs "${cxx_path}/helloworld.grpc.pb.h")
add_custom_command(
      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
      DEPENDS "${hw_proto}")

# Include generated *.pb.h files
message(STATUS "${cxx_path}")
include_directories("${cxx_path}")

# hw_grpc_proto
add_library(hw_grpc_proto
  ${hw_grpc_srcs}
  ${hw_grpc_hdrs}
  ${hw_proto_srcs}
  ${hw_proto_hdrs})
target_link_libraries(hw_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})


set(hw_fort_srcs 
    ${CMAKE_CURRENT_SOURCE_DIR}/greeter_interface.f90
    ${CMAKE_CURRENT_SOURCE_DIR}/greeter_server.f90
    ${CMAKE_CURRENT_SOURCE_DIR}/greeter_service.cxx
    )

add_executable(server_fort ${hw_fort_srcs})
target_link_libraries(server_fort hw_grpc_proto ${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})