"""
    Main Functions which is called to auto generate message source and header files
    for c / c++ and c# wrapper
    All files in generate are used.
"""

import sys

#prevent compiled files being created
sys.dont_write_bytecode = True

from generate.generate_protonet import *
from generate.generate_proto_wrapper import *    
    
#function calls   
generate_protonet("../protonet/", ".h", ".cpp")
generate_proto_wrapper("../protowrapper/", ".h", ".cpp")
#wait for enter to exit
raw_input("Press Enter to exit...")
