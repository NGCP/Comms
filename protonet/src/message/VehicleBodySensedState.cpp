/* This file was autogenerated. All changes will be undone. */

/* Message: Vehicle_Body_Sensed_State, ID: 2003*/

#include <protonet_marshal.h>
#include <protonet_message.h>
#include <message/VehicleBodySensedState.h>

msg_offset pack_vehicle_body_sensed_state(
   vehicle_body_sensed_state_t* vehicle_body_sensed_state,
   msg_offset offset)
{
   offset = pack_float64_t(vehicle_body_sensed_state->timestamp,offset);
   offset = pack_uint16_t(vehicle_body_sensed_state->vehicle_ID,offset);
   offset = pack_int16_t(vehicle_body_sensed_state->x_accel,offset);
   offset = pack_int16_t(vehicle_body_sensed_state->y_accel,offset);
   offset = pack_int16_t(vehicle_body_sensed_state->z_accel,offset);
   offset = pack_int16_t(vehicle_body_sensed_state->roll_rate,offset);
   offset = pack_int16_t(vehicle_body_sensed_state->pitch_rate,offset);
   offset = pack_int16_t(vehicle_body_sensed_state->yaw_rate,offset);
   return offset;
}

msg_offset unpack_vehicle_body_sensed_state(
   msg_offset offset,
   vehicle_body_sensed_state_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->timestamp);
   offset = unpack_uint16_t(offset, &out_ptr->vehicle_ID);
   offset = unpack_int16_t(offset, &out_ptr->x_accel);
   offset = unpack_int16_t(offset, &out_ptr->y_accel);
   offset = unpack_int16_t(offset, &out_ptr->z_accel);
   offset = unpack_int16_t(offset, &out_ptr->roll_rate);
   offset = unpack_int16_t(offset, &out_ptr->pitch_rate);
   offset = unpack_int16_t(offset, &out_ptr->yaw_rate);
   return offset;
}

void encode_vehicle_body_sensed_state(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   vehicle_body_sensed_state_t* tx_msg,
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
   msg->header.message_length = 22;
   msg->header.message_type = Proto_Vehicle_Body_Sensed_State;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   offset = pack_vehicle_body_sensed_state(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}