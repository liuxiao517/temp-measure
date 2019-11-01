/* 
 * File:   templib.h
 * Author: apleilx
 */

#ifndef TEMPLIB_H_
#define	TEMPLIB_H_

#ifdef   _TEMPLIB_MODULE_
#define  TEMP_EXT
#else
#define  TEMP_EXT  extern
#endif

#include "stdint.h"

#ifdef	__cplusplus
extern "C" {
#endif

    
#define TEMP_ERR_LIMITE_H_MASK          0x01
#define TEMP_ERR_LIMITE_L_MASK          0x10
#define TEMP_ERR_TABLE_H_MASK           0x02
#define TEMP_ERR_TABLE_L_MASK           0x20
    
#define TEMP_DIVISION_MAX               (20000L)
#define TEMP_DIVISION_MIN               (0L)
    
/*-----------------------------------------------------------------------------*
 * 
 * ADMarkH    -->     DivisionMax    
 * ADMarkL    -->     DivisionMin
 * 
 * Dx = (ADx - ADMarkL) * (DivisionMax - DivisionMin) / (ADMarkH -  ADMarkL)
 * Tx = (Dx - x0) * (y1 - y0) / (x1 - x0) 
 *-----------------------------------------------------------------------------*/    
    
    typedef struct
    {
        int16_t Division;
        int16_t Temp;
        
    } TEMP_TABLE_Type;
    
    typedef struct
    {
        int16_t MarkADL;
        int16_t MarkADH;
    } TEMP_AD_MARK_Type;
    
    typedef struct
    {
        int16_t MarkTempL;
        int16_t MarkTempH;
    } TEMP_VAL_MARK_Type;	
	
    typedef struct
    {
        int16_t PB;
        int16_t PK;
    } TEMP_CORRECT_Type;
    
    typedef struct
    {
        int16_t LimiteH;
        int16_t LimiteL;
    } TEMP_LIMITE_Type;
    
	
	typedef pdata struct
	{
		uint8_t Err;
		int16_t ADVal;
		float Temp;
		float TempReal;
		float TempDis;
        float Flt;
		TEMP_AD_MARK_Type Mark;
		TEMP_CORRECT_Type Correct;
		TEMP_LIMITE_Type Limite;
	
	} TEMP_OBJ_Type;
	                        
    TEMP_EXT uint8_t bCFEn;
    
    void TempCal(TEMP_OBJ_Type* TempObj);
    float  TempGet(TEMP_OBJ_Type* TempObj);
	int16_t TempIntGet(TEMP_OBJ_Type* TempObj);
	int16_t  DispTempGet(TEMP_OBJ_Type* TempObj);
    void TempADSet(TEMP_OBJ_Type* TempObj ,int16_t AD_Val);
    uint8_t TempErrGet(TEMP_OBJ_Type* TempObj);
	


#ifdef	__cplusplus
}
#endif

#undef TEMP_EXT

#endif	/* TEMPLIB_H_ */

