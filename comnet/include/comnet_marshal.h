/** @file

libc serialization/deserialization functions.

All pack functions take a data type and
packs the data into a uint8_t buffer.

Function returns specify the offset
after the packing or unpacking is complete.

*/
#ifndef PROTONET_MARSHAL_H
#define PROTONET_MARSHAL_H

#include <stdint.h>

typedef char* string; 
typedef uint8_t* msg_offset; /** denotes the start location to begin packing*/
typedef float float32_t; /** 32 bit floating point integer*/
typedef double float64_t; /** 64 bit floating point integer*/

typedef enum {
    ND = 0,  /*No Data*/
    NO = 3,  /*Normal Operation*/
    FT = 12, /*Functional Test*/
    NCD = 48 /*No Computed Data*/
}functional_status;

/** String Marshaling pack*/
msg_offset pack_string(
        string pack_data,
        uint16_t string_length,
        msg_offset offset);

/** String Marshaling unpack*/
msg_offset unpack_string(
        msg_offset offset,
        string out_data,
        uint16_t* length);

/** Functional Status Set Marshaling pack*/
msg_offset pack_functional_status(
        functional_status fs[4],
        msg_offset offset);
		
/** Functional Status Set Marshaling unpack*/
msg_offset unpack_functional_status(
        msg_offset offset,
        functional_status fs[4]);

/** 8-bit Unsigned Integer Marshaling pack*/
msg_offset pack_uint8_t(
        uint8_t pack_data,
        msg_offset offset);
        
/** 8-bit Unsigned Integer array Marshaling pack*/        
msg_offset pack_uint8_t_ptr(
        uint8_t *pack_data,
        msg_offset offset,
        uint8_t length);        
        
/** 8-bit Unsigned Integer aray Marshaling unpack*/
msg_offset unpack_uint8_t_ptr(
        msg_offset offset,
        uint8_t* out_ptr,
        uint8_t length);        
		
/** 8-bit Unsigned Integer  Marshaling unpack*/
msg_offset unpack_uint8_t(
        msg_offset offset,
        uint8_t* out_ptr);

/** 16-bit Unsigned Integer Marshaling pack*/
msg_offset pack_uint16_t(
        uint16_t pack_data,
        msg_offset offset);
		
/** 16-bit Unsigned Integer Marshaling unpack*/
msg_offset unpack_uint16_t(
        msg_offset offset,
        uint16_t* out_ptr);

/** 32-bit Unsigned Integer Marshaling pack*/
msg_offset pack_uint32_t(
        uint32_t pack_data,
        msg_offset offset);
		
/** 32-bit Unsigned Integer Marshaling unpack*/
msg_offset unpack_uint32_t(
        msg_offset offset,
        uint32_t* out_ptr);

/** 64-bit Unsigned Integer Marshaling pack*/
msg_offset pack_uint64_t(
        uint64_t pack_data,
        msg_offset offset);

/** 64-bit Unsigned Integer Marshaling unpack*/
msg_offset unpack_uint64_t(
        msg_offset offset,
        uint64_t* out_ptr);

/** 8-bit Signed Integer Marshaling pack*/
msg_offset pack_int8_t(
        int8_t pack_data,
        msg_offset offset);
		
/** 8-bit Signed Integer Marshaling unpack*/
msg_offset unpack_int8_t(
        msg_offset offset,
        int8_t* out_ptr);

/** 16-bit Signed Integer Marshaling pack*/
msg_offset pack_int16_t(
        int16_t pack_data,
        msg_offset offset);
		
/** 16-bit Signed Integer Marshaling unpack*/
msg_offset unpack_int16_t(
        msg_offset offset,
        int16_t* out_ptr);

/** 32-bit Signed Integer Marshaling pack*/
msg_offset pack_int32_t(
        int32_t pack_data,
        msg_offset offset);

/** 32-bit Signed Integer Marshaling unpack*/		
msg_offset unpack_int32_t(
        msg_offset offset,
        int32_t* out_ptr);

/** 64-bit Signed Integer Marshaling pack*/
msg_offset pack_int64_t(
        int64_t pack_data,
        msg_offset offset);

/** 64-bit Signed Integer Marshaling unpack*/		
msg_offset unpack_int64_t(
        msg_offset offset,
        int64_t* out_ptr);

/** 32-bit Float Marshaling pack*/
msg_offset pack_float32_t(
        float32_t pack_data,
        msg_offset offset);

/** 32-bit Float Marshaling unpack*/
msg_offset unpack_float32_t(
        msg_offset offset,
        float32_t* out_ptr);

/** 64-bit Float Marshaling pack*/
msg_offset pack_float64_t(
        float64_t pack_data,
        msg_offset offset);

/** 64-bit Float Marshaling unpack*/		
msg_offset unpack_float64_t(
        msg_offset offset,
        float64_t* out_ptr);


/** A quick marshaling test for each function  pack*/
void marshaling_test();

#endif
