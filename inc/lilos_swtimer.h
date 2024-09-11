/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_swtimer.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.3
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __LILOS_SWTIMER_H__
#define __LILOS_SWTIMER_H__

#include "lilos_config.h"

#ifndef LILOS_MAX_SWTIMER_TASK
#define LILOS_MAX_SWTIMER_TASK 10
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*LILOS_TIMER_CallBack)(void);
enum LILOS_TIME_STATE_Enum {
  LILOS_TIME_END = 0,
  LILOS_TIME_START = 1,
  LILOS_TIME_STOP = 2,
  LILOS_TIME_PROCESS = 3,
};

enum LILOS_SWTIME_ERR_Enum {
  LILOS_SW_TIMER_NOT_EXIST = 0xE0,
  LILOS_SW_TIMER_OVER_MAX_ID,
};

#define LILOS_SWTIME_ONE_TIME 1
#define LILOS_SWTIME_LOOP_TIME 2
#define LILOS_SWTIME_ONE_TIME_NOT_DELETE 3

/**
 * @brief   Creat a software timer
 *
 * @param   ID    return software timer allocation id
 * @param   mode  timer mode
 *                now hava three mode:
 *                LILOS_SWTIME_ONE_TIME,            at time out delete timer
 *                LILOS_SWTIME_LOOP_TIME,           at time out restart timer
 *                LILOS_SWTIME_ONE_TIME_NOT_DELETE  stop timer clean time
 * @param   time    set callback time
 *                  (unit:ms)
 * @param   Task    time to callback function
 *                  now support function types:(void function(void))
 * @return  0: success LILOS_SWTIME_ERR_Enum: error
 */
unsigned char lilos_Creat_swTimer(unsigned int *ID, unsigned char mode,
                                  unsigned int time, LILOS_TIMER_CallBack Task);

/**
 * @brief   start software timer
 *
 * @param   ID     timer id
 * @return  0: success LILOS_SWTIME_ERR_Enum: error
 */
unsigned char lilos_Start_swTimer(unsigned int ID);

/**
 * @brief   Stop software timer
 *
 * @param   ID     timer id
 * @return  0: success LILOS_SWTIME_ERR_Enum: error
 */
unsigned char lilos_Stop_swTimer(unsigned int ID);

/**
 * @brief   Delete software timer
 *
 * @param   ID     timer id
 * @return  0: success LILOS_SWTIME_ERR_Enum: error
 */
unsigned char lilos_Delete_swTimer(unsigned int ID);

#ifdef __cplusplus
}
#endif

#endif
