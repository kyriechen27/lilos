/********************************** (C) COPYRIGHT ******************************
 * File Name          : main.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2024.09.10
 * Copyright (c) 2024 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>

#include "lilos_init.h"
#include "lilos_time.h"
#include "test.h"

static void *systick_time_thread(void *arg) {
  struct timespec interval;
  interval.tv_sec = 0;         // 秒数
  interval.tv_nsec = 1000000;  // 纳秒数，1毫秒 = 1,000,000纳秒

  while (1) {
    if (nanosleep(&interval, NULL) == -1) {
      perror("nanosleep");
      break;
    }
    lil_os_systick();
  }
  return NULL;
}

static int sys_init(void) {
  pthread_t systick_task_id;

  if (pthread_create(&systick_task_id, NULL, systick_time_thread, NULL) != 0) {
    perror("pthread_create");
    return 1;
  }
  pthread_detach(systick_task_id);
}

static void task_init(void) {
  time_t now;
  time(&now);
  lilos_time_set(now * 1000, TIMEZONE_UTC);
  test_init();
}

int main(void) {
  sys_init();
  task_init();
  lilos_Start();
  return 0;
}
