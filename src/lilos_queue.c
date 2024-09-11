/********************************** (C) COPYRIGHT ******************************
 * File Name          : lilos_queue.c
 * Author             : kyriechen
 * E-mail             : kyriechen@czlilstar.com
 * Date               : 2023.7.3
 * Copyright (c) 2023 Changzhou Lilstar Internet of Things Technology Co., Ltd
 *******************************************************************************/
#include "lilos_queue.h"

#include <malloc.h>

#include "lilos_log.h"

typedef struct {
  int size;
  unsigned char* buf;
} LILOS_QUEUE_DataTypeDef;

typedef struct {
  int front;
  int rear;
  int maxSize;
  int count;
  LILOS_QUEUE_DataTypeDef* data;
  int data_len;
} LILOS_QUEUE_HandleTypeDef;

LILOS_QUEUE_HandleTypeDef* LILOS_QUEUE_TASK[LILOS_MAX_QUEUE_NUM + 1] = {NULL};

LILOS_QUEUE_Status lilos_Create_Queue(unsigned int* ID, unsigned int buf_len,
                                     unsigned int max_size) {
  int i, n, j;
  for (i = 1; i <= LILOS_MAX_QUEUE_NUM; i++) {
    if (LILOS_QUEUE_TASK[i] == NULL) {
      LILOS_QUEUE_TASK[i] = malloc(sizeof(LILOS_QUEUE_HandleTypeDef));
      if (LILOS_QUEUE_TASK[i] == NULL) {
        PRINT_ERR("Creat_Queue Malloc Error\n");
        return LILOS_QUEUE_ERROR;
      }

      LILOS_QUEUE_TASK[i]->data =
          malloc(sizeof(LILOS_QUEUE_DataTypeDef) * max_size);
      if (LILOS_QUEUE_TASK[i]->data == NULL) {
        PRINT_ERR("Creat_Queue Malloc Error\n");
        free(LILOS_QUEUE_TASK[i]);
        LILOS_QUEUE_TASK[i] = NULL;
        return LILOS_QUEUE_ERROR;
      }

      for (n = 0; n < max_size; n++) {
        LILOS_QUEUE_TASK[i]->data[n].buf = calloc(buf_len, sizeof(char));
        if (LILOS_QUEUE_TASK[i]->data[n].buf == NULL) {
          PRINT_ERR("Creat_Queue calloc Error\n");
          for (j = 0; j < n; j++) {
            free(LILOS_QUEUE_TASK[i]->data[j].buf);
            LILOS_QUEUE_TASK[i]->data[j].buf = NULL;
          }
          free(LILOS_QUEUE_TASK[i]->data);
          LILOS_QUEUE_TASK[i]->data = NULL;
          free(LILOS_QUEUE_TASK[i]);
          LILOS_QUEUE_TASK[i] = NULL;
          return LILOS_QUEUE_ERROR;
        }
      }

      LILOS_QUEUE_TASK[i]->front = 0;
      LILOS_QUEUE_TASK[i]->rear = -1;
      LILOS_QUEUE_TASK[i]->maxSize = max_size;
      LILOS_QUEUE_TASK[i]->count = 0;
      LILOS_QUEUE_TASK[i]->data_len = buf_len;
      *ID = i;
      PRINT_DEBUG("Creat_Queue Success ID:%d\n", i);
      return LILOS_QUEUE_OK;
    }
  }
  PRINT_ERR("Creat_Queue NO FREE\n");
  return LILOS_QUEUE_ERROR;
}

static int lilos_Queue_Is_Full(unsigned int ID) {
  return LILOS_QUEUE_TASK[ID]->count == LILOS_QUEUE_TASK[ID]->maxSize;
}

static int lilos_Queue_Is_Empty(unsigned int ID) {
  return LILOS_QUEUE_TASK[ID]->count == 0;
}

int lilos_Queue_Get_Count(unsigned int ID) {
  return LILOS_QUEUE_TASK[ID]->count;
}

LILOS_QUEUE_Status lilos_Delete_Queue(unsigned int ID) {
  if (LILOS_QUEUE_TASK[ID] == NULL) {
    return LILOS_QUEUE_EXIST;
  }
  int i;
  if (ID > 0 && ID <= LILOS_MAX_QUEUE_NUM) {
    for (i = 0; i < LILOS_QUEUE_TASK[ID]->maxSize; i++) {
      free(LILOS_QUEUE_TASK[ID]->data[i].buf);
      LILOS_QUEUE_TASK[ID]->data[i].buf = NULL;
    }
    free(LILOS_QUEUE_TASK[ID]->data);
    LILOS_QUEUE_TASK[ID]->data = NULL;
    free(LILOS_QUEUE_TASK[ID]);
    LILOS_QUEUE_TASK[ID] = NULL;
    PRINT_DEBUG("Delete_Queue ID %d\n", ID);
    return LILOS_QUEUE_OK;
  }
  PRINT_ERR("Delete_Queue ID ERROR\n");
  return LILOS_QUEUE_ERROR;
}

LILOS_QUEUE_Status lilos_Queue_Write(unsigned int ID, char* data,
                                     unsigned int len) {
  if (LILOS_QUEUE_TASK[ID] == NULL) {
    PRINT_ERR("No Queue No %d\n", ID);
    return LILOS_QUEUE_EXIST;
  }
  if (lilos_Queue_Is_Full(ID)) {
    PRINT_ERR("Queue is Full ID = %d\n",ID);
    return LILOS_QUEUE_OVERLOAD;
  }
  if (len > LILOS_QUEUE_TASK[ID]->data_len) {
    return LILOS_QUEUE_LEN_OVER;
  }
  LILOS_QUEUE_TASK[ID]->rear =
      (LILOS_QUEUE_TASK[ID]->rear + 1) % LILOS_QUEUE_TASK[ID]->maxSize;
  memcpy(LILOS_QUEUE_TASK[ID]->data[LILOS_QUEUE_TASK[ID]->rear].buf, data, len);
  LILOS_QUEUE_TASK[ID]->data[LILOS_QUEUE_TASK[ID]->rear].size = len;
  LILOS_QUEUE_TASK[ID]->count++;
  return LILOS_QUEUE_OK;
}

LILOS_QUEUE_Status lilos_Queue_Read(unsigned int ID, char* data,
                                    unsigned int* len) {
  if (LILOS_QUEUE_TASK[ID] == NULL) {
    PRINT_ERR("No Queue No %d\n", ID);
    return LILOS_QUEUE_EXIST;
  }
  if (lilos_Queue_Is_Empty(ID)) {
    return LILOS_QUEUE_FREE;
  }

  memcpy(data, LILOS_QUEUE_TASK[ID]->data[LILOS_QUEUE_TASK[ID]->front].buf,
         LILOS_QUEUE_TASK[ID]->data[LILOS_QUEUE_TASK[ID]->front].size);
  *len = LILOS_QUEUE_TASK[ID]->data[LILOS_QUEUE_TASK[ID]->front].size;
  LILOS_QUEUE_TASK[ID]->front =
      (LILOS_QUEUE_TASK[ID]->front + 1) % LILOS_QUEUE_TASK[ID]->maxSize;
  LILOS_QUEUE_TASK[ID]->count--;

  return LILOS_QUEUE_OK;
}