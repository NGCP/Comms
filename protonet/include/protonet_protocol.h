/** @file This file was autogenerated. All changes will be undone. */

#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <protonet_message.h>
#include <message/Enter.h>
#include <message/Exit.h>
#include <message/Ping.h>
#include <message/Pong.h>
#include <message/VehicleIdentification.h>
#include <message/AmyStuff.h>
#include <message/VehicleAuthorizationRequest.h>
#include <message/VehicleAuthorizationReply.h>
#include <message/VehicleModeCommand.h>
#include <message/VehicleTerminationCommand.h>
#include <message/VehicleTelemetryCommand.h>
#include <message/VehicleWaypointCommand.h>
#include <message/VehicleSystemStatus.h>
#include <message/VehicleInertialState.h>
#include <message/VehicleGlobalPosition.h>
#include <message/VehicleBodySensedState.h>
#include <message/VehicleAttitude.h>
#include <message/VehicleGroundRelativeState.h>
#include <message/PayloadBayCommand.h>
#include <message/PayloadBayModeCommand.h>
#include <message/TargetDesignationCommand.h>
#include <message/UGVJoystick.h>
#include <message/UGVBatteryStatus.h>
const uint8_t MSG_DATA_OFFSET = 12;


/**Global typdef union with all message types declared as proto_msg_bug_t.
Used to easily transmit data as same variable. Could of used base class as message and created derived classes for polymorphism.
Would have lost C ability if done so.*/
typedef union {
   enter_t enter;
   exit_t exit;
   ping_t ping;
   pong_t pong;
   vehicle_identification_t vehicle_identification;
   amy_stuff_t amy_stuff;
   vehicle_authorization_request_t vehicle_authorization_request;
   vehicle_authorization_reply_t vehicle_authorization_reply;
   vehicle_mode_command_t vehicle_mode_command;
   vehicle_termination_command_t vehicle_termination_command;
   vehicle_telemetry_command_t vehicle_telemetry_command;
   vehicle_waypoint_command_t vehicle_waypoint_command;
   vehicle_system_status_t vehicle_system_status;
   vehicle_inertial_state_t vehicle_inertial_state;
   vehicle_global_position_t vehicle_global_position;
   vehicle_body_sensed_state_t vehicle_body_sensed_state;
   vehicle_attitude_t vehicle_attitude;
   vehicle_ground_relative_state_t vehicle_ground_relative_state;
   payload_bay_command_t payload_bay_command;
   payload_bay_mode_command_t payload_bay_mode_command;
   target_designation_command_t target_designation_command;
   UGV_joystick_t UGV_joystick;
   UGV_battery_status_t UGV_battery_status;
} proto_msg_buf_t;

/**Global function to unpack message with proto_msg and proto_msg_bug_t union.*/
void unpack_proto_msg_t(
   proto_msg_t* msg,
   proto_msg_buf_t* buf);

/**Global function which returns the message string description*/
char* proto_typestr(proto_msg_type_t msg_type);

#endif