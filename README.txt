Files should already be compiled for linux and windows in build folder.

Make sure you use correct data link for your platform and corresponding platforms listed under xBee_to_Platform.
    The ID is the row number. 
    ex: GCS is ID 1 with mac address "0013A2004067E4AE"
    
    //GCS setting up connection to UGV on com port 6 through xbee in windows c++
    int8_t zigBee_1 = 0;
   	comnet::node gcs_node(1);
    gcs_node.add_zigBee(&udp_1, 57600, "6");	
	gcs_node.establish_zigBee(zigBee_1, 2, "0013A2004067E4A0");


All OS and language versions require key.txt file to be located with compiled program to read AES key. If you have 16 chars and recieve error thre are 17 keys you probably have an extra white space at the end of the file.


---------------------------------------------------------
In linux just look at examples in cmake file "C++ Linux Example / build" for linking and including needed resources.

---------------------------------------------------------
In windows C++ you will need to include folders:
libxbee3-3.0.11/include/
cryptopp563/include/
comnet/include/
comnet/include/message/

Link libraries:
build/win32/"Debug or Release"/NGCP_COM.lib
libxbee3-3.0.11/win32/libxbee3.lib
cryptopp563/win32/"Debug or Release"/cryptlib.lib

You will need to put file:
"libxbee3-3.0.11/win32/libxbee3.dll"
into the output directory with the created compiled file or it will not run.

----------------------------------------------------------
In windows C# just add NGCP_COM.dll

If you need help contact me or if you find an error contact me or put an error on Github website.
Contact: Michael Wallace
Email: Michael.Wallace30@gmail.com
