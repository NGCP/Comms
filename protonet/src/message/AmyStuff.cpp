/* This file was autogenerated. All changes will be undone. */

/* Message: Amy_Stuff, ID: 9000*/

#include <protonet_marshal.h>
#include <protonet_message.h>
#include <message/AmyStuff.h>

msg_offset pack_amy_stuff(
   amy_stuff_t* amy_stuff,
   msg_offset offset)
{
   offset = pack_float64_t(amy_stuff->hello,offset);
   return offset;
}

msg_offset unpack_amy_stuff(
   msg_offset offset,
   amy_stuff_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->hello);
   return offset;
}

void encode_amy_stuff(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   amy_stuff_t* tx_msg,
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
   msg->header.message_type = Proto_Amy_Stuff;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);
   offset = pack_amy_stuff(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}