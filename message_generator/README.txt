Python 3.5 (tested)
Python 2.7 (tested)


pydoc command
-------------
windows: python -m pydoc -w [module]

linux: pydoc -w [module]

document all files on subdirectory windows: python -m pydoc -w .\
-------------


*Files created with messages are:
	- comnet .h & .cpp
	- comnet_message .h & .cpp
	- comnet_protocol .h & .cpp
	- com_wrapper .h & .cpp
	- all files in:
		- ..\include\message
		- ..\src\message

*Files only copied (just add new files to native as needed)
	- comgen\native\src\
	- comgen\native\include\


generate.py - 	Generates files for c++ \ c# code with messages
		File location will be
		\..\comgen\ 
		\..\comwrapper\




Corresponding c++ / c# with its python file 	"...\message_generator\generate\"
-----------------------------------------------------------------------------------------
		c++ 				->		python
-----------------------------------------------------------------------------------------
...\comnet\include\message\******.h		->	message_include.py
...\comnet\include\comnet_message.h		->	message_file_include.py
...\comnet\include\comnet.h			->	protonet_file_include.py
...\comnet\include\comnet_protocol.h		->	protocol_file_include.py

...\comnet\src\message\*****.cpp		->	message_sources.py
...\comnet\src\protonet_message			->	message_file_sources.py
...\comnet\src\protonet.cpp			->	comnet_file_src.py
...\comnet\src\protonet.protocol.cpp		->	protocol_file_src.py
------------------------------------------------------------------------------------------
		c#				->			python
------------------------------------------------------------------------------------------
...\comwrapper\com_wrapper.h			->	com_wrapper_include.py
...\comwrapper\com_wrapper.cpp			->	com_wrapper_src.py
