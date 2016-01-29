#include <protonet_marshal.h>
#include <string.h>
#include <stdio.h>

#define LITTLE_ENDIAN
/* String Marshaling*/
msg_offset pack_string(
		string pack_data,
		uint16_t string_length,
		msg_offset offset)
{
	memcpy(offset, (uint16_t*)&string_length, 2);
	offset += 2;
	memcpy(offset, pack_data, string_length);
	return offset+string_length;
}

msg_offset unpack_string(
		msg_offset offset,
		string pack_data,
		uint16_t* length)
{
	uint16_t data_length;
	data_length= *((uint16_t*) offset)+2;
	memcpy(pack_data, (char*)offset, data_length);
	offset = offset + data_length;
	*length = data_length;
	return offset;
}

/* Functional Status Set Marshaling*/
msg_offset pack_functional_status(
		functional_status fs[4],
		msg_offset offset)
{
	int32_t i;
	for(i=0;i<4;i++)
	{
		memcpy( offset, (uint8_t*) &fs[i], 1);
		offset = offset+1;
	}
	return offset;
}

msg_offset unpack_functional_status(
		msg_offset offset,
		functional_status fs[4])
{
	int32_t i;
	for(i=0;i<4;i++)
	{
		memcpy( &fs[i], (int32_t*)offset, 1);
		offset = offset+1;
	}
	return offset;
}

/* 8-bit Unsigned Integer Marshaling*/
msg_offset pack_uint8_t(
		uint8_t pack_data,
		msg_offset offset)
{
	memcpy(offset, &pack_data, 1);
	return offset+1;
}

msg_offset unpack_uint8_t(
		msg_offset offset,
		uint8_t* out_ptr)
{
	memcpy(out_ptr, offset, 1);
	return offset+1;
}

#ifdef LITTLE_ENDIAN

/* 16-bit Unsigned Integer Marshaling for LE*/
msg_offset pack_uint16_t(
		uint16_t pack_data,
		msg_offset offset)
{
	*offset = *((uint8_t*)&pack_data+1);
	*(offset+1) = *((uint8_t*)&pack_data);
	return offset+2;
}

#else


/* 16-bit Unsigned Integer Marshaling*/
msg_offset pack_uint16_t(
		uint16_t pack_data,
		msg_offset offset)
{
	memcpy(offset, (uint8_t*)&pack_data, 2);
	return offset+2;
}

#endif


msg_offset unpack_uint16_t(
		msg_offset offset,
		uint16_t* out_ptr)
{
	*out_ptr = *(offset+1)<<0 | *offset<<8;
	return offset+2;
}


#ifdef LITTLE_ENDIAN

/* 32-bit Unsigned Integer Marshaling for LE*/
msg_offset pack_uint32_t(
		uint32_t pack_data,
		msg_offset offset)
{
	*offset = *((uint8_t*)&pack_data+3);
	*(offset+1) = *((uint8_t*)&pack_data+2);
	*(offset+2) = *((uint8_t*)&pack_data+1);
	*(offset+3) = *((uint8_t*)&pack_data);
	return offset+4;
}

#else

/* 32-bit Unsigned Integer Marshaling*/
msg_offset pack_uint32_t(
		uint32_t pack_data,
		msg_offset offset)
{
	memcpy(offset, (uint8_t*)&pack_data, 4);
	return offset+4;
}
#endif

msg_offset unpack_uint32_t(
		msg_offset offset,
		uint32_t* out_ptr)
{
	*out_ptr = *(offset+3)<<0 | *(offset+2)<<8 |
			   *(offset+1)<<16 | *offset<<24;
	return offset+4;
}

#ifdef LITTLE_ENDIAN

/* 64-bit Unsigned Integer Marshaling for LE*/
msg_offset pack_uint64_t(
		uint64_t pack_data,
		msg_offset offset)
{
	*(offset) = *((uint8_t*)&pack_data+7);
	*(offset+1) = *((uint8_t*)&pack_data+6);
	*(offset+2) = *((uint8_t*)&pack_data+5);
	*(offset+3) = *((uint8_t*)&pack_data+4);
	*(offset+4) = *((uint8_t*)&pack_data+3);
	*(offset+5) = *((uint8_t*)&pack_data+2);
	*(offset+6) = *((uint8_t*)&pack_data+1);
	*(offset+7) = *((uint8_t*)&pack_data);
	return offset+8;
}

msg_offset unpack_uint64_t(
	msg_offset offset, 
	uint64_t* out_ptr)
{
	*(uint8_t*)(out_ptr) = *(offset+7);
	*((uint8_t*)(out_ptr)+1) = *(offset+6);
	*((uint8_t*)(out_ptr)+2) = *(offset+5);
	*((uint8_t*)(out_ptr)+3) = *(offset+4);
	*((uint8_t*)(out_ptr)+4) = *(offset+3);
	*((uint8_t*)(out_ptr)+5) = *(offset+2);
	*((uint8_t*)(out_ptr)+6) = *(offset+1);
	*((uint8_t*)(out_ptr)+7) = *offset;
	return offset+8;
}


#else

/* 64-bit Unsigned Integer Marshaling*/
msg_offset pack_uint64_t(
		uint64_t pack_data,
		msg_offset offset)
{
	memcpy(offset, (uint64_t*)&pack_data, 8);
	return offset+8;
}

msg_offset unpack_uint64_t(
		msg_offset offset,
		uint64_t* out_ptr)
{
	memcpy(out_ptr, (uint64_t*)offset, 8);
	return offset+8;
}
#endif



/* 8-bit Signed Integer Marshaling*/
msg_offset pack_int8_t(
		int8_t pack_data,
		msg_offset offset)
{
	memcpy(offset, (uint8_t*)&pack_data, 1);
	return offset+1;
}

msg_offset unpack_int8_t(
		msg_offset offset,
		int8_t* out_ptr)
{
	memcpy(out_ptr, offset, 1);
	return offset+1;
}

#ifdef LITTLE_ENDIAN

/* 16-bit Signed Integer Marshaling for LE*/
msg_offset pack_int16_t(
		int16_t pack_data,
		msg_offset offset)
{
	*offset = *((uint8_t*)&pack_data+1);
	*(offset+1) = *((uint8_t*)&pack_data);
	return offset+2;
}

#else

/* 16-bit Signed Integer Marshaling*/
msg_offset pack_int16_t(
		int16_t pack_data,
		msg_offset offset)
{
	memcpy(offset, (uint8_t*)&pack_data, 2);
	return offset+2;
}

#endif

msg_offset unpack_int16_t(
		msg_offset offset,
		int16_t* out_ptr)
{
	*out_ptr = *(offset+1)<<0 | *offset<<8;
	return offset+2;
}

#ifdef LITTLE_ENDIAN

/* 32-bit Signed Integer Marshaling for LE*/
msg_offset pack_int32_t(
		int32_t pack_data,
		msg_offset offset)
{
	*offset = *((uint8_t*)&pack_data+3);
	*(offset+1) = *((uint8_t*)&pack_data+2);
	*(offset+2) = *((uint8_t*)&pack_data+1);
	*(offset+3) = *((uint8_t*)&pack_data);
	return offset+4;
}
#else
/* 32-bit Signed Integer Marshaling*/
msg_offset pack_int32_t(
		int32_t pack_data,
		msg_offset offset)
{
	memcpy(offset, (uint8_t*)&pack_data, 4);
	return offset+4;
}
#endif

msg_offset unpack_int32_t(
		msg_offset offset,
		int32_t* out_ptr)
{
	*out_ptr = *(offset+3)<<0 | *(offset+2)<<8 |
			   *(offset+1)<<16 | *offset<<24;
	return offset+4;
}
#ifdef LITTLE_ENDIAN
/* 64-bit Signed Integer Marshaling for LE*/
msg_offset pack_int64_t(
		int64_t pack_data,
		msg_offset offset)
{
	*(offset) = *((uint8_t*)&pack_data+7);
	*(offset+1) = *((uint8_t*)&pack_data+6);
	*(offset+2) = *((uint8_t*)&pack_data+5);
	*(offset+3) = *((uint8_t*)&pack_data+4);
	*(offset+4) = *((uint8_t*)&pack_data+3);
	*(offset+5) = *((uint8_t*)&pack_data+2);
	*(offset+6) = *((uint8_t*)&pack_data+1);
	*(offset+7) = *((uint8_t*)&pack_data);
	return offset+8;
}


msg_offset unpack_int64_t(
	msg_offset offset, 
	int64_t* out_ptr)
{
	*(uint8_t*)(out_ptr) = *(offset+7);
	*((uint8_t*)(out_ptr)+1) = *(offset+6);
	*((uint8_t*)(out_ptr)+2) = *(offset+5);
	*((uint8_t*)(out_ptr)+3) = *(offset+4);
	*((uint8_t*)(out_ptr)+4) = *(offset+3);
	*((uint8_t*)(out_ptr)+5) = *(offset+2);
	*((uint8_t*)(out_ptr)+6) = *(offset+1);
	*((uint8_t*)(out_ptr)+7) = *offset;
	return offset+8;
}


#else
/* 64-bit Signed Integer Marshaling*/
msg_offset pack_int64_t(
		int64_t pack_data,
		msg_offset offset)
{
	memcpy(offset, (uint8_t*)&pack_data, 8);
	return offset+8;
}

msg_offset unpack_int64_t(
		msg_offset offset,
		int64_t* out_ptr)
{
	memcpy(out_ptr, offset, 4);
	return offset+8;
}

#endif


#ifdef LITTLE_ENDIAN
msg_offset pack_float32_t(
		float32_t pack_data,
		msg_offset offset)
{
	memcpy(offset+3, (uint8_t *)&pack_data, 1);
	memcpy(offset+2, ((uint8_t *)&pack_data) + 1, 1);
	memcpy(offset+1, ((uint8_t *)&pack_data) + 2, 1);
	memcpy(offset, ((uint8_t *)&pack_data) + 3, 1);

	return offset+4;
}
msg_offset unpack_float32_t(
		msg_offset offset,
		float32_t* out_ptr)
{
	memcpy((uint8_t*)(out_ptr), offset+3, 1);
	memcpy((uint8_t*)(out_ptr)+1, offset+2, 1);
	memcpy((uint8_t*)(out_ptr)+2, offset+1, 1);
	memcpy((uint8_t*)(out_ptr)+3, offset, 1);

	return offset+4;
}
#else
msg_offset pack_float32_t(
		float32_t pack_data,
		msg_offset offset)
{
	memcpy(offset, (uint8_t*)&pack_data, 4);

	return offset + 4;
}

msg_offset unpack_float32_t(
		msg_offset offset,
		float32_t *out_ptr)
{
	memcpy(out_ptr, offset, 4);

	return offset + 4;
}
#endif


#ifdef LITTLE_ENDIAN
/* 64-bit Float Marshaling for LE*/
msg_offset pack_float64_t(
		float64_t pack_data,
		msg_offset offset)
{
	*(offset) = *((uint8_t*)&pack_data+7);
	*(offset+1) = *((uint8_t*)&pack_data+6);
	*(offset+2) = *((uint8_t*)&pack_data+5);
	*(offset+3) = *((uint8_t*)&pack_data+4);
	*(offset+4) = *((uint8_t*)&pack_data+3);
	*(offset+5) = *((uint8_t*)&pack_data+2);
	*(offset+6) = *((uint8_t*)&pack_data+1);
	*(offset+7) = *((uint8_t*)&pack_data);
	return offset+8;
}

msg_offset unpack_float64_t(
		msg_offset offset,
		float64_t* out_ptr)
{
	*(uint8_t*)(out_ptr) = *(offset+7);
	*((uint8_t*)(out_ptr)+1) = *(offset+6);
	*((uint8_t*)(out_ptr)+2) = *(offset+5);
	*((uint8_t*)(out_ptr)+3) = *(offset+4);
	*((uint8_t*)(out_ptr)+4) = *(offset+3);
	*((uint8_t*)(out_ptr)+5) = *(offset+2);
	*((uint8_t*)(out_ptr)+6) = *(offset+1);
	*((uint8_t*)(out_ptr)+7) = *offset;

	return offset+8;
}

#else
/* 64-bit Float Marshaling*/
msg_offset pack_float64_t(
		float64_t pack_data,
		msg_offset offset)
{
	memcpy(offset, (float64_t*)&pack_data, 8);
	return offset+8;
}

msg_offset unpack_float64_t(
		msg_offset offset,
		float64_t* out_ptr)
{
	memcpy(out_ptr, (float64_t*)offset, 8);
	return offset+8;
}
#endif


void marshaling_test()
{	
	uint8_t data[10];
	
	uint16_t bit16u;
	int16_t bit16i;
	
	uint32_t bit32u;
	int32_t bit32i;

	float32_t f32;
	float64_t f64;

	uint64_t bit64u;
	int64_t bit64i;

	pack_int16_t(-100,data);
	unpack_int16_t(data, &bit16i);
	pack_uint16_t(100,data);
	unpack_uint16_t(data, &bit16u);

	pack_int32_t(-100,data);
	unpack_int32_t(data, &bit32i);
	pack_uint32_t(100,data);
	unpack_uint32_t(data, &bit32u);

	pack_int64_t(-100,data);
	unpack_int64_t(data, &bit64i);
	pack_uint64_t(100,data);
	unpack_uint64_t(data, &bit64u);

	pack_float32_t(1.1,data);
	unpack_float32_t(data,&f32);

	pack_float64_t(1.1,data);
	unpack_float64_t(data,&f64);

	printf("f32: %f\n", f32);
	printf("f64: %f\n", f64);
	
	printf("16u: %d\n", bit16u);
	printf("16i: %d\n", bit16i);

	printf("32u: %d\n", bit32u);
	printf("32i: %d\n", bit32i);

	printf("64u: %d\n", bit64u);
	printf("64i: %d\n", bit64i);
	return;
}
