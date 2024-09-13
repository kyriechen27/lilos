/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_init_call.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.06.01
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __LILOS_INIT_CALL_H__
#define __LILOS_INIT_CALL_H__

#include "lilos_config.h"

#ifndef LILOS_NO_INIT_CALL
typedef void (*initcall_t)(void);

#define __define_initcall(fn, id)                                   \
  static const initcall_t __initcall_##fn##id __attribute__((used)) \
  __attribute__((__section__("initcall" #id "init"))) = fn;

#define sys_initcall(fn) __define_initcall(fn, 0)
#define device_initcall(fn) __define_initcall(fn, 1)
#define app_initcall(fn) __define_initcall(fn, 2)
#endif

#endif
