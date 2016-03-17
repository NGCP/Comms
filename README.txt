Files should already be compiled for linux and windows in build folder.

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
