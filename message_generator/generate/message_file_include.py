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
    f = open(directory + "include/" + 'comnet_message' + include_extension, 'w')
    # warning
    f.write('/** @file This file was auto generated. All changes will be undone. */\n\n')
    # include guards
    f.write('#ifndef _COMNET_MSG_H_\n')
    f.write('#define _COMNET_MSG_H_\n\n')
    # includes
    f.write('#include <stdint.h>\n')
    f.write('#include <stdio.h>\n')
    f.write('#include <comnet_marshal'+include_extension+'>\n\n')
    
    #define max data zize 
    f.write("#define MAX_DATA_SIZE               540\n")
    # header struct
    f.write("/** Global typdef struct which is the packet header used to transmit data. */\n")
    f.write('typedef struct {\n')
    for field in header:
        if(check_valid_type(field.get('type')) == 0):
            print ('error: field: '+ field.get('name') + ' in header has invalid type.')
        f.write(tab + field.get('type') + ' ' + field.get('name') + ';\n')
    #Priority Queue real crap way to split message_length: 15, is_emergency: 1;
    f.seek(-3, 1)
    f.write("\t: 15," "\n" + tab + tab + tab + tab +"is_emergency \t: 1;\n")
    f.write('} com_header_t;\n\n')
    
    # checksum
    f.write("/**Global typdef which hold checksum value.*/\n")
    f.write('typedef int8_t checksum_t;\n\n')
    # direction
    f.write("/**Global enum to determine if message destination is input or output.*/\n")
    f.write('typedef enum com_direction {\n')
    f.write(tab+ 'Com_Out = 0,\n')
    f.write(tab+ 'Com_In = 1\n')
    f.write('} com_direction_t;\n\n')
    
    #msg_t struct
    f.write("/**Global typdef struct of the data packet which contains typdef header, enum direction, and typdef checksum. */\n")
    f.write('typedef struct {\n')
    f.write(tab + 'com_header_t header;\n')
    f.write(tab + 'com_direction_t direction;\n')
    f.write(tab + 'uint8_t link_id;\n')
    f.write(tab + 'uint8_t data[MAX_DATA_SIZE];\n')
    f.write(tab + 'uint16_t  tx_len;\n')
    f.write(tab + 'checksum_t checksum;\n')
    f.write('} com_msg_t;\n\n')
    
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
    f.write(tab + 'com_header_t* header,\n')
    f.write(tab + 'msg_offset offset);\n\n')
    #unpack header
    f.write("/**Global function to unpack header*/\n")
    f.write('msg_offset unpack_header(\n')
    f.write(tab + 'msg_offset offset,\n')
    f.write(tab + 'com_header_t* out_ptr);\n\n')        
    
    # message type enum
    f.write("/**Global enum auto created to id com message type*/\n")
    f.write('typedef enum {\n')    
    for message in protocol:
        f.write(tab+'Proto_'+ message.get('name') + ' = ' + message.get('id') + ',\n')
    f.write('} com_msg_type_t;\n\n')
    
    # include guard #endif
    f.write('#endif')
    
    print("Created: " + 'comnet_message' + include_extension)
