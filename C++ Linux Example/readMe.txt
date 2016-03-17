CmakeLists.txt - shows example how to compile program using comnet with cmake.

To check serial ports :$ dmesg | grep tty

Look for FDTI serial device and mark down number next to ttyUSB for comport number or for serial look for ttyS.

When running the compiled program you must use sudo or the device path will be denied.

When entering ports for linux use the whole path.
Ex usb port 1
"/dev/ttyUSB1"
Ex serail port 0
"/dev/ttyS0"

Program will fail if xbee is not connected.
From buid file locatoin:
$cmake "Unix Makefile" ../
$make
$sudo ./comnetTest
