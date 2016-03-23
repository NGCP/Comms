"""
    File is used to auto geneate all possible call back functions to copy paste in platform code
"""

import sys

#prevent compiled files being created
sys.dont_write_bytecode = True
  
#load header structure and the messages in variables from xml file
import xml.etree.ElementTree as ET
tree = ET.parse('message_generator/message_definition.xml')
comcol = tree.findall('message')
f = open("callbacklist.cpp", "w+")

for message in comcol:
	name = message.get('name')
	f.write("void* " + name + "(int8_t link_id, com_header_t header, ping_t ping, comnet::node* node)\n")
	f.write("{\n\n}\n\n")
f.close()
