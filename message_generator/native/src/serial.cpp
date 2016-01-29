/* System Includes */

#include <stdint.h>

/* User Includes */
#include <serial.h>

/* Defines unix versions of serial functions */
#ifdef __unix__

/* Includes required for serial ports */
#include <stdio.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

int32_t serial_open(serial_fd_t* fd, serial_config_t* config)
{
	/* Typical method for openeing a serial port in unix */
	struct termios newtio;
	*fd = open((char*)config->device_path, O_RDWR | O_NOCTTY);
	if(*fd==-1){
		return -1;
	}
	tcgetattr(*fd, &newtio);
	memset(&newtio, 0, sizeof(newtio));
	speed_t speed = B115200;
	switch (config->baud_rate){
		case 110: speed = B110; break;
		case 300: speed = B300; break;
		case 600: speed = B600; break;
		case 1200: speed = B1200; break;
		case 2400: speed = B2400; break;
		case 4800: speed = B4800; break;
		case 9600: speed = B9600; break;
		case 19200: speed = B19200; break;
		case 38400: speed = B38400; break;
		case 57600: speed = B57600; break;
		case 115200: speed = B115200; break;
	}
	/* Input and output speed */
	cfsetispeed(&newtio, speed);
	cfsetospeed(&newtio, speed);

	/* 8n1 parity */
	newtio.c_cflag = CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNBRK | IGNPAR;
	newtio.c_oflag = 0;

	/* VMIN defines IO timeout properties */
	newtio.c_cc[VMIN] = 1;
	tcflush(*fd, TCIFLUSH);
	tcsetattr(*fd, TCSANOW, &newtio);
	return 0;
}
int32_t serial_close(serial_fd_t* fd)
{
#ifdef SERIAL_PRINTF
	printf("Serial: Link closed\n");
#endif
	close(*fd);
	return 0;
}

int32_t serial_send(
	serial_fd_t* fd,
	uint8_t* buf,
	int32_t tx_len)
{
	int32_t n;
	n = write(*fd, buf, tx_len);
	if (n!=1){
		return -1;
	}
	return 0;
}

int32_t serial_read(
	serial_fd_t* fd,
	uint8_t* buf,
	int32_t* rx_len)
{
	uint8_t b;
	int32_t n;
	*rx_len = 1;
	n = read(*fd, &b, 1);
	if (n!=1){
		return -1;
	}
	return b;
}

#endif

/* Here be dragons */
#ifdef _WIN32

int32_t serial_open(serial_fd_t* fd, serial_config_t* config)
{
	DCB dcbSerialParams;
	COMMTIMEOUTS timeouts;
	char port_name[80];
	/* \\\\.\\ is a COM port hack to get around 
	   Windows not opening ports above 9.
	*/
	sprintf(port_name, "\\\\.\\%s", config->device_path);
	*fd = CreateFileA((LPCSTR)port_name,
				GENERIC_READ | GENERIC_WRITE,
				0,
				0,
				OPEN_EXISTING,
				0,
				0);

	if (*fd == INVALID_HANDLE_VALUE) {
		puts("Invalid handle value\n");
		return -1;
		/* call GetLastError(); to gain more information */
	}

	memset( &dcbSerialParams, 0, sizeof( DCB ) );
	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	if (!GetCommState(*fd, &dcbSerialParams)) {
	}
	/* 8n1 parity */
	dcbSerialParams.BaudRate=config->baud_rate;
	dcbSerialParams.ByteSize=8;
	dcbSerialParams.StopBits=ONESTOPBIT;
	dcbSerialParams.Parity=NOPARITY;
	if(!SetCommState(*fd, &dcbSerialParams)){
		puts("Error in setting COMM state!\n");
		return -1;
	}


	/* Timeouts work, probably needs to be optimized 
	   I/O blocking and real-time behavior happens here
	*/
	timeouts.ReadIntervalTimeout=1;
	timeouts.ReadTotalTimeoutConstant=1;
	timeouts.ReadTotalTimeoutMultiplier=1;
	timeouts.WriteTotalTimeoutConstant=0;
	timeouts.WriteTotalTimeoutMultiplier=0;
	if(!SetCommTimeouts(*fd, &timeouts)){
		puts("Error in setting timeouts!\n");
		return -1;
	}

	return 0;

}
int32_t serial_close(serial_fd_t* fd)
{
	CloseHandle(*fd);
	return 0;
}
int32_t serial_send(
	serial_fd_t* fd,
	uint8_t* buf,
	int32_t tx_len)
{
	DWORD dwBytesRead = 0;
	if(!WriteFile(*fd, buf, tx_len, &dwBytesRead, NULL))
	{
		return -1;
	}
	return 0;

}

int32_t serial_read(
	serial_fd_t* fd,
	uint8_t* buf,
	int32_t* rx_len)
{
	wchar_t b[1];
	uint8_t byte[1];
	DWORD dwBytesRead = 0;
    if(!ReadFile(*fd, b, 1, &dwBytesRead, NULL)){
    	return -1;
    }

	/* Unicode to ANSI/ASCII conversion */
	wcstombs((char*)byte,b, 1);
	*buf = b[0];
	*rx_len = dwBytesRead;
    return 0;
}
Serial::Serial()
{
	/* IMPORTANT! Ensure all structs are zeroed out */
	memset(&info, 0, sizeof(serial_info_t));
	memset(&config, 0, sizeof(serial_config_t));
	memset(&fd, 0, sizeof(serial_fd_t));
	memset(rx_buf, 0, sizeof(rx_buf));
	connected = 0;
	link_id = 0;
}
Serial::~Serial()
{
	/* Ensure port gets closed on destructor, shouldn't be left open */
	this->close();
}

/* 
Implement the generic open/close/send/recv functions from the inherited 
datalink interface. open is harder to wrap, so ignore.
*/
int32_t Serial::open(uint32_t baud_rate, char device_path[50])
{
	config.baud_rate = baud_rate;
	strcpy(config.device_path, device_path);
	if(serial_open(&fd, &config) == 0)
	{
		datalink_type = SERIAL_TYPE;
		connected = 1;
	}
	else
	{
		return -1;
		connected = 0;
	}
	return 0;
}
int32_t Serial::close()
{
	if(connected)
	{
		return(serial_close(&fd));
	}
	return -1;
}
int32_t Serial::send(uint8_t node_id, uint8_t* tx_data, int32_t tx_len)
{
	if(connected)
	{
		return(serial_send(&fd, tx_data, tx_len));
	}
	return -1;
}
int32_t Serial::recv(uint8_t* rx_data, int32_t* rx_len)
{
	if(connected)
	{
		return(serial_read(&fd, rx_data, rx_len));
	}
	return -1;
}
int32_t Serial::establish(uint8_t node_id)
{
	info.node_id = node_id;
	return 0;
}

#endif
