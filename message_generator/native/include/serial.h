#ifndef SERIAL_H_
#define SERIAL_H_
/**@file
	Globabl typedef used for serial communication
	and Global functions which are just called my Serial class methods
	@todo No reason class calls global methods besides possible conflicts of global variables being used.
*/
/* System Includes */
#include <stdint.h>
#include <stdio.h>
#include <string.h>


/* User Includes */
#include <config.h>
#include <datalink.h>



#ifndef _WIN32
/**Global Typedef Define a cross platform serial handle for Linux*/
typedef int32_t serial_fd_t;
#endif

#ifdef _WIN32
/*Global Typedef Define a cross platform serial handle for Windows*/
typedef HANDLE serial_fd_t;
#endif

/**Global Typedef Configuration struct to store in the datalink class & methods */
typedef struct serial_config_s
{
	uint32_t baud_rate;
	char device_path[64];
}serial_config_t;

/**Global Typedef Store serial port configuration data, handle and connected node_id */
typedef struct serial_info_s
{
	serial_fd_t fd;
	serial_config_t config;
	uint8_t node_id;
}serial_info_t;

/**Global function used for serial communication to open connection will be called by serial class*/
int32_t serial_open(serial_fd_t* fd, serial_config_t* config);
/**Global function used for serial communication to close connection will be called by serial class*/
int32_t serial_close(serial_fd_t* fd);
/**Global function used for serial communication to configure connection*/
int32_t serial_config(serial_fd_t* fd, serial_config_t* config);
/**Global function used for serial communication to read data will be called by serial class*/
int32_t serial_read(
	serial_fd_t* fd,
	uint8_t* buf,
	int32_t* rx_len);
/**Global function used for serial communication to send data will be called by serial class*/
int32_t serial_send(
	serial_fd_t* fd,
	uint8_t* buf,
	int32_t tx_len);

using namespace comnet;
/** 
Datalink class is inherited to provide abstraction from transport layers 
The serial port is as a one-to-one connection with a specified node.
*/
class Serial : public datalink
{
public: 
	Serial();
	~Serial();

	/* 
	Implement the generic open/close/send/recv functions from the inherited 
	datalink interface. open is harder to wrap, so ignore.
	*/
	/**Public method calls global function declared in serial.h file serial_open*/
	int32_t open(uint32_t baud_rate, char device_path[50]);
	/**Public method calls global function declared in serial.h file serial_close*/
	int32_t close();
	/**Public method calls global function declared in serial.h file serial_send*/
	int32_t send(
		uint8_t node_id, 
		uint8_t* tx_data, 
		int32_t tx_len);
	/**Public method calls global function declared in serial.h file serial_recv*/
	int32_t recv(uint8_t* rx_data, int32_t* rx_len);
	/*
	Serial is one-to-one, so each serial datalink is mapped to
	a single node ID
	*/
	/** Public method used to esstablish a serial connection must be used*/
	int32_t establish(uint8_t node_id);
	
	/** Used datalink inherited data member*/
	using datalink::set_link_id;
    /** Used datalink inherited data member*/
	using datalink::get_link_id;
    /** Used datalink inherited data member*/
	using datalink::get_datalink_type;
    /** Used datalink inherited data member*/
	using datalink::is_connected;
private:
    /** Used datalink inherited data member*/
	using datalink::connected;
    /** Used datalink inherited data member*/
	using datalink::link_id;
    /** Used datalink inherited data member*/
	using datalink::rx_buf;
    /** Used datalink inherited data member*/
	using datalink::datalink_type;
    /** Private data member used for socket programming*/
	serial_fd_t fd;
    /** Private data member used for socket programming*/
	serial_config_t config;
    /** Private data member used for socket programming*/
	serial_info_t info;
    /** Private data member used for socket programming*/
	uint8_t rx_node;
};

#endif /* SERIAL_H_ */
