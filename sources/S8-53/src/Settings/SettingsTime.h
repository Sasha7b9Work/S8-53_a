

#pragma once
#include "SettingsTypes.h"
#include "defines.h"


/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsTime
 *  @{
 */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SET_TBASE                           (set.time.tBase)        ///< SettingTime.tBase

#define TSHIFT                              (set.time.tShiftRel)    ///< SettingsTime.tShiftRel

#define TIME_DIV_XPOS                       (set.time.timeDivXPos)  ///< SettingsTime.timeDivXPos
#define TIME_DIV_XPOS_IS_SHIFT_IN_MEMORY    (TIME_DIV_XPOS == FunctionTime_ShiftInMemory)

#define SET_TPOS                            (set.time.tPos)         ///< SettingsTime.tPos
#define SET_TPOS_IS_LEFT                    (SET_TPOS == TPos_Left)
#define SET_TPOS_IS_CENTER                  (SET_TPOS == TPos_Center)
#define SET_TPOS_IS_RIGHT                   (SET_TPOS == TPos_Right)

#define SAMPLE_TYPE                         (set.time.sampleType)   ///< SettingsTime.sampleType
#define SAMPLE_TYPE_IS_EQUAL                (SAMPLE_TYPE == SampleType_Equal)
#define SAMPLE_TYPE_IS_REAL                 (SAMPLE_TYPE == SampleType_Real)

#define PEAKDET                             (set.time.peakDet)      ///< SettingsTime.peakDet
#define PEAKDET_IS_DISABLE                  (PEAKDET == PeackDet_Disable)
#define PEAKDET_IS_ENABLE                   (PEAKDET == PeackDet_Enable)

#define SET_SELFRECORDER                    (set.time.selfRecorder) ///< SettingsTime.selfRecorder


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ������� ����� �����/���.
typedef enum
{
    FunctionTime_Time,              ///< ����� ��������� ��������� �� �������.
    FunctionTime_ShiftInMemory      ///< ����� ��������� ������������ �� ������ �������� ������.
} FunctionTime;

/// �������� ������������� � ������.
typedef enum
{
    TPos_Left,      ///< ������������� ��������� � ������ ������.
    TPos_Center,    ///< ������������� ��������� � ������ ������.
    TPos_Right      ///< ������������� ��������� � ����� ������.
} TPos;

/// ��� ������� ��� ������ �������������.
typedef enum
{
    SampleType_Real,   ///< �������� ����� - � ���������� ��������� ������ ������� ��������� �����, ������ �� ��������������.
    SampleType_Equal   ///< ������������� - ������ �������� �� ��������� ������, ���������� �� �������������.
} SampleType;

/// ����� ������ �������� ���������.
typedef enum
{
    PeackDet_Disable,
    PeackDet_Enable,
    PeackDet_Average
} PeackDetMode;

/// ����� ����� �������, � ������� ��� ������.
typedef enum
{
    FNP_281,
    FNP_512,
    FNP_1024
} ENUM_POINTS_FPGA;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� ��� X.
typedef struct
{ //-V802
    TBase               tBase;          ///< ������� �� �������.
    int16               tShiftRel;      ///< �������� �� �������.
    FunctionTime        timeDivXPos;
    TPos                tPos;           ///< �������� ������������� � ������.
    SampleType          sampleType;     ///< ��� ������� ��� ������ �������������.
    PeackDetMode        peakDet;        ///< ����� ������ �������� ���������
    bool                selfRecorder;   ///< ������� �� ����� ���������.
    ENUM_POINTS_FPGA    oldNumPoints;   ///< \brief ����� ������������� � ����� �������� ���������, ������������� ���������� ����� � 1024, � ���� 
                                        /// ���������� ��, ��� ����, ����� ����� ������������.
} SettingsTime;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� ������� �� �������.
void sTime_SetTBase(TBase tBase);
/// ��������� �������� �� ������� � ������������� ��������.
void sTime_SetTShift(int16 shift);                   
/// ������ �������� ���������� ������ ������������� � ������.
int sTime_TPosInPoints(PeackDetMode peakDet, int numPoints, TPos tPos);
/// �������� �� ������� � ������ ������. �.�. �� ����� � ��� �������� ��� ��� ���������, ��� �������� ���������� �� ����������� � ���������� ����� � ��� ����.
int sTime_TShiftInPoints(PeackDetMode peakDet);
/// ����������� �������� �� �������, ������� ����� ���� �������� � ���������� �����.
int16 sTime_TShiftMin();
/// �������� �� �������, ��������������� ������� TPos.
int16 sTime_TShiftZero();
/// ���� true, ������, �������� ������������.
bool sTime_RandomizeModeEnabled();


/** @}  @}
 */
