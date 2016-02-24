---------------------------------------------------------------------------------------------
*** Priority Queue Update Notes
---------------------------------------------------------------------------------------------
* Because header stuct has bitfield variable in c++ and c# does not the 
* autogeneration of the stuct is manual with in python code and not part of the .xml file

added files:
	- priority_queue.h
	- standard_logic.h

edited files:
	- queue.h 
		- edited priority as queue
	- comnet_file_include.py
		- edited all message send_name to include emergency bool as default argument of false
	- message_file_include.py 
		- edited 540 to #define MAX_DATA_SIZE
		- edited header stuct creationg to inlcude after message_length ' : 15, is_emergency : 1;'
	- message_file_src.py 
		- pack / unpack header function added merged data bit shift
		- pack / unpack header offset for message_length changed to merged_data
	- comnet_file_source.y
		- removed queue instantiation in node constructor not sure why Mario?
		- added argument for all send_name messages called bool is_emergency
		- added in send_name function the assignement of com_msg.header.is_emergency = is_emergency argument
	- com_wrapper.h
		- add bool emergency to header struct
		- all send_name functions had added bool emergency variable
		- no default arguments in c# so the send_name method will be over written
	- com_wrapper.cpp
		- add new method to override default method of send_name
		- defauflt send_name method call new method with extra 0 argument