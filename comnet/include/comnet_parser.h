#ifndef PROTONET_PARSER_H_
#define PROTONET_PARSER_H_
/**@File
Global functions to parse message by using a checksum*/

/*System Includes */
#include <stdint.h>

/* User Includes */
#include <comnet_message.h>

/**Global Typedef to keep track of the bytes we are parsing */
typedef enum parse_state_e{
	WAIT_SYNC_C = 0, /* CPP\0 is the sync byte */
	WAIT_SYNC_P1,
	WAIT_SYNC_P2,
	WAIT_SYNC_NULL,
	WAIT_MESSAGE_HEADER,
	WAIT_MESSAGE_DATA,
	WAIT_MESSAGE_CHECKSUM
} parse_state_t;

/**Global variable to keep track of length to help parse multibyte sections */
typedef uint16_t parse_count_t;

/**Global Typedef which holds the state data for the parser, simple Skolem machine */
typedef struct parse_data
{
	parse_state_t parse_state;
	parse_count_t parse_count;
}parse_data_t;


/**Global Variable ensure that the parser starts out uninitialized */
int32_t parse_init(parse_data_t* parse_data);

/** 
Global function Extracts sections of a comnet message from each byte
Returns 1 if a valid comnet message has been received
*/
int32_t parse_message(
		uint8_t rx_byte, /*in*/
		parse_data_t* parse_data, /*in*/
		com_msg_t* rx_msg); /*out*/
/**Global function whicih prints the parse state for debugging purposes*/
uint32_t print_parse_state(parse_state_t parse_state);

#endif 
