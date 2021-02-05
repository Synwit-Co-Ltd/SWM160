#include <stdio.h>  
#include <stdlib.h>  
#include "circle_queue.h"
#include "define.h"

bool Queue_Init(CircleQueue_t *pQue)  
{  
	assert(pQue != NULL);
	
	pQue->front = 0;
	pQue->rear = 0;  
	pQue->count = 0;  
	return true;  
}  
  
bool Queue_IfEmpty(CircleQueue_t *pQue)  
{  
	assert(pQue != NULL);
	
	if(pQue->count == 0)  
		return true;  
	else  
		return false;  
}  
  
bool Queue_IfFull(CircleQueue_t *pQue)  
{  
	assert(pQue != NULL);
	
	if(pQue->count == QUEUESIZE)  
		return true;  
	else  
		return false;  
}  
  
bool Queue_Put(CircleQueue_t *pQue, QueueElem_t e)  
{  
	assert(pQue != NULL);
	
	if(pQue->count == QUEUESIZE)  
	{  
		//TRACE("The pQue is full");  
		return false;  
	}  

	pQue->data[pQue->rear] = e;  
	pQue->rear = (pQue->rear + 1) % QUEUESIZE;  
	pQue->count++;  
	return true;  
}  
  
bool Queue_Get(CircleQueue_t *pQue, QueueElem_t *e)  
{  
	assert(pQue != NULL);
	
	if(pQue->count == 0)  
	{  
		return false;  
	}  

	*e = pQue->data[pQue->front];  
	pQue->front = (pQue->front + 1) % QUEUESIZE;  
	pQue->count--;  
	return true;  
}  
  
bool Queue_QueryHead(CircleQueue_t *pQue, QueueElem_t *e)  
{  
	assert(pQue != NULL);
	
	if(pQue->count == 0)  
	{  
		return false;  
	}  

	*e = pQue->data[pQue->front];
	return true;  
}  
  
bool Queue_Clear(CircleQueue_t *pQue )  
{  
	assert(pQue != NULL);
	
	pQue->front = pQue->rear = 0;  
	pQue->count = 0;  
	return true;   
}  
  
uint16_t Queue_Length(CircleQueue_t *pQue)  
{  
	assert(pQue != NULL);
	return pQue->count;  
}

