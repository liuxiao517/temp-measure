/* 
 * File:   taskmanger.h
 * Author: Administrator
 */

#ifndef TASKMANGER_H
#define	TASKMANGER_H

#include "stdint.h"

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef   _TASKMANGER_MODULE_
#define  TASKMAN_EXT
#else
#define  TASKMAN_EXT  extern
#endif

#define OS_TASK_PEND_ENABLE   1
#define OS_TASK_POST_ENABLE   1
#define OS_TASK_SLEEP_ENABLE  1
#define OS_TASK_WAKEUP_ENABLE 1
  
#define OS_PRIO_MAX           64
#define OS_LIST_LOW_PRIO      0
#define OS_LIST_HIGH_PRIO     1
#define OS_TASK_STATE_SLEEP   0
#define OS_TASK_STATE_ACTIVE  1

	sbit IEA   = 0xAF;
	
	typedef xdata struct OST_CB
	{
		uint8_t  Priority;
		uint8_t  TaskSt; 
		struct OST_CB xdata * NextTask;
		void (*TaskPtr)(void);
	} OS_TCB;
	
void OSInit(void);	
void OSTaskCreat(OS_TCB  *TaskTCB, uint8_t Prio, void (*TaskPtr)(void));	
void OSRun(void);	
void OSTaskPend(OS_TCB  *TCB); //For low / high Obj，Just called in interrupt
void OSTaskPost(OS_TCB  *TCB); //For low / high Obj，Just called in interrupt
void OSTaskSleep(OS_TCB  *TCB);  //For low / high Obj，Just for low_list   //Just Called in app
void OSTaskWakeup(OS_TCB  *TCB); //Just For low Obj，Just for low_list     //Just Called in app

void OSTaskSwHook(void);

#undef TASKMAN_EXT

#ifdef	__cplusplus
}
#endif

#endif	/* TASK_H */

