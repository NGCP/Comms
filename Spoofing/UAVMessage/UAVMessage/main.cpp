#include "main.h"
void* tx_thread(){
	float64_t latitude = -117.631;
	std::vector<float64_t> longitude = { -0.15, -0.17, -0.18, -0.19, -0.2, -0.21, -0.21, -0.2, -0.2, -0.2, -0.21, -0.22, -0.23,
		-0.24, -0.25, -0.25, -0.26, -0.26, -0.27, -0.27, -0.24, -0.23, -0.22, -0.21, -0.2, -0.19, -0.18, -0.16, -0.19, -0.2, -0.2, -0.19,
		-0.18, -0.17, -0.16, -0.12, -0.12, -0.09, -0.09, -0.08, -0.09, -0.1, };
	
	std::vector<double> altitude = { 1.2,
		1.24,
		1.27,
		1.41,
		1.45,
		1.58,
		1.53,
		1.42,
		1.4,
		1.3,
		1.67,
		1.66,
		1.66,
		1.62,
		1.58,
		1.69,
		1.83,
		2.08,
		2.52,
		3.1,
		3.72,
		4.39,
		5.14,
		6.64,
		8.14,
		9.46,
		10.4,
		22.22,
		22.75,
		22.87,
		22.09,
		22.04,
		21.82,
		21.51,
		21.18,
		20.82,
		20.51,
		20.39,
		20.11,
		19.93,
		19.69,
		19.59,
		19.4,
		19.39,
		19.25,
		19.18,
		19.17,
		19,
		18.93,
		18.92,
		18.66,
		18.42,
		18.35,
		18.23,
		17.95,
		17.82,
		17.69,
		17.57,
		17.37,
		17.44,
		17.39,
		17.41,
		17.34,
		17.53,
		17.71,
	};

	std::vector<double> speed = { 0.26,
		0.26,
		0.26,
		0.26,
		0.26,
		0.26,
		0.26,
		0.26,
		0.26,
		0.26,
		318.83,
		314.19,
		315.13,
		311.53,
		300.94,
		314.66,
		314.66,
		314.66,
		314.66,
		314.66,
		314.66,
		314.66,
		314.66,
		314.66,
		314.66,
		314.66,
		317.67,
		309.4,
		306.69,
		311.11,
		310.49,
		308.03,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		308.96,
		307.2,
		301.86,
		309.3,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
		308.14,
	};
	
	comnet::node gcs_node(101); // UAV NODE at 101

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

		/*
		This node will receive a ping from Node 1, so
		the Ping needs to be handled as the Pong was above
		*/
	  } catch ( comnet::error::AbsException& e) {
    std::cout << e.explain_error() << std::endl;
  }


	std::chrono::milliseconds dura(1000);
	while (1)
	{
		for (int x = 0; x < longitude.size(); x++)
		{
			gcs_node.send_ping(1, 0, false);
			//gcs_node.send_vehicle_authorization_reply(1, 0, 2, 0, 0, 0, false);
			//gcs_node.send_vehicle_authorization_request(1, 0, 1, 0, 0, 0, false);
			//gcs_node.send_vehicle_system_status(1, 0, 2, 0, 0, false);
			gcs_node.send_vehicle_inertial_state(1, 0, 101, latitude, longitude[x], static_cast<float32_t>(altitude[x]), 0, 0, 0, static_cast<float32_t>(speed[x]), static_cast<float32_t>(speed[x]), static_cast<float32_t>(speed[x]), 0, 0, 0, 0, 0, 0, false);
			gcs_node.send_vehicle_global_position(1, 0, 101, latitude, longitude[x], altitude[x], speed[x], speed[x], speed[x], false);
			//gcs_node.send_vehicle_attitude(1, 0, 2, 0, 0, 0, false);
			//gcs_node.send_target_designation_command(0, 3, 0, 2, 0, 0, 0, 0, 0, 0, false);
			//gcs_node.send_vehicle_waypoint_command(1, 0, 2, 0, 0, 0, false);
			
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