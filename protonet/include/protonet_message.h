/** @file This file was auto generated. All changes will be undone. */

#ifndef _PROTONET_MSG_H_
#define _PROTONET_MSG_H_

#include <stdint.h>
#include <stdio.h>
#include <protonet_marshal.h>

/** Global typdef struct which is the packet header used to transmit data. */
typedef struct {
   uint8_t node_src_id;
   uint8_t node_dest_id;
   uint8_t sequence_number;
   uint8_t message_ttl;
   uint16_t message_type;
   uint16_t message_length;
} proto_header_t;

/**Global typdef which hold checksum value.*/
typedef int8_t checksum_t;

/**Global enum to determine if message destination is input or output.*/
typedef enum proto_direction {
   Proto_Out = 0,
   Proto_In = 1
} proto_direction_t;

/**Global typdef struct of the data packet which contains typdef header, enum direction, and typdef checksum. */
typedef struct {
   proto_header_t header;
   proto_direction_t direction;
   uint8_t link_id;
   uint8_t data[540];
   uint16_t  tx_len;
   checksum_t checksum;
} proto_msg_t;

/**Global variable for message offset used to pack data for to transmit*/
msg_offset pack_sync(msg_offset offset);

/**Global function pack checksum*/
msg_offset pack_checksum(
   const msg_offset start,
   const msg_offset end);

/**Global function to pack header*/
msg_offset pack_header(
   proto_header_t* header,
   msg_offset offset);

/**Global function to unpack header*/
msg_offset unpack_header(
   msg_offset offset,
   proto_header_t* out_ptr);

/**Global enum auto created to id proto message type*/
typedef enum {
   Proto_Enter = 0000,
   Proto_Exit = 0001,
   Proto_Ping = 0002,
   Proto_Pong = 0003,
   Proto_Vehicle_Identification = 1000,
   Proto_Amy_Stuff = 9000,
   Proto_Vehicle_Authorization_Request = 1001,
   Proto_Vehicle_Authorization_Reply = 1002,
   Proto_Vehicle_Mode_Command = 1003,
   Proto_Vehicle_Termination_Command = 1004,
   Proto_Vehicle_Telemetry_Command = 1005,
   Proto_Vehicle_Waypoint_Command = 1006,
   Proto_Vehicle_System_Status = 2000,
   Proto_Vehicle_Inertial_State = 2001,
   Proto_Vehicle_Global_Position = 2002,
   Proto_Vehicle_Body_Sensed_State = 2003,
   Proto_Vehicle_Attitude = 2004,
   Proto_Vehicle_Ground_Relative_State = 2005,
   Proto_Payload_Bay_Command = 3000,
   Proto_Payload_Bay_Mode_Command = 3001,
   Proto_Target_Designation_Command = 5000,
   Proto_UGV_Joystick = 6000,
   Proto_UGV_Battery_Status = 6001,
} proto_msg_type_t;

#endif