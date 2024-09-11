/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_task.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.1
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __LOS_TASK_H__
#define __LOS_TASK_H__

#include "lilos_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LILOS_MAX_TASK
#define LILOS_MAX_TASK 32
#endif

#ifndef LILOS_MAX_CALL_BACK
#define LILOS_MAX_CALL_BACK 32
#endif

typedef void (*LILOS_TASK_CallBack)(void);
typedef struct LILOS_TASK_INITTypeDef {
  unsigned char mode;
  unsigned int settime;
  unsigned int time;
  unsigned char state;
  LILOS_TASK_CallBack TaskCallBack;
} LILOS_TASK_INIT;

typedef struct LILOS_CALL_BACK_INITTypeDef {
  unsigned char state;
  LILOS_TASK_CallBack TaskCallBack;
} LILOS_CALL_BACK_INIT;

enum LILOS_TASK_STATE_Enum {
  LILOS_TASK_END,
  LILOS_TASK_START,
  LILOS_TASK_STOP,
  LILOS_TASK_PROCESS,
};

typedef enum TASK_RETURN_Enum {
  LILOS_TASK_OK,
  LILOS_TASK_ERROR,
} LILOS_TASK_STATE;

#define LILOS_TASK_NO_DELAY 0

/**
 * @brief   Creat a task
 * @note    This function is used to create a task to while(1) loop.
 *
 * @param   task_id       return task allocation id
 * @param   TaskCallBack  task callback function
 *                        now support function types:(void function(void))
 * @param   time          set callback time (unit:ms)
 * @return  LILOS_TASK_OK: success LILOS_TASK_ERROR: error
 */
LILOS_TASK_STATE lilos_Create_Task(unsigned int *task_id,
                                   LILOS_TASK_CallBack TaskCallBack,
                                   unsigned int time);

/**
 * @brief   Delete a task
 *
 * @param   task_id       task id
 * @return  LILOS_TASK_OK: success LILOS_TASK_ERROR: error
 */
LILOS_TASK_STATE lilos_Delete_Task(unsigned int task_id);

/**
 * @brief   Stop task
 *
 * @param   task_id       task id
 * @return  LILOS_TASK_OK: success LILOS_TASK_ERROR: error
 */
LILOS_TASK_STATE lilos_Stop_Task(unsigned int task_id);

/**
 * @brief   Start task
 *
 * @param   task_id       task id
 * @return  LILOS_TASK_OK: success LILOS_TASK_ERROR: error
 */
LILOS_TASK_STATE lilos_Start_Task(unsigned int task_id);

/**
 * @brief   Creat CallBack Task
 * @note    This function is used to create a task to while(1) loop.
 *          This task will be executed only once.
 *          mostly used for interrupt callback function.
 *
 * @param   TaskCallBack  task callback function
 *                        now support function types:(void function(void))
 * @return  LILOS_TASK_OK: success LILOS_TASK_ERROR: error
 */
LILOS_TASK_STATE lilos_Creat_CallBack_Task(LILOS_TASK_CallBack TaskCallBack);

#ifdef __cplusplus
}
#endif

#endif
