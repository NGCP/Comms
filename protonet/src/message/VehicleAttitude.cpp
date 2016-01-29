/* This file was autogenerated. All changes will be undone. */

/* Message: Vehicle_Attitude, ID: 2004*/

#include <protonet_marshal.h>
#include <protonet_message.h>
#include <message/VehicleAttitude.h>

msg_offset pack_vehicle_attitude(
   vehicle_attitude_t* vehicle_attitude,
   msg_offset offset)
{
   offset = pack_float64_t(vehicle_attitude->timestamp,offset);
   offset = pack_uint16_t(vehicle_attitude->vehicle_ID,offset);
   offset = pack_float32_t(vehicle_attitude->roll,offset);
   offset = pack_float32_t(vehicle_attitude->pitch,offset);
   offset = pack_float32_t(vehicle_attitude->yaw,offset);
   return offset;
}

msg_offset unpack_vehicle_attitude(
   msg_offset offset,
   vehicle_attitude_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->timestamp);
   offset = unpack_uint16_t(offset, &out_ptr->vehicle_ID);
   offset = unpack_float32_t(offset, &out_ptr->roll);
   offset = unpack_float32_t(offset, &out_ptr->pitch);
   offset = unpack_float32_t(offset, &out_ptr->yaw);
   return offset;
}

void encode_vehicle_attitude(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   vehicle_attitude_t* tx_msg,
   proto_msg_t* msg)
{
   msg_offset start_offset, offset;
   msg->direction = Proto_Out;
   start_offset = msg->data;
   offset = msg->data;
   msg->header.node_src_id = src_id;
   msg->header.node_dest_id = dest_id;
   msg->header.message_ttl = msg_ttl;
   msg->header.sequence_number = seq_number;
   msg->header.message_length = 22;
   msg->header.message_type = Proto_Vehicle_Attitude;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);
   offset = pack_vehicle_attitude(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}