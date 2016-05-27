// System Includes
#include <string.h>
#include <stdint.h>

// User Includes
#include <error_handle.h>
#include <zigBee.h>
	
ZigBee::ZigBee(uint32_t baud_rate, char device_path[50])
{
	for (int x = 1; x <= MAX_ZIGBEE_CONNECTIONS + 1; x++) {
		con[x] = NULL;
	}

	minIndex = MAX_ZIGBEE_CONNECTIONS + 1;
	memset(rx_buf, 0, sizeof(rx_buf));
	connected = 0;

	link_id = 0;
	open(baud_rate, device_path);

}

ZigBee::~ZigBee()
{
	this->close();
}

/** Public method used to open connection.*/
int32_t ZigBee::open(uint32_t baud_rate, char device_path[50])
{
	

#ifdef _WIN32
	char port_name[55];
	sprintf(port_name, "\\\\.\\COM%s", device_path);//change to com
	if ((ret = xbee_setup(&xbee, "xbee5", port_name, baud_rate)) != XBEE_ENONE) {
		printf("Construct ret: %d (%s)\n", ret, xbee_errorToStr(ret));
        throw error::ConnectionException(error::OSErrors::error_no_os, error::error_xbee_error_init);
		//return ret;
	}
	connected = 1;
	datalink_type = ZIGBEE_TYPE;
	return 1;
#endif


	if ((ret = xbee_setup(&xbee, "xbee5", device_path, baud_rate)) != XBEE_ENONE) {
		printf("Construct ret: %d (%s)\n", ret, xbee_errorToStr(ret));
        throw error::ConnectionException(error::OSErrors::error_no_os, error::error_xbee_error_init);
		//return ret;
	}
	connected = 1;
	datalink_type = ZIGBEE_TYPE;
	return 1;
}

/** Public method used to close connection.*/
int32_t ZigBee::close()
{
	for (int x = 1; x <= MAX_ZIGBEE_CONNECTIONS + 1; x++) {
		if (con[x] != NULL) {
         if ((ret = xbee_conEnd(con[x])) != XBEE_ENONE) {
            xbee_log(xbee, -1, "xbee_conEnd() returned: %d", ret);
            throw error::ConnectionException(error::OSErrors::error_no_os, error::error_xbee_error_close);
            //return ret;
         }
      }
   }
		
		if (xbee != NULL)xbee_shutdown(xbee);
	

	return 1;
}

/** Public method used to send communication.*/
int32_t ZigBee::send(uint8_t node_id, uint8_t* tx_data, int32_t tx_len)
{
	if (con[node_id] != NULL)
	{
		xbee_connTx(con[node_id], NULL, tx_data, tx_len);
	}
	
	return 1;
}

/** Public method used to receive communication.*/
int32_t ZigBee::recv(uint8_t* rx_data, int32_t* rx_len)
{
	*rx_len = 0;
  // Check which node a package is coming from.
  for (int i = 0; i < nodes.size(); ++i) {
    // Receive a package from the node.
    xbee_conRx(con[nodes.at(i)], &pkt, NULL);
    // Package is not null, means we got a package from somewhere.
    if (pkt != NULL) {
      for(int i = 0; i < pkt->dataLen; i++) {
        rx_data[i] = pkt->data[i];
      }
   
      *rx_len = pkt->dataLen;
      if(xbee_pktFree(pkt) != XBEE_ENONE);
      // Try to save time by breaking off when a package is read.
      break;
    }
  }
//	if ((ret = xbee_conRx(con[6], &pkt, NULL)) != XBEE_ENONE) {
		//printf("Error after calling xbee_conRx(): %s\n", xbee_errorToStr(ret));
//	}
//	else {
//		for (int i = 0; i < pkt->dataLen; i++) {
//			rx_data[i] = pkt->data[i];
//		}
//		*rx_len = pkt->dataLen;
//		if (xbee_pktFree(pkt) != XBEE_ENONE);
//	}
	return 1;
}

/** Public method used to establish communication.*/
int32_t ZigBee::establish(uint8_t node_id, std::string address64Hex)
{
	if (node_id > 0 && node_id <= (MAX_ZIGBEE_CONNECTIONS + 1))
	{
		if (con[node_id] == NULL)
		{

			memset(&address, 0, sizeof(address));
			stringToAddress(address64Hex, 16, address[node_id]);

			if ((ret = xbee_conNew(xbee, &con[node_id], "Data", &address[node_id])) != XBEE_ENONE) {
				xbee_log(xbee, -1, "xbee_conNew() node_id: %d  returned: %d (%s)", node_id, ret, xbee_errorToStr(ret));
                throw error::ConnectionException(error::OSErrors::error_no_os, error::error_xbee_error_new_connection);
				//return ret;
			}
      // Push node id into the list to record the availabe nodes.
      nodes.push_back(node_id);
//			xbee_conSettings(con[node_id], NULL, &settings);
//			settings.catchAll = 1;
//			xbee_conSettings(con[node_id], &settings, NULL);
			if (node_id < minIndex)minIndex = node_id;
			
		}
		else
		{
			throw error::ConnectionException(error::OSErrors::error_no_os, error::error_already_connected);
		}
	}

	
	return ret;
}



uint8_t ZigBee::hexCharToInt(unsigned char value)
{
	if (isalpha(value))
	{
		unsigned char c = toupper(value);
		return c = c - '7';// or c -= 55
	}
	else if (isdigit(value))
	{
		return value = value - '0';
	}
	return 0;
}

// 16 ^ 1 * 15 + 16 ^ 0 * 15
uint8_t ZigBee::doubleHexCharToInt(unsigned char c1, unsigned char c2)
{
	//16 ^ 1 * C1 + 16 ^ 0 * C2
	uint8_t value = hexCharToInt(c1) * 16;
	value += hexCharToInt(c2);
	return value;
}

void ZigBee::stringToAddress(std::string str, uint8_t length, xbee_conAddress &address)
{
	//if no spaces in string increment is 2 if spaces increment is 3
	int increment = (str[2] == ' ') ? 3 : 2;
	address.addr64_enabled = 1;
	int x = 0;
	//check if string is right size to calc double hex char to int
	if ((increment == 2 && (length) % increment == 0)
		|| (increment == 3 && ((length - 1) % increment == 0)))
	{
		//loop for each pair of chars to find int value ex: FF = 255
		for (int index = 0; index < length; index += increment)
		{
			
			address.addr64[x] = doubleHexCharToInt(str[index], str[index + 1]);
			x++;
		}
	}
	else
	{
		throw error::InternalException(error::OSErrors::error_no_os, error::error_invalid_hex_string);
	}
}
