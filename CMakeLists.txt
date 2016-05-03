
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
comnet/src/comnet_protocol.cpp
comnet/src/threadCom.cpp
comnet/src/random_numbers.cpp
comnet/src/comnet_parser.cpp
comnet/src/pqueue.cpp
comnet/src/zigBee.cpp
comnet/src/comnet_marshal.cpp
comnet/src/serial.cpp
comnet/src/rand_array.cpp
comnet/src/udp.cpp
comnet/src/mutexCom.cpp
comnet/src/datalink.cpp
comnet/src/error_handle.cpp
comnet/src/comnet.cpp
comnet/src/cond.cpp
comnet/src/comnet_message.cpp
comnet/src/message/Pong.cpp
comnet/src/message/ROVStatusMessage.cpp
comnet/src/message/AirVehicleGroundRelativeState.cpp
comnet/src/message/CommunicationsPayloadCommand.cpp
comnet/src/message/PayloadOperatingStatus.cpp
comnet/src/message/UAVHeading.cpp
comnet/src/message/VehicleInertialState.cpp
comnet/src/message/ConnectionRequest.cpp
comnet/src/message/UAVCollisionAvodianceStatus.cpp
comnet/src/message/UAVBattery.cpp
comnet/src/message/VehicleJoystickCommand.cpp
comnet/src/message/PayloadBayModeCommand.cpp
comnet/src/message/PayloadDataRecorderStatus.cpp
comnet/src/message/VehicleTerminationCommand.cpp
comnet/src/message/RawData.cpp
comnet/src/message/PayloadBayCommand.cpp
comnet/src/message/VehicleBodySensedState.cpp
comnet/src/message/UUVStatus.cpp
comnet/src/message/Exit.cpp
comnet/src/message/PayloadDataRecorderCommand.cpp
comnet/src/message/PayloadOperationCommand.cpp
comnet/src/message/VehicleModeCommand.cpp
comnet/src/message/TargetAcknowledgement.cpp
comnet/src/message/Enter.cpp
comnet/src/message/TargetStatus.cpp
comnet/src/message/CommunicationsPayloadConfigurationCommand.cpp
comnet/src/message/VehicleAuthorizationRequest.cpp
comnet/src/message/UAVLocation.cpp
comnet/src/message/VehicleGlobalPosition.cpp
comnet/src/message/Ping.cpp
comnet/src/message/VehicleIdentification.cpp
comnet/src/message/CommunicationsPayloadStatus.cpp
comnet/src/message/UAVCollisionAvodianceMessage.cpp
comnet/src/message/VehicleAuthorizationReply.cpp
comnet/src/message/VehicleTelemetryCommand.cpp
comnet/src/message/VehicleSystemStatus.cpp
comnet/src/message/ConnectionReply.cpp
comnet/src/message/VehicleAttitude.cpp
comnet/src/message/UAVMissionStatus.cpp
comnet/src/message/UAVSpeed.cpp
comnet/src/message/PayloadBayStatus.cpp
)

target_link_libraries (NGCP_COM ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries (NGCP_COM ${CMAKE_CURRENT_SOURCE_DIR}/cryptopp563/osx/libcryptopp.a)

target_link_libraries (NGCP_COM ${CMAKE_CURRENT_SOURCE_DIR}/libxbee3-3.0.11/osx/libxbee.so)

