#include <stdio.h>  
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef __CIRCLE_QUEUE_H__
#define __CIRCLE_QUEUE_H__

#define QUEUESIZE 256  
  
typedef unsigned char QueueElem_t ;  
  
typedef struct _CircleQueue  {  
    QueueElem_t data[QUEUESIZE];
    uint16_t front;
    uint16_t rear;
    uint16_t count;
}CircleQueue_t;   
  
bool Queue_Init(CircleQueue_t *pQue);
  
bool Queue_IfEmpty(CircleQueue_t *pQue);
  
bool Queue_IfFull(CircleQueue_t *pQue);
  
bool Queue_Put(CircleQueue_t *pQue, QueueElem_t e);

bool Queue_Get(CircleQueue_t *pQue, QueueElem_t *e); 
  
bool Queue_QueryHead(CircleQueue_t *pQue, QueueElem_t *e); 
  
bool Queue_Clear(CircleQueue_t *pQue );
  
uint16_t Queue_Length(CircleQueue_t *pQue);

#endif	//__CIRCLE_QUEUE_H__

