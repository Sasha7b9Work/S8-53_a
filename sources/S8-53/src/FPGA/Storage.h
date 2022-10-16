#pragma once
#include "defines.h"
#include "FPGA/FPGA.h"
#include "Settings/SettingsTypes.h"


class Storage
{
public:
    /// �������� ���� ���������� ���������
    static void Clear();
    /// �������� ��������� ������. ��� ���� ����������� ��������� ������� ��������� �������.
    static void AddData(uint8 *data0, uint8 *data1, DataSettings dss);
    /// ���������� ����� ����������� ���������, ������� � ����������, � ������ �� �����������, ��� � ����������.
    static int NumElementsWithSameSettings();
    /// ���������� ����� ����������� ���������, ������� � ����������, � �������� ����������� �������
    static int NumElementsWithCurrentSettings();
    /// ���������� ���������� ���������� ���������
    static int NumElementsInStorage();
    /// �������� ��������� �� ������
    static bool GetDataFromEnd(int fromEnd, DataSettings **ds, uint8 **data0, uint8 **data1);

    static uint8* GetData(Channel chan, int fromEnd);
    /// �������� ���������� ������ �� ���������� ����������.
    static uint8* GetAverageData(Channel chan);
    /// ������� ����� ��������� ��������� � ������.
    static int AllDatas();
    /// �������� �������������� ����� ������� 0 - �����, 1 - ������.
    static uint8* GetLimitation(Channel chan, int direction);                                      

    static int NumberAvailableEntries();
private:

    static void CalculateSums(void);
    /// ���������� ���������� ��������� ������ � ������
    static int MemoryFree();
    /// ���������, ������� ������ ���������, ����� ��������� ��������� � ����������� dp
    static int SizeElem(DataSettings *dp);
    /// ������� ������ (����� ������) ���������
    static void RemoveFirstElement();
    /// ��������� ������
    static void PushData(DataSettings *dp, uint8 *data0, uint8 *data1);
    /// ���������� ��������� �� ���������, ��������� �� elem
    static DataSettings* NextElem(DataSettings *elem);
    /// ���������� ��������� �� ������, ��������� �� indexFromEnd o� ���������� �����������
    static DataSettings* FromEnd(int indexFromEnd);
    /// ���������� true, ���� ��������� ��������� � ��������� elemFromEnd0 � elemFromEnd1 ���������, � false � ���� ������.
    static bool SettingsIsIdentical(int elemFromEnd0, int elemFromEnd1);
    /// ��������� true, ���� ��������� � ����� ���������� ���������
    static bool SettingsIsEquals(DataSettings *dp0, DataSettings *dp1);
    /// ������� �������� ���, ���� � ����
    static void ClearLimitsAndSums();

    static void CalculateLimits(uint8 *data0, uint8 *data1, DataSettings *dss);

    static DataSettings* GetSettingsDataFromEnd(int fromEnd);
    /// �������� ������ ������ chan ��, ������������ ds, � ���� �� ���� ����� ������� dataImportRel. ������������ �������� false ��������, ��� ������ ����� ��������.
    static bool CopyData(DataSettings *ds, Channel chan, uint8 datatImportRel[NumChannels][FPGA_MAX_POINTS]);

    static void PrintElement(DataSettings *dp);
    
    static void CalculateAroundAverage(uint8 *data0, uint8 *data1, DataSettings *dss);
    /// ���������� ��������� ��� ��������� ������.
    static const int SIZE_POOL = (30 * 1024);
    /// ����� �������� ������.
    static uint8 pool[SIZE_POOL];
    /// ����� ������ ������ ��� ��������
    static uint8* beginPool;
    /// ����� ���������� ����� ������ ��� ��������
    static uint8* endPool;
    /// ����� �������� ����� ��������� ����� �������
    static uint  sum[NumChannels][FPGA_MAX_POINTS];
    /// ������������ �������� �������
    static uint8 limitUp[NumChannels][FPGA_MAX_POINTS];
    /// ����������� �������� �������
    static uint8 limitDown[NumChannels][FPGA_MAX_POINTS];
    /// ��������� �� ������ ���������� ������
    static DataSettings* firstElem;
    /// ��������� �� ��������� ���������� ������
    static DataSettings* lastElem;
    /// ����� ������ ���������
    static int allData;
    /// � ���� �������� �������� ���������� ��������, ������������ �� ���������������� ���������.
    static float aveData0[FPGA_MAX_POINTS];

    static float aveData1[FPGA_MAX_POINTS];
    /// ���� true, �� ����� ����� ����������, � ����� ��������� ������ ��������
    static bool newSumCalculated[NumChannels];

};
