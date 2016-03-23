#ifndef ZIGBEE_H_
#define ZIGBEE_H_

#include <config.h>
#include <datalink.h>
#include <string>
#include <stdio.h>
#include <xbee.h>
#include <ctype.h>

#ifdef _WIN32
#include <Windows.h>
#pragma comment (lib, "libxbee3.lib")
#endif

int const MAX_ZIGBEE_CONNECTIONS = 25;

using namespace comnet;


class ZigBee : public datalink
{
public:
	ZigBee(uint32_t baud_rate, char device_path[50]);
	~ZigBee();

	/** Public method used to open connection.*/
	int32_t open(uint32_t baud_rate, char device_path[50]);
	/** Public method used to close connection.*/
	int32_t close();
	/** Public method used to send communication.*/
	int32_t send(uint8_t node_id, uint8_t* tx_data, int32_t tx_len);
	/** Public method used to receive communication.*/
	int32_t recv(uint8_t* rx_data, int32_t* rx_len);
	/** Public method used to establish communication.*/
	int32_t establish(uint8_t node_id, std::string address64Hex);

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


	uint8_t hexCharToInt(unsigned char value);
	uint8_t doubleHexCharToInt(unsigned char c1, unsigned char c2);
	void stringToAddress(std::string str, uint8_t length, xbee_conAddress &address);

	struct xbee *xbee;
	struct xbee_con *con[MAX_ZIGBEE_CONNECTIONS + 1];
	struct xbee_conAddress address[MAX_ZIGBEE_CONNECTIONS + 1];
	struct xbee_pkt *pkt;
	xbee_err ret;
	struct xbee_conSettings settings;
	uint8_t minIndex;
};

#endif //ZIGBEE_H_
