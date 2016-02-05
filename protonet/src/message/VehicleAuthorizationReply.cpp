/* This file was autogenerated. All changes will be undone. */

/* Message: Vehicle_Authorization_Reply, ID: 1002*/

#include <protonet_marshal.h>
#include <protonet_message.h>
#include <message/VehicleAuthorizationReply.h>

msg_offset pack_vehicle_authorization_reply(
   vehicle_authorization_reply_t* vehicle_authorization_reply,
   msg_offset offset)
{
   offset = pack_float64_t(vehicle_authorization_reply->timestamp,offset);
   offset = pack_uint16_t(vehicle_authorization_reply->vehicle_ID,offset);
   offset = pack_uint8_t(vehicle_authorization_reply->vehicle_type,offset);
   offset = pack_uint8_t(vehicle_authorization_reply->authorized_services,offset);
   offset = pack_uint8_t(vehicle_authorization_reply->granted_services,offset);
   return offset;
}

msg_offset unpack_vehicle_authorization_reply(
   msg_offset offset,
   vehicle_authorization_reply_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->timestamp);
   offset = unpack_uint16_t(offset, &out_ptr->vehicle_ID);
   offset = unpack_uint8_t(offset, &out_ptr->vehicle_type);
   offset = unpack_uint8_t(offset, &out_ptr->authorized_services);
   offset = unpack_uint8_t(offset, &out_ptr->granted_services);
   return offset;
}

void encode_vehicle_authorization_reply(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   vehicle_authorization_reply_t* tx_msg,
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
   msg->header.message_length = 13;
   msg->header.message_type = Proto_Vehicle_Authorization_Reply;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   /** Encrypt */
   /* Managed C (CLR) will freak out if you pass SecByteBlock as an argument this is my half ass fix MW*/
   CryptoPP::SecByteBlock key(keyArr, AES::DEFAULT_KEYLENGTH);
   CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), msg->header.iv);
   cfbEncryption.ProcessData((byte*)offset, (byte*)offset, msg->header.message_length);

   offset = pack_vehicle_authorization_reply(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}