/* This file was autogenerated. All changes will be undone. */

/* Message: UGV_Battery_Status, ID: 6001*/

#include <protonet_marshal.h>
#include <protonet_message.h>
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

void encode_UGV_battery_status(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   UGV_battery_status_t* tx_msg,
   proto_msg_t* msg,
   uint8_t keyArr[])//key for encryption CryptoPP

{
   /** Random IV*/
   Random::RandomNumberGen randIV = Random::RandomNumberGen();
   randIV.generate_numbers<uint8_t>(msg->header.iv,0, AES::BLOCKSIZE,0,255);

   msg_offset start_offset, offset;
   msg->direction = Proto_Out;
   start_offset = msg->data;
   offset = msg->data;
   msg->header.node_src_id = src_id;
   msg->header.node_dest_id = dest_id;
   msg->header.message_ttl = msg_ttl;
   msg->header.sequence_number = seq_number;
   msg->header.message_length = 40;
   msg->header.message_type = Proto_UGV_Battery_Status;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   /** Encrypt */
   /* Managed C (CLR) will freak out if you pass SecByteBlock as an argument this is my half ass fix MW*/
   CryptoPP::SecByteBlock key(keyArr, AES::DEFAULT_KEYLENGTH);
   CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), msg->header.iv);
   cfbEncryption.ProcessData((byte*)offset, (byte*)offset, msg->header.message_length);

   offset = pack_UGV_battery_status(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}