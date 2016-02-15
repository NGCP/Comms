
cmake_minimum_required(VERSION 3.0)

project("ProtonetTest")

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")


include_directories(protonet/include/
		    protonet/include/message/
		    /source/)


add_executable(protonetTest
		source/main.cpp)

target_link_libraries (protonetTest ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries (protonetTest ${CMAKE_CURRENT_SOURCE_DIR}/lib/libNGCP_COM.a)



