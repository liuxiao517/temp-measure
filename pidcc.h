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
	
    void  exit_autoturning(void);      //����ֹͣ����������
    void  start_at_pid(void);          //������������������
    bit   autoturning_process(void);   // ÿ��0.5�����һ�Σ�����0���������1��ȫ���
    
    extern bit EndAuto_bit;            //Ϊ1���������������豣��PID��������
    extern bit RunAtSign_Bit;
    extern unsigned int ton_heat_num; // 
	
#endif	/* PIDDEVICE_H */
