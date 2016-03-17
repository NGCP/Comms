CmakeLists.txt - shows example how to compile program using comnet with cmake.

To check serial ports :$ dmesg | grep tty

Look for FDTI serial device and mark down number next to ttyUSB for comport number.

When running the compiled program you must use sudo or the device path will be denied.

Program will fail if xbee is not connected.
From buid file locatoin:
$cmake "Unix Makefile" ../
$make
$sudo ./comnetTest
