/* This file was autogenerated. All changes will be undone. */

/* Message: Payload_Bay_Command, ID: 3000*/

#include <protonet_marshal.h>
#include <protonet_message.h>
#include <message/PayloadBayCommand.h>

msg_offset pack_payload_bay_command(
   payload_bay_command_t* payload_bay_command,
   msg_offset offset)
{
   offset = pack_float64_t(payload_bay_command->timestamp,offset);
   offset = pack_uint32_t(payload_bay_command->payload_ID,offset);
   offset = pack_uint8_t(payload_bay_command->payload_command,offset);
   return offset;
}

msg_offset unpack_payload_bay_command(
   msg_offset offset,
   payload_bay_command_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->timestamp);
   offset = unpack_uint32_t(offset, &out_ptr->payload_ID);
   offset = unpack_uint8_t(offset, &out_ptr->payload_command);
   return offset;
}

void encode_payload_bay_command(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   payload_bay_command_t* tx_msg,
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
   msg->header.message_length = 13;
   msg->header.message_type = Proto_Payload_Bay_Command;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   offset = pack_payload_bay_command(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}