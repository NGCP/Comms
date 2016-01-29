import os
import shutil

#import all files with desired functions to create header and source code        
from proto_wrapper_src import *
from proto_wrapper_include import *

def generate_proto_wrapper(directory, include_extension, src_extension):
    """
    Function will create source & header folders for c# wrapper and files for c# wrapper.
    If files or folders already exists function will delete them.
    All C# files are auto generated in desired directory. No file are copied.
    """       
    if os.path.isdir(directory):
        shutil.rmtree(directory)
        print("Deleted directory: " + directory)

    if os.path.isdir(directory) == False:
        os.mkdir(directory)
        print("Created directory: " + directory)

    generate_proto_wrapper_include(directory, include_extension, src_extension)
    generate_proto_wrapper_src(directory, include_extension, src_extension)