/* System Includes */
#include <string.h>

/* User Includes */
#include <datalink.h>
#include <comnet_parser.h>
using namespace comnet;

/* Constructor */
datalink::datalink()
{
	memset(rx_buf, 0, sizeof(rx_buf));
	this->datalink_type = UNINIT_TYPE;
	connected = 0;
}
/* Destructor */
datalink::~datalink()
{
}
/* Set queue as another queue */
void datalink::set_queue(com_msg_queue* queue)
{
	this->queue = queue;
}
/* Set link id */
void datalink::set_link_id(int8_t link_id)
{
	this->link_id = link_id;
}
/* Get link id9 */
int8_t datalink::get_link_id()
{
	return(this->link_id);
}
/* Virtual open Functions does nothing, must override for functionality*/
int32_t datalink::open()
{
	return 0;
}
/* Virtual close Functions does nothing, must override for functionality*/
int32_t datalink::close()
{
	return 0;
}
/* Virtual send Functions does nothing, must override for functionality*/
int32_t datalink::send(uint8_t node_id, uint8_t* tx_data, int32_t tx_len)
{
	return 0;
}
/* Virtual receive Functions does nothing, must override for functionality*/
int32_t datalink::recv(uint8_t* rx_data, int32_t* rx_len)
{
	return 0;
}
/* Virtual establish Functions does nothing, must override for functionality*/
int32_t datalink::establish(uint8_t node_id)
{
	return 0;
}
/* Virtual run which will invoke the datalink handler */
int32_t datalink::run()
{
	thread_create(&this->datalink_thread, thread_helper, this);
	return 0;
}

/* Datalink handler init, parse, and puts message into inbound com_msg_t which goes in queue */
void* datalink::datalink_handler()
{
	int32_t rx_len = 0;
	uint8_t rx_buf[1024];
	int32_t i = 0;
	parse_data_t parse_data;
	/* Storage for incoming message */
	com_msg_t rx_msg;
	/* Ensure parser state is zeroed out */
	parse_init(&parse_data);

	while(1)
	{
		recv(rx_buf, &rx_len);
		if(rx_len >0)
		{	
			for(i=0;i<rx_len;i++)
			{
				/* Parser returns a 1 if a message is received */
				if(parse_message(rx_buf[i], &parse_data, &rx_msg))
				{		
					rx_msg.link_id = get_link_id(); 
					/* 
					Message will have unpacked sync, header, and checksum.
					However, the message data will not be unpacked
					in the event that the destination node ID does 
					not match this node's ID.
					*/
					queue->add(&rx_msg); 
				}
			}
		
		}
	}
	return 0;
}

/* Helper function to convert between C++ and C function signatures*/
void* datalink::thread_helper(void* context)
{
	/* Casting to C style API for compatibility with thread_create method */
	return ((datalink*)context)->datalink_handler();
}
/* returns datalink type */
datalink_type_t datalink::get_datalink_type()
{
	return datalink_type;
}
/* returns true if connected */
int32_t datalink::is_connected()
{
	return this->connected;
}
