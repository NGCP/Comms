Python 2.7 (tested)


pydoc command
-------------
windows: python -m pydoc -w [module]

linux: pydoc -w [module]

document all files on subdirectory windows: python -m pydoc -w .\
-------------


*Files created with messages are:
	- protonet .h & .cpp
	- protonet_message .h & .cpp
	- protonet_protocol .h & .cpp
	- proto_wrapper .h & .cpp
	- all files in:
		- ..\include\message
		- ..\src\message

*Files only copied (just add new files to native as needed)
	- protgen\native\src\
	- protgen\native\include\


generate.py - 	Generates files for c++ \ c# code with messages
		File location will be
		\..\protogen\ 
		\..\protowrapper\




Corresponding c++ / c# with its python file 	"...\message_generator\generate\"
-----------------------------------------------------------------------------------------
		c++ 				->		python
-----------------------------------------------------------------------------------------
...\protonet\include\message\******.h		->	message_include.py
...\protonet\include\protonet_message.h		->	message_file_include.py
...\protonet\include\protonet.h			->	protonet_file_include.py
...\protonet\include\protonet_protocol.h	->	protocol_file_include.py

...\protonet\src\message\*****.cpp		->	message_sources.py
...\protonet\src\protonet_message		->	message_file_sources.py
...\protonet\src\protonet.cpp			->	protonet_file_src.py
...\protonet\src\protonet.protocol.cpp		->	protocol_file_src.py
------------------------------------------------------------------------------------------
		c#				->			python
------------------------------------------------------------------------------------------
...\protowrapper\proto_wrapper.h		->	proto_wrapper_include.py
...\protowrapper\proto_wrapper.cpp		->	proto_wrapper_src.py
