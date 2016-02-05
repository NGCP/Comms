/**@file This file was autogenerated. All changes will be undone. */

/** Message: Vehicle_Authorization_Reply, ID: 1002*/

#ifndef _VEHICLE_AUTHORIZATION_REPLY_H_
#define _VEHICLE_AUTHORIZATION_REPLY_H_

#include <protonet_marshal.h>
#include <protonet_message.h>

#include"random_numbers.h"
#include "aes.h"
using CryptoPP::AES;
#include "ccm.h"
using CryptoPP::CFB_Mode;
typedef struct {
   float64_t timestamp;
   uint16_t vehicle_ID;
   uint8_t vehicle_type;
   uint8_t authorized_services;
   uint8_t granted_services;
} vehicle_authorization_reply_t;

msg_offset pack_vehicle_authorization_reply(
   vehicle_authorization_reply_t* vehicle_authorization_reply,
   msg_offset offset);

msg_offset unpack_vehicle_authorization_reply(
   msg_offset offset,
   vehicle_authorization_reply_t* out_ptr);

void encode_vehicle_authorization_reply(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   vehicle_authorization_reply_t* tx_msg,
   proto_msg_t* msg,
   uint8_t keyArr[]);//key for encryption CryptoPP

#endif