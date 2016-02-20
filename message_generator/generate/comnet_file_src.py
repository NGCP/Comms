from .lower_case_acronym import *

def generate_comnet_file_src(directory, include_extension, src_extension):
    """
    Function will create the protonet source file in .../src/
    File has 4 main parts
        -native node class methods
        -null_call_back storage init
        -handle_com_msg_t for each message sequence
        -send_message methods    
    """
    #load header structure and the messages in variables from xml file
    import xml.etree.ElementTree as ET
    tree = ET.parse('message_definition.xml')
    protocol = tree.findall('message')
    header = tree.find('header')
    tab = '   '            
    #open file
    f = open(directory + "/src/" + 'comnet' + src_extension, 'w')
    # warning
    f.write('/* This file was autogenerated. All changes will be undone. */\n\n')
    f.write('#include <stdio.h>\n')
    f.write('#include <stdlib.h>\n')
    f.write('#include <time.h>\n\n')
    #include files
    f.write('#include <comnet' +include_extension+'>\n')
    f.write('#include <comnet_parser' +include_extension+'>\n')
    f.write('#include <comnet_message' +include_extension+'>\n')
    f.write('#include <datalink' +include_extension+'>\n')
    f.write('#include <serial' +include_extension+'>\n')
    f.write('#include <udp' +include_extension+'>\n')
    f.write('#include <pqueue' +include_extension+'>\n')
    f.write('#include <thread' +include_extension+'>\n\n')
    f.write('#include <fstream>\n')
    f.write('#include <string>\n\n')
    
    f.write('using namespace comnet;\n\n')
    # native methods
    f.write(r'''node::node(uint8_t node_id)
{ 
	memset(datalinks,0,sizeof(datalinks));
	num_datalinks = 0;

	null_callback_storage();

	/* destroy pointer and node in the event of invalid id */
	if(node_id == 0)
	{
		this->~node();
		return;
	}
	this->node_id = node_id;

	thread_create(&handler_thread, &node::handler_helper, this);
	
}

/* Create a node with a specified mode, TBD */
node::node(uint8_t node_id, int32_t mode)
{ 
	memset(datalinks,0,sizeof(datalinks));
	num_datalinks = 0;

	null_callback_storage();

	if(node_id == 0)
	{
		this->~node();
		return;
	}
	this->node_id = node_id;

	thread_create(&handler_thread, &node::handler_helper, this);
	
}
node::~node()
{
	int32_t i;
	for(i = 0; i<num_datalinks; i++)
	{
		datalinks[i]->close();
	}

}

/* Need to call start to create the protonet handler, usually after establish functions */
void node::start()
{
	try
	{
		//thread_create(&upkeep_thread, &node::upkeep_helper, this);
	}
	catch(int e)
	{
		printf("thread_create out: %d\n", e);
	
	}
}

/* Entry point for the event handler that performs callbacks based on incoming messages */
void* node::comnet_handler()
{
	com_msg_t com_msg;	
	while(1)
	{
		/* Blocking call to the message queue, unblock when messages are in queue */
		queue.remove(&com_msg);
		{
			{				
				/* Behavior on an outgoing message from client*/
				if(com_msg.direction == Com_Out)
				{
//#ifdef DEBUG
					printf("Node %d Outbound: Source id: %d, Dest. id %d, Message type: %s\n", this->node_id,com_msg.header.node_src_id, com_msg.header.node_dest_id, com_typestr((com_msg_type_t)com_msg.header.message_type));
//#endif
					int32_t i;
					if(num_datalinks>0)
					{
						for(i = 0;i<num_datalinks;i++)
						{
							datalinks[i]->send(com_msg.header.node_dest_id, com_msg.data, com_msg.tx_len);
						}
					}
				}
				/* Behavior on an incoming message from client*/
				else if(com_msg.direction == Com_In)				
				{
//#ifdef DEBUG
					printf("Node %d Inbound: Source id: %d, Dest. id %d, Message type: %s\n", this->node_id,com_msg.header.node_src_id, com_msg.header.node_dest_id, com_typestr((com_msg_type_t)com_msg.header.message_type));
//#endif
					if((com_msg.header.node_dest_id == this->node_id) || (com_msg.header.node_dest_id == 0))
					{

						com_msg_buf_t rx_buf;
						/* Unpack and identify the type of incoming message */
						unpack_com_msg_t(&com_msg, &rx_buf);
                                                
						/* Perform a callback based on message type */
						handle_com_msg_t(&com_msg, &rx_buf);
					}
				}
			}
		}
	}
	return 0;
}

void* node::upkeep_handler()
{
	while(1)
	{
		//this->send_enter();
#ifdef _WIN32
		_sleep(5000);
#endif
#ifdef __unix__
		sleep(5000);
#endif
	}
	return 0;
}

void node::add_serial(int8_t* link_id, uint32_t baud_rate, char device_path[50])
{
	/* Initialize a datalink pointer as a Serial link */
	datalinks[num_datalinks] = new Serial();

	/* Cast the datalink as a Serial datalink and open it with required options */
	if(((Serial*)(datalinks[num_datalinks]))->open(baud_rate, device_path) == 0)
	{
		/* Provide a reference to the queue for access to protonet handler, runs the datalink */
		datalinks[num_datalinks]->set_link_id(num_datalinks);
		datalinks[num_datalinks]->set_queue(&this->queue);
		datalinks[num_datalinks]->run();

		/* Provide the link_id for future reference, simply increment to keep track */
		*link_id = num_datalinks;
		num_datalinks++;
	}
}


void node::add_udp(int8_t* link_id, uint16_t port)
{
	/* Follows the same format as the above function, except UDP oriented */
	datalinks[num_datalinks] = new UDP(port);
	if(datalinks[num_datalinks]->is_connected())
	{
		datalinks[num_datalinks]->set_link_id(num_datalinks);
		datalinks[num_datalinks]->set_queue(&this->queue);
		datalinks[num_datalinks]->run();
		*link_id = num_datalinks;
		num_datalinks++;
	}
}
	
void node::add_udp(int8_t* link_id, uint16_t port, char addr[16])
{
	/* 
	Follows the same format as the above function, 
	except targets an interface specified by IP
	*/
	datalinks[num_datalinks] = new UDP(port, addr);
	if(datalinks[num_datalinks]->is_connected())
	{
		datalinks[num_datalinks]->set_link_id(num_datalinks);
		datalinks[num_datalinks]->set_queue(&this->queue);
		datalinks[num_datalinks]->run();
		*link_id = num_datalinks;
		num_datalinks++;
	}
}

void node::establish_serial(int8_t link_id, uint8_t node_id)
{
	/* 
	Check that the datalink is of the correct type & connected, 
	and set the node_id 
	*/
	if(datalinks[link_id]->get_datalink_type() == SERIAL_TYPE && datalinks[link_id]->is_connected())
	{
		datalinks[link_id]->establish(node_id);
	}
	
}
void node::establish_udp(int8_t link_id, uint8_t node_id, uint16_t port, char addr[16])
{
	/* This is similar to the Serial establish function, except for UDP */
	if(datalinks[link_id]->get_datalink_type()== UDP_TYPE && datalinks[link_id]->is_connected())
	{
		((UDP*)datalinks[link_id])->establish(node_id, port, addr);
	}
}

uint8_t node::get_num_datalinks()
{
	return(this->num_datalinks);
}

int32_t node::query_datalink_connected(int8_t link_id)
{
	/* Returns 1 if the datalink is connected */
	return(datalinks[link_id]->is_connected());
}

datalink_type_t node::query_datalink_type(int8_t link_id)
{
	return(datalinks[link_id]->get_datalink_type());
}

/* Helper functions from C style from C++ entry point with class member linkage */
void* node::handler_helper(void* context)
{
	return ((node*)context)->comnet_handler();
}

void* node::upkeep_helper(void* context)
{
	return ((node*)context)->upkeep_handler();
}'''+'\n\n')
    
    #message call back storage init
    f.write('void node::null_callback_storage()\n')
    f.write('{\n')
    for message in protocol:
        name = message.get('name')
        variable_name = lower_case_acronym(name)
        f.write(tab+'on_'+ variable_name+' = NULL;\n')
    f.write('}\n')
    
    #handles each message type with giant switch case
    f.write('void node::handle_com_msg_t(com_msg_t* rx_msg, com_msg_buf_t* rx_buf)\n{\n' + tab +'switch(rx_msg->header.message_type)\n'+tab+'{\n')
    for message in protocol:
        name = message.get('name')
        variable_name = lower_case_acronym(name)
        f.write(tab + 'case Com_'+name+':\n'+tab+tab+'{\n')
        f.write(tab+tab+tab+'if(on_'+variable_name+' == NULL)\n')
        f.write(tab+tab+tab+'{\n')
        f.write(tab+tab+tab+'}\n')
        f.write(tab+tab+tab+'else\n')
        f.write(tab+tab+tab+'{\n')
        f.write(tab+tab+tab+tab+'this->on_'+ variable_name+'(rx_msg->link_id, rx_msg->header, rx_buf->'+variable_name+', this);\n')
        f.write(tab+tab+tab+'}\n')
        f.write(tab+tab+tab+'break;\n')
        f.write(tab+tab+'}\n')
    f.write(tab+'}\n')
    f.write('}\n\n')
    
    #create all send_message methods
    for message in protocol:
        name = message.get('name')
        variable_name = lower_case_acronym(name)
        type_t_name = variable_name + "_t"
        f.write('void node::send_'+ variable_name+'(\n')
        f.write(tab+'uint8_t dest_id,')
        for field in message:
            f.write('\n'+tab+field.get('type')+' '+ field.get('name'))
            if(field != message[-1]):
                f.write(',')
        f.write(',\n' + tab + 'bool is_emergency')        
        f.write(')\n')
        f.write('{\n')
        f.write(tab+'com_msg_t com_msg;\n')
        f.write(tab + 'com_msg.header.is_emergency = (uint16_t)is_emergency;\n')
        f.write(tab+type_t_name+' '+variable_name+';\n')
        for field in message:
            f.write(tab+variable_name+'.'+ field.get('name')+' = '+ field.get('name')+';\n')
        f.write(tab+'encode_'+variable_name+'(this->node_id, dest_id, 3, 0, &'+variable_name+', &com_msg);\n')
        f.write(tab+'queue.add(&com_msg);\n')
        f.write(tab+'return;\n')
        f.write('}\n\n')
    print("Created: " + 'comnet' + src_extension)