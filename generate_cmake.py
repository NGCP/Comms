import os
import shutil

 
ACCEPTABLE_FILE_TYPES = ('.cpp', '.h', '.txt')    
    



fastqS = [f for f in os.listdir("comnet/src/") if f.endswith('.cpp')]
fastqSM = [f for f in os.listdir("comnet/src/message/") if f.endswith('.cpp')]


f = open('CMakeLists.txt', 'w+')



f.write("""
cmake_minimum_required(VERSION 3.0)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

project("NGCP COM")

include_directories(comnet/src/
		    comnet/src/message/
		    comnet/include/
		    comnet/include/message/))


add_library(NGCP_COM
""")

for fileToWrite in fastqS:
	f.write("comnet/src/" + fileToWrite + '\n')

for fileToWrite in fastqSM:
	f.write("comnet/src/message/" + fileToWrite + '\n')

f.write(")\n")







