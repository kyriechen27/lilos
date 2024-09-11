/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_log.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.1
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __LILOS_LOG_H__
#define __LILOS_LOG_H__

#include "lilos_types.h"

#include "lilos_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LOS_OK
#define LOS_OK 0U
#endif

#ifndef LOS_NOK
#define LOS_NOK 1U
#endif

#define LOG_EMG_LEVEL 0

#define LOG_COMMON_LEVEL (LOG_EMG_LEVEL + 1)

#define LOG_ERR_LEVEL (LOG_COMMON_LEVEL + 1)

#define LOG_WARN_LEVEL (LOG_ERR_LEVEL + 1)

#define LOG_INFO_LEVEL (LOG_WARN_LEVEL + 1)

#define LOG_DEBUG_LEVEL (LOG_INFO_LEVEL + 1)

#ifdef BUILD_DEBUG
#define PRINT_LEVEL LOG_DEBUG_LEVEL
#endif

#ifndef PRINT_LEVEL
#define PRINT_LEVEL LOG_ERR_LEVEL
#endif

unsigned char log_leve_check(unsigned int level);
#define LILOS_LOG_Printf(level, fmt, args...) \
  do {                                        \
    if (!log_leve_check(level)) {             \
      printf(fmt, ##args);                    \
      fflush(stdout);                         \
    }                                         \
  } while (0)

#define PRINT_DEBUG(fmt, args...) LILOS_LOG_Printf(LOG_DEBUG_LEVEL, fmt, ##args)
#define PRINT_INFO(fmt, args...) LILOS_LOG_Printf(LOG_INFO_LEVEL, fmt, ##args)
#define PRINT_WARN(fmt, args...) \
  LILOS_LOG_Printf(LOG_WARN_LEVEL, "[%s:%d]" fmt, __func__, __LINE__, ##args)
#define PRINT_ERR(fmt, args...) \
  LILOS_LOG_Printf(LOG_ERR_LEVEL, "[%s:%d]" fmt, __func__, __LINE__, ##args)
#define PRINTK(fmt, args...) LILOS_LOG_Printf(LOG_COMMON_LEVEL, fmt, ##args)
#define PRINT_EMG(fmt, args...) LILOS_LOG_Printf(LOG_EMG_LEVEL, fmt, ##args)

/**
 * @brief   Print hex data
 *
 * @param   head_string before data message
 * @param   data        data pointer
 * @param   len         data length
 */
void PRINT_DEBUG_HEX(const char *head_string, const unsigned char *data,
                     unsigned int len);

#ifdef __cplusplus
}
#endif

#endif
