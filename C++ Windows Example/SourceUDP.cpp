/* System Includes */
#include <stdio.h>
#include <thread>


/* Include comnet.h for communication system API */
#include <comnet.h>



/*------
When a Ping is received, we want to send a Pong back to the sender of the Ping.

In order to do so, we define a callback that is executed whenever a Ping message
is received. The callback must match the signature of the function below.

To define a callback for any given message type, simply change the 3rd argument:
ping_t ping to the desired message type: [message_type]_t [message_type], and
rename the callback to on_[message_type];

Parameters:

int8_t link_id: Provides the ID of the datalink the message was received from

com_header_t: The header of a comnet message, defined in the communication spec

ping_t ping: The data section of the message; the ping message provides a timestamp

comnet::node* node: A pointer to the comNet session that received the message.
This allows the user to access comNet functions from inside
the callback, such as sending messages or adding datalinks.
*/
void* on_ping(
int8_t link_id,
com_header_t header,
ping_t ping,
comnet::node* node)
{
	/* Send a pong message back to the sender of the ping */
	node->send_pong(header.node_src_id,100);
	printf("Priotiry: %d\n", header.is_emergency);
	return 0;
}

void* on_enter(
	int8_t link_id,
	com_header_t header,
	enter_t enter,
	comnet::node* node)
{
	/* Send a pong message back to the sender of the ping */
	node->send_pong(header.node_src_id,100);
	printf("Priotiry: %d\n", header.is_emergency);
	return 0;
}

/*
Since the sender of the Ping will receive a pong,
ensure that Pong messages are handled
*/

void* on_pong(
	int8_t link_id,
	com_header_t header,
	pong_t pong,
	comnet::node* node)
{
	/*Acknowledge that a Pong was received */
	printf("Got pong from Node %d\n", header.node_src_id);
	printf("Timestamp: %f\n", pong.timestamp);
	
	return 0;
}


void* rx_thread(){
	/* Create the UAV node at node 1*/
	comnet::node uav_node(1);

	/* Handle for the UDP Datalink */
	int8_t udp_1 = 0;

	/* Ceate a datalink at 1337 */
	uav_node.add_udp(&udp_1, 1337, "127.0.0.1");

	/*
	Map Node ID 2 to the IP address/port of the other datalink.
	This way, when a message is sent to Node 2, it'll be
	sent to the right IP address/port.
	*/
	uav_node.establish_udp(udp_1, 2, 1338, "127.0.0.1");

	/*
	This node will receive a ping from Node 1, so
	the Ping needs to be handled as the Pong was above
	*/
	uav_node.register_on_ping(on_ping);
	uav_node.register_on_enter(on_enter);

	std::chrono::milliseconds dura(500);
	while (1)
	{
		std::this_thread::sleep_for(dura);
	}
	return 0;
}

void* tx_thread(){
	/* Create the UAV node at node 2*/
	comnet::node gcs_node(2);

	/* Handle for the UDP Datalink */
	int8_t udp_1 = 0;

	/* Instead of Port: 1337, create a datalink at 1338 */
	gcs_node.add_udp(&udp_1, 1338, "127.0.0.1");

	/*
	Map Node ID 1 to the IP address/port of the other datalink.
	This way, when a message is sent to Node 1, it'll be
	sent to the right IP address/port.
	*/
	gcs_node.establish_udp(udp_1, 1, 1337, "127.0.0.1");

	/*
	This node will receive a ping from Node 1, so
	the Ping needs to be handled as the Pong was above
	*/


	std::chrono::milliseconds dura(1000);
	while (1)
	{

		gcs_node.send_ping(1, 0, false);
		std::this_thread::sleep_for(dura);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	/* Create both threads */
	
	std::thread rx(rx_thread);
	std::thread tx(tx_thread);

	/*
	Join threads to ensure main doesn't quit
	and the std::thread API is satisfied
	*/

	rx.join();
	tx.join();

	return 0;
}
