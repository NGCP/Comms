#ifndef _STD_LOGIC_H_
#define _STD_LOGIC_H_
#pragma once

#define LEAST_SIG_BIT                  1

/** @file shift left bit wise macro. Shifts the bits of a value by the number
	specified.*/
    
#define LSHIFT_BIT_0(x)          (x << 0)
#define LSHIFT_BIT_1(x)          (x << 1)
#define LSHIFT_BIT_2(x)          (x << 2)
#define LSHIFT_BIT_3(x)          (x << 3)
#define LSHIFT_BIT_4(x)          (x << 4)
#define LSHIFT_BIT_5(x)          (x << 5)
#define LSHIFT_BIT_6(x)          (x << 6)
#define LSHIFT_BIT_7(x)          (x << 7)
#define LSHIFT_BIT_8(x)          (x << 8)
#define LSHIFT_BIT_9(x)          (x << 9)
#define LSHIFT_BIT_10(x)         (x << 10)
#define LSHIFT_BIT_11(x)         (x << 11)
#define LSHIFT_BIT_12(x)         (x << 12)
#define LSHIFT_BIT_13(x)         (x << 13)
#define LSHIFT_BIT_14(x)         (x << 14)
#define LSHIFT_BIT_15(x)         (x << 15)
#define LSHIFT_BIT_16(x)         (x << 16)
#define LSHIFT_BIT_17(x)         (x << 17)
#define LSHIFT_BIT_18(x)         (x << 18)
#define LSHIFT_BIT_19(x)         (x << 19)
#define LSHIFT_BIT_20(x)         (x << 20)
#define LSHIFT_BIT_21(x)         (x << 21)
#define LSHIFT_BIT_22(x)         (x << 22)
#define LSHIFT_BIT_23(x)         (x << 23)
#define LSHIFT_BIT_24(x)         (x << 24)
#define LSHIFT_BIT_25(x)         (x << 25)
#define LSHIFT_BIT_26(x)         (x << 26)
#define LSHIFT_BIT_27(x)         (x << 27)
#define LSHIFT_BIT_28(x)         (x << 28)
#define LSHIFT_BIT_29(x)         (x << 29)
#define LSHIFT_BIT_30(x)         (x << 30)
#define LSHIFT_BIT_31(x)         (x << 31)
#define LSHIFT_BIT_32(x)         (x << 32)
/** shift bits to the left number of times! */
#define LSHIFT_BITS(x, num)      (x << num)

/** Shift right bit wise macro */
#define RSHIFT_BIT_0(x)          (x >> 0)
#define RSHIFT_BIT_1(x)          (x >> 1)
#define RSHIFT_BIT_2(x)          (x >> 2)
#define RSHIFT_BIT_3(x)          (x >> 3)
#define RSHIFT_BIT_4(x)          (x >> 4)
#define RSHIFT_BIT_5(x)          (x >> 5)
#define RSHIFT_BIT_6(x)          (x >> 6)
#define RSHIFT_BIT_7(x)          (x >> 7)
#define RSHIFT_BIT_8(x)          (x >> 8)
#define RSHIFT_BIT_9(x)          (x >> 9)
#define RSHIFT_BIT_10(x)         (x >> 10)
#define RSHIFT_BIT_11(x)         (x >> 11)
#define RSHIFT_BIT_12(x)         (x >> 12)
#define RSHIFT_BIT_13(x)         (x >> 13)
#define RSHIFT_BIT_14(x)         (x >> 14)
#define RSHIFT_BIT_15(x)         (x >> 15)
#define RSHIFT_BIT_16(x)         (x >> 16)
#define RSHIFT_BIT_17(x)         (x >> 17)
#define RSHIFT_BIT_18(x)         (x >> 18)
#define RSHIFT_BIT_19(x)         (x >> 19)
#define RSHIFT_BIT_20(x)         (x >> 20)
#define RSHIFT_BIT_21(x)         (x >> 21)
#define RSHIFT_BIT_22(x)         (x >> 22)
#define RSHIFT_BIT_23(x)         (x >> 23)
#define RSHIFT_BIT_24(x)         (x >> 24)
#define RSHIFT_BIT_25(x)         (x >> 25)
#define RSHIFT_BIT_26(x)         (x >> 26)
#define RSHIFT_BIT_27(x)         (x >> 27)
#define RSHIFT_BIT_28(x)         (x >> 28)
#define RSHIFT_BIT_29(x)         (x >> 29)
#define RSHIFT_BIT_30(x)         (x >> 30)
#define RSHIFT_BIT_31(x)         (x >> 31)
#define RSHIFT_BIT_32(x)         (x >> 32)
/** shift bits to the right number of times */
#define RSHIFT_BITS(x, num)      (x >> num)

/** MAX VALUE FOR EACH BIT SIZE.*/
#define UBIT8_MAX                 255
#define UBIT16_MAX                0xffff
#define UBIT32_MAX                0x7fffffff

#endif /* _STD_LOGIC_H_ */
