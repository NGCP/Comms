/**@file This file was autogenerated. All changes will be undone. */

/** Message: Vehicle_Identification, ID: 1000*/

#ifndef _VEHICLE_IDENTIFICATION_H_
#define _VEHICLE_IDENTIFICATION_H_

#include <protonet_marshal.h>
#include <protonet_message.h>

typedef struct {
   float64_t timestamp;
   uint16_t vehicle_ID;
   uint8_t vehicle_type;
   uint16_t owner_ID;
} vehicle_identification_t;

msg_offset pack_vehicle_identification(
   vehicle_identification_t* vehicle_identification,
   msg_offset offset);

msg_offset unpack_vehicle_identification(
   msg_offset offset,
   vehicle_identification_t* out_ptr);

void encode_vehicle_identification(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   vehicle_identification_t* tx_msg,
   proto_msg_t* msg);

#endif