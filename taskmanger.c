/****************************************************************************
 * Dirve taskmanger
 * Tested MCU 
 * Owner : apleilx
 * **************************************************************************/
#define _TASKMANGER_MODULE_

#include "taskmanger.h"
#include "taskapp.h"
#include "systimer.h"

#define TASK_NULL ((OS_TCB  *)(&IdleTaskTCB))		

OS_TCB  *pOSTaskListHigh;
OS_TCB  *pOSTaskListLow;
OS_TCB  *pOSTaskCur;


//void OSTaskSw(void);

/*****************************************************************************//*!
*
* @brief   task list init.
*          lowest priority list¡£       
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void OSInit()
{
	//tell us  that the list is empty 
	pOSTaskListHigh  = TASK_NULL;
	
	//init the idle task
	IdleTaskTCB.NextTask  = &IdleTaskTCB;
	IdleTaskTCB.Priority  = OS_PRIO_MAX;
	IdleTaskTCB.TaskSt    = OS_TASK_STATE_ACTIVE;
	IdleTaskTCB.TaskPtr   = &IdleTask;
	
	//add the first task to the list
	pOSTaskListLow        = &IdleTaskTCB;
	
	PowerUpTimeCnt = 0;
	AutoCnt        = 0;
}

/*****************************************************************************//*!
*
* @brief   add tast to task list.
*          lowest priority list¡£       
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void OSTaskCreat(OS_TCB *TaskTCB, uint8_t Prio, void (*TaskPtr)(void))
{
	OS_TCB *TaskFind;
	
	TaskTCB->Priority    = Prio;
	TaskTCB->TaskPtr     = TaskPtr;
	
	if( OS_PRIO_MAX == Prio )
	{
		TaskTCB->TaskSt = OS_TASK_STATE_ACTIVE;
		
		//check either the task has been in the list or not
		TaskFind     = IdleTaskTCB.NextTask;
		while((TaskFind != TaskTCB) && (TaskFind != &IdleTaskTCB)) 
		{
			TaskFind     = TaskFind->NextTask;
		}
		
		if(TaskFind == &IdleTaskTCB)
		{
			//it is not life, insert it to the list 
			TaskTCB->NextTask   = pOSTaskListLow->NextTask;          
			pOSTaskListLow->NextTask = TaskTCB;
			
			//point to newest task //no necessery
			//OSTaskListLow = TaskTCB;
		}	
		else
		{
			//the task has been in the list, out
		}		
	}
	else
	{
		//higher priority task
		TaskTCB->TaskSt = OS_TASK_STATE_SLEEP;
		TaskTCB->NextTask = TASK_NULL;
	}
}

/*****************************************************************************//*!
*
* @brief   make a task(high/low) to sleep. only used in user functon
*          Just called in interrupt
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
#if OS_TASK_PEND_ENABLE > 0

void OSTaskPend(OS_TCB  *TCB)
{
	IEA = 0;
	TCB->TaskSt     = OS_TASK_STATE_SLEEP;
	IEA = 1;
}

#endif
/*****************************************************************************//*!
*
* @brief   active a task(high/low).  only used in interrupt functon
*          Just called in interrupt 
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
#if OS_TASK_POST_ENABLE > 0
	
void OSTaskPost(OS_TCB *TCB)
{
	OS_TCB *TaskListSite;
	OS_TCB *TaskListSiteLast;
	
	if(OS_PRIO_MAX != TCB->Priority)
	{
		//WOW! it is a VIP
		TCB->TaskSt = OS_TASK_STATE_ACTIVE;
		if( TASK_NULL == pOSTaskListHigh)                  
		{
			//list is empty ,it is the first man
			pOSTaskListHigh = TCB;
			TCB->NextTask = TASK_NULL;
		}
		else                                              
		{
			//Oh, shit! there is someone in the list, I will do something to find it's site
			TaskListSiteLast = pOSTaskListHigh;
			TaskListSite = pOSTaskListHigh->NextTask;
			
			//wait a moment, the partner has a VIP card, I should judge how many power in the card 
			while(TaskListSite->Priority < TCB->Priority) 
			{
				TaskListSiteLast = TaskListSite;
				TaskListSite     = TaskListSite->NextTask;
			}
			//here it is, seat
			TaskListSiteLast->NextTask = TCB;
			TCB->NextTask = TaskListSite;
		}
	}
	else
	{
		//quick up, give life to him. God is calling him.
		TCB->TaskSt = OS_TASK_STATE_ACTIVE;
	}
}

#endif

/*****************************************************************************//*!
*
* @brief   system task.
*       
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void OSRun()
{
	for(;;)
	{
		//pOSTaskListHigh 
		//disableInterrupts();
		IEA = 0;
		pOSTaskCur = pOSTaskListHigh;
		IEA = 1;
		//enableInterrupts();
		 
		if(TASK_NULL == pOSTaskCur )                
		{
			//high priority list is empty, run lowest priority list
			if( OS_TASK_STATE_ACTIVE == pOSTaskListLow->TaskSt)
			{
				pOSTaskListLow->TaskPtr();
			}
			else
			{
			
			}
			//point to the next task
			//there is not necessary to disable interrupt ,interrupu proc don't modify "pOSTaskListLow"
			pOSTaskListLow = pOSTaskListLow->NextTask;
	
		}
		else
		{
			//there is some  high priority task exciting, game start
			pOSTaskCur->TaskPtr();
			//game over, discard it
			//must disable interrupt ,because interrupu proc may modify "pOSTaskListHigh"
			IEA = 0;
			pOSTaskListHigh->TaskSt = OS_TASK_STATE_SLEEP;
			pOSTaskListHigh = pOSTaskListHigh->NextTask;
			//OSTaskPend(pOSTaskListHigh); 
			IEA = 1; 	
		}
	
		OSTaskSwHook();
	}
}

/*****************************************************************************//*!
*
* @brief   make a task (high/low) to sleep. only used in user functon
*          //Just Called in app //
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
#if OS_TASK_SLEEP_ENABLE > 0
void OSTaskSleep(OS_TCB  *TCB)  
{
	IEA = 0;
	TCB->TaskSt     = OS_TASK_STATE_SLEEP;
	IEA = 1;
}

#endif

/*****************************************************************************//*!
*
* @brief   active a task(low).  only used in interrupt functon
*          //Just for low_list  //Just Called in app
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
#if OS_TASK_WAKEUP_ENABLE > 0
void OSTaskWakeup(OS_TCB  *TCB)
{
	if(OS_PRIO_MAX == TCB->Priority)
	{
		//quick up, give life to him. God is calling him.
		TCB->TaskSt = OS_TASK_STATE_ACTIVE;
	}
	else
	{
		//do nothing
	}
}

#endif

