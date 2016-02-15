/**@file This file was autogenerated. All changes will be undone. */

/** Message: Target_Designation_Command, ID: 5000*/

#ifndef _TARGET_DESIGNATION_COMMAND_H_
#define _TARGET_DESIGNATION_COMMAND_H_

#include <protonet_marshal.h>
#include <protonet_message.h>

typedef struct {
   float64_t timestamp;
   uint16_t vehicle_ID;
   uint8_t payload_ID;
   uint8_t target_ID;
   uint8_t target_type;
   int32_t latitude;
   int32_t longitude;
   int32_t altitude;
} target_designation_command_t;

msg_offset pack_target_designation_command(
   target_designation_command_t* target_designation_command,
   msg_offset offset);

msg_offset unpack_target_designation_command(
   msg_offset offset,
   target_designation_command_t* out_ptr);

void encode_target_designation_command(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   target_designation_command_t* tx_msg,
   proto_msg_t* msg);
#endif