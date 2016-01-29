/**@file This file was autogenerated. All changes will be undone. */

/** Message: Pong, ID: 0003*/

#ifndef _PONG_H_
#define _PONG_H_

#include <protonet_marshal.h>
#include <protonet_message.h>

typedef struct {
   float64_t timestamp;
} pong_t;

msg_offset pack_pong(
   pong_t* pong,
   msg_offset offset);

msg_offset unpack_pong(
   msg_offset offset,
   pong_t* out_ptr);

void encode_pong(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   pong_t* tx_msg,
   proto_msg_t* msg);

#endif