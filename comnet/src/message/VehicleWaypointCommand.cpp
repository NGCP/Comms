/* This file was autogenerated. All changes will be undone. */

/* Message: Vehicle_Waypoint_Command, ID: 1006*/

#include <comnet_marshal.h>
#include <comnet_message.h>
#include <message/VehicleWaypointCommand.h>

msg_offset pack_vehicle_waypoint_command(
   vehicle_waypoint_command_t* vehicle_waypoint_command,
   msg_offset offset)
{
   offset = pack_float64_t(vehicle_waypoint_command->timestamp,offset);
   offset = pack_uint16_t(vehicle_waypoint_command->vehicle_ID,offset);
   offset = pack_int32_t(vehicle_waypoint_command->latitude,offset);
   offset = pack_int32_t(vehicle_waypoint_command->longitude,offset);
   offset = pack_int32_t(vehicle_waypoint_command->altitude,offset);
   offset = pack_int32_t(vehicle_waypoint_command->heading,offset);
   offset = pack_uint8_t(vehicle_waypoint_command->waypoint_ID,offset);
   offset = pack_uint8_t(vehicle_waypoint_command->waypoint_type,offset);
   return offset;
}

msg_offset unpack_vehicle_waypoint_command(
   msg_offset offset,
   vehicle_waypoint_command_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->timestamp);
   offset = unpack_uint16_t(offset, &out_ptr->vehicle_ID);
   offset = unpack_int32_t(offset, &out_ptr->latitude);
   offset = unpack_int32_t(offset, &out_ptr->longitude);
   offset = unpack_int32_t(offset, &out_ptr->altitude);
   offset = unpack_int32_t(offset, &out_ptr->heading);
   offset = unpack_uint8_t(offset, &out_ptr->waypoint_ID);
   offset = unpack_uint8_t(offset, &out_ptr->waypoint_type);
   return offset;
}

void com_vehicle_waypoint_command(
   uint8_t src_id,
   uint8_t dest_id,
   vehicle_waypoint_command_t* tx_msg,
   com_msg_t* msg)


{
   msg_offset start_offset, offset;
   msg->direction = Com_Out;
   start_offset = msg->data;
   offset = msg->data;
   msg->header.node_src_id = src_id;
   msg->header.node_dest_id = dest_id;
   msg->header.message_length = 28;
   msg->header.message_type = Com_Vehicle_Waypoint_Command;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   offset = pack_vehicle_waypoint_command(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}