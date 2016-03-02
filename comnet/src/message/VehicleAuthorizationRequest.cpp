/* This file was autogenerated. All changes will be undone. */

/* Message: Vehicle_Authorization_Request, ID: 1001*/

#include <comnet_marshal.h>
#include <comnet_message.h>
#include <message/VehicleAuthorizationRequest.h>

msg_offset pack_vehicle_authorization_request(
   vehicle_authorization_request_t* vehicle_authorization_request,
   msg_offset offset)
{
   offset = pack_float64_t(vehicle_authorization_request->timestamp,offset);
   offset = pack_uint16_t(vehicle_authorization_request->vehicle_ID,offset);
   offset = pack_uint8_t(vehicle_authorization_request->link_key,offset);
   offset = pack_uint8_t(vehicle_authorization_request->requested_services,offset);
   offset = pack_uint8_t(vehicle_authorization_request->handover_node,offset);
   return offset;
}

msg_offset unpack_vehicle_authorization_request(
   msg_offset offset,
   vehicle_authorization_request_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->timestamp);
   offset = unpack_uint16_t(offset, &out_ptr->vehicle_ID);
   offset = unpack_uint8_t(offset, &out_ptr->link_key);
   offset = unpack_uint8_t(offset, &out_ptr->requested_services);
   offset = unpack_uint8_t(offset, &out_ptr->handover_node);
   return offset;
}

void encode_vehicle_authorization_request(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   vehicle_authorization_request_t* tx_msg,
   com_msg_t* msg)


{
   msg_offset start_offset, offset;
   msg->direction = Com_Out;
   start_offset = msg->data;
   offset = msg->data;
   msg->header.node_src_id = src_id;
   msg->header.node_dest_id = dest_id;
   msg->header.message_ttl = msg_ttl;
   msg->header.sequence_number = seq_number;
   msg->header.message_length = 13;
   msg->header.message_type = Com_Vehicle_Authorization_Request;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   offset = pack_vehicle_authorization_request(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}