/* 
 * File:   pic24e_timer.c
 * Author: apleilx
 *
 * Created on 2015年9月3日, 上午9:59
 */
#define _TIMER_MODULE_
#include "systimer.h"

/*  IEN0   */
sbit EA = 0xAF;


/*****************************************************************************/
/*********************************Systimer运行**********************************/
/*
 *用于产生系统时基
 */

void SysPulseCreat()
{
    uint8_t TickCntTemp;
    
    if(0 == SysTickCnt)
        return;
    

	EA = 0;
    TickCntTemp = SysTickCnt;
    SysTickCnt  = 0;
    EA = 1;
    
    Counter_50ms  += TickCntTemp;
    Counter_100ms += TickCntTemp;
    Counter_250ms += TickCntTemp;
    Counter_1s    += TickCntTemp;
    Counter_2s    += TickCntTemp;
    Counter_500ms += TickCntTemp;
    Counter_10s   += TickCntTemp;
    Counter_60s   += TickCntTemp;

    bPulseSysTick   = 1;

    if(Counter_50ms >= COUNTER_50MS)
    {
        Counter_50ms -= COUNTER_50MS;
        bPulse_50ms = 1;
    }
    if(Counter_100ms >= COUNTER_100MS)
    {
        Counter_100ms -= COUNTER_100MS;
        bPulse_100ms = 1;
        AutoCnt++;
        if(PowerUpTimeCnt < 0xFF)
            PowerUpTimeCnt++;
    }
    if(Counter_250ms >= COUNTER_250MS)
    {
        Counter_250ms -= COUNTER_250MS;
        bPulse_250ms = 1;
    }
    if(Counter_1s >= COUNTER_1S)
    {
        Counter_1s -= COUNTER_1S;
        bPulse_1s = 1;
    }
    if(Counter_2s >= COUNTER_2S)
    {
        Counter_2s -= COUNTER_2S;
        bPulse_2s = 1;
    }
    if(Counter_500ms >= COUNTER_500MS)
    {
        Counter_500ms -= COUNTER_500MS;
        bPulse_500ms = 1;
    }
    if(Counter_10s >= COUNTER_10S)
    {
        Counter_10s -= COUNTER_10S;
        bPulse_10s = 1;
    }
    if(Counter_60s >= COUNTER_60S)
    {
        Counter_60s -= COUNTER_60S;
        bPulse_60s = 1;
    }
}

/*--------------------------------------------------------------------
 * 脉冲信号清除
 *-------------------------------------------------------------------*/
void SysPulseClear()
{
    bPulseSysTick = 0;
    bPulse_50ms  = 0;
    bPulse_100ms = 0;
    bPulse_250ms = 0;
    bPulse_1s    = 0;
    bPulse_2s    = 0;
    bPulse_500ms = 0;
    bPulse_10s   = 0;
    bPulse_60s   = 0;
}
/************************************TIMER0运行*******************************/
/*****************************************************************************/

/*****************************************************************************//*!
*
* @brief   Tick Init.
*               
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void SysTickInit(void)
{
    bPulseSysTick = 0;
    bPulse_50ms  = 0;
    bPulse_100ms = 0;
    bPulse_250ms = 0;
    bPulse_1s    = 0;
    bPulse_2s    = 0;
    bPulse_500ms = 0;
    bPulse_10s   = 0;
    bPulse_60s   = 0;

    Counter_50ms  = 0;
    Counter_100ms = 0;
    Counter_250ms = 0;
    Counter_1s    = 0;
    Counter_2s    = 0;
    Counter_500ms = 0;
    Counter_10s   = 0;
    Counter_60s   = 0;
	SysTickCnt    = 0;
    
    PowerUpTimeCnt = 0;
}
