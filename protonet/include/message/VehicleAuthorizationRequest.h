/**@file This file was autogenerated. All changes will be undone. */

/** Message: Vehicle_Authorization_Request, ID: 1001*/

#ifndef _VEHICLE_AUTHORIZATION_REQUEST_H_
#define _VEHICLE_AUTHORIZATION_REQUEST_H_

#include <protonet_marshal.h>
#include <protonet_message.h>

typedef struct {
   float64_t timestamp;
   uint16_t vehicle_ID;
   uint8_t link_key;
   uint8_t requested_services;
   uint8_t handover_node;
} vehicle_authorization_request_t;

msg_offset pack_vehicle_authorization_request(
   vehicle_authorization_request_t* vehicle_authorization_request,
   msg_offset offset);

msg_offset unpack_vehicle_authorization_request(
   msg_offset offset,
   vehicle_authorization_request_t* out_ptr);

void encode_vehicle_authorization_request(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   vehicle_authorization_request_t* tx_msg,
   proto_msg_t* msg);
#endif