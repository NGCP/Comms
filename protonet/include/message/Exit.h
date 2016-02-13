/**@file This file was autogenerated. All changes will be undone. */

/** Message: Exit, ID: 0001*/

#ifndef _EXIT_H_
#define _EXIT_H_

#include <protonet_marshal.h>
#include <protonet_message.h>

typedef struct {
   float64_t timestamp;
} exit_t;

msg_offset pack_exit(
   exit_t* exit,
   msg_offset offset);

msg_offset unpack_exit(
   msg_offset offset,
   exit_t* out_ptr);

void encode_exit(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   exit_t* tx_msg,
   proto_msg_t* msg);
#endif