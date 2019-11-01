/****************************************************************************
 * taskapp
 * Tested MCU 
 * Owner : apleilx
 * **************************************************************************/
#define _TEMPLIB_MODULE_
#include "templib.h"

extern  TEMP_TABLE_Type code * TempTab;

#ifndef INT16_MAX
#define INT16_MAX 0x7FFF
#endif

/*****************************************************************************//*!
*
* @brief   temperature calculate .
*          ad val to temperature       
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

void TempCal(TEMP_OBJ_Type* TempObj) {
    float Temp;
    float CalData, Cal;

    int16_t CalInt;
    int16_t x0, x1, y0, y1;
    int8_t Cnt;


    //linear transformation                                                     //y = (x - ADL) * (DIV_H - DIV_L)/(ADH - ADL)
    Temp = (TempObj->ADVal - TempObj->Mark.MarkADL);
    Temp*=(TEMP_DIVISION_MAX - TEMP_DIVISION_MIN);
    Temp /= (TempObj->Mark.MarkADH - TempObj->Mark.MarkADL);

    //Non-linear correct with TempSensorTab                                        //y = (x-x0)*(y1-y0)/(x1-x0)
    CalData = TempTab[0].Division;
    if (Temp < CalData) {
        Temp = TempTab[0].Temp;
        TempObj->Err |= TEMP_ERR_TABLE_L_MASK;
    } else {
        TempObj->Err &= ~TEMP_ERR_TABLE_L_MASK;
        Cnt = 0;
        do {
            Cnt++;
            CalData = TempTab[Cnt].Division;
            CalInt = TempTab[Cnt].Division;
        } while ((CalData < Temp) && (CalInt != INT16_MAX));

        if (INT16_MAX == CalInt) {
            Temp = TempTab[Cnt - 1].Temp;
            TempObj->Err |= TEMP_ERR_TABLE_H_MASK;
        } else {
            TempObj->Err &= ~TEMP_ERR_TABLE_H_MASK;
            x1 = TempTab[Cnt].Division;
            y1 = TempTab[Cnt].Temp;
            x0 = TempTab[Cnt - 1].Division;
            y0 = TempTab[Cnt - 1].Temp;

            Temp = (Temp - x0);
            Temp *=  (y1 - y0);
            Temp /= (x1 - x0);
            Temp += y0;
        }
    }

    if (bCFEn) {
        Temp *= 1.8;
        Temp += 320;
    }

    //user correct                                                              //y = ( 1 + pk/4000)*x + pb
    CalData = Temp;
    Temp *= TempObj->Correct.PK;
    Temp /= 4000;
    Temp += CalData;
    Temp += TempObj->Correct.PB;

    CalData = TempObj->Limite.LimiteL - 20;
    Cal = TempObj->Limite.LimiteH + 20;

    TempObj->Err &= ~(TEMP_ERR_LIMITE_L_MASK | TEMP_ERR_LIMITE_H_MASK);
    if (Temp < CalData) {
        TempObj->Err |= TEMP_ERR_LIMITE_L_MASK;
        Temp = CalData;
    } else if (Temp > Cal) {
        TempObj->Err |= TEMP_ERR_LIMITE_H_MASK;
        Temp = Cal;
    } else {

    }

    TempObj->TempReal = Temp;
    TempObj->Temp = TempObj->Temp * TempObj->Flt + Temp * (1 - TempObj->Flt);
    TempObj->TempDis = TempObj->TempDis * TempObj->Flt + TempObj->Temp * (1 - TempObj->Flt);
}

/*****************************************************************************//*!
*
* @brief   get temperature .
*               
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

float TempGet(TEMP_OBJ_Type* TempObj) {
    return TempObj->Temp;
}

/*****************************************************************************//*!
*
* @brief   get temperature For display.
*               
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

int16_t TempIntGet(TEMP_OBJ_Type* TempObj) {

    if (TempObj->Temp < 0)
        return (int16_t) (TempObj->Temp - 0.5);
    else
        return (int16_t) (TempObj->Temp + 0.5);

}

/*****************************************************************************//*!
*
* @brief   get temperature For display.
*               
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

int16_t DispTempGet(TEMP_OBJ_Type* TempObj) {

    if (TempObj->TempDis < 0)
        return (int16_t) (TempObj->TempDis - 0.5);
    else
        return (int16_t) (TempObj->TempDis + 0.5);

}

/*****************************************************************************//*!
*
* @brief   set Ad val .
*               
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

void TempADSet(TEMP_OBJ_Type* TempObj, int16_t AD_Val) {

    TempObj->ADVal = AD_Val;
}

/*****************************************************************************//*!
*
* @brief   Get error .
*                
* @param   none
*
* @return  none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

uint8_t TempErrGet(TEMP_OBJ_Type* TempObj) {
    return TempObj->Err;
}
