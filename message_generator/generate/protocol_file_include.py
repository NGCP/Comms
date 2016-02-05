from .lower_case_acronym import *

def generate_protocol_file_include(directory, include_extension, src_extension):
    """
    Function will create the protocol header file in .../include/
    File has 4 main parts
        -include all message header files
        -union of all messages
        -unpack function
        -proto_typster function
    """
    #load header structure and the messages in variables from xml file
    import xml.etree.ElementTree as ET
    tree = ET.parse('message_definition.xml')
    protocol = tree.findall('message')
    header = tree.find('header')
    tab = '   '  
    #open file
    f = open(directory + "include/" + 'protonet_protocol' + include_extension, 'w')
    # warning
    f.write('/** @file This file was autogenerated. All changes will be undone. */\n\n')
    # include guards
    f.write('#ifndef _PROTOCOL_H_\n')
    f.write('#define _PROTOCOL_H_\n\n')
    
    #include message header
    f.write('#include <protonet_message' +include_extension+'>\n')
    # include all messages header files
    for message in protocol:
        name = message.get('name')
        filename = name.replace("_", "")
        f.write('#include <message/'+filename+include_extension+'>\n')
    
    #declare msg_data_offset should be size of header
    f.write('const uint8_t MSG_DATA_OFFSET = 28;\n\n')
    
    #create a union with all the message types as proto_msg_buf_t
    f.write("\n/**Global typdef union with all message types declared as proto_msg_bug_t.\n")
    f.write("Used to easily transmit data as same variable. Could of used base class as message and created derived classes for polymorphism.\n")
    f.write("Would have lost C ability if done so.*/\n")
    f.write('typedef union {\n')    
    for message in protocol:
        name = message.get('name')
        variable_name = lower_case_acronym(name)
        type_t_name = variable_name + "_t"        
        f.write(tab + type_t_name+ ' '+variable_name +';\n')
    f.write('} proto_msg_buf_t;\n\n')
    
    #declare unpack function
    f.write("/**Global function to unpack message with proto_msg and proto_msg_bug_t union.*/\n")
    f.write('void unpack_proto_msg_t(\n')
    f.write(tab + 'proto_msg_t* msg,\n')
    f.write(tab + 'proto_msg_buf_t* buf);\n\n')
    
    #declare proto_typster function
    f.write("/**Global function which returns the message string description*/\n")
    f.write('char* proto_typestr(proto_msg_type_t msg_type);\n\n')
    #end of guard
    f.write('#endif')
    
    print("Created: " + 'protonet_protocol' + include_extension)