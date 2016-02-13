/* This file was autogenerated. All changes will be undone. */

/* Message: Vehicle_Termination_Command, ID: 1004*/

#include <protonet_marshal.h>
#include <protonet_message.h>
#include <message/VehicleTerminationCommand.h>

msg_offset pack_vehicle_termination_command(
   vehicle_termination_command_t* vehicle_termination_command,
   msg_offset offset)
{
   offset = pack_float64_t(vehicle_termination_command->timestamp,offset);
   offset = pack_uint16_t(vehicle_termination_command->vehicle_ID,offset);
   offset = pack_uint8_t(vehicle_termination_command->termination_mode,offset);
   return offset;
}

msg_offset unpack_vehicle_termination_command(
   msg_offset offset,
   vehicle_termination_command_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->timestamp);
   offset = unpack_uint16_t(offset, &out_ptr->vehicle_ID);
   offset = unpack_uint8_t(offset, &out_ptr->termination_mode);
   return offset;
}

void encode_vehicle_termination_command(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   vehicle_termination_command_t* tx_msg,
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
   msg->header.message_length = 11;
   msg->header.message_type = Proto_Vehicle_Termination_Command;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   /** Encrypt */
   /* Managed C (CLR) will freak out if you pass SecByteBlock as an argument this is my half ass fix MW*/
   CryptoPP::SecByteBlock key(keyArr, AES::DEFAULT_KEYLENGTH);
   CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), msg->header.iv);
   cfbEncryption.ProcessData((byte*)offset, (byte*)offset, msg->header.message_length);

   offset = pack_vehicle_termination_command(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}