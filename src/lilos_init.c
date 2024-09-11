/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_init.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.06.01
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "lilos_init.h"

#include "lilos_config.h"
#include "lilos_log.h"

unsigned int task_state = 0;
unsigned int lowpower_vote = 0;
extern unsigned int swtimer_state;

extern void lilos_swTIMER_Handler(void);
extern void lilos_CallBack_Handler(void);
extern void lilos_TASK_Handler(void);

extern initcall_t __initcall_start[];
extern initcall_t __initcall_end[];

#ifndef LILOS_NO_INIT_CALL
void lilos_init_call(void) {
  initcall_t *fn_entry;

  for (fn_entry = __initcall_start; fn_entry < __initcall_end; fn_entry++) {
    if (fn_entry) {
      (*fn_entry)();
    } else {
      PRINT_DEBUG("fn_entry is NULL\n");
    }
  }
}
#endif

unsigned int lilos_task(void) {
  lilos_swTIMER_Handler();
  lilos_TASK_Handler();
  lilos_CallBack_Handler();
  return task_state || swtimer_state || lowpower_vote || LILOS_LOWPOER_MODE;
}

void lilos_Start(void) {
  PRINTK("Lil_Os_Start\n");
#ifndef LILOS_NO_INIT_CALL
  lilos_init_call();
#endif
  while (1) {
    lilos_task();
  }
}

