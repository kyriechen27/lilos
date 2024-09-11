/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_swtimer.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.3
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "lilos_swtimer.h"

#include <malloc.h>

#include "lilos_log.h"
static unsigned char LILOS_Timer_Task_NUM;
static unsigned char LILOS_Timer_ID_NUM;
unsigned int swtimer_state;
typedef struct TIMER_INITTypeDef {
  unsigned char TIME_STATE;
  unsigned char mode;
  unsigned int timecount;
  unsigned int set_time;
  LILOS_TIMER_CallBack TimeCallBack;
} LILOS_TIMER_INIT;

LILOS_TIMER_INIT *LILOS_TIMER_TASK[LILOS_MAX_SWTIMER_TASK + 1] = {NULL};

static void lilos_swTimer_mode_choice(unsigned int num) {
  if (LILOS_TIMER_TASK[num]->mode == LILOS_SWTIME_ONE_TIME) {
    lilos_Delete_swTimer(num);
  } else if (LILOS_TIMER_TASK[num]->mode == LILOS_SWTIME_LOOP_TIME) {
    LILOS_TIMER_TASK[num]->timecount = 0;
    LILOS_TIMER_TASK[num]->TIME_STATE = LILOS_TIME_START;
  } else if (LILOS_TIMER_TASK[num]->mode == LILOS_SWTIME_ONE_TIME_NOT_DELETE) {
    LILOS_TIMER_TASK[num]->timecount = 0;
    LILOS_TIMER_TASK[num]->TIME_STATE = LILOS_TIME_STOP;
  }
}

unsigned char lilos_Creat_swTimer(unsigned int *ID, unsigned char mode,
                                  unsigned int time,
                                  LILOS_TIMER_CallBack Task) {
  unsigned int i;
  for (i = 1; i <= LILOS_MAX_SWTIMER_TASK + 1; i++) {
    if (LILOS_TIMER_TASK[i] == NULL) {
      LILOS_TIMER_TASK[i] = malloc(sizeof(LILOS_TIMER_INIT));
      if (LILOS_TIMER_TASK[i] == NULL) {
        PRINT_ERR("Creat_Timer Malloc Error\n");
        return LOS_NOK;
      }
      LILOS_TIMER_TASK[i]->set_time = time;
      LILOS_TIMER_TASK[i]->TimeCallBack = Task;
      LILOS_TIMER_TASK[i]->mode = mode;
      LILOS_TIMER_TASK[i]->timecount = 0;
      LILOS_TIMER_TASK[i]->TIME_STATE = LILOS_TIME_STOP;
      *ID = i;
      PRINT_DEBUG("Creat_Timer Success ID:%d\n", i);
      return LOS_OK;
    }
  }
  PRINT_ERR("Creat_Timer NO FREE\n");
  return LOS_NOK;
}

unsigned char lilos_Start_swTimer(unsigned int ID) {
  if (LILOS_TIMER_TASK[ID] == NULL) {
    PRINT_ERR("SW TIMER NOT EXIST\n");
    return LILOS_SW_TIMER_NOT_EXIST;
  }

  if (ID > 0 && ID <= LILOS_MAX_SWTIMER_TASK) {
    LILOS_TIMER_TASK[ID]->TIME_STATE = LILOS_TIME_START;
    return LOS_OK;
  }

  PRINT_ERR("START TIMER ID ERROR\n");
  return LILOS_SW_TIMER_OVER_MAX_ID;
}

unsigned char lilos_Stop_swTimer(unsigned int ID) {
  if (LILOS_TIMER_TASK[ID] == NULL) {
    PRINT_ERR("SW TIMER NOT EXIST\n");
    return LILOS_SW_TIMER_NOT_EXIST;
  }

  if (ID > 0 && ID <= LILOS_MAX_SWTIMER_TASK && LILOS_TIMER_TASK[ID] != NULL) {
    LILOS_TIMER_TASK[ID]->TIME_STATE = LILOS_TIME_STOP;
    return LOS_OK;
  }
  PRINT_ERR("STOP TIMER ID ERROR\n");
  return LILOS_SW_TIMER_OVER_MAX_ID;
}

unsigned char lilos_Delete_swTimer(unsigned int ID) {
  if (LILOS_TIMER_TASK[ID] == NULL) {
    PRINT_WARN("SW TIMER NOT EXIST\n");
    return LILOS_SW_TIMER_NOT_EXIST;
  }

  if (ID > 0 && ID <= LILOS_MAX_SWTIMER_TASK) {
    free(LILOS_TIMER_TASK[ID]);
    LILOS_TIMER_TASK[ID] = NULL;
    PRINT_DEBUG("Delete_Timer ID %d\n", ID);
    return LOS_OK;
  }
  PRINT_ERR("Delete_Timer ID ERROR\n");
  return LILOS_SW_TIMER_OVER_MAX_ID;
}

void lilos_swTIMER_Delay(void) {
  for (LILOS_Timer_ID_NUM = 1; LILOS_Timer_ID_NUM < LILOS_MAX_SWTIMER_TASK;
       LILOS_Timer_ID_NUM++) {
    if (LILOS_TIMER_TASK[LILOS_Timer_ID_NUM] != NULL) {
      if (LILOS_TIMER_TASK[LILOS_Timer_ID_NUM]->TIME_STATE ==
          LILOS_TIME_START) {
        LILOS_TIMER_TASK[LILOS_Timer_ID_NUM]->timecount++;
        if (LILOS_TIMER_TASK[LILOS_Timer_ID_NUM]->timecount >=
            LILOS_TIMER_TASK[LILOS_Timer_ID_NUM]->set_time) {
          LILOS_TIMER_TASK[LILOS_Timer_ID_NUM]->TIME_STATE = LILOS_TIME_PROCESS;
        }
      }
    }
  }
}

void lilos_swTIMER_Handler(void) {
  for (LILOS_Timer_Task_NUM = 1; LILOS_Timer_Task_NUM < LILOS_MAX_SWTIMER_TASK;
       LILOS_Timer_Task_NUM++) {
    if (LILOS_TIMER_TASK[LILOS_Timer_Task_NUM] != NULL) {
      if (LILOS_TIMER_TASK[LILOS_Timer_Task_NUM]->TIME_STATE ==
          LILOS_TIME_PROCESS) {
        LILOS_TIMER_TASK[LILOS_Timer_Task_NUM]->TimeCallBack();
        lilos_swTimer_mode_choice(LILOS_Timer_Task_NUM);
      }
    }
  }
}