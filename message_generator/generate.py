"""
    Main Functions which is called to auto generate message source and header files
    for c / c++ and c# wrapper
    All files in generate are used.
"""

import sys

#prevent compiled files being created
sys.dont_write_bytecode = True

from generate.generate_comnet import *
from generate.generate_com_wrapper import *    
    
#function calls   
generate_comnet("../comnet", ".h", ".cpp", "native")
generate_com_wrapper("../comwrapper", ".h", ".cpp", True)
#wait for enter to exit
if( sys.version_info >= (3,0)):
    input("Press Enter to exit...")
else:
    raw_input("Press Enter to exit...")
