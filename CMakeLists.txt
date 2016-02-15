
cmake_minimum_required(VERSION 3.0)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

project("NGCP COM")

include_directories(protonet/src/
		    protonet/src/message/
		    protonet/include/
		    protonet/include/message/)


add_library(NGCP_COM
protonet/src/mutex.cpp
protonet/src/protonet_marshal.cpp
protonet/src/thread.cpp
protonet/src/protonet.cpp
protonet/src/pqueue.cpp
protonet/src/serial.cpp
protonet/src/udp.cpp
protonet/src/datalink.cpp
protonet/src/protonet_message.cpp
protonet/src/protonet_parser.cpp
protonet/src/cond.cpp
protonet/src/protonet_protocol.cpp
protonet/src/message/Pong.cpp
protonet/src/message/VehicleGroundRelativeState.cpp
protonet/src/message/UGVJoystick.cpp
protonet/src/message/VehicleInertialState.cpp
protonet/src/message/PayloadBayModeCommand.cpp
protonet/src/message/VehicleTerminationCommand.cpp
protonet/src/message/PayloadBayCommand.cpp
protonet/src/message/VehicleBodySensedState.cpp
protonet/src/message/Exit.cpp
protonet/src/message/VehicleModeCommand.cpp
protonet/src/message/Enter.cpp
protonet/src/message/UGVBatteryStatus.cpp
protonet/src/message/VehicleAuthorizationRequest.cpp
protonet/src/message/AmyStuff.cpp
protonet/src/message/VehicleGlobalPosition.cpp
protonet/src/message/Ping.cpp
protonet/src/message/VehicleWaypointCommand.cpp
protonet/src/message/VehicleIdentification.cpp
protonet/src/message/VehicleAuthorizationReply.cpp
protonet/src/message/VehicleTelemetryCommand.cpp
protonet/src/message/VehicleSystemStatus.cpp
protonet/src/message/VehicleAttitude.cpp
protonet/src/message/TargetDesignationCommand.cpp
)
