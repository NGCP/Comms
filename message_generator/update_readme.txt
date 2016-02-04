---------------------------------------------------------------------------------------------
*** AES CFB Mode 128 Bit Encryption Update Notes
---------------------------------------------------------------------------------------------
*If creating C# wrapper define _CLR in protonet.h else leave comment  (#define _CLR)
*Add #define to C# include protonet.h if header files are needed
*key.txt file must be with c# binary or it wont be found
*C++ codem ust include cryptlib.lib

	- Created an array pack and unpack for protonet marshall
	- added 16 byte array to header struct for rand iv
	- renamed "queue.h" to "pqueue.h" because of conflict with cryptopp include queue
	- In protonet_protocol.h changed size of msg_data_offset which is the size of the header struct
	- In proto+parser changed literal 12 to use msg_data_offset constant from protonet_protocol.h
	- size of msg_data_offset doesnt seem to matter, but it should
	- protonet will load file from key.txt to read in 16 byte encryption key
	- removed queue macros
	- proto wrapper has been changed to handle c++ array in header struct
	- rand IV class was added due to conflict of "osrng.h" and c# wrapper
	- C# wrapper can not use fstream added managed c++ code to load ket.txt file





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
	- protonet_file_include.py
		- edited all message send_name to include emergency bool as default argument of false
	- message_file_include.py 
		- edited 540 to #define MAX_DATA_SIZE
		- edited header stuct creationg to inlcude after message_length ' : 15, is_emergency : 1;'
	- message_file_src.py 
		- pack / unpack header function added merged data bit shift
		- pack / unpack header offset for message_length changed to merged_data
	- protonet_file_source.y
		- removed queue instantiation in node constructor not sure why Mario?
		- added argument for all send_name messages called bool is_emergency
		- added in send_name function the assignement of proto_msg.header.is_emergency = is_emergency argument
	- proto_wrapper.h
		- add bool emergency to header struct
		- all send_name functions had added bool emergency variable
		- no default arguments in c# so the send_name method will be over written
	- proto_wrapper.cpp
		- add new method to override default method of send_name
		- defauflt send_name method call new method with extra 0 argument