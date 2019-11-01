/* 
 * File:   taskapp.h
 * Author: Administrator
 */

#ifndef TASKAPP_H
#define	TASKAPP_H

#ifdef   _TASKAPP_MODULE_
#define  TASKAPP_EXT
#else
#define  TASKAPP_EXT  extern
#endif

#include "taskmanger.h"

	TASKAPP_EXT OS_TCB  IdleTaskTCB;

	void IdleTask(void);//创建脉冲并调用hook,无其他操作
	void IdleTaskHook(void);
	
#ifdef	__cplusplus
extern "C" {
#endif



#ifdef	__cplusplus
}
#endif

#undef TASKAPP_EXT

#endif	/* TASK_H */

