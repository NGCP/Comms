/* This file was autogenerated. All changes will be undone. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <comnet.h>
#include <comnet_parser.h>
#include <comnet_message.h>
#include <datalink.h>
#include <serial.h>
#include <udp.h>
#include <pqueue.h>
#include <threadCom.h>
#include <zigBee.h>

#include <fstream>
#include <string>

using namespace comnet;

node::node(uint8_t node_id)
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

void node::add_zigBee(int8_t* link_id, uint32_t baudRate, char device_path[50])
{
	datalinks[num_datalinks] = new ZigBee(baudRate, device_path);

	if (datalinks[num_datalinks]->is_connected())
	{
		datalinks[num_datalinks]->set_link_id(num_datalinks);
		datalinks[num_datalinks]->set_queue(&this->queue);
		datalinks[num_datalinks]->run();//doesnt do any thing
		*link_id = num_datalinks;
		num_datalinks++;
	}
}

void node::establish_zigBee(int8_t link_id, uint8_t node_id, std::string address64Hex)
{
	if (datalinks[link_id]->get_datalink_type() == ZIGBEE_TYPE && datalinks[link_id]->is_connected())
	{
		((ZigBee*)datalinks[link_id])->establish(node_id, address64Hex);
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
}

void node::null_callback_storage()
{
   on_enter = NULL;
   on_exit = NULL;
   on_ping = NULL;
   on_pong = NULL;
   on_vehicle_identification = NULL;
   on_amy_stuff = NULL;
   on_vehicle_authorization_request = NULL;
   on_vehicle_authorization_reply = NULL;
   on_vehicle_mode_command = NULL;
   on_vehicle_termination_command = NULL;
   on_vehicle_telemetry_command = NULL;
   on_vehicle_waypoint_command = NULL;
   on_vehicle_system_status = NULL;
   on_vehicle_inertial_state = NULL;
   on_vehicle_global_position = NULL;
   on_vehicle_body_sensed_state = NULL;
   on_vehicle_attitude = NULL;
   on_vehicle_ground_relative_state = NULL;
   on_payload_bay_command = NULL;
   on_payload_bay_mode_command = NULL;
   on_target_designation_command = NULL;
   on_UGV_joystick = NULL;
   on_UGV_battery_status = NULL;
}
void node::handle_com_msg_t(com_msg_t* rx_msg, com_msg_buf_t* rx_buf)
{
   switch(rx_msg->header.message_type)
   {
   case Com_Enter:
      {
         if(on_enter == NULL)
         {
         }
         else
         {
            this->on_enter(rx_msg->link_id, rx_msg->header, rx_buf->enter, this);
         }
         break;
      }
   case Com_Exit:
      {
         if(on_exit == NULL)
         {
         }
         else
         {
            this->on_exit(rx_msg->link_id, rx_msg->header, rx_buf->exit, this);
         }
         break;
      }
   case Com_Ping:
      {
         if(on_ping == NULL)
         {
         }
         else
         {
            this->on_ping(rx_msg->link_id, rx_msg->header, rx_buf->ping, this);
         }
         break;
      }
   case Com_Pong:
      {
         if(on_pong == NULL)
         {
         }
         else
         {
            this->on_pong(rx_msg->link_id, rx_msg->header, rx_buf->pong, this);
         }
         break;
      }
   case Com_Vehicle_Identification:
      {
         if(on_vehicle_identification == NULL)
         {
         }
         else
         {
            this->on_vehicle_identification(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_identification, this);
         }
         break;
      }
   case Com_Amy_Stuff:
      {
         if(on_amy_stuff == NULL)
         {
         }
         else
         {
            this->on_amy_stuff(rx_msg->link_id, rx_msg->header, rx_buf->amy_stuff, this);
         }
         break;
      }
   case Com_Vehicle_Authorization_Request:
      {
         if(on_vehicle_authorization_request == NULL)
         {
         }
         else
         {
            this->on_vehicle_authorization_request(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_authorization_request, this);
         }
         break;
      }
   case Com_Vehicle_Authorization_Reply:
      {
         if(on_vehicle_authorization_reply == NULL)
         {
         }
         else
         {
            this->on_vehicle_authorization_reply(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_authorization_reply, this);
         }
         break;
      }
   case Com_Vehicle_Mode_Command:
      {
         if(on_vehicle_mode_command == NULL)
         {
         }
         else
         {
            this->on_vehicle_mode_command(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_mode_command, this);
         }
         break;
      }
   case Com_Vehicle_Termination_Command:
      {
         if(on_vehicle_termination_command == NULL)
         {
         }
         else
         {
            this->on_vehicle_termination_command(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_termination_command, this);
         }
         break;
      }
   case Com_Vehicle_Telemetry_Command:
      {
         if(on_vehicle_telemetry_command == NULL)
         {
         }
         else
         {
            this->on_vehicle_telemetry_command(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_telemetry_command, this);
         }
         break;
      }
   case Com_Vehicle_Waypoint_Command:
      {
         if(on_vehicle_waypoint_command == NULL)
         {
         }
         else
         {
            this->on_vehicle_waypoint_command(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_waypoint_command, this);
         }
         break;
      }
   case Com_Vehicle_System_Status:
      {
         if(on_vehicle_system_status == NULL)
         {
         }
         else
         {
            this->on_vehicle_system_status(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_system_status, this);
         }
         break;
      }
   case Com_Vehicle_Inertial_State:
      {
         if(on_vehicle_inertial_state == NULL)
         {
         }
         else
         {
            this->on_vehicle_inertial_state(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_inertial_state, this);
         }
         break;
      }
   case Com_Vehicle_Global_Position:
      {
         if(on_vehicle_global_position == NULL)
         {
         }
         else
         {
            this->on_vehicle_global_position(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_global_position, this);
         }
         break;
      }
   case Com_Vehicle_Body_Sensed_State:
      {
         if(on_vehicle_body_sensed_state == NULL)
         {
         }
         else
         {
            this->on_vehicle_body_sensed_state(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_body_sensed_state, this);
         }
         break;
      }
   case Com_Vehicle_Attitude:
      {
         if(on_vehicle_attitude == NULL)
         {
         }
         else
         {
            this->on_vehicle_attitude(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_attitude, this);
         }
         break;
      }
   case Com_Vehicle_Ground_Relative_State:
      {
         if(on_vehicle_ground_relative_state == NULL)
         {
         }
         else
         {
            this->on_vehicle_ground_relative_state(rx_msg->link_id, rx_msg->header, rx_buf->vehicle_ground_relative_state, this);
         }
         break;
      }
   case Com_Payload_Bay_Command:
      {
         if(on_payload_bay_command == NULL)
         {
         }
         else
         {
            this->on_payload_bay_command(rx_msg->link_id, rx_msg->header, rx_buf->payload_bay_command, this);
         }
         break;
      }
   case Com_Payload_Bay_Mode_Command:
      {
         if(on_payload_bay_mode_command == NULL)
         {
         }
         else
         {
            this->on_payload_bay_mode_command(rx_msg->link_id, rx_msg->header, rx_buf->payload_bay_mode_command, this);
         }
         break;
      }
   case Com_Target_Designation_Command:
      {
         if(on_target_designation_command == NULL)
         {
         }
         else
         {
            this->on_target_designation_command(rx_msg->link_id, rx_msg->header, rx_buf->target_designation_command, this);
         }
         break;
      }
   case Com_UGV_Joystick:
      {
         if(on_UGV_joystick == NULL)
         {
         }
         else
         {
            this->on_UGV_joystick(rx_msg->link_id, rx_msg->header, rx_buf->UGV_joystick, this);
         }
         break;
      }
   case Com_UGV_Battery_Status:
      {
         if(on_UGV_battery_status == NULL)
         {
         }
         else
         {
            this->on_UGV_battery_status(rx_msg->link_id, rx_msg->header, rx_buf->UGV_battery_status, this);
         }
         break;
      }
   }
}

void node::send_enter(
   uint8_t dest_id,
   float64_t timestamp,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   enter_t enter;
   enter.timestamp = timestamp;
   com_enter(this->node_id, dest_id, &enter, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_exit(
   uint8_t dest_id,
   float64_t timestamp,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   exit_t exit;
   exit.timestamp = timestamp;
   com_exit(this->node_id, dest_id, &exit, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_ping(
   uint8_t dest_id,
   float64_t timestamp,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   ping_t ping;
   ping.timestamp = timestamp;
   com_ping(this->node_id, dest_id, &ping, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_pong(
   uint8_t dest_id,
   float64_t timestamp,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   pong_t pong;
   pong.timestamp = timestamp;
   com_pong(this->node_id, dest_id, &pong, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_identification(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   uint8_t vehicle_type,
   uint16_t owner_ID,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_identification_t vehicle_identification;
   vehicle_identification.timestamp = timestamp;
   vehicle_identification.vehicle_ID = vehicle_ID;
   vehicle_identification.vehicle_type = vehicle_type;
   vehicle_identification.owner_ID = owner_ID;
   com_vehicle_identification(this->node_id, dest_id, &vehicle_identification, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_amy_stuff(
   uint8_t dest_id,
   float64_t hello,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   amy_stuff_t amy_stuff;
   amy_stuff.hello = hello;
   com_amy_stuff(this->node_id, dest_id, &amy_stuff, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_authorization_request(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   uint8_t link_key,
   uint8_t requested_services,
   uint8_t handover_node,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_authorization_request_t vehicle_authorization_request;
   vehicle_authorization_request.timestamp = timestamp;
   vehicle_authorization_request.vehicle_ID = vehicle_ID;
   vehicle_authorization_request.link_key = link_key;
   vehicle_authorization_request.requested_services = requested_services;
   vehicle_authorization_request.handover_node = handover_node;
   com_vehicle_authorization_request(this->node_id, dest_id, &vehicle_authorization_request, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_authorization_reply(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   uint8_t vehicle_type,
   uint8_t authorized_services,
   uint8_t granted_services,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_authorization_reply_t vehicle_authorization_reply;
   vehicle_authorization_reply.timestamp = timestamp;
   vehicle_authorization_reply.vehicle_ID = vehicle_ID;
   vehicle_authorization_reply.vehicle_type = vehicle_type;
   vehicle_authorization_reply.authorized_services = authorized_services;
   vehicle_authorization_reply.granted_services = granted_services;
   com_vehicle_authorization_reply(this->node_id, dest_id, &vehicle_authorization_reply, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_mode_command(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   uint8_t vehicle_mode,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_mode_command_t vehicle_mode_command;
   vehicle_mode_command.timestamp = timestamp;
   vehicle_mode_command.vehicle_ID = vehicle_ID;
   vehicle_mode_command.vehicle_mode = vehicle_mode;
   com_vehicle_mode_command(this->node_id, dest_id, &vehicle_mode_command, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_termination_command(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   uint8_t termination_mode,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_termination_command_t vehicle_termination_command;
   vehicle_termination_command.timestamp = timestamp;
   vehicle_termination_command.vehicle_ID = vehicle_ID;
   vehicle_termination_command.termination_mode = termination_mode;
   com_vehicle_termination_command(this->node_id, dest_id, &vehicle_termination_command, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_telemetry_command(
   uint8_t dest_id,
   float64_t timestamp,
   uint8_t telemetry_select,
   uint8_t telemetry_rate,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_telemetry_command_t vehicle_telemetry_command;
   vehicle_telemetry_command.timestamp = timestamp;
   vehicle_telemetry_command.telemetry_select = telemetry_select;
   vehicle_telemetry_command.telemetry_rate = telemetry_rate;
   com_vehicle_telemetry_command(this->node_id, dest_id, &vehicle_telemetry_command, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_waypoint_command(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   int32_t latitude,
   int32_t longitude,
   int32_t altitude,
   int32_t heading,
   uint8_t waypoint_ID,
   uint8_t waypoint_type,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_waypoint_command_t vehicle_waypoint_command;
   vehicle_waypoint_command.timestamp = timestamp;
   vehicle_waypoint_command.vehicle_ID = vehicle_ID;
   vehicle_waypoint_command.latitude = latitude;
   vehicle_waypoint_command.longitude = longitude;
   vehicle_waypoint_command.altitude = altitude;
   vehicle_waypoint_command.heading = heading;
   vehicle_waypoint_command.waypoint_ID = waypoint_ID;
   vehicle_waypoint_command.waypoint_type = waypoint_type;
   com_vehicle_waypoint_command(this->node_id, dest_id, &vehicle_waypoint_command, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_system_status(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   uint8_t vehicle_mode,
   uint8_t vehicle_state,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_system_status_t vehicle_system_status;
   vehicle_system_status.timestamp = timestamp;
   vehicle_system_status.vehicle_ID = vehicle_ID;
   vehicle_system_status.vehicle_mode = vehicle_mode;
   vehicle_system_status.vehicle_state = vehicle_state;
   com_vehicle_system_status(this->node_id, dest_id, &vehicle_system_status, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_inertial_state(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   float64_t latitude,
   float64_t longitude,
   float32_t altitude,
   float32_t roll,
   float32_t pitch,
   float32_t heading,
   float32_t north_speed,
   float32_t east_speed,
   float32_t vertical_speed,
   float32_t roll_rate,
   float32_t pitch_rate,
   float32_t yaw_rate,
   float32_t north_accel,
   float32_t east_accel,
   float32_t vertical_accel,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_inertial_state_t vehicle_inertial_state;
   vehicle_inertial_state.timestamp = timestamp;
   vehicle_inertial_state.vehicle_ID = vehicle_ID;
   vehicle_inertial_state.latitude = latitude;
   vehicle_inertial_state.longitude = longitude;
   vehicle_inertial_state.altitude = altitude;
   vehicle_inertial_state.roll = roll;
   vehicle_inertial_state.pitch = pitch;
   vehicle_inertial_state.heading = heading;
   vehicle_inertial_state.north_speed = north_speed;
   vehicle_inertial_state.east_speed = east_speed;
   vehicle_inertial_state.vertical_speed = vertical_speed;
   vehicle_inertial_state.roll_rate = roll_rate;
   vehicle_inertial_state.pitch_rate = pitch_rate;
   vehicle_inertial_state.yaw_rate = yaw_rate;
   vehicle_inertial_state.north_accel = north_accel;
   vehicle_inertial_state.east_accel = east_accel;
   vehicle_inertial_state.vertical_accel = vertical_accel;
   com_vehicle_inertial_state(this->node_id, dest_id, &vehicle_inertial_state, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_global_position(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   int32_t latitude,
   int32_t longitude,
   int32_t altitude,
   int32_t heading,
   int16_t x_speed,
   int16_t y_speed,
   int16_t z_speed,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_global_position_t vehicle_global_position;
   vehicle_global_position.timestamp = timestamp;
   vehicle_global_position.vehicle_ID = vehicle_ID;
   vehicle_global_position.latitude = latitude;
   vehicle_global_position.longitude = longitude;
   vehicle_global_position.altitude = altitude;
   vehicle_global_position.heading = heading;
   vehicle_global_position.x_speed = x_speed;
   vehicle_global_position.y_speed = y_speed;
   vehicle_global_position.z_speed = z_speed;
   com_vehicle_global_position(this->node_id, dest_id, &vehicle_global_position, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_body_sensed_state(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   int16_t x_accel,
   int16_t y_accel,
   int16_t z_accel,
   int16_t roll_rate,
   int16_t pitch_rate,
   int16_t yaw_rate,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_body_sensed_state_t vehicle_body_sensed_state;
   vehicle_body_sensed_state.timestamp = timestamp;
   vehicle_body_sensed_state.vehicle_ID = vehicle_ID;
   vehicle_body_sensed_state.x_accel = x_accel;
   vehicle_body_sensed_state.y_accel = y_accel;
   vehicle_body_sensed_state.z_accel = z_accel;
   vehicle_body_sensed_state.roll_rate = roll_rate;
   vehicle_body_sensed_state.pitch_rate = pitch_rate;
   vehicle_body_sensed_state.yaw_rate = yaw_rate;
   com_vehicle_body_sensed_state(this->node_id, dest_id, &vehicle_body_sensed_state, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_attitude(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   float32_t roll,
   float32_t pitch,
   float32_t yaw,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_attitude_t vehicle_attitude;
   vehicle_attitude.timestamp = timestamp;
   vehicle_attitude.vehicle_ID = vehicle_ID;
   vehicle_attitude.roll = roll;
   vehicle_attitude.pitch = pitch;
   vehicle_attitude.yaw = yaw;
   com_vehicle_attitude(this->node_id, dest_id, &vehicle_attitude, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_vehicle_ground_relative_state(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   float32_t angle_of_attack,
   float32_t angle_of_sideslip,
   float32_t true_airspeed,
   float32_t indicated_airspeed,
   float32_t north_wind_speed,
   float32_t east_wind_speed,
   float32_t north_ground_speed,
   float32_t east_ground_speed,
   float32_t barometric_pressure,
   float32_t barometric_altitude,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   vehicle_ground_relative_state_t vehicle_ground_relative_state;
   vehicle_ground_relative_state.timestamp = timestamp;
   vehicle_ground_relative_state.vehicle_ID = vehicle_ID;
   vehicle_ground_relative_state.angle_of_attack = angle_of_attack;
   vehicle_ground_relative_state.angle_of_sideslip = angle_of_sideslip;
   vehicle_ground_relative_state.true_airspeed = true_airspeed;
   vehicle_ground_relative_state.indicated_airspeed = indicated_airspeed;
   vehicle_ground_relative_state.north_wind_speed = north_wind_speed;
   vehicle_ground_relative_state.east_wind_speed = east_wind_speed;
   vehicle_ground_relative_state.north_ground_speed = north_ground_speed;
   vehicle_ground_relative_state.east_ground_speed = east_ground_speed;
   vehicle_ground_relative_state.barometric_pressure = barometric_pressure;
   vehicle_ground_relative_state.barometric_altitude = barometric_altitude;
   com_vehicle_ground_relative_state(this->node_id, dest_id, &vehicle_ground_relative_state, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_payload_bay_command(
   uint8_t dest_id,
   float64_t timestamp,
   uint32_t payload_ID,
   uint8_t payload_command,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   payload_bay_command_t payload_bay_command;
   payload_bay_command.timestamp = timestamp;
   payload_bay_command.payload_ID = payload_ID;
   payload_bay_command.payload_command = payload_command;
   com_payload_bay_command(this->node_id, dest_id, &payload_bay_command, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_payload_bay_mode_command(
   uint8_t dest_id,
   float64_t timestamp,
   uint32_t payload_ID,
   uint8_t payload_mode,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   payload_bay_mode_command_t payload_bay_mode_command;
   payload_bay_mode_command.timestamp = timestamp;
   payload_bay_mode_command.payload_ID = payload_ID;
   payload_bay_mode_command.payload_mode = payload_mode;
   com_payload_bay_mode_command(this->node_id, dest_id, &payload_bay_mode_command, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_target_designation_command(
   uint8_t dest_id,
   float64_t timestamp,
   uint16_t vehicle_ID,
   uint8_t payload_ID,
   uint8_t target_ID,
   uint8_t target_type,
   int32_t latitude,
   int32_t longitude,
   int32_t altitude,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   target_designation_command_t target_designation_command;
   target_designation_command.timestamp = timestamp;
   target_designation_command.vehicle_ID = vehicle_ID;
   target_designation_command.payload_ID = payload_ID;
   target_designation_command.target_ID = target_ID;
   target_designation_command.target_type = target_type;
   target_designation_command.latitude = latitude;
   target_designation_command.longitude = longitude;
   target_designation_command.altitude = altitude;
   com_target_designation_command(this->node_id, dest_id, &target_designation_command, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_UGV_joystick(
   uint8_t dest_id,
   float64_t timestamp,
   uint8_t vehicle_id,
   float32_t steering,
   float32_t throttle,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   UGV_joystick_t UGV_joystick;
   UGV_joystick.timestamp = timestamp;
   UGV_joystick.vehicle_id = vehicle_id;
   UGV_joystick.steering = steering;
   UGV_joystick.throttle = throttle;
   com_UGV_joystick(this->node_id, dest_id, &UGV_joystick, &com_msg);
   queue.add(&com_msg);
   return;
}

void node::send_UGV_battery_status(
   uint8_t dest_id,
   float64_t timestamp,
   float32_t voltage_3_3V,
   float32_t voltage_5V,
   float32_t voltage_12V,
   float32_t current_3_3V,
   float32_t current_5V,
   float32_t current_12V,
   float32_t current_fore_motor,
   float32_t current_aft_motor,
   bool is_emergency)
{
   com_msg_t com_msg;
   com_msg.header.is_emergency = (uint16_t)is_emergency;
   UGV_battery_status_t UGV_battery_status;
   UGV_battery_status.timestamp = timestamp;
   UGV_battery_status.voltage_3_3V = voltage_3_3V;
   UGV_battery_status.voltage_5V = voltage_5V;
   UGV_battery_status.voltage_12V = voltage_12V;
   UGV_battery_status.current_3_3V = current_3_3V;
   UGV_battery_status.current_5V = current_5V;
   UGV_battery_status.current_12V = current_12V;
   UGV_battery_status.current_fore_motor = current_fore_motor;
   UGV_battery_status.current_aft_motor = current_aft_motor;
   com_UGV_battery_status(this->node_id, dest_id, &UGV_battery_status, &com_msg);
   queue.add(&com_msg);
   return;
}

