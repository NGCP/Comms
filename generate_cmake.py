import os
import shutil

 
ACCEPTABLE_FILE_TYPES = ('.cpp', '.h', '.txt')    
    



fastqS = [f for f in os.listdir("protonet/src/") if f.endswith('.cpp')]
fastqSM = [f for f in os.listdir("protonet/src/message/") if f.endswith('.cpp')]


f = open('CMakeLists.txt', 'w+')



f.write("""
cmake_minimum_required(VERSION 3.0)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

project("NGCP COM")

include_directories(protonet/src/
		    protonet/src/message/
		    protonet/include/
		    protonet/include/message/))


add_library(NGCP_COM
""")

for fileToWrite in fastqS:
	f.write("protonet/src/" + fileToWrite + '\n')

for fileToWrite in fastqSM:
	f.write("protonet/src/message/" + fileToWrite + '\n')

f.write(")\n")







