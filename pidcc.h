/* 
 * File:   PIDdevice.h
 */

#ifndef PIDCCDEVICE_H
#define	PIDCCDEVICE_H

    // c51 pid st
    void Pid_Control_C51(void);
    void Pid_C51_Set( int xdata * Par);
    void Pid_C51_Pv(float temp);
    void Pid_C51_Sv(int temp);
    void Pid_C51_Al(int temp);
    void Pid_C51_Clr(void);
    void Pid_C51_DvClr(void);
    void Pid_C51_GetPid(int xdata *Des);
	
    void  exit_autoturning(void);      //按键停止自整定调用
    void  start_at_pid(void);          //按键启动自整定调用
    bit   autoturning_process(void);   // 每隔0.5秒调用一次，返回0，关输出；1：全输出
    
    extern bit EndAuto_bit;            //为1，自整定结束，需保存PID到存贮器
    extern bit RunAtSign_Bit;
    extern unsigned int ton_heat_num; // 
	
#endif	/* PIDDEVICE_H */
