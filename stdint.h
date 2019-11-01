/* Copyright (C) ARM Ltd., 1999 */
/* All rights reserved */

/*
 * RCS $Revision: 178085 $
 * Checkin $Date: 2012-12-11 14:54:17 +0000 (Tue, 11 Dec 2012) $
 * Revising $Author: agrant $
 */

#ifndef __stdint_h
#define __stdint_h

/*
 * 'signed' is redundant below, except for 'signed char' and if
 * the typedef is used to declare a bitfield.
 * '__int64' is used instead of 'long long' so that this header
 * can be used in --strict mode.
 */

    /* 7.18.1.1 */

    /* exact-width signed integer types */
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed long      int int32_t;


    /* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned long      int uint32_t;


    /* 7.18.1.2 */

    /* smallest type of at least n bits */
    /* minimum-width signed integer types */
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed long      int int_least32_t;


    /* minimum-width unsigned integer types */
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned long      int uint_least32_t;


    /* 7.18.1.3 */

    /* fastest minimum-width signed integer types */
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;


    /* fastest minimum-width unsigned integer types */
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;


    /* 7.18.1.4 integer types capable of holding object pointers */
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

/*------------------------------------------------------*/
typedef union 
{
    uint16_t Val;
    struct
    {
        uint8_t HB;
        uint8_t LB;
    } byte;
} UINT16_VAL;
/*------------------------------------------------------*/
typedef union
{
    uint16_t Val;
    struct
    {
        uint8_t HB;
        uint8_t LB;
    } byte;

} WORD_VAL;
/*------------------------------------------------------*/
typedef union
{
    uint32_t Val;
    struct
    {
        uint16_t HW;
        uint16_t LW;
    } word;
    struct
    {
        uint8_t MB;
        uint8_t UB;
        uint8_t HB;
        uint8_t LB;
    } byte;
} UINT32_VAL;
/*------------------------------------------------------*/
    /* 7.18.2.1 */

    /* minimum values of exact-width signed integer types */
#define INT8_MIN                   -128
#define INT16_MIN                -32768
#define INT32_MIN          (~0x7fffffff)   /* -2147483648 is unsigned */


    /* maximum values of exact-width signed integer types */
#define INT8_MAX                    127
#define INT16_MAX                 32767
#define INT32_MAX            2147483647


    /* maximum values of exact-width unsigned integer types */
#define UINT8_MAX                   255
#define UINT16_MAX                65535
#define UINT32_MAX           4294967295u


    /* 7.18.2.2 */

    /* minimum values of minimum-width signed integer types */
#define INT_LEAST8_MIN                   -128
#define INT_LEAST16_MIN                -32768
#define INT_LEAST32_MIN          (~0x7fffffff)


    /* maximum values of minimum-width signed integer types */
#define INT_LEAST8_MAX                    127
#define INT_LEAST16_MAX                 32767
#define INT_LEAST32_MAX            2147483647


    /* maximum values of minimum-width unsigned integer types */
#define UINT_LEAST8_MAX                   255
#define UINT_LEAST16_MAX                65535
#define UINT_LEAST32_MAX           4294967295u


#endif /* __stdint_h */

/* end of stdint.h */



