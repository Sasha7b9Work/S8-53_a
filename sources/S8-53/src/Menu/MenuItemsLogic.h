#pragma once
#include "defines.h"
#include "MenuItems.h"


void    Governor_StartChange(Governor *governor, int detla);    // ��������� �������� �������� ���������� ��� ���������� �������� ���� ���� Governor (� ����������� �� ����� delta)
float   Governor_Step(Governor *governor);                      // ������������ ��������� ���� ��������.
void    Governor_ChangeValue(Governor *governor, int delta);    // �������� �������� � ������� ������� ��� ��������� ��������
int16   Governor_NextValue(Governor *governor);                 // ���������� ��������� ������� ��������, ������� ����� ������� governor.
int16   Governor_PrevValue(Governor *governor);                 // ���������� ��������� ������� ��������, ������� ����� ������� governor.
void    Governor_NextPosition(Governor *governor);              // ��� �������� �������� ������������ ������ �� ��������� �������
int     Governor_NumDigits(Governor *governor);                 // ���������� ����� ��������� � ���� ��� ����� �������� governor. ������� �� ������������� ��������, ������� ����� ��������� governor.

void    IPaddress_NextPosition(IPaddress *ip);                  // ��� �������� �������� ������������ ������ �� ��������� �������
void    IPaddress_ChangeValue(IPaddress *ip, int delta);        // �������� �������� � ������� ������� ��� �������� ��������
void    IPaddress_GetNumPosIPvalue(int *numIP, int *selPos);        // ���������� ����� �������� ����� (4 - ����� �����) � ����� ������� ������� � �����.

void    MACaddress_ChangeValue(MACaddress *mac, int delta);

void    ItemTime_SetOpened(Time *time);
void    ItemTime_SetNewTime(Time *time);
void    ItemTime_SelectNextPosition(Time *time);
void    ItemTime_IncCurrentPosition(Time *time);
void    ItemTime_DecCurrentPosition(Time *time);

void    GovernorColor_ChangeValue(GovernorColor *governor, int delta);  // �������� ������� ����� � governor

extern int8 gCurDigit;
