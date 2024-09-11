/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_sysTick.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.6.29
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "lilos_systick.h"

#include "lilos_swtimer.h"
#include "lilos_task.h"
#include "lilos_time.h"

extern void lilos_TASK_TIME_COUNT(void);
extern void lilos_swTIMER_Delay(void);
extern void lilos_time_count(void);

void lil_os_systick(void) {
  lilos_time_count();
  lilos_swTIMER_Delay();
  lilos_TASK_TIME_COUNT();
}
