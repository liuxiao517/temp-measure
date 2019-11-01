#ifndef SYS_TIMER_H
#define	SYS_TIMER_H

#include "stdint.h"
  
#ifdef   _TIMER_MODULE_
#define  TIM_EXT
#else
#define  TIM_EXT  extern
#endif      
    
#define SYSTICK_CYCLE             1                                            //system tick timer interrupt cycle 
#define COUNTER_50MS              (50/SYSTICK_CYCLE)
#define COUNTER_100MS             (100/SYSTICK_CYCLE)
#define COUNTER_250MS             (250/SYSTICK_CYCLE)
#define COUNTER_1S                (1000/SYSTICK_CYCLE)
#define COUNTER_2S                (2000/SYSTICK_CYCLE)
#define COUNTER_500MS             (500/SYSTICK_CYCLE)
#define COUNTER_10S               (10000/SYSTICK_CYCLE)
#define COUNTER_60S               (60000/SYSTICK_CYCLE)

TIM_EXT pdata uint16_t Counter_50ms;
TIM_EXT pdata uint16_t Counter_100ms;
TIM_EXT pdata uint16_t Counter_250ms;
TIM_EXT pdata uint16_t Counter_1s;
TIM_EXT pdata uint16_t Counter_2s;
TIM_EXT pdata uint16_t Counter_500ms;
TIM_EXT pdata uint16_t Counter_10s;
TIM_EXT pdata uint16_t Counter_60s;

TIM_EXT bit  bPulse_50ms;
TIM_EXT bit  bPulse_100ms;
TIM_EXT bit  bPulse_250ms;
TIM_EXT bit  bPulse_1s;
TIM_EXT bit  bPulse_2s;
TIM_EXT bit  bPulse_500ms;
TIM_EXT bit  bPulse_10s;
TIM_EXT bit  bPulse_60s;
TIM_EXT bit  bPulseSysTick;

TIM_EXT uint8_t SysTickCnt;
TIM_EXT uint8_t PowerUpTimeCnt;   //base on 100ms
TIM_EXT uint8_t  AutoCnt;        //base on 100ms
    
void SysPulseCreat(void);
void SysPulseClear(void);
void SysTickInit(void);


#undef TIM_EXT

#endif	/* SYS_TIMER_H */

