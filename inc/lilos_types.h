/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_types.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2024.07.01
 * Copyright (c) 2024 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __LILOS_TYPES_H__
#define __LILOS_TYPES_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef UINT_MAX
#define UINT_MAX 0xFFFFFFFF
#endif

#ifndef UCHAR_MAX
#define UCHAR_MAX 0xFF
#endif

typedef unsigned long long lilos_u64;
typedef signed long long lilos_s64;
typedef unsigned int lilos_u32;
typedef signed int lilos_s32;
typedef unsigned short lilos_u16;
typedef signed int lilos_s16;
typedef unsigned char lilos_u8;
typedef signed char lilos_s8;
typedef char lilos_bool;

enum lilos_bool_e {
  LILOS_FALSE = 0,
  LILOS_TRUE,
};

#ifdef __cplusplus
}
#endif

#endif
