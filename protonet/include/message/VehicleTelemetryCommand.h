/**@file This file was autogenerated. All changes will be undone. */

/** Message: Vehicle_Telemetry_Command, ID: 1005*/

#ifndef _VEHICLE_TELEMETRY_COMMAND_H_
#define _VEHICLE_TELEMETRY_COMMAND_H_

#include <protonet_marshal.h>
#include <protonet_message.h>

typedef struct {
   float64_t timestamp;
   uint8_t telemetry_select;
   uint8_t telemetry_rate;
} vehicle_telemetry_command_t;

msg_offset pack_vehicle_telemetry_command(
   vehicle_telemetry_command_t* vehicle_telemetry_command,
   msg_offset offset);

msg_offset unpack_vehicle_telemetry_command(
   msg_offset offset,
   vehicle_telemetry_command_t* out_ptr);

void encode_vehicle_telemetry_command(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   vehicle_telemetry_command_t* tx_msg,
   proto_msg_t* msg);
#endif