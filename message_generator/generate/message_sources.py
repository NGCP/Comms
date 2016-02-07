from .lower_case_acronym import *
from .check_valid_type import *

# generates source files for protonet messages
def generate_message_sources(directory, include_extension, src_extension):
    """
    Function will create all message source files in .../src/message/
    File has 3 main parts
        -pack
        -unpack
        -encode
    """
    #load header structure and the messages in variables from xml file
    import xml.etree.ElementTree as ET
    tree = ET.parse('message_definition.xml')
    protocol = tree.findall('message')
    header = tree.find('header')
    tab = '   '        
    for message in protocol:
        #declare message variables from xml    
        name = message.get('name')
        variable_name = lower_case_acronym(name)
        type_t_name = variable_name + "_t"
        filename = name.replace("_", "")
        #open file
        f = open(directory + "/src/message/" + filename + src_extension, 'w')
        # warning message
        f.write('/* This file was autogenerated. All changes will be undone. */\n\n')        
        f.write('/* Message: '+ name +', ID: ' + message.get('id')+ '*/\n\n')
        # includes
        f.write('#include <protonet_marshal'+include_extension+'>\n')
        f.write('#include <protonet_message'+include_extension+'>\n')
        f.write('#include <message/'+filename+include_extension+'>\n\n')
        
        # pack
        f.write('msg_offset pack_'+variable_name+'(\n')
        f.write(tab+type_t_name+'* ' +variable_name +',\n')
        f.write(tab+'msg_offset offset)\n')
        f.write('{\n')

        for field in message:
            if(check_valid_type(field.get('type')) == 0):
                print ('error: field: '+ field.get('name') + ' in message: '+ name+ ' has invalid type.')
            f.write(tab + 'offset = pack_'+field.get('type') + '(' + variable_name+ '->'+field.get('name') + ',offset);\n')
        f.write(tab + 'return offset;\n')
        f.write('}\n\n')
        
        #unpack
        f.write('msg_offset unpack_'+variable_name+'(\n')
        f.write(tab+'msg_offset offset,\n')        
        f.write(tab+type_t_name+'* ' 'out_ptr)\n')
        f.write('{\n')
        message_length = 0
        for field in message:
            if(check_valid_type(field.get('type')) == 0):
                print ('error: field: '+ field.get('name') + ' in message: '+ name+ ' has invalid type.')
            field_type_string = field.get('type')
            s = ''.join(x for x in field_type_string if x.isdigit())
            message_length = message_length + int(s)
            f.write(tab + 'offset = unpack_'+field.get('type') + '(offset, &out_ptr->'+field.get('name') + ');\n')
        message_length = message_length/8
            
            
            
        f.write(tab + 'return offset;\n')
        f.write('}\n\n')
        
        # encode
        f.write('void encode_' + variable_name+'(\n')
        f.write(tab + 'uint8_t src_id,\n')
        f.write(tab + 'uint8_t dest_id,\n')
        f.write(tab + 'uint8_t msg_ttl,\n')
        f.write(tab + 'uint8_t seq_number,\n')
        f.write(tab + type_t_name+'* tx_msg,\n')
        f.write(tab + 'proto_msg_t* msg,\n')
        f.write(tab + "uint8_t keyArr[])//key for encryption CryptoPP\n\n")
        f.write('{\n')        
        
        f.write(tab+'/** Random IV*/\n')    
        f.write(tab+'Random::RandomNumberGen randIV = Random::RandomNumberGen();\n')
        f.write(tab+'randIV.generate_numbers<uint8_t>(msg->header.iv,0, AES::BLOCKSIZE,0,255);\n\n')
        
        f.write(tab+'msg_offset start_offset, offset;\n')
        f.write(tab+'msg->direction = Proto_Out;\n')
        f.write(tab+'start_offset = msg->data;\n')
        f.write(tab+'offset = msg->data;\n')
        f.write(tab+'msg->header.node_src_id = src_id;\n')
        f.write(tab+'msg->header.node_dest_id = dest_id;\n')
        f.write(tab+'msg->header.message_ttl = msg_ttl;\n')
        f.write(tab+'msg->header.sequence_number = seq_number;\n')
        f.write(tab+'msg->header.message_length = '+str(message_length)+';\n')
        f.write(tab+'msg->header.message_type = Proto_'+name+';\n')
        f.write(tab+'offset = pack_sync(offset);\n')
        f.write(tab+'offset = pack_header(&msg->header, offset);\n\n')        
        f.write(tab+'/** Encrypt */\n')
        f.write(tab+'/* Managed C (CLR) will freak out if you pass SecByteBlock as an argument this is my half ass fix MW*/\n')
        f.write(tab+'CryptoPP::SecByteBlock key(keyArr, AES::DEFAULT_KEYLENGTH);\n')
        f.write(tab+'CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), msg->header.iv);\n')
        f.write(tab+'cfbEncryption.ProcessData((byte*)offset, (byte*)offset, msg->header.message_length);\n\n')        
        f.write(tab+'offset = pack_'+variable_name+'(tx_msg, offset);\n')
        f.write(tab+'offset = pack_checksum(start_offset, offset);\n')
        f.write(tab+'msg->tx_len = offset-start_offset;\n')
        f.write('}')
        f.close() 
        #print what file was created
        print("Created message source: " + filename + src_extension)