import os
import shutil

 
ACCEPTABLE_FILE_TYPES = ('.cpp', '.h', '.txt')    
    



fastqS = [f for f in os.listdir("comnet/src/") if f.endswith('.cpp')]
fastqSM = [f for f in os.listdir("comnet/src/message/") if f.endswith('.cpp')]


f = open('CMakeLists.txt', 'w+')



f.write("""
cmake_minimum_required(VERSION 3.0)
project("NGCP_COM")

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

include_directories(comnet/src/
		    comnet/src/message/
		    comnet/include/
		    comnet/include/message/
		    cryptopp563/include/
		    libxbee3-3.0.11/include/)


add_library(NGCP_COM
""")

for fileToWrite in fastqS:
	f.write("comnet/src/" + fileToWrite + '\n')

for fileToWrite in fastqSM:
	f.write("comnet/src/message/" + fileToWrite + '\n')

f.write(")\n")

f.write('''
target_link_libraries (NGCP_COM ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries (NGCP_COM ${CMAKE_CURRENT_SOURCE_DIR}/cryptopp563/linux/libcryptopp.a)

target_link_libraries (NGCP_COM ${CMAKE_CURRENT_SOURCE_DIR}/libxbee3-3.0.11/linux/libxbee.so)

''')







