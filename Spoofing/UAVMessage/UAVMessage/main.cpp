#include "main.h"
#include <iostream>

void* tx_thread(){

	comnet::node gcs_node(2); // UAV NODE at 2

	int8_t zigBee_2 = 0;
  
	char *address2 = "0013A20040917974";
  try {	
    /* id, baudrate, comport  */
	  gcs_node.add_zigBee(&zigBee_2, 57600, "/dev/ttyUSB0");

	  /*
	  create zig bee connection
	  id, dest id, 64 bit hex address in char
	  */
	  gcs_node.establish_zigBee(zigBee_2, 1, address2);
  } catch ( comnet::error::AbsException& e) {
    std::cout << e.explain_error() << std::endl;
  }
	/*
	This node will receive a ping from Node 1, so
	the Ping needs to be handled as the Pong was above
	*/


	std::chrono::milliseconds dura(1000);
	while (1)
	{
		for (int x = 0; x < 5; x++)
		{
			gcs_node.send_ping(1, 0, false);
			gcs_node.send_vehicle_authorization_reply(1, 0, 2, 0, 0, 0, false);
			gcs_node.send_vehicle_authorization_request(1, 0, 1, 0, 0, 0, false);
			gcs_node.send_vehicle_system_status(1, 0, 2, 0, 0, false);
			gcs_node.send_vehicle_inertial_state(1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, false);
			gcs_node.send_vehicle_global_position(1, 0, 2, 0, 0, 0, 0, 0, 0, false);
			gcs_node.send_vehicle_attitude(1, 0, 2, 0, 0, 0, false);
			gcs_node.send_target_designation_command(0, 3, 0, 2, 0, 0, 0, 0, 0, 0, false);
			gcs_node.send_vehicle_waypoint_command(1, 0, 2, 0, 0, 0, false);
			
		}

		gcs_node.send_enter(1, 0, true);
		std::this_thread::sleep_for(dura);
	}
	return 0;
}
int main(int argc, char *argv[])
{
	std::thread tx(tx_thread);

	tx.join();


	return 0;

}