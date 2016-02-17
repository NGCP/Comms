import os
import shutil

 
ACCEPTABLE_FILE_TYPES = ('.cpp', '.h', '.txt')    
    



fastqS = [f for f in os.listdir("protonet/src/") if f.endswith('.cpp')]
fastqSM = [f for f in os.listdir("protonet/src/message/") if f.endswith('.cpp')]


f = open('CMakeLists.txt', 'w+')



f.write("""
cmake_minimum_required(VERSION 3.0)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

project("NGCP_COM")

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

include_directories(protonet/src/
		    protonet/src/message/
		    protonet/include/
		    protonet/include/message/
		    cryptopp563/include/)


add_library(NGCP_COM
""")

for fileToWrite in fastqS:
	f.write("protonet/src/" + fileToWrite + '\n')

for fileToWrite in fastqSM:
	f.write("protonet/src/message/" + fileToWrite + '\n')

f.write(")\n")

f.write('''
target_link_libraries (NGCP_COM ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries (NGCP_COM ${CMAKE_CURRENT_SOURCE_DIR}/cryptopp563/linux/libcryptopp.a)

''')







