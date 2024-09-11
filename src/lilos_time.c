/********************************** (C) COPYRIGHT ******************************
 * File Name          : c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.11.21
 * Description        : system time function
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "lilos_time.h"

#include <stdlib.h>
#include <time.h>

static unsigned long long time_count = 0;

void lilos_time_count(void) { time_count++; }

void lilos_time_set(unsigned long long ms, char time_zone) {
  long long time;
  time = time_zone * 3600 * 1000;
  time += ms;
  if (time < 0) {
    time = 0;
  }
  time_count = time;
}

unsigned long long lilos_time_get(void) { return time_count; }

lilos_time lilos_time_convert(unsigned long long ms) {
  time_t time_sec = ms / 1000;
  lilos_time time;
  struct tm* time_info = localtime(&time_sec);
  time.year = time_info->tm_year + 1900;
  time.month = time_info->tm_mon + 1;
  time.day = time_info->tm_mday;
  time.hour = time_info->tm_hour;
  time.min = time_info->tm_min;
  time.sec = time_info->tm_sec;
  time.year_day = time_info->tm_yday;
  time.week = time_info->tm_wday;
  return time;
}