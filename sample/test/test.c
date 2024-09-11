/********************************** (C) COPYRIGHT ******************************
 * File Name          : test.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2024.09.10
 * Copyright (c) 2024 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "test.h"

#include "lilos_log.h"
#include "lilos_swtimer.h"
#include "lilos_task.h"
#include "lilos_time.h"
#include "lilos_queue.h"

static void test_task(void) {
  lilos_time time;
  unsigned long long ms = lilos_time_get();
  time = lilos_time_convert(ms);
  PRINT_DEBUG("time: %d-%d-%d %d:%d:%d\n", time.year, time.month, time.day,
              time.hour, time.min, time.sec);
  PRINT_DEBUG("test task\n");
}

static void task_init(void) {
  unsigned int task_id;
  lilos_Create_Task(&task_id, test_task, 1000);
}

static void test_swtimer(void) {
  PRINT_DEBUG("swtimer one time %lld\n", lilos_time_get());
}

static void loop_swtimer(void) {
  PRINT_DEBUG("swtimer loop %lld\n", lilos_time_get());
}

static void swtimer_init(void) {
  unsigned int swtimer_one_id;
  lilos_Creat_swTimer(&swtimer_one_id, LILOS_SWTIME_ONE_TIME, 1000,
                      test_swtimer);
  lilos_Start_swTimer(swtimer_one_id);
  PRINT_DEBUG("swtimer one time %d time %lld\n", swtimer_one_id,
              lilos_time_get());

  unsigned int swtimer_loop_id;
  lilos_Creat_swTimer(&swtimer_loop_id, LILOS_SWTIME_LOOP_TIME, 2000,
                      loop_swtimer);
  lilos_Start_swTimer(swtimer_loop_id);
  PRINT_DEBUG("swtimer LOOP %d time %lld\n", swtimer_one_id, lilos_time_get());
  PRINT_DEBUG("swtimer test\n");
}

unsigned int queue_id;

static void test_queue(void) {
  unsigned char data[10] = {0};
  unsigned int len = 10;
  lilos_Queue_Write(queue_id, data, len);
  data[0] = 1;
  lilos_Queue_Write(queue_id, data, len);
  data[0] = 2;
  lilos_Queue_Write(queue_id, data, len);

  unsigned char read_data[10] = {0};
  unsigned int read_len;
  lilos_Queue_Read(queue_id, read_data, &read_len);
  PRINT_DEBUG_HEX("read data", read_data, read_len);
  lilos_Queue_Read(queue_id, read_data, &read_len);
  PRINT_DEBUG_HEX("read data", read_data, read_len);
  lilos_Queue_Read(queue_id, read_data, &read_len);
  PRINT_DEBUG_HEX("read data", read_data, read_len);
  PRINT_DEBUG("queue test\n");
}

static void queue_init(void) {
  unsigned int queue_task_id;
  lilos_Create_Queue(&queue_id, 10, 10);
  PRINT_DEBUG("queue test\n");
  lilos_Create_Task(&queue_task_id, test_queue, 1000);
}

void test_init(void) {
  task_init();
  swtimer_init();
  queue_init();
}
