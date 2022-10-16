#include "defines.h"
#include "Settings/Settings.h"
#include "Settings/SettingsTypes.h"
#include "PageMemory.h"
#include "FPGA/FPGA.h"
#include "Log.h"
#include "Display/Display.h"
#include "Utils/GlobalFunctions.h"
#include "Utils/Math.h"
#include "Hardware/FSMC.h"
#include "Display/Grid.h"


/** @addtogroup Menu
 *  @{
 *  @addtogroup PageTime
 *  @{
 */


extern const Page pTime;


extern const Choice mcSample;           // ��������� - �������
static bool  IsActive_Sample();
extern const Choice mcPeakDet;          // ��������� - ��� ���
static bool  IsActive_PeakDet();
void        OnChanged_PeakDet(bool active);
extern const Choice mcTPos;             // ��������� - To
void        OnChanged_TPos(bool active);
extern const Choice mcSelfRecorder;     // ��������� - ���������
static bool  IsActive_SelfRecorder();
extern const Choice mcDivRole;          // ��������� - �-��� ��/���


extern Page mainPage;


// ��������� //////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsTime =
{
    (void*)&mcSample,       // ��������� - �������
    (void*)&mcPeakDet,      // ��������� - ��� ���
    (void*)&mcTPos,         // ��������� - To
    (void*)&mcSelfRecorder, // ��������� - ���������
    (void*)&mcDivRole       // ��������� - �-��� ��/���    
};

const Page pTime            ///< ���������
(
    &mainPage, 0,
    "���������", "SCAN",
    "�������� ��������� ��������.",
    "Contains scan settings.",
    Page_Time, &itemsTime
);

// ��������� - ������� -------------------------------------------------------------------------------------------------------------------------------
static const Choice mcSample =
{
    Item_Choice, &pTime, IsActive_Sample,
    {
        "�������", "Sampling"
        ,
        "\"��������\" - \n"
        "\"�������������\" -"
        ,
        "\"Real\" - \n"
        "\"Equals\" - "
    },
    {
        {"�������� �����",  "Real"},
        {"�������������",   "Equals"}
    },
    (int8*)&SAMPLE_TYPE
};

static bool IsActive_Sample(void)
{
    return sTime_RandomizeModeEnabled();
}

// ��������� - ��� ��� -------------------------------------------------------------------------------------------------------------------------------
static const Choice mcPeakDet =
{
    Item_Choice, &pTime, IsActive_PeakDet,
    {
        "��� ���", "Pic deat",
        "��������/��������� ������� ��������.",
        "Turns on/off peak detector."
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
        /* , {"�������",   "Average"} */
    },
    (int8*)&PEAKDET, OnChanged_PeakDet
};

static bool IsActive_PeakDet(void)
{
    return (SET_TBASE >= MIN_TBASE_PEC_DEAT);
}

void OnChanged_PeakDet(bool active)
{
    if (active)
    {
        FPGA::SetPeackDetMode(PEAKDET);
        FPGA::SetTBase(SET_TBASE);
        if (PEAKDET_IS_DISABLE)
        {
            int8 shift[2][3] =
            {
                {0, SET_BALANCE_ADC_A, BALANCE_ADC_A},
                {0, SET_BALANCE_ADC_B, BALANCE_ADC_B}
            };

            FPGA::WriteToHardware(WR_ADD_RSHIFT_DAC1, (uint8)shift[0][BALANCE_ADC_TYPE], false);
            FPGA::WriteToHardware(WR_ADD_RSHIFT_DAC2, (uint8)shift[1][BALANCE_ADC_TYPE], false);
        }
        else
        {
            FPGA::WriteToHardware(WR_ADD_RSHIFT_DAC1, 3, false);     // ������-�� ��� ������� ��������� �������� ����������. ��� ��� � ������������.
            FPGA::WriteToHardware(WR_ADD_RSHIFT_DAC2, 3, false);
        }
        if (PEAKDET_IS_DISABLE)
        {
            int centerX = SHIFT_IN_MEMORY + Grid::Width() / 2;
            SHIFT_IN_MEMORY = centerX * 2 - Grid::Width() / 2;
            ENUM_POINTS = set.time.oldNumPoints;
            ChangeC_Memory_NumPoints(true);
        }
        else if (PEAKDET_IS_ENABLE)
        {
            int centerX = SHIFT_IN_MEMORY + Grid::Width() / 2;
            LIMITATION(SHIFT_IN_MEMORY, centerX / 2 - Grid::Width() / 2, 0, sMemory_GetNumPoints(false) - Grid::Width());
            ChangeC_Memory_NumPoints(true);
        }
    }
    else
    {
        Display::ShowWarningBad(TooSmallSweepForPeakDet);
    }
}

// ��������� - To ------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcTPos =
{
    Item_Choice, &pTime, 0,
    {
        "\x7b", "\x7b",
        "����� ����� �������� �������� �������� �� ������� � ������ - ����� ����, �����, ������ ����.",
        "Sets the anchor point nuleovgo time offset to the screen - the left edge, center, right edge."
    },
    {
        {"����",    "Left"},
        {"�����",   "Center"},
        {"�����",   "Right"}
    },
    (int8*)&SET_TPOS, OnChanged_TPos
};

void OnChanged_TPos(bool active)
{
    ChangeC_Memory_NumPoints(active);
    FPGA::SetTShift(TSHIFT);
}

// ��������� - ��������� -----------------------------------------------------------------------------------------------------------------------------
static const Choice mcSelfRecorder =
{
    Item_Choice, &pTime, IsActive_SelfRecorder,
    {
        "���������", "Self-Recorder",
        "��������/��������� ����� ���������. ���� ����� �������� �� ��������� 20��/��� � ����� ���������.",
        "Turn on/off the recorder. This mode is available for scanning 20ms/div and slower."
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&SET_SELFRECORDER
};

static bool IsActive_SelfRecorder(void)
{
    return SET_TBASE >= MIN_TBASE_P2P;
}

// ��������� - �-��� ��/��� --------------------------------------------------------------------------------------------------------------------------
static const Choice mcDivRole =
{
    Item_Choice, &pTime, 0,
    {
        "�-��� ��/���", "Func Time/DIV"
        ,
        "����� ������� ��� ����� �����/���: � ������ ����� ���������� (����/���� � ��������� ����):\n"
        "1. \"�����\" - ��������� �������� �� �������.\n"
        "2. \"������\" - ����������� �� ������."
        ,
        "Sets the function to handle TIME/DIV: mode of collecting information (START/STOP to start position):\n"
        "1. \"Time\" - change the time shift.\n"
        "2. \"Memory\" - moving from memory."
    },
    {
        {"�����",   "Time"},
        {"������",  "Memory"}
    },
    (int8*)&TIME_DIV_XPOS
};


/** @}  @}
 */
