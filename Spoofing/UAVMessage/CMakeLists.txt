# UAV Spoofing cmake build.
# This is a spoof program, designed to only play as an emulator for UAV plan.
cmake_minimum_required( VERSION 2.8 )
project ( NGCP_UAV )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

get_filename_component(ROOT_DIR ${CMAKE_SOURCE_DIR}/../../../ DIRECTORY)
get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

message(${ROOT_DIR})

include_directories(${ROOT_DIR}/comnet/include/
  ${ROOT_DIR}/comnet/include/message/
  ${ROOT_DIR}/cryptopp563/include/
  ${ROOT_DIR}/libxbee3-3.0.11/include/
  ${ROOT_DIR}/Spoofing/UAVMessage/UAVMessage/
)

set(SOURCE_BUILD
  ${PARENT_DIR}/UAVMessage/UAVMessage/fromGCS.cpp
  ${PARENT_DIR}/UAVMessage/UAVMessage/main.cpp)

set(HEADER_BUILD
  ${PARENT_DIR}/UAVMessage/UAVMessage/fromGCS.h
  ${PARENT_DIR}/UAVMessage/UAVMessage/main.h)

add_executable(UAVtest
  ${SOURCE_BUILD}
  ${HEADER_BUILD})

target_link_libraries (UAVtest ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries (UAVtest ${ROOT_DIR}/build/linux/libNGCP_COM.a
${ROOT_DIR}/cryptopp563/linux/libcryptopp.a
${ROOT_DIR}/libxbee3-3.0.11/linux/libxbee.so
)



