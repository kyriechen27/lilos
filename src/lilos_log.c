/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_log.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.1
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "lilos_log.h"
static const char *g_logString[] = {
    "EMG", "COMMON", "ERR", "WARN", "INFO", "DEBUG",
};

unsigned char log_leve_check(unsigned int level) {
  if (level > PRINT_LEVEL) {
    return LOS_NOK;
  }

  if ((level != LOG_COMMON_LEVEL) &&
      ((level > LOG_EMG_LEVEL) && (level <= LOG_DEBUG_LEVEL))) {
    PRINTK("[%s]", g_logString[level]);
  }

  return LOS_OK;
}

void PRINT_DEBUG_HEX(const char *head_string, const unsigned char *data,
                     unsigned int len) {
#ifdef BUILD_DEBUG
  unsigned int i;
  PRINT_DEBUG("%s[", head_string);
  for (i = 0; i < len; i++) {
    PRINTK("%02x ", data[i]);
  }
  PRINTK("]\n");
#else
  (void)head_string;
  (void)data;
  (void)len;
#endif
}
