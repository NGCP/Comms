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
*-------/
void* on_ping(
    int8_t link_id, 
    com_header_t header, 
    ping_t ping, 
    comnet::node* node)
{
    /* Send a pong message back to the sender of the ping */
    node->send_pong(header.node_src_id);
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
}


/* Create a sample thread to transmit messages */
void* tx_thread()
{
    /* 
    Create a comNet session at node ID 1.
    Imagine that this is a system, say the GCS 
    that is trying to ping the UAV.
    */
    comnet::node gcs_node(1);
    
    /* 
    A handle to reference the datalink by.
    This is similar to a socket or file descriptor
    */
    int8_t udp_1 = 0;
    
    /*
    Add a UDP datalink to the comNet session.
    The handle is passed in, so we can later establish
    that nodes are connected to the interface at a specified
    port and IP.
    
    Both the receiver and transmitter datalinks are bound to the same
    IP address, but given different ports to distinguish them apart.
    */
    gcs_node.add_udp(&udp_1, 1337, "127.0.0.1");
    
    /*
    Any message that is sent or addressed to node 2 is directly
    sent to Port: 1338, IP: 127.0.0.1, which will be set as 
    the address of the receiver.
    
    The udp_1 link handle is passed in to denote that this is
    the datalink that is connected to node through via
    the IP/Port mapping.
    */
    gcs_node.establish_udp(udp_1, 2, 1338, "127.0.0.1");
    
    /* 
    Since this node is pinging, it can expect a pong back.
    
    In order to handle the inbound messages, one must pass in
    the user defined callback using the register_on_[message_type]
    functions defined in the API.
    */
    gcs_node.register_on_pong(on_pong);
   
    /* Define a sleep duration of 1 second */
    std::chrono::milliseconds dura(1000);
    while(1)
    {
        /* Send a Ping to the UAV node */
        gcs_node.send_ping(2);
        /* Sleep for a second */
        std::this_thread::sleep_for(dura);
    }
    return 0;
}

void* rx_thread(){
    /* Create the UAV node at node 2*/ 
    comnet::node uav_node(2);

    /* Handle for the UDP Datalink */
    int8_t udp_1 = 0;
    
    /* Instead of Port: 1337, create a datalink at 1338 */
    uav_node.add_udp(&udp_1, 1338, "127.0.0.1");
    
    /* 
    Map Node ID 1 to the IP address/port of the other datalink.
    This way, when a message is sent to Node 1, it'll be
    sent to the right IP address/port.    
    */
    uav_node.establish_udp(udp_1, 1, 1337, "127.0.0.1");
    
    /* 
    This node will receive a ping from Node 1, so
    the Ping needs to be handled as the Pong was above
    */
    uav_node.register_on_ping(on_ping);

    std::chrono::milliseconds dura(500);
    while(1)
    {
        std::this_thread::sleep_for(dura);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    /* Create both threads */
    std::thread tx(tx_thread);
    std::thread rx(rx_thread);

    /* 
    Join threads to ensure main doesn't quit
    and the std::thread API is satisfied 
    */
    tx.join();
    rx.join();

    return 0;
}
