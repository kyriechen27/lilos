/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_time.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.11.21
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __LILOS_TIME_H__
#define __LILOS_TIME_H__

#include "lilos_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lilos_time_t {
  unsigned int year;
  unsigned int year_day;
  unsigned char month;
  unsigned char day;
  unsigned char hour;
  unsigned char min;
  unsigned char sec;
  unsigned char week;
} lilos_time;

#define TIMEZONE_UTC 0
#define TIMEZONE_HAWAII -10
#define TIMEZONE_US_PACIFIC -8
#define TIMEZONE_ALASKA -9
#define TIMEZONE_US_MOUNTAIN -7
#define TIMEZONE_US_CENTRAL -6
#define TIMEZONE_US_EASTERN -5
#define TIMEZONE_BRAZIL -3
#define TIMEZONE_ARGENTINA -3
#define TIMEZONE_CENTRAL_EUROPE 1
#define TIMEZONE_CHINA 8
#define TIMEZONE_JAPAN 9
#define TIMEZONE_KOREA 9
#define TIMEZONE_AUSTRALIA_EAST 10

/**
 * @brief   set local time
 *
 * @param   time    local time (unit:ms)
 * @param   time_zone time zone
 */
void lilos_time_set(unsigned long long ms,char time_zone);

/**
 * @brief   get local time
 *
 * @return  local time (unit:ms)
 */
unsigned long long lilos_time_get(void);

/**
 * @brief   convert time to local time
 *
 * @param   ms        time (unit:ms)
 *
 * @return  local time
 */
lilos_time lilos_time_convert(unsigned long long ms);

#ifdef __cplusplus
}
#endif

#endif
