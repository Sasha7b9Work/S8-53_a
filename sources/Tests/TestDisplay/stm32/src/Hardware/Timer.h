#pragma once 
#include "defines.h"


typedef enum
{
    kPressKey,                  // ����� �������������, ����� �������� ������� �������.
    kShowLevelRShift0,          // ����� �������������, ����� ���������� ��������� ����� �������� ������ 1.
    kShowLevelRShift1,          // ����� �������������, ����� ���������� ��������� ����� �������� ������ 2.
    kShowLevelTrigLev,          // ����� �������������, ����� ���������� ��������� ����� ������ �������������
    kNumSignalsInSec,           // ��� ��������� ���������� ���������� ������� � �������.
    kFlashDisplay,              // ������ ��� ��������� �������� ������ �����-������ �������.
    kP2P,                       // ������ ��� ������ ������ � ������ ����������� ������.
    kShowMessages,              // ������ ��� ��������� ����� ������ �������������� � ��������������� ���������.
    kMenuAutoHide,              // ������ ��� ������� ������� ��������� ����.
    kRShiftMarkersAutoHide,     // ������ ��� ������� ������� ��������� �������������� ������� �����.
    kTemp,                      // ���������������, ��� ����� ����.
    kStopSound,                 // ��������� ����
    kTemporaryPauseFPGA,        // ��������� ����� ��� �������� ������� �� ������ ����� �������� �����
    kTimerDrawHandFunction,     // ���� ������ ����� ������������ �������, ������������ ���� ��������� ���������
    TypeTimerSize               // ����� ���������� ��������.
} TypeTimer;


void    Timer_PauseOnTime(uint timeMS);
void    Timer_PauseOnTicks(uint numTicks);
void    Timer_Update1ms(void);                  // ������� ���������� �� ���������� ���������� ������� ��� ������ ��������. ����������� ��������� ����� �������� �� 1��.
void    Timer_Update10ms(void);                 // ������� ���������� �� ���������� ���������� ������� ��� ������ ��������. ����������� ���������� ����� �������� �� 10��.

void    Timer_Enable(TypeTimer type, int timeInMS, pFuncVV);
void    Timer_Disable(TypeTimer type);          // ���������� ������
void    Timer_Pause(TypeTimer type);            // ������������� ������. ��������� ����� ����� �������� Timer_Continue()
void    Timer_Continue(TypeTimer type);         // ���������� ������ �������, ����� ����������������� �������� Timer_Pause()
bool    Timer_IsRun(TypeTimer type);            // � ������� ���� ������� ����� ������, �������� �� ������

void    Timer_StartMultiMeasurement(void);      // ��������� ������� ��� ��������� ����� �������� �������.

void    Timer_StartLogging(void);               // ������������� ��������� ����� ������������. ����� ������ Timer_LogPoint �������� ��������� ��������� �� ��� �����.
uint    Timer_LogPointUS(char *name);
uint    Timer_LogPointMS(char *name);

extern volatile uint gTimerMS;                  // �����, ��������� � ������� ������������� �������, � ��������
/**
  * gTimerTics - ���������� �����, ��������� � ������� ���������� ������ ������� Timer_StartMultiMeasurement().
  * � ����� ������� 120.000.000 �����. ������������ ������� �������, ������� ����� ��������� � � ������� - 35 ���.
  * ���������� �����, ��������� � ������� ���������� ������ ������� Timer_StartMultiMeasurement(). �� ����� (1 << 32).
***/
#define gTimerTics (TIM2->CNT)
