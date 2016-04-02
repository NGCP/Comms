/** @file This file was auto generated. All changes will be undone. */

#ifndef _COMNET_MSG_H_
#define _COMNET_MSG_H_

#include <stdint.h>
#include <stdio.h>
#include <comnet_marshal.h>

#define MAX_DATA_SIZE               540
/** Global typdef struct which is the packet header used to transmit data. */
typedef struct {
   uint8_t node_src_id;
   uint8_t node_dest_id;
   uint8_t iv[16];
   uint16_t message_type;
   uint16_t message_length	: 15,
            is_emergency 	: 1;
} com_header_t;

/**Global typdef which hold checksum value.*/
typedef int16_t checksum_t;

/** Fletcher 16 for checksum of input stream of data */
checksum_t fletcher16(msg_offset start, msg_offset end);

/**Global enum to determine if message destination is input or output.*/
typedef enum com_direction {
   Com_Out = 0,
   Com_In = 1
} com_direction_t;

/**Global typdef struct of the data packet which contains typdef header, enum direction, and typdef checksum. */
typedef struct {
   com_header_t header;
   com_direction_t direction;
   uint8_t link_id;
   uint8_t data[MAX_DATA_SIZE];
   uint16_t  tx_len;
   checksum_t checksum;
} com_msg_t;

/**Global variable for message offset used to pack data for to transmit*/
msg_offset pack_sync(msg_offset offset);

/**Global function pack checksum*/
msg_offset pack_checksum(
   const msg_offset start,
   const msg_offset end);

/** Global unpack checksum*/
msg_offset unpack_checksum(
   msg_offset offset,
   checksum_t* out_ptr);

/**Global function to pack header*/
msg_offset pack_header(
   com_header_t* header,
   msg_offset offset);

/**Global function to unpack header*/
msg_offset unpack_header(
   msg_offset offset,
   com_header_t* out_ptr);

/**Global enum auto created to id com message type*/
typedef enum {
   Com_Enter = 0000,
   Com_Exit = 0001,
   Com_Ping = 0002,
   Com_Pong = 0003,
   Com_Vehicle_Identification = 1000,
   Com_Amy_Stuff = 9000,
   Com_Vehicle_Authorization_Request = 1001,
   Com_Vehicle_Authorization_Reply = 1002,
   Com_Vehicle_Mode_Command = 1003,
   Com_Vehicle_Termination_Command = 1004,
   Com_Vehicle_Telemetry_Command = 1005,
   Com_Vehicle_Waypoint_Command = 1006,
   Com_Vehicle_System_Status = 2000,
   Com_Vehicle_Inertial_State = 2001,
   Com_Vehicle_Global_Position = 2002,
   Com_Vehicle_Body_Sensed_State = 2003,
   Com_Vehicle_Attitude = 2004,
   Com_Vehicle_Ground_Relative_State = 2005,
   Com_Payload_Bay_Command = 3000,
   Com_Payload_Bay_Mode_Command = 3001,
   Com_Target_Designation_Command = 5000,
   Com_UGV_Joystick = 6000,
   Com_UGV_Battery_Status = 6001,
} com_msg_type_t;

#endif