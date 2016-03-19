
cmake_minimum_required(VERSION 3.0)

project("ComnetTest")

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)


include_directories(${PARENT_DIR}/comnet/include/
		    ${PARENT_DIR}/comnet/include/message/
		    ${PARENT_DIR}/libxbee3-3.0.11/include/
		    /source/
)


add_executable(comnetTest
		source/main.cpp)

target_link_libraries (comnetTest ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries (comnetTest ${PARENT_DIR}/build/linux/libNGCP_COM.a
${PARENT_DIR}/libxbee3-3.0.11/linux/libxbee.so
)



