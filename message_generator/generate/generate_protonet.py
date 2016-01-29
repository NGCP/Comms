import os
import shutil

#import all files with desired functions to create header and source code        
from message_file_include import *
from message_file_src import *
from message_includes import *
from message_sources import *
from native import *
from protocol_file_include import *
from protocol_file_src import *
from protonet_file_include import *
from protonet_file_src import *

def generate_protonet(directory, include_extension, src_extension):
    """
    Generate Function will create source & header folders / files from message_definition.xml
    If files or folders already exists function will delete them.
    Auto Gnerated Files include:
        - protnet_message
        - protnet
        - protonet_protocol
        - All message files in folder /message/
    It will also copy files in /native 
    """  
    #check if directory exists if not create directories
    try:
        if os.path.isdir(directory) == False:
            os.mkdir(directory)
            print("Created directory: " + directory)
    except Exception, e:
        print e            
    #delete old files if they exist
    try:
        if os.path.isdir(directory+'src/'):
            shutil.rmtree(directory+'src/')
            print("Deleted directory: " + directory + "src/")
        if os.path.isdir(directory+'include/'):
            shutil.rmtree(directory+'include/')
            print("Deleted directory: " + directory + "include/")
    except Exception, e:
        print e
    #make the needed directories /src, /include, /src/message, /include/message
    try:
        os.mkdir(directory+'src/')
        print("Created directory: " + directory + "src/")
        os.mkdir(directory+'include/')
        print("Created directory: " + directory + "include/")
        os.mkdir(directory+'src/message/')
        print("Created directory: " + directory + 'src/message/')
        os.mkdir(directory+'include/message/')
        print("Created directory: " + directory + 'include/message/')
    except Exception, e:
        print e
        
    #generate the files    
    generate_message_sources(directory, include_extension, src_extension)
    generate_message_includes(directory, include_extension, src_extension)
    generate_message_file_include(directory, include_extension, src_extension)
    generate_message_file_src(directory, include_extension, src_extension)
    generate_protocol_file_include(directory, include_extension, src_extension)
    generate_protocol_file_src(directory, include_extension, src_extension)
    generate_protonet_file_include(directory, include_extension, src_extension)
    generate_protonet_file_src(directory, include_extension, src_extension)    
    #copy native files
    generate_native(directory)
