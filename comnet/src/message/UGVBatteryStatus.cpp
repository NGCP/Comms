/* This file was autogenerated. All changes will be undone. */

/* Message: UGV_Battery_Status, ID: 6001*/

#include <comnet_marshal.h>
#include <comnet_message.h>
#include <message/UGVBatteryStatus.h>

msg_offset pack_UGV_battery_status(
   UGV_battery_status_t* UGV_battery_status,
   msg_offset offset)
{
   offset = pack_float64_t(UGV_battery_status->timestamp,offset);
   offset = pack_float32_t(UGV_battery_status->voltage_3_3V,offset);
   offset = pack_float32_t(UGV_battery_status->voltage_5V,offset);
   offset = pack_float32_t(UGV_battery_status->voltage_12V,offset);
   offset = pack_float32_t(UGV_battery_status->current_3_3V,offset);
   offset = pack_float32_t(UGV_battery_status->current_5V,offset);
   offset = pack_float32_t(UGV_battery_status->current_12V,offset);
   offset = pack_float32_t(UGV_battery_status->current_fore_motor,offset);
   offset = pack_float32_t(UGV_battery_status->current_aft_motor,offset);
   return offset;
}

msg_offset unpack_UGV_battery_status(
   msg_offset offset,
   UGV_battery_status_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->timestamp);
   offset = unpack_float32_t(offset, &out_ptr->voltage_3_3V);
   offset = unpack_float32_t(offset, &out_ptr->voltage_5V);
   offset = unpack_float32_t(offset, &out_ptr->voltage_12V);
   offset = unpack_float32_t(offset, &out_ptr->current_3_3V);
   offset = unpack_float32_t(offset, &out_ptr->current_5V);
   offset = unpack_float32_t(offset, &out_ptr->current_12V);
   offset = unpack_float32_t(offset, &out_ptr->current_fore_motor);
   offset = unpack_float32_t(offset, &out_ptr->current_aft_motor);
   return offset;
}

void com_UGV_battery_status(
   uint8_t src_id,
   uint8_t dest_id,
   UGV_battery_status_t* tx_msg,
   com_msg_t* msg)


{
   msg_offset start_offset, offset;
   msg->direction = Com_Out;
   start_offset = msg->data;
   offset = msg->data;
   msg->header.node_src_id = src_id;
   msg->header.node_dest_id = dest_id;
   msg->header.message_length = 40;
   msg->header.message_type = Com_UGV_Battery_Status;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   offset = pack_UGV_battery_status(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}