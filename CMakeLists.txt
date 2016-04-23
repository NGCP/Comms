
cmake_minimum_required(VERSION 3.0)
project("NGCP_COM")

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

include_directories(comnet/src/
		    comnet/src/message/
		    comnet/include/
		    comnet/include/message/
		    cryptopp563/include/
		    libxbee3-3.0.11/include/)


add_library(NGCP_COM
comnet/src/pqueue.cpp
comnet/src/serial.cpp
comnet/src/comnet_parser.cpp
comnet/src/threadCom.cpp
comnet/src/comnet.cpp
comnet/src/datalink.cpp
comnet/src/comnet_message.cpp
comnet/src/cond.cpp
comnet/src/comnet_marshal.cpp
comnet/src/zigBee.cpp
comnet/src/error_handle.cpp
comnet/src/mutexCom.cpp
comnet/src/comnet_protocol.cpp
comnet/src/rand_array.cpp
comnet/src/random_numbers.cpp
comnet/src/udp.cpp
comnet/src/message/UGVJoystick.cpp
comnet/src/message/VehicleTerminationCommand.cpp
comnet/src/message/VehicleAuthorizationReply.cpp
comnet/src/message/UGVBatteryStatus.cpp
comnet/src/message/Exit.cpp
comnet/src/message/TargetDesignationCommand.cpp
comnet/src/message/VehicleGroundRelativeState.cpp
comnet/src/message/VehicleGlobalPosition.cpp
comnet/src/message/Pong.cpp
comnet/src/message/VehicleInertialState.cpp
comnet/src/message/PayloadBayCommand.cpp
comnet/src/message/VehicleIdentification.cpp
comnet/src/message/VehicleModeCommand.cpp
comnet/src/message/Ping.cpp
comnet/src/message/VehicleTelemetryCommand.cpp
comnet/src/message/VehicleAttitude.cpp
comnet/src/message/AmyStuff.cpp
comnet/src/message/VehicleAuthorizationRequest.cpp
comnet/src/message/PayloadBayModeCommand.cpp
comnet/src/message/VehicleWaypointCommand.cpp
comnet/src/message/Enter.cpp
comnet/src/message/VehicleBodySensedState.cpp
comnet/src/message/VehicleSystemStatus.cpp
)

target_link_libraries (NGCP_COM ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries (NGCP_COM ${CMAKE_CURRENT_SOURCE_DIR}/cryptopp563/linux/libcryptopp.a)

target_link_libraries (NGCP_COM ${CMAKE_CURRENT_SOURCE_DIR}/libxbee3-3.0.11/linux/libxbee.so)

