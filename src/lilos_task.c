/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_task.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.1
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "lilos_task.h"

#include <malloc.h>

#include "lilos_log.h"

LILOS_TASK_INIT *LILOS_TASK_LIST[LILOS_MAX_TASK + 1] = {NULL};
LILOS_CALL_BACK_INIT *LILOS_CALL_BACK_LIST[LILOS_MAX_CALL_BACK + 1] = {NULL};
LILOS_TASK_STATE lilos_Create_Task(unsigned int *task_id,
                                  LILOS_TASK_CallBack TaskCallBack,
                                  unsigned int time) {
  static unsigned int i;
  for (i = 1; i <= LILOS_MAX_TASK; i++) {
    if (LILOS_TASK_LIST[i] == NULL) {
      LILOS_TASK_LIST[i] = malloc(sizeof(LILOS_TASK_INIT));
      if (LILOS_TASK_LIST[i] == NULL) {
        PRINT_ERR("Creat_Task Malloc Error\n");
        return LILOS_TASK_ERROR;
      }
      LILOS_TASK_LIST[i]->TaskCallBack = TaskCallBack;
      LILOS_TASK_LIST[i]->state = LILOS_TASK_STOP;
      LILOS_TASK_LIST[i]->settime = time;
      LILOS_TASK_LIST[i]->time = 0;
      *task_id = i;
      PRINT_DEBUG("Creat_Task Success ID:%d\n", i);
      return LILOS_TASK_OK;
    }
  }
  PRINT_ERR("Creat_Task NO FREE\n");
  return LILOS_TASK_ERROR;
}

LILOS_TASK_STATE lilos_Delete_Task(unsigned int task_id) {
  if (LILOS_TASK_LIST[task_id] == NULL) {
    return LILOS_TASK_ERROR;
  }
  if (task_id > 0 && task_id <= LILOS_MAX_TASK) {
    free(LILOS_TASK_LIST[task_id]);
    LILOS_TASK_LIST[task_id] = NULL;
    PRINT_DEBUG("Delete_Task ID %d\n", task_id);
    return LILOS_TASK_OK;
  } else {
    PRINT_ERR("Delete_Task ID ERROR\n");
    return LILOS_TASK_ERROR;
  }
}

LILOS_TASK_STATE lilos_Start_Task(unsigned int task_id) {
  if (LILOS_TASK_LIST[task_id] == NULL) {
    return LILOS_TASK_ERROR;
  }
  if (task_id > 0 && task_id <= LILOS_MAX_TASK) {
    LILOS_TASK_LIST[task_id]->time = 0;
    LILOS_TASK_LIST[task_id]->state = LILOS_TASK_START;
    PRINT_DEBUG("Start_Task ID %d\n", task_id);
    return LILOS_TASK_OK;
  } else {
    PRINT_ERR("Start_Task ID ERROR\n");
    return LILOS_TASK_ERROR;
  }
}

LILOS_TASK_STATE lilos_Stop_Task(unsigned int task_id) {
  if (LILOS_TASK_LIST[task_id] == NULL) {
    return LILOS_TASK_ERROR;
  }
  if (task_id > 0 && task_id <= LILOS_MAX_TASK) {
    LILOS_TASK_LIST[task_id]->state = LILOS_TASK_STOP;
    PRINT_DEBUG("Stop_Task ID %d\n", task_id);
    return LILOS_TASK_OK;
  } else {
    PRINT_ERR("Stop_Task ID ERROR\n");
    return LILOS_TASK_ERROR;
  }
}

LILOS_TASK_STATE lilos_Creat_CallBack_Task(LILOS_TASK_CallBack TaskCallBack) {
  static unsigned int i;
  for (i = 1; i <= LILOS_MAX_CALL_BACK; i++) {
    if (LILOS_CALL_BACK_LIST[i] == NULL) {
      LILOS_CALL_BACK_LIST[i] = malloc(sizeof(LILOS_CALL_BACK_INIT));
      LILOS_CALL_BACK_LIST[i]->TaskCallBack = TaskCallBack;
      LILOS_CALL_BACK_LIST[i]->state = LILOS_TASK_START;
      PRINT_DEBUG("CALL BACK Success ID:%d\n", i);
      return LILOS_TASK_OK;
    }
  }
  PRINT_ERR("Call_Back NO FREE\n");
  return LILOS_TASK_ERROR;
}

void lilos_CallBack_Handler(void) {
  static unsigned int i;
  for (i = 1; i <= LILOS_MAX_CALL_BACK; i++) {
    if (LILOS_CALL_BACK_LIST[i] != NULL) {
      if (LILOS_CALL_BACK_LIST[i]->state == LILOS_TASK_START) {
        LILOS_CALL_BACK_LIST[i]->state = LILOS_TASK_STOP;
        LILOS_CALL_BACK_LIST[i]->TaskCallBack();
        free(LILOS_CALL_BACK_LIST[i]);
        LILOS_CALL_BACK_LIST[i] = NULL;
      }
    }
  }
}

void lilos_TASK_Handler(void) {
  static unsigned int i;
  for (i = 1; i <= LILOS_MAX_TASK; i++) {
    if (LILOS_TASK_LIST[i] != NULL) {
      if (LILOS_TASK_LIST[i]->state == LILOS_TASK_START) {
        LILOS_TASK_LIST[i]->TaskCallBack();
        if (LILOS_TASK_LIST[i]->settime != LILOS_TASK_NO_DELAY) {
          LILOS_TASK_LIST[i]->state = LILOS_TASK_STOP;
        }
      }
    }
  }
}

void lilos_TASK_TIME_COUNT(void) {
  static unsigned int i;
  for (i = 1; i <= LILOS_MAX_TASK; i++) {
    if (LILOS_TASK_LIST[i] != NULL) {
      if (LILOS_TASK_LIST[i]->state == LILOS_TASK_STOP) {
        LILOS_TASK_LIST[i]->time++;
        if (LILOS_TASK_LIST[i]->time >= LILOS_TASK_LIST[i]->settime) {
          LILOS_TASK_LIST[i]->time = 0;
          LILOS_TASK_LIST[i]->state = LILOS_TASK_START;
        }
      }
    }
  }
}

