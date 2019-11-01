/****************************************************************************
 * taskapp
 * Tested MCU 
 * Owner : apleilx
 * **************************************************************************/
#define _TASKAPP_MODULE_
#include "taskapp.h"

extern void SysPulseCreat(void);
extern void SysPulseClear(void);

/*****************************************************************************//*!
*
* @brief   idle task.
*          lowest priority list¡£       
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void IdleTask()
{
	SysPulseClear();
	SysPulseCreat();

	IdleTaskHook();
}

