/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_queue.h
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.3
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#ifndef __LILOS_QUEUE_H__
#define __LILOS_QUEUE_H__

#include "lilos_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LILOS_MAX_QUEUE_NUM
#define LILOS_MAX_QUEUE_NUM 10
#endif

#ifndef LILOS_MAX_QUEUE_MASSGAE_NUM
#define LILOS_MAX_QUEUE_MASSGAE_NUM 128
#endif

typedef enum {
  LILOS_QUEUE_OK = 0x00,
  LILOS_QUEUE_ERROR = 0x01,
  LILOS_QUEUE_BUSY = 0x02,
  LILOS_QUEUE_TIMEOUT = 0x03,
  LILOS_QUEUE_OVERLOAD = 0x04,
  LILOS_QUEUE_FREE = 0x05,
  LILOS_QUEUE_EXIST = 0x06,
  LILOS_QUEUE_LEN_OVER = 0x07,
} LILOS_QUEUE_Status;

/**
 * @brief   Queue Create
 *
 * @param   ID      return queue allocation id
 * @param   buf_len queue buffer max length
 * @param   max_size queue max size
 * @return  LILOS_QUEUE_Status
 */
LILOS_QUEUE_Status lilos_Create_Queue(unsigned int* ID, unsigned int buf_len,
                                      unsigned int max_size);

/**
 * @brief   Queue Delete
 *
 * @param   ID      queue id
 * @return  LILOS_QUEUE_Status
 */
LILOS_QUEUE_Status lilos_Delete_Queue(unsigned int ID);

/**
 * @brief   Queue Write
 *
 * @param   ID      queue id
 * @param   data    write data pointer
 * @param   len     write data length
 * @return  LILOS_QUEUE_Status
 */
LILOS_QUEUE_Status lilos_Queue_Write(unsigned int ID, char* data,
                                     unsigned int len);

/**
 * @brief   Queue Read
 *
 * @param   ID      queue id
 * @param   data    read return data pointer
 * @param   len     read return data length pointer
 * @return  LILOS_QUEUE_Status
 */
LILOS_QUEUE_Status lilos_Queue_Read(unsigned int ID, char* data,
                                    unsigned int* len);
/**
 * @brief   Queue Get Count
 *
 * @param   ID      queue id
 * @return  count
 */
int lilos_Queue_Get_Count(unsigned int ID);

#ifdef __cplusplus
}
#endif

#endif
