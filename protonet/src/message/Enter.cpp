/* This file was autogenerated. All changes will be undone. */

/* Message: Enter, ID: 0000*/

#include <protonet_marshal.h>
#include <protonet_message.h>
#include <message/Enter.h>

msg_offset pack_enter(
   enter_t* enter,
   msg_offset offset)
{
   offset = pack_float64_t(enter->timestamp,offset);
   return offset;
}

msg_offset unpack_enter(
   msg_offset offset,
   enter_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->timestamp);
   return offset;
}

void encode_enter(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   enter_t* tx_msg,
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
   msg->header.message_length = 8;
   msg->header.message_type = Proto_Enter;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   offset = pack_enter(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}