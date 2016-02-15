/**@file This file was autogenerated. All changes will be undone. */

/** Message: Vehicle_Inertial_State, ID: 2001*/

#ifndef _VEHICLE_INERTIAL_STATE_H_
#define _VEHICLE_INERTIAL_STATE_H_

#include <protonet_marshal.h>
#include <protonet_message.h>

typedef struct {
   float64_t timestamp;
   uint16_t vehicle_ID;
   float64_t latitude;
   float64_t longitude;
   float32_t altitude;
   float32_t roll;
   float32_t pitch;
   float32_t heading;
   float32_t north_speed;
   float32_t east_speed;
   float32_t vertical_speed;
   float32_t roll_rate;
   float32_t pitch_rate;
   float32_t yaw_rate;
   float32_t north_accel;
   float32_t east_accel;
   float32_t vertical_accel;
} vehicle_inertial_state_t;

msg_offset pack_vehicle_inertial_state(
   vehicle_inertial_state_t* vehicle_inertial_state,
   msg_offset offset);

msg_offset unpack_vehicle_inertial_state(
   msg_offset offset,
   vehicle_inertial_state_t* out_ptr);

void encode_vehicle_inertial_state(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   vehicle_inertial_state_t* tx_msg,
   proto_msg_t* msg);
#endif