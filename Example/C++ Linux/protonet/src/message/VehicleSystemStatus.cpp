/* This file was autogenerated. All changes will be undone. */

/* Message: Vehicle_System_Status, ID: 2000*/

#include <protonet_marshal.h>
#include <protonet_message.h>
#include <message/VehicleSystemStatus.h>

msg_offset pack_vehicle_system_status(
   vehicle_system_status_t* vehicle_system_status,
   msg_offset offset)
{
   offset = pack_float64_t(vehicle_system_status->timestamp,offset);
   offset = pack_uint16_t(vehicle_system_status->vehicle_ID,offset);
   offset = pack_uint8_t(vehicle_system_status->vehicle_mode,offset);
   offset = pack_uint8_t(vehicle_system_status->vehicle_state,offset);
   return offset;
}

msg_offset unpack_vehicle_system_status(
   msg_offset offset,
   vehicle_system_status_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->timestamp);
   offset = unpack_uint16_t(offset, &out_ptr->vehicle_ID);
   offset = unpack_uint8_t(offset, &out_ptr->vehicle_mode);
   offset = unpack_uint8_t(offset, &out_ptr->vehicle_state);
   return offset;
}

void encode_vehicle_system_status(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   vehicle_system_status_t* tx_msg,
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
   msg->header.message_length = 12;
   msg->header.message_type = Proto_Vehicle_System_Status;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   offset = pack_vehicle_system_status(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}