from .lower_case_acronym import *
from .check_valid_type import *

def generate_message_includes(directory, include_extension, src_extension):
    """
    Function will create all message header files in .../include/message/
    File has 3 main parts
        -message structure
        -pack / unpack
        -encode
    """
    #load header structure and the messages in variables from xml file
    import xml.etree.ElementTree as ET
    tree = ET.parse('message_definition.xml')
    protocol = tree.findall('message')
    header = tree.find('header')
    tab = '   '
    for message in protocol:#for each message
        #declare message variables from xml
        name = message.get('name')        
        variable_name = lower_case_acronym(name)
        type_t_name = variable_name + "_t"
        filename = name.replace("_", "")
        #open file
        f = open(directory + "/include/message/"+ filename + include_extension, 'w')
        # warning message
        f.write('/**@file This file was autogenerated. All changes will be undone. */\n\n')
        f.write('/** Message: '+ name +', ID: ' + message.get('id')+ '*/\n\n')
        # include guards
        f.write('#ifndef ' + '_' + name.upper()+'_H_\n')
        f.write('#define ' + '_' + name.upper()+'_H_\n\n')
        # protonet includes
        f.write('#include <comnet_marshal'+include_extension+'>\n')
        f.write('#include <comnet_message'+include_extension+'>\n\n')
                
        # message structure
        f.write('typedef struct {\n')
        for field in message:
            if(check_valid_type(field.get('type')) == 0):
                print ('error: field: '+ field.get('name') + ' in message: '+ name+ ' has invalid type.')
            f.write(tab + field.get('type') + ' ' + field.get('name') + ';\n')
            
            
        f.write('} '+type_t_name+';\n\n')
        # pack/unpack
        f.write('msg_offset pack_'+variable_name+'(\n')
        f.write(tab+type_t_name+'* ' +variable_name +',\n')
        f.write(tab+'msg_offset offset);\n\n')

        f.write('msg_offset unpack_'+variable_name+'(\n')
        f.write(tab+'msg_offset offset,\n')        
        f.write(tab+type_t_name+'* ' 'out_ptr);\n\n')
        
        # encode
        f.write('void encode_' + variable_name+'(\n')
        f.write(tab + 'uint8_t src_id,\n')
        f.write(tab + 'uint8_t dest_id,\n')
        f.write(tab + 'uint8_t msg_ttl,\n')
        f.write(tab + 'uint8_t seq_number,\n')
        f.write(tab + type_t_name+'* tx_msg,\n')
        f.write(tab + 'com_msg_t* msg);\n')
        
        # include guard #endif
        f.write('#endif')
       
        f.close()
        
        print("Created message header: " + filename + include_extension)
