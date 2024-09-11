/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_init.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.06.01
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __LILOS_INIT_H__
#define __LILOS_INIT_H__

#include "lilos_init_call.h"
#include "lilos_systick.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   lilos task
 * @note    lilos task used to while(1) loop
 *
 * @return  return task status
 */
unsigned int lilos_task(void);

/**
 * @brief   lilos Start function
 * @note    start lilos system used to main function
 */
void lilos_Start(void);

/**
 * @brief   lilos init call
 * @note    init call used to init function
 */
void lilos_init_call(void);

#ifdef __cplusplus
}
#endif

#endif
