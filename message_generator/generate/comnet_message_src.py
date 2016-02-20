
from .check_valid_type import *

def generate_message_file_src(directory, include_extension, src_extension):
    """
    Function will create the message source file in .../src/
    File has 3 main parts
        -pack sync
        -pack checksum
        -pack /unpack header
    """
    #load header structure and the messages in variables from xml file
    import xml.etree.ElementTree as ET
    tree = ET.parse('message_definition.xml')
    protocol = tree.findall('message')
    header = tree.find('header')    
    tab = '   '            
    #open file
    f = open(directory + "/src/" + 'comnet_message' + src_extension, 'w')
    # warning
    f.write('/* This file was autogenerated. All changes will be undone. */\n\n')
    # includes
    f.write('#include <string.h>\n')
    f.write('#include <stdio.h>\n')
    f.write('#include <comnet_marshal'+include_extension+'>\n')
    f.write('#include <comnet_message'+include_extension+'>\n\n')
    f.write('#include <standard_logic.h>\n')
    
    #pack sync functions
    f.write('msg_offset pack_sync(msg_offset offset)\n')
    f.write('{\n')
    f.write(tab + "*offset = 'C\';\n")
    f.write(tab + "*(offset+1) = 'P\';\n")
    f.write(tab + "*(offset+2) = 'P\';\n")
    f.write(tab + "*(offset+3) = 0;\n")
    f.write(tab + 'return offset+4;\n')
    f.write('}\n\n')
    
    #Fletcher 16
    f.write('''checksum_t fletcher16(msg_offset start, msg_offset end)
    {
        uint8_t count = end - start;
        uint16_t sum1 = 0;
        uint16_t sum2 = 0;
        int index;

        for (index = 0; index < count; ++index)
        {
            sum1 = (sum1 + start[index]) % 255;
            sum2 = (sum2 + sum1) % 255;
        }

        return (sum2 << 8) | sum1;
    }''')
    f.write('\n\n')
    #pack checksum function
    f.write('msg_offset pack_checksum(\n')
    f.write(tab + 'const msg_offset start,\n')
    f.write(tab + 'const msg_offset end)\n')
    f.write('{\n')
    f.write('checksum_t sum = fletcher16(start, end);\n')
    f.write('return pack_uint16_t(sum, end);\n')
    f.write('\n}\n\n')
    #unpack checksum function
    f.write('msg_offset unpack_checksum(\n')
    f.write(tab + 'msg_offset offset,\n')
    f.write(tab + 'checksum_t* out_ptr)\n')
    f.write('{\n')
    f.write(tab + 'return unpack_uint16_t(offset, (uint16_t*)out_ptr);\n')
    f.write('}\n\n')
    #pack header function
    f.write('msg_offset pack_header(\n')
    f.write(tab + 'com_header_t* header,\n')
    f.write(tab + 'msg_offset offset)\n')
    f.write('{\n')
    #priority
    f.write(tab + ''' /** Shift the message length one bit to the left and merge it with the is_emergency! */
    /** ex.
		message length (15 bit)   is_emergency (1 bit)
		100000000000010           1

		shift left -->   1           000000000000100      
						discarded!
						
						MERGE

						0000000000001001 <-- OUTPUT
    */\n\n''')
    #priority
    f.write(tab + "uint16_t merged_data = LSHIFT_BIT_1(header->message_length) | header->is_emergency;\n\n")
    for field in header:
        if(check_valid_type(field.get('type')) == 0):
            print ('error: field: '+ field.get('name') + ' in header has invalid type.')
        #check for for prioirty special case merged_data replaces message_length    
        if(field.get('name') == 'message_length'):
            f.write(tab + 'offset = pack_uint16_t(merged_data, offset);\n')
        elif(field.get('type').endswith('*')):            
            f.write(tab + 'offset = pack_'+field.get('type')[:-1] + '_ptr' + '(header->' + field.get('name')  + ', offset,' + field.get('length') +' );\n')               
        else: 
            f.write(tab + 'offset = pack_'+field.get('type') + '(header->' + field.get('name') + ', offset);\n')    
    f.write(tab+ 'return offset;\n')
    f.write('}\n\n')
    
    #priority unpack method for merged variable
    f.write(tab + '''/**Grabs the mergd bit pattern and obtains the least significant bit for the emergency 
    protocol, and obtains the last 15 bits for the message length.    
    shift the bit value right 0 times, meaning do nothing, then AND it by value 1 to obtain
    least sig bit that determines if the header contains an emergency (1) or not (0).                 
    OBTAIN FOR MESSAGE LENGTH-> 000000000000100 | 1 <- OBTAIN LAST ONE FOR EMERGENCY!*/
    inline void unpack_merged_variable(com_header_t* out_ptr, uint16_t* merged_message)
    {
        out_ptr->is_emergency = RSHIFT_BIT_0(*merged_message) & LEAST_SIG_BIT;

        // Shift to the right one bit and AND it by the max value obtainable with 16 bits.
        out_ptr->message_length = RSHIFT_BIT_1(*merged_message) & UBIT16_MAX;
    }\n\n''') 
    
    
    #unpack header function
    f.write('msg_offset unpack_header(\n')
    f.write(tab + 'msg_offset offset,\n')
    f.write(tab + 'com_header_t* out_ptr)\n')        
    f.write('{\n')
    #priority
    f.write(tab + 'uint16_t merged_message;\n')
    for field in header:
        if(check_valid_type(field.get('type')) == 0):
            print ('error: field: '+ field.get('name') + ' in header has invalid type.')
        #check for for prioirty special case merged_data replaces message_length    
        if(field.get('name') == 'message_length'):
            f.write(tab +'offset = unpack_uint16_t(offset, &merged_message);\n' + tab + 'unpack_merged_variable(out_ptr, &merged_message);\n')
        elif(field.get('type').endswith('*')):            
            f.write(tab + 'offset = unpack_'+field.get('type')[:-1] + '_ptr' + '(offset, out_ptr->' + field.get('name') + ',' + field.get('length') + ');\n')    
        else:    
            f.write(tab + 'offset = unpack_'+field.get('type') + '(offset, &out_ptr->' + field.get('name') + ');\n')    
    f.write(tab+ 'return offset;\n')
    f.write('}\n')

    print("Created: " + 'comnet_message' + src_extension)
