#pragma once
#include "defines.h"
#include "FPGA_Types.h"
#include "Panel/Controls.h"
#include "Settings/SettingsTrig.h"
#include "Settings/SettingsService.h"


class FPGA
{
public:

    static void Init();
    /// ���������� ���������� ����������� �������� � �������.
    static void SetNumSignalsInSec(int numSigInSec);

    static void Update();
    /// ������ � ������� ���� ������ ��������.
    static void WriteToHardware				        
                            (uint8 *address,    ///< ����� ��������.
                                uint8 value,    ///< ������������ ��������.
                                bool restart    ///< true ��������, ��� ����� ������ ����� �������� ����� ���������, ���� �� ����� ������ �� ��������� � ������ �����.
                            );

    static StateWorkFPGA FPGA_CurrentStateWork();
    /// ��������� ���� ����� ����������.
    static void OnPressStartStop();
    /// ������ �������� ����� ����������.
    static void Start();
    /// ��������� ������� ����� ����������.
    static void Stop(bool pause);
    /// ���������� true, ���� ������ ��������� �� � �������� ����� ����������.
    static bool IsRunning();
    /// ��������� ������� ���������. ����� �� ����� ������������ �������� FPGA_RestoreState().
    static void SaveState();
    /// ��������������� ���������, ����� ���������� �������� FPGA_SaveState().
    static void RestoreState();
    /// �������� �������� �������.
    static float GetFreq();
    /// ������� ������. ����� ��� ������ �������������, ��� ���������� ������� ����� �� �������� ���������������.
    static void ClearData();
    /// ���������� �������������� ��������. ����� ��� ���������� ����������� ����� � ������ �������������.
    static void SetAdditionShift(int shift);
    /// ���������� true,���� ��� ����� �������� � ������ �������������.
    static bool AllPointsRandomizer();
    /// ���������� ���������� ���������, �� ������� ����� �������������� ������ � ������ �������������.
    static void SetNumberMeasuresForGates(int number);
    /// ������������� ��������� �������������.
    static void SwitchingTrig();
    /// ��������� ������� ������ �������.
    static void StartAutoFind();
    /// ���������� ��������� ����� ����� ��������� ����� - ����� ��������� ������ ������������� �� ��������� �����
    static void TemporaryPause();

    static void FillDataPointer(DataSettings *dp);
    /// ����� � ���������� ������� ������������� �� ���������� ���������� �������
    static void FindAndSetTrigLevel();
    /// ���������� ����� ������ �� �����.
    static void SetModeCouple(Channel chan, ModeCouple modeCoupe);
    /// ��������/��������� ������ �� ����� ������.
    static void EnableChannelFiltr(Channel chan, bool enable);
    /// ���������� ������� �� ����������.
    static void SetRange(Channel chan, Range range);
    /// ��������� ������� �� ����������.
    static bool RangeIncrease(Channel chan);
    /// ��������� ������� �� ����������.
    static bool RangeDecrease(Channel chan);
    /// ���������� ������� �� �������.
    static void SetTBase(TBase tBase);
    /// ��������� ������� �� �������.
    static void TBaseDecrease();
    /// ��������� ������� �� �������.
    static void TBaseIncrease();
    /// ���������� ������������� �������� �� ����������.
    static void SetRShift(Channel chan, int16 rShift);
    /// ���������� ������������� �������� �� �������.
    static void SetTShift(int tShift);
    /// ���������� ���������� �������� �� ������� ��� ������ �������������. � ������ �������� ��� �������� ������ ���� ������.
    static void SetDeltaTShift(int16 shift);
    /// ��������/��������� ����� �������� ���������.
    static void SetPeackDetMode(PeackDetMode peackDetMode);
    /// ��������/��������� ����������.
    static void SetCalibratorMode(CalibratorMode calibratorMode);
    /// ��������� � ������� ������������ ���������� �������.
    static void LoadKoeffCalibration(Channel chan);
    /// ���������� ������������� ������� �������������.
    static void SetTrigLev(TrigSource chan, int16 trigLev);
    /// ���������� �������� �������������.
    static void SetTrigSource(TrigSource trigSource);
    /// ���������� ���������� �������������.
    static void SetTrigPolarity(TrigPolarity polarity);
    /// ���������� ����� ����� �������������.
    static void SetTrigInput(TrigInput trigInput);
    /// ���������� ������������� �������� �� ������� � ��������� ����, ��������� ��� ������ �� �����.
    static const char* GetTShiftString(int16 tShiftRel, char buffer[20]);
    /// ������ ������� ����������.
    static void ProcedureCalibration();

    static StateWorkFPGA CurrentStateWork();

private:
    /// ��������� ��������� � ���������� ����� �� ���������� ��������� SSettings.
    static void LoadSettings();
    /// �������� ����������� �������� � ���������� �����.
    static void LoadTBase();
    /// �������� �������� �� ������� � ���������� �����.
    static void LoadTShift();
    /// �������� �������� �� ���������� � ���������� �����.
    static void LoadRange(Channel chan);
    /// �������� �������� �� ���������� � ���������� �����.
    static void LoadRShift(Channel chan);
    /// �������� ������ ������������� � ���������� �����.
    static void LoadTrigLev();                                  
    /// ������� ���������� ������������� � ���������� �����.
    static void LoadTrigPolarity();
    /// ��������� ��� ��������� ���������� ������� � ������������� � ���������� �����.
    static void SetAttribChannelsAndTrig(TypeWriteAnalog type);
    /// ��������� ������� WR_UPR (������� �������� � ����������).
    static void LoadRegUPR();

    static void WriteToAnalog(TypeWriteAnalog type, uint data);

    static void WriteToDAC(TypeWriteDAC type, uint16 data);
    /// ��������� ������.
    static void DataRead(
                        bool necessaryShift,    ///< ������� ����, ��� ������ ����� �������.
                        bool saveToStorage      ///< ����� � ������ ������������� ��� ��������, ��� ���� ��������� ���������
                        );

    static bool CalculateGate(uint16 rand, uint16 *min, uint16 *max);

    static int CalculateShift();
    /// ����������� ������.
    static void InverseDataIsNecessary(Channel chan, uint8 *data);

    static void AutoFind();

    static uint8 CalculateMinWithout0(uint8 buffer[100]);

    static uint8 CalculateMaxWithout255(uint8 buffer[100]);

    static bool ProcessingData();

    static void ReadRandomizeMode();

    static void ReadRealMode(bool necessaryShift);

    static Range AccurateFindRange(Channel chan);

    static TBase FindTBase(Channel chan);

    static TBase AccurateFindTBase(Channel chan);

    static bool FindWave(Channel chan);
};
