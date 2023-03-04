cmake_minimum_required(VERSION 3.2)

project(LogicalClocks)

include(./cmake/common.cmake)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Proto file
get_filename_component(lc_proto "./logicalClock.proto" ABSOLUTE)
get_filename_component(lc_proto_path "${lc_proto}" PATH)

# Generated sources
set(lc_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/logicalClock.pb.cc")
set(rlc_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/logicalClock.pb.h")
set(lc_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/logicalClock.grpc.pb.cc")
set(lc_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/logicalClock.grpc.pb.h")
add_custom_command(
      OUTPUT "${lc_proto_srcs}" "${cs_proto_hdrs}" "${lc_grpc_srcs}" "${lc_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${lc_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${lc_proto}"
      DEPENDS "${lc_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# hw_grpc_proto
add_library(lc_grpc_proto
  ${lc_grpc_srcs}
  ${lc_grpc_hdrs}
  ${lc_proto_srcs}
  ${cs_proto_hdrs})
target_link_libraries(lc_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})


add_executable(logicalClock ./main.cc)
target_link_libraries(logicalClock
    lc_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})