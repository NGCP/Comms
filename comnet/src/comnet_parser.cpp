/* System Includes */
#include <stdio.h>
#include <string.h>

/* User Includes */
#include <comnet_parser.h>
#include <comnet_message.h>
/** inlucde com protocol for const MSG_DATA_OFFSET*/
#include <comnet_protocol.h>

int32_t parse_init(parse_data_t* parse_data)
{
	memset(parse_data, 0, sizeof(parse_data_t));
	return 0;
}

int32_t parse_message(
		uint8_t rx_byte,
		parse_data_t* parse_data,
		com_msg_t* rx_msg)
{
	switch(parse_data->parse_state){

	case WAIT_SYNC_C :
	{
		if(rx_byte == 'C') parse_data->parse_state = WAIT_SYNC_P1;
		rx_msg->data[0] = rx_byte;
		break;
	}
	case WAIT_SYNC_P1 :
	{
		parse_data->parse_state = (rx_byte == 'P') ? WAIT_SYNC_P2 : WAIT_SYNC_C;
		rx_msg->data[1] = rx_byte;
		break;
	}
	case WAIT_SYNC_P2 :
	{
		parse_data->parse_state = (rx_byte == 'P') ? WAIT_SYNC_NULL : WAIT_SYNC_C;
		rx_msg->data[2] = rx_byte;
		break;
	}
	case WAIT_SYNC_NULL :
	{
		parse_data->parse_state = (rx_byte == 0) ? WAIT_MESSAGE_HEADER : WAIT_SYNC_C;
		rx_msg->data[3] = rx_byte;
		parse_data->parse_count = 0;
		break;
	}
	case WAIT_MESSAGE_HEADER:
	{
		rx_msg->data[parse_data->parse_count+4] = rx_byte;
		++parse_data->parse_count;			/* Store parser count to keep track of header length */
		if(parse_data->parse_count == sizeof(com_header_t))
		{
			unpack_header(rx_msg->data+4, &rx_msg->header); 
			/* Checks if parsed message size is too large */
			parse_data->parse_state = rx_msg->header.message_length <= 512 ? WAIT_MESSAGE_DATA : WAIT_SYNC_C;
			parse_data->parse_count = 0;
		}
		break;
	}
	case WAIT_MESSAGE_DATA:
	{
		rx_msg->data[parse_data->parse_count+MSG_DATA_OFFSET] = rx_byte;
		/* Increment parser count until the size of the data section is received */
		parse_data->parse_state = parse_data->parse_count < rx_msg->header.message_length-1 ? WAIT_MESSAGE_DATA: WAIT_MESSAGE_CHECKSUM;
		if (parse_data->parse_state == WAIT_MESSAGE_CHECKSUM)parse_data->parse_count = 0;
		else ++parse_data->parse_count;
		break;
	}
	case WAIT_MESSAGE_CHECKSUM:
	{
		rx_msg->data[rx_msg->header.message_length + MSG_DATA_OFFSET + parse_data->parse_count] = rx_byte;
		parse_data->parse_state = WAIT_MESSAGE_CHECKSUM;
		if (parse_data->parse_count > 0)
		{	
         unpack_checksum(rx_msg->data + (rx_msg->header.message_length + MSG_DATA_OFFSET), &rx_msg->checksum);			
			rx_msg->direction = Com_In;
			parse_data->parse_state = WAIT_SYNC_C;		
			checksum_t sum = fletcher16((msg_offset)rx_msg->data, (msg_offset)rx_msg->data + rx_msg->header.message_length + MSG_DATA_OFFSET);
			if ((rx_msg->checksum - sum) == 0)
			{
				return 1;
			}
			else
			{
				printf("Parse Fail");
			}									  
		}
		parse_data->parse_count++;
		break;
	}
	default :
	{
		parse_data->parse_state = WAIT_SYNC_C;
		break;
	}
	}
	return 0;
}

/* Convenient function to help debug the parser */
uint32_t print_parse_state(parse_state_t parse_state)
{
	switch(parse_state){

	case WAIT_SYNC_C :
	{
		printf("WAIT_SYNC_C\n");
		break;
	}
	case WAIT_SYNC_P1 :
	{
		printf("WAIT_SYNC_P1\n");
		break;
	}
	case WAIT_SYNC_P2 :
	{
		printf("WAIT_SYNC_P2\n");
		break;
	}
	case WAIT_SYNC_NULL :
	{
		printf("WAIT_SYNC_NULL\n");
		break;
	}
	case WAIT_MESSAGE_HEADER :
	{
		printf("WAIT_MESSAGE_HEADER\n");
		break;
	}
	case WAIT_MESSAGE_DATA:
	{
		printf("WAIT_HEADER_MESSAGE_DATA\n");
		break;
	}
	case WAIT_MESSAGE_CHECKSUM:
	{
		printf("WAIT_HEADER_MESSAGE_CHECKSUM\n");
		break;
	}
	}
	return 0;
}
