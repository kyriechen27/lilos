/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_sysTick.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.6.29
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __LOS_SYSTICK_H__
#define __LOS_SYSTICK_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   os systick function
 * @note    This function is os timer.
 *          Place this function in the system tick timer interrupt.
 *          system tick time set 1ms.
 */
extern void lil_os_systick(void);

#ifdef __cplusplus
}
#endif

#endif
