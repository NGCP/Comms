/* This file was autogenerated. All changes will be undone. */

/* Message: Payload_Bay_Mode_Command, ID: 3001*/

#include <comnet_marshal.h>
#include <comnet_message.h>
#include <message/PayloadBayModeCommand.h>

msg_offset pack_payload_bay_mode_command(
   payload_bay_mode_command_t* payload_bay_mode_command,
   msg_offset offset)
{
   offset = pack_float64_t(payload_bay_mode_command->timestamp,offset);
   offset = pack_uint32_t(payload_bay_mode_command->payload_ID,offset);
   offset = pack_uint8_t(payload_bay_mode_command->payload_mode,offset);
   return offset;
}

msg_offset unpack_payload_bay_mode_command(
   msg_offset offset,
   payload_bay_mode_command_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->timestamp);
   offset = unpack_uint32_t(offset, &out_ptr->payload_ID);
   offset = unpack_uint8_t(offset, &out_ptr->payload_mode);
   return offset;
}

void com_payload_bay_mode_command(
   uint8_t src_id,
   uint8_t dest_id,
   payload_bay_mode_command_t* tx_msg,
   com_msg_t* msg)


{
   msg_offset start_offset, offset;
   msg->direction = Com_Out;
   start_offset = msg->data;
   offset = msg->data;
   msg->header.node_src_id = src_id;
   msg->header.node_dest_id = dest_id;
   msg->header.message_length = 13;
   msg->header.message_type = Com_Payload_Bay_Mode_Command;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   offset = pack_payload_bay_mode_command(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}