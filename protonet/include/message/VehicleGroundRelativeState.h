/**@file This file was autogenerated. All changes will be undone. */

/** Message: Vehicle_Ground_Relative_State, ID: 2005*/

#ifndef _VEHICLE_GROUND_RELATIVE_STATE_H_
#define _VEHICLE_GROUND_RELATIVE_STATE_H_

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
   float32_t angle_of_attack;
   float32_t angle_of_sideslip;
   float32_t true_airspeed;
   float32_t indicated_airspeed;
   float32_t north_wind_speed;
   float32_t east_wind_speed;
   float32_t north_ground_speed;
   float32_t east_ground_speed;
   float32_t barometric_pressure;
   float32_t barometric_altitude;
} vehicle_ground_relative_state_t;

msg_offset pack_vehicle_ground_relative_state(
   vehicle_ground_relative_state_t* vehicle_ground_relative_state,
   msg_offset offset);

msg_offset unpack_vehicle_ground_relative_state(
   msg_offset offset,
   vehicle_ground_relative_state_t* out_ptr);

void encode_vehicle_ground_relative_state(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   vehicle_ground_relative_state_t* tx_msg,
   proto_msg_t* msg,
   uint8_t keyArr[]);//key for encryption CryptoPP

#endif