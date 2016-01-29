from check_valid_type import *

def generate_message_file_include(directory, include_extension, src_extension):
    """
    Function will create the message header file in .../include/
    File has 8 main parts
        -header structure
        -checksum
        -direction
        -msg_t
        -pack sync
        -pack_header
        -unpack header
        -msg_type_t (used for message identification)
    """
    
    #load header structure and the messages in variables from xml file
    import xml.etree.ElementTree as ET
    tree = ET.parse('message_definition.xml')
    protocol = tree.findall('message')
    header = tree.find('header')
    tab = '   '        
    #open file
    f = open(directory + "include/" + 'protonet_message' + include_extension, 'w')
    # warning
    f.write('/** @file This file was auto generated. All changes will be undone. */\n\n')
    # include guards
    f.write('#ifndef _PROTONET_MSG_H_\n')
    f.write('#define _PROTONET_MSG_H_\n\n')
    # includes
    f.write('#include <stdint.h>\n')
    f.write('#include <stdio.h>\n')
    f.write('#include <protonet_marshal'+include_extension+'>\n\n')
    
    # header struct
    f.write("/** Global typdef struct which is the packet header used to transmit data. */\n")
    f.write('typedef struct {\n')
    for field in header:
        if(check_valid_type(field.get('type')) == 0):
            print 'error: field: '+ field.get('name') + ' in header has invalid type.'
        f.write(tab + field.get('type') + ' ' + field.get('name') + ';\n')
    f.write('} proto_header_t;\n\n')
    
    # checksum
    f.write("/**Global typdef which hold checksum value.*/\n")
    f.write('typedef int8_t checksum_t;\n\n')
    # direction
    f.write("/**Global enum to determine if message destination is input or output.*/\n")
    f.write('typedef enum proto_direction {\n')
    f.write(tab+ 'Proto_Out = 0,\n')
    f.write(tab+ 'Proto_In = 1\n')
    f.write('} proto_direction_t;\n\n')
    
    #msg_t struct
    f.write("/**Global typdef struct of the data packet which contains typdef header, enum direction, and typdef checksum. */\n")
    f.write('typedef struct {\n')
    f.write(tab + 'proto_header_t header;\n')
    f.write(tab + 'proto_direction_t direction;\n')
    f.write(tab + 'uint8_t link_id;\n')
    f.write(tab + 'uint8_t data[540];\n')
    f.write(tab + 'uint16_t  tx_len;\n')
    f.write(tab + 'checksum_t checksum;\n')
    f.write('} proto_msg_t;\n\n')
    
    #pack sync functions
    f.write("/**Global variable for message offset used to pack data for to transmit*/\n")
    f.write('msg_offset pack_sync(msg_offset offset);\n\n')
    f.write("/**Global function pack checksum*/\n")
    f.write('msg_offset pack_checksum(\n')
    f.write(tab + 'const msg_offset start,\n')
    f.write(tab + 'const msg_offset end);\n\n')
    #pack header
    f.write("/**Global function to pack header*/\n")
    f.write('msg_offset pack_header(\n')
    f.write(tab + 'proto_header_t* header,\n')
    f.write(tab + 'msg_offset offset);\n\n')
    #unpack header
    f.write("/**Global function to unpack header*/\n")
    f.write('msg_offset unpack_header(\n')
    f.write(tab + 'msg_offset offset,\n')
    f.write(tab + 'proto_header_t* out_ptr);\n\n')        
    
    # message type enum
    f.write("/**Global enum auto created to id proto message type*/\n")
    f.write('typedef enum {\n')    
    for message in protocol:
        f.write(tab+'Proto_'+ message.get('name') + ' = ' + message.get('id') + ',\n')
    f.write('} proto_msg_type_t;\n\n')
    
    # include guard #endif
    f.write('#endif')
    
    print("Created: " + 'protonet_message' + include_extension)