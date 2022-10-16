#include "defines.h"
#include "Definition.h"
#include "FlashDrive/FlashDrive.h"
#include "Settings/SettingsTypes.h"
#include "Settings/Settings.h"
#include "Display/Display.h"
#include "Display/Grid.h"
#include "Display/Symbols.h"
#include "Utils/GlobalFunctions.h"
#include "FPGA/FPGA.h"
#include "FPGA/FPGA_Types.h"
#include "Hardware/FSMC.h"
#include "Hardware/Sound.h"
#include "Hardware/EPROM.h"
#include "Menu/Menu.h"
#include "Menu/Pages/PageDebug.h"
#include "Log.h"


/** @addtogroup Menu
 *  @{
 *  @defgroup PageDebug
 *  @{
 */

extern const Page pDebug;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const Choice     mcStats;                            ///< ������� - ����������
extern const Page       mpConsole;                          ///< ������� - �������
extern const Governor   mgConsole_NumStrings;               ///< ������� - ������� - ����� �����
extern const Choice     mcConsole_SizeFont;                 ///< ������� - ������� - ������ ������
extern const Page       mpConsole_Registers;                ///< ������� - ������� - ��������
extern const Choice     mcConsole_Registers_ShowAll;        ///< ������� - ������� - �������� - ���������� ���
extern const Choice     mcConsole_Registers_RD_FL;          ///< ������� - ������� - �������� - RD_FL
static bool      IsActive_Console_Registers_RD_FL();
extern const Choice     mcConsole_Registers_RShiftA;        ///< ������� - ������� - �������� - U ��. 1�
extern const Choice     mcConsole_Registers_RShiftB;        ///< ������� - ������� - �������� - U ��. 2�
extern const Choice     mcConsole_Registers_TrigLev;        ///< ������� - ������� - �������� - U �����.
extern const Choice     mcConsole_Registers_RangeA;         ///< ������� - ������� - �������� - �����/��� 1
extern const Choice     mcConsole_Registers_RangeB;         ///< ������� - ������� - �������� - �����/��� 2
extern const Choice     mcConsole_Registers_TrigParam;      ///< ������� - ������� - �������� - �����. �����.
extern const Choice     mcConsole_Registers_ChanParamA;     ///< ������� - ������� - �������� - �����. ���. 1
extern const Choice     mcConsole_Registers_ChanParamB;     ///< ������� - ������� - �������� - �����. ���. 2
extern const Choice     mcConsole_Registers_TBase;          ///< ������� - ������� - �������� - �����/���
extern const Choice     mcConsole_Registers_tShift;         ///< ������� - ������� - �������� - � ��.
extern const Page       mpADC;                              ///< ������� - ���
extern const Page       mpADC_Balance;                      ///< ������� - ��� - ������
extern const Choice     mcADC_Balance_Mode;                 ///< ������� - ��� - ������ - �����
static void     OnChanged_ADC_Balance_Mode(bool active);
static void          Draw_ADC_Balance_Mode(int x, int y);
extern const Governor   mgADC_Balance_ShiftA;               ///< ������� - ��� - ������ - �������� 1
static bool      IsActive_ADC_Balance_Shift();
static void     OnChanged_ADC_Balance_ShiftA();
extern const Governor   mgADC_Balance_ShiftB;               ///< ������� - ��� - ������ - �������� 2
static void     OnChanged_ADC_Balance_ShiftB();
extern const Page       mpADC_Stretch;                      ///< ������� - ��� - ��������
extern const Choice     mcADC_Stretch_Mode;                 ///< ������� - ��� - �������� - �����
static void     OnChanged_ADC_Stretch_Mode(bool active);
void LoadStretchADC(Channel chan);
extern const Governor   mgADC_Stretch_ADC_A;                ///< ������� - ��� - �������� - �����. 1�
static bool      IsActive_ADC_Stretch_ADC();
static void     OnChanged_ADC_Stretch_ADC_A();
extern const Governor   mgADC_Stretch_ADC_B;                ///< ������� - ��� - �������� - �����. 2�
static void     OnChanged_ADC_Stretch_ADC_B();
extern const Page       mpADC_AltRShift;                    ///< ������� - ��� - ��� ����
extern const Button     mbADC_AltRShift_Reset;              ///< ������� - ��� - ��� ���� - �����
static void       OnPress_ADC_AltRShift_Reset();
extern const Governor   mbADC_AltRShift_2mV_DC_A;           ///< ������� - ��� - ��� ���� - �� 1� 2�� ����
static void     OnChanged_ADC_AltRShift_A();
extern const Governor   mbADC_AltRShift_2mV_DC_B;           ///< ������� - ��� - ��� ���� - �� 2� 2�� ����
static void     OnChanged_ADC_AltRShift_B();
extern const Governor   mbADC_AltRShift_5mV_DC_A;           ///< ������� - ��� - ��� ���� - �� 1� 5�� ����
extern const Governor   mbADC_AltRShift_5mV_DC_B;           ///< ������� - ��� - ��� ���� - �� 2� 5�� ����
extern const Governor   mbADC_AltRShift_10mV_DC_A;          ///< ������� - ��� - ��� ���� - �� 1� 10�� ����
extern const Governor   mbADC_AltRShift_10mV_DC_B;          ///< ������� - ��� - ��� ���� - �� 2� 10�� ����
extern const Page       mpRandomizer;                       ///< ������� - ����-���
extern const Governor   mgRandomizer_SamplesForGates;       ///< ������� - ����-��� - ���-�/������
static void     OnChanged_Randomizer_SamplesForGates();
extern const Governor   mgRandomizer_AltTShift0;            ///< ������� - ����-��� - tShift ���.
static void     OnChanged_Randomizer_AltTShift0();
extern const Governor   mgRandomizer_Average;               ///< ������� - ����-��� - ������.
extern const Choice     mcSizeSettings;                     ///< ������� - ������ ��������
static void        OnDraw_SizeSettings(int x, int y);
extern const Button     mbSaveFirmware;                     ///< ������� - ����. ��������
static bool      IsActive_SaveFirmware();
static void       OnPress_SaveFirmware();
extern const       Page ppSerialNumber;                     ///< ������� - �/�
static void       OnPress_SerialNumber();
static void Draw_EnterSerialNumber();
static void      OnRegSet_SerialNumber(int);
extern const SmallButton bSerialNumber_Exit;                ///< ������� - �/� - �����
static void       OnPress_SerialNumber_Exit();
extern const SmallButton bSerialNumber_Change;              ///< ������� - �/� - �������
static void       OnPress_SerialNumber_Change();
static void          Draw_SerialNumber_Change(int, int);
extern const  SmallButton bSerialNumber_Save;               ///< ������� - �/� - ���������
static void        OnPress_SerialNumber_Save();
static void           Draw_SerialNumber_Save(int, int);
extern const       Button bEraseData;                       ///< ������� - ������� ������
static void       OnPress_EraseData();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// � ���� ��������� ����� ��������� ������ ��������� ������ ��� �������� �������� ppSerialNumer
typedef struct
{
    int number;     ///< ��������������, ���������� �����.
    int year;       ///< ��������������, ���.
    int curDigt;    ///< ��������������, ������� (0) ��� ����� (1) ��������� ����� ���������.
} StructForSN;


extern Page mainPage;

void *PageDebug::SerialNumber::GetPointer()
{
    return (void *)&ppSerialNumber;
}


// ������� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsDebug =
{
    (void *)&mcStats,            // ������� - ����������
    (void *)&mpConsole,          // ������� - �������
    (void *)&mpADC,              // ������� - ���
    (void *)&mpRandomizer,       // ������� - ����-���
    (void *)&mcSizeSettings,     // ������� - ������ ��������
    (void *)&mbSaveFirmware,     // ������� - ����. ��������
    (void *)&bEraseData          // ������� - ������� ������
    //(void*)&ppSerialNumber     // ������� - �/�
    //(void*)&mspDebugInformation
};

const Page pDebug
(
    &mainPage, 0,
    "�������", "DEBUG",
    "",
    "",
    Page_Debug, &itemsDebug
);

// ������� - ���������� ------------------------------------------------------------------------------------------------------------------------------
static const Choice mcStats =
{
    Item_Choice, &pDebug, 0,
    {
        "����������", "Statistics",
        "����������/�� ���������� �����/����, ������ � �������, ���������� �������� � ���������� ����������� � ������/���������� ����������� � ������ ��������",
        "To show/not to show a time/shot, frames per second, quantity of signals with the last settings in memory/quantity of the signals kept in memory"
    },
    {
        "�� ����������",    "Hide",
        "����������",       "Show"
    },
    (int8*)&SHOW_STATS
};


// ������� - ������� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsConsole =
{
    (void*)&mgConsole_NumStrings,   // ������� - ������� - ����� �����
    (void*)&mcConsole_SizeFont,     // ������� - ������� - ������ ������
    (void*)&mpConsole_Registers     // ������� - ������� - ��������
};

static const Page mpConsole
(
    &pDebug, 0,
    "�������", "CONSOLE",
    "",
    "",
    Page_DebugConsole, &itemsConsole
);

// ������� - ������� - ����� ����� -------------------------------------------------------------------------------------------------------------------
static const Governor mgConsole_NumStrings
(
    &mpConsole, 0,
    "����� �����", "Number strings",
    "",
    "",
    &NUM_STRINGS,  0, 33
);

// ������� - ������� - ������ ������ -----------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_SizeFont =
{
    Item_Choice, &mpConsole, 0,
    {
        "������ ������", "Size font",
        "",
        ""
    },
    {
        "5",    "5",
        "8",    "8"
    },
    (int8*)&SIZE_FONT_CONSOLE
};


// ������� - ������� - �������� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsConsole_Registers =
{
    (void*)&mcConsole_Registers_ShowAll,    // ������� - ������� - �������� - ���������� ���
    (void*)&mcConsole_Registers_RD_FL,      // ������� - ������� - �������� - RD_FL
    (void*)&mcConsole_Registers_RShiftA,    // ������� - ������� - �������� - U ��. 1�
    (void*)&mcConsole_Registers_RShiftB,    // ������� - ������� - �������� - U ��. 2�
    (void*)&mcConsole_Registers_TrigLev,    // ������� - ������� - �������� - U �����.
    (void*)&mcConsole_Registers_RangeA,     // ������� - ������� - �������� - �����/��� 1
    (void*)&mcConsole_Registers_RangeB,     // ������� - ������� - �������� - �����/��� 2
    (void*)&mcConsole_Registers_TrigParam,  // ������� - ������� - �������� - �����. �����.
    (void*)&mcConsole_Registers_ChanParamA, // ������� - ������� - �������� - �����. ���. 1
    (void*)&mcConsole_Registers_ChanParamB, // ������� - ������� - �������� - �����. ���. 2
    (void*)&mcConsole_Registers_TBase,      // ������� - ������� - �������� - �����/���
    (void*)&mcConsole_Registers_tShift      // ������� - ������� - �������� - � ��.
};

static const Page mpConsole_Registers
(
    &mpConsole, 0,
    "��������", "REGISTERS",
    "",
    "",
    Page_DebugShowRegisters, &itemsConsole_Registers
);

// ������� - ������� - �������� - ���������� ��� -----------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_ShowAll =
{
    Item_Choice, &mpConsole_Registers, 0,
    {
        "���������� ���", "Show all",
        "���������� ��� ��������, ���������� � ��������",
        "To show all values transferred in registers"
    },
    {
        "���",  "No",
        "��",   "Yes"
    },
    (int8*)&IS_SHOW_REGISTERS_ALL
};

// ������� - ������� - �������� - RD_FL --------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_RD_FL =
{
    Item_Choice, &mpConsole_Registers, IsActive_Console_Registers_RD_FL,
    {
        "RD_FL", "RD_FL",
        "",
        ""
    },
    {
        DISABLE_RU, DISABLE_EN,
        ENABLE_RU,  ENABLE_EN
    },
    (int8*)&set.debug.showRegisters.flag
};

static bool IsActive_Console_Registers_RD_FL(void)
{
    return !IS_SHOW_REGISTERS_ALL;
}

// ������� - ������� - �������� - U ��. 1� -----------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_RShiftA =
{
    Item_Choice, &mpConsole_Registers, IsActive_Console_Registers_RD_FL,
    {
        "U ��. 1�", "U shift 1ch",
        "",
        ""
    },
    {
        DISABLE_RU, DISABLE_EN,
        ENABLE_RU,  ENABLE_EN
    },
    (int8*)&set.debug.showRegisters.rShiftA
};

// ������� - ������� - �������� - U ��. 2� -----------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_RShiftB =
{
    Item_Choice, &mpConsole_Registers, IsActive_Console_Registers_RD_FL,
    {
        "U ��. 2�", "U shift 2ch",
        "",
        ""
    },
    {
        DISABLE_RU, DISABLE_EN,
        ENABLE_RU,  ENABLE_EN
    },
    (int8*)&set.debug.showRegisters.rShiftB
};

// ������� - ������� - �������� - U �����. -----------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_TrigLev =
{
    Item_Choice, &mpConsole_Registers, IsActive_Console_Registers_RD_FL,
    {
        "U �����.", "U trig.",
        "",
        ""
    },
    {
        DISABLE_RU, DISABLE_EN,
        ENABLE_RU,  ENABLE_EN
    },
    (int8*)&set.debug.showRegisters.trigLev
};

// ������� - ������� - �������� - �����/��� 1 --------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_RangeA =
{
    Item_Choice, &mpConsole_Registers, IsActive_Console_Registers_RD_FL,
    {
        "�����/��� 1", "Range 1",
        "",
        ""
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&set.debug.showRegisters.range[0]
};

// ������� - ������� - �������� - �����/��� 2 --------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_RangeB =
{
    Item_Choice, &mpConsole_Registers, IsActive_Console_Registers_RD_FL,
    {
        "�����/��� 2", "Range 2",
        "",
        ""
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&set.debug.showRegisters.range[1]
};

// ������� - ������� - �������� - �����. �����. ------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_TrigParam =
{
    Item_Choice, &mpConsole_Registers, IsActive_Console_Registers_RD_FL,
    {
        "�����. �����.", "Trig param",
        "",
        ""
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&set.debug.showRegisters.trigParam
};

// ������� - ������� - �������� - �����. ���. 1 ------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_ChanParamA =
{
    Item_Choice, &mpConsole_Registers, IsActive_Console_Registers_RD_FL,
    {
        "�����. ���. 1",  "Chan 1 param",
        "",
        ""
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&set.debug.showRegisters.chanParam[0]
};

// ������� - ������� - �������� - �����. ���. 2 ------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_ChanParamB =
{
    Item_Choice, &mpConsole_Registers, IsActive_Console_Registers_RD_FL,
    {
        "�����. ���. 2", "Chan 2 param",
        "",
        ""
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&set.debug.showRegisters.chanParam[1]
};

// ������� - ������� - �������� - �����/��� ----------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_TBase =
{
    Item_Choice, &mpConsole_Registers, IsActive_Console_Registers_RD_FL,
    {
        "�����/���", "TBase",
        "",
        ""
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&set.debug.showRegisters.tBase
};

// ������� - ������� - �������� - � ��. --------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_tShift =
{
    Item_Choice, &mpConsole_Registers, IsActive_Console_Registers_RD_FL,
    {
        "� ��.", "tShift",
        "",
        ""
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&set.debug.showRegisters.tShift
};


// ������� - ��� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsADC =
{
    (void*)&mpADC_Balance,      // ������� - ��� - ������
    (void*)&mpADC_Stretch,      // ������� - ��� - ��������
    (void*)&mpADC_AltRShift     // ������� - ��� - ��� ����
    //, (void*)&mspDebugADCaltShift
};

static const Page mpADC
(
    &pDebug, 0,
    "���", "ADC",
    "",
    "",
    Page_DebugADC, &itemsADC
);

// ������� - ��� - ������ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsADC_Balance =
{
    (void*)&mcADC_Balance_Mode,     // ������� - ��� - ������ - �����
    (void*)&mgADC_Balance_ShiftA,   // ������� - ��� - ������ - �������� 1
    (void*)&mgADC_Balance_ShiftB    // ������� - ��� - ������ - �������� 2
};

static const Page mpADC_Balance
(
    &mpADC, 0,
    "������", "BALANCE",
    "",
    "",
    Page_DebugADCbalance, &itemsADC_Balance
);

// ������� - ��� - ������ - ����� --------------------------------------------------------------------------------------------------------------------
static const Choice mcADC_Balance_Mode =
{
    Item_Choice, &mpADC_Balance, 0,
    {
        "�����", "Mode",
        "",
        ""
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {"��������",    "Real"},
        {"������",      "Manual"}
    },
    (int8*)&BALANCE_ADC_TYPE, OnChanged_ADC_Balance_Mode, Draw_ADC_Balance_Mode
};

static int16 shiftADCA;
static int16 shiftADCB;

static void OnChanged_ADC_Balance_Mode(bool active)
{
    Draw_ADC_Balance_Mode(0, 0);

    FPGA::WriteToHardware(WR_ADD_RSHIFT_DAC1, (uint8)shiftADCA, false);
    FPGA::WriteToHardware(WR_ADD_RSHIFT_DAC2, (uint8)shiftADCB, false);
}

static void Draw_ADC_Balance_Mode(int x, int y)
{
    int8 shift[2][3] =
    {
        {0, SET_BALANCE_ADC_A, BALANCE_ADC_A},
        {0, SET_BALANCE_ADC_B, BALANCE_ADC_B}
    };

    shiftADCA = shift[0][BALANCE_ADC_TYPE];
    shiftADCB = shift[1][BALANCE_ADC_TYPE];
}

// ������� - ��� - ������ - �������� 1 ---------------------------------------------------------------------------------------------------------------
static const Governor mgADC_Balance_ShiftA
(
    &mpADC_Balance, IsActive_ADC_Balance_Shift,
    "�������� 1", "Offset 1",
    "",
    "",
    &shiftADCA, -125, 125, OnChanged_ADC_Balance_ShiftA
);

static void OnChanged_ADC_Balance_ShiftA(void)
{
    BALANCE_ADC_A = shiftADCA;
    FPGA::WriteToHardware(WR_ADD_RSHIFT_DAC1, (uint8)BALANCE_ADC_A, false);
}

static bool IsActive_ADC_Balance_Shift(void)
{
    return BALANCE_ADC_TYPE_IS_HAND;
}

// ������� - ��� - ������ - �������� 2----------------------------------------------------------------------------------------------------------------
static const Governor mgADC_Balance_ShiftB
(
    &mpADC_Balance, IsActive_ADC_Balance_Shift,
    "�������� 2", "Offset 2",
    "",
    "",
    &shiftADCB, -125, 125, OnChanged_ADC_Balance_ShiftB
);

static void OnChanged_ADC_Balance_ShiftB(void)
{
    BALANCE_ADC_B = shiftADCB;
    FPGA::WriteToHardware(WR_ADD_RSHIFT_DAC2, (uint8)BALANCE_ADC_B, false);
}


// ������� - ��� - �������� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsADC_Stretch =
{
    (void*)&mcADC_Stretch_Mode,     // ������� - ��� - �������� - �����
    (void*)&mgADC_Stretch_ADC_A,    // ������� - ��� - �������� - �����. 1�
    (void*)&mgADC_Stretch_ADC_B     // ������� - ��� - �������� - �����. 2�    
};

static const Page mpADC_Stretch
(
    &mpADC, 0,
    "��������", "STRETCH",
    "",
    "",
    Page_DebugADCstretch, &itemsADC_Stretch
);

// ������� - ��� - �������� - ����� ------------------------------------------------------------------------------------------------------------------
static const Choice mcADC_Stretch_Mode =
{
    Item_Choice, &mpADC_Stretch, 0,
    {
        "�����", "Mode",
        "",
        ""
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {"��������",    "Real"},
        {"������",      "Manual"}
    },
    (int8*)&DEBUG_STRETCH_ADC_TYPE, OnChanged_ADC_Stretch_Mode
};

static void OnChanged_ADC_Stretch_Mode(bool active)
{
    if(active)
    {
        LoadStretchADC(A);
        LoadStretchADC(B);
    }
}

void LoadStretchADC(Channel chan)
{
    if(DEBUG_STRETCH_ADC_TYPE_IS_DISABLED)
    {
        FPGA::WriteToHardware(chan == A ? WR_CAL_A : WR_CAL_B, 0x80, true);
    }
    else if(DEBUG_STRETCH_ADC_TYPE_IS_HAND)
    {
        FPGA::WriteToHardware(chan == A ? WR_CAL_A : WR_CAL_B, (uint8)DEBUG_STRETCH_ADC(chan), true);
    }
    else if(DEBUG_STRETCH_ADC_TYPE_IS_SETTINGS)
    {
        FPGA::LoadKoeffCalibration(chan);
    }
}

// ������� - ��� - �������� - �����. 1� --------------------------------------------------------------------------------------------------------------
static const Governor mgADC_Stretch_ADC_A
(
    &mpADC_Stretch, IsActive_ADC_Stretch_ADC, 
    "�����. 1�", "Koeff. 1ch",
    "",
    "",
    &DEBUG_STRETCH_ADC_A, 0, 255, OnChanged_ADC_Stretch_ADC_A
);

static bool IsActive_ADC_Stretch_ADC(void)
{
    return DEBUG_STRETCH_ADC_TYPE_IS_HAND;
}

static void OnChanged_ADC_Stretch_ADC_A(void)
{
    FPGA::WriteToHardware(WR_CAL_A, (uint8)DEBUG_STRETCH_ADC_A, true);
}


// ������� - ��� - �������� - �����. 2� --------------------------------------------------------------------------------------------------------------
static const Governor mgADC_Stretch_ADC_B
(
    &mpADC_Stretch, IsActive_ADC_Stretch_ADC,
    "�����. 2�", "Koeff. 2ch",
    "",
    "",
    &DEBUG_STRETCH_ADC_B, 0, 255, OnChanged_ADC_Stretch_ADC_B
);

static void OnChanged_ADC_Stretch_ADC_B(void)
{
    FPGA::WriteToHardware(WR_CAL_B, (uint8)DEBUG_STRETCH_ADC_B, true);
}

// ������� - ��� - ��� ���� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsADC_AltRShift =
{
    (void*)&mbADC_AltRShift_Reset,          // ������� - ��� - ��� ���� - �����
    (void*)&mbADC_AltRShift_2mV_DC_A,       // ������� - ��� - ��� ���� - �� 1� 2�� ����
    (void*)&mbADC_AltRShift_2mV_DC_B,       // ������� - ��� - ��� ���� - �� 2� 2�� ����
    (void*)&mbADC_AltRShift_5mV_DC_A,       // ������� - ��� - ��� ���� - �� 1� 5�� ����
    (void*)&mbADC_AltRShift_5mV_DC_B,       // ������� - ��� - ��� ���� - �� 2� 5�� ����
    (void*)&mbADC_AltRShift_10mV_DC_A,      // ������� - ��� - ��� ���� - �� 1� 10�� ����
    (void*)&mbADC_AltRShift_10mV_DC_B       // ������� - ��� - ��� ���� - �� 2� 10�� ����    
};

static const Page mpADC_AltRShift
(
    &mpADC, 0,
    "��� ����", "ADD RSHFIT",
    "",
    "",
    Page_DebugADCrShift, &itemsADC_AltRShift
);

// ������� - ��� - ��� ���� - ����� ------------------------------------------------------------------------------------------------------------------
static const Button mbADC_AltRShift_Reset
(
    &mpADC_AltRShift, 0,
    "�����", "Reset",
    "", "",
    OnPress_ADC_AltRShift_Reset
);

static void OnPress_ADC_AltRShift_Reset(void)
{
    for(int chan = 0; chan < 2; chan++)
    {
        for(int mode = 0; mode < 2; mode++)
        {
            for(int range = 0; range < RangeSize; range++)
            {
                RSHIFT_ADD(chan, range, mode) = 0;
            }
        }
    }
    FPGA::SetRShift(A, SET_RSHIFT_A);
    FPGA::SetRShift(B, SET_RSHIFT_B);
}

// ������� - ��� - ��� ���� - �� 1� 2�� ���� ---------------------------------------------------------------------------------------------------------
static const Governor mbADC_AltRShift_2mV_DC_A
(
    &mpADC_AltRShift, 0,
    "�� 1� 2�� ����", "Shift 1ch 2mV DC",
    "",
    "",
    &RSHIFT_ADD(A, Range_2mV, ModeCouple_DC), -100, 100, OnChanged_ADC_AltRShift_A
);

static void OnChanged_ADC_AltRShift_A(void)
{
    FPGA::SetRShift(A, SET_RSHIFT_A);
}

// ������� - ��� - ��� ���� - �� 2� 2�� ���� ---------------------------------------------------------------------------------------------------------
static const Governor mbADC_AltRShift_2mV_DC_B
(
    &mpADC_AltRShift, 0,
    "�� 2� 2�� ����", "Shift 2ch 2mV DC",
    "",
    "",
    &RSHIFT_ADD(B, Range_2mV, ModeCouple_DC), -100, 100, OnChanged_ADC_AltRShift_B
);

static void OnChanged_ADC_AltRShift_B(void)
{
    FPGA::SetRShift(B, SET_RSHIFT_B);
}

// ������� - ��� - ��� ���� - �� 1� 5�� ���� ---------------------------------------------------------------------------------------------------------
static const Governor mbADC_AltRShift_5mV_DC_A
(
    &mpADC_AltRShift, 0,
    "�� 1� 5�� ����", "Shift 1ch 5mV DC",
    "",
    "",
    &RSHIFT_ADD(A, Range_5mV, ModeCouple_DC), -100, 100, OnChanged_ADC_AltRShift_A
);

// ������� - ��� - ��� ���� - �� 2� 5�� ���� ---------------------------------------------------------------------------------------------------------
static const Governor mbADC_AltRShift_5mV_DC_B
(
    &mpADC_AltRShift, 0,
    "�� 2� 5�� ����", "Shift 2ch 5mV DC",
    "",
    "",
    &RSHIFT_ADD(B, Range_5mV, ModeCouple_DC), -100, 100, OnChanged_ADC_AltRShift_B
);

// ������� - ��� - ��� ���� - �� 1� 10�� ���� --------------------------------------------------------------------------------------------------------
static const Governor mbADC_AltRShift_10mV_DC_A
(
    &mpADC_AltRShift, 0,
    "�� 1� 10�� ����", "Shift 1ch 10mV DC",
    "",
    "",
    &RSHIFT_ADD(A, Range_10mV, ModeCouple_DC), -100, 100, OnChanged_ADC_AltRShift_A
);

// ������� - ��� - ��� ���� - �� 2� 10�� ���� --------------------------------------------------------------------------------------------------------
static const Governor mbADC_AltRShift_10mV_DC_B
(
    &mpADC_AltRShift, 0,
    "�� 2� 10�� ����", "Shift 2ch 10mV DC",
    "",
    "",
    &RSHIFT_ADD(B, Range_10mV, ModeCouple_DC), -100, 100, OnChanged_ADC_AltRShift_B
);


// ������� - ����-��� ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsRandomizer =
{
    (void*)&mgRandomizer_SamplesForGates,   // ������� - ����-��� - ���-�/������
    (void*)&mgRandomizer_AltTShift0,        // ������� - ����-��� - tShift ���.
    (void*)&mgRandomizer_Average            // ������� - ����-��� - ������.
};

static const Page mpRandomizer
(
    &pDebug, 0,
    "����-���", "RANDOMIZER",
    "",
    "",
    Page_DebugRandomizer, &itemsRandomizer
);

// ������� - ����-��� - ���-�/������ -----------------------------------------------------------------------------------------------------------------
static const Governor mgRandomizer_SamplesForGates
(
    &mpRandomizer, 0,
    "���-�/������", "Samples/gates",
    "",
    "",
    &NUM_MEAS_FOR_GATES, 1, 2500, OnChanged_Randomizer_SamplesForGates
);

static void OnChanged_Randomizer_SamplesForGates(void)
{
    FPGA::SetNumberMeasuresForGates(NUM_MEAS_FOR_GATES);
}

// ������� - ����-��� - tShift ���. ------------------------------------------------------------------------------------------------------------------
static const Governor mgRandomizer_AltTShift0
(
    &mpRandomizer, 0,
    "tShift ���.", "tShift alt.",
    "",
    "",
    &ADD_SHIFT_T0, 0, 510, OnChanged_Randomizer_AltTShift0
);

static void OnChanged_Randomizer_AltTShift0(void)
{
    FPGA::SetDeltaTShift(ADD_SHIFT_T0);
}

// ������� - ����-��� - ������. ----------------------------------------------------------------------------------------------------------------------
static const Governor mgRandomizer_Average
(
    &mpRandomizer, 0,
    "������.", "Average",
    "",
    "",
    &NUM_AVE_FOR_RAND, 1, 32
);


// ������� - ������ ��������  ------------------------------------------------------------------------------------------------------------------------
static const Choice mcSizeSettings =
{
    Item_Choice, &pDebug, 0,
    {
        "������ ��������", "Size settings",
        "����� ������� ��������� Settings",
        "Show size of struct Settings"
    },
    {
        {"������", "Size"},
        {"������", "Size"}
    },
    0, 0, OnDraw_SizeSettings
};

static void OnDraw_SizeSettings(int x, int y)
{
    Painter::DrawFormatText(x + 5, y + 21, COLOR_BLACK, "������ %d", sizeof(Settings));
}


// ������� - ����. �������� --------------------------------------------------------------------------------------------------------------------------
static const Button mbSaveFirmware
(
    &pDebug, IsActive_SaveFirmware,
    "����. ��������", "Save firmware",
    "���������� �������� - �������� 5, 6, 7 ����� ������� 3 � 128 ��, ��� �������� ���������",
    "Saving firmware - sectors 5, 6, 7 with a total size of 3 x 128 kB, where the program is stored",
    OnPress_SaveFirmware
);

static bool IsActive_SaveFirmware()
{
    return FLASH_DRIVE_IS_CONNECTED == 1;
}

static void OnPress_SaveFirmware()
{
    StructForWrite structForWrite;

    FlashDrive::OpenNewFileForWrite("S8-53.bin", &structForWrite);

    uint8 *address = (uint8*)0x08020000;
    uint8 *endAddress = address + 128 * 1024 * 3;

    int sizeBlock = 512;

    while (address < endAddress)
    {
        FlashDrive::WriteToFile(address, sizeBlock, &structForWrite);
        address += sizeBlock;
    }

    FlashDrive::CloseFile(&structForWrite);

    Display::ShowWarningGood(FirmwareSaved);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Button bEraseData
(
    &pDebug, EmptyFuncBV,
    "������� ������", "Erase data",
    "������� ������� � �������",
    "Erases data sectors",
    OnPress_EraseData
);

static void OnPress_EraseData()
{
    EPROM::EraseData();
}


// ������� - �/� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsSerialNumber =
{
    (void*)&bSerialNumber_Exit,     // ������� - �/� - �����
    (void*)&bSerialNumber_Change,   // ������� - �/� - �������
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)&bSerialNumber_Save      // ������� - �/� - ���������    
};

static const Page ppSerialNumber
(
    &pDebug, 0,
    "�/�", "S/N",
    "������ ��������� ������ � OTP-������. ��������!!! ��P-������ - ������ � ����������� �������.",
    "Serial number recording in OTP-memory. ATTENTION!!! OTP memory is a one-time programming memory.",
    Page_SB_SerialNumber, &itemsSerialNumber, OnPress_SerialNumber, 0, OnRegSet_SerialNumber
);

static void OnPress_SerialNumber(void)
{
    Menu::OpenPageAndSetItCurrent(PageDebug::SerialNumber::GetPointer());
    Display::SetAddDrawFunction(Draw_EnterSerialNumber);
    MALLOC_EXTRAMEM(StructForSN, s);
    s->number = 01;
    s->year = 2017;
    s->curDigt = 0;
}

static void Draw_EnterSerialNumber(void)
{
    int x0 = Grid::Left() + 40;
    int y0 = GRID_TOP + 20;
    int width = Grid::Width() - 80;
    int height = 160;

    Painter::DrawRectangleC(x0, y0, width, height, COLOR_FILL);
    Painter::FillRegionC(x0 + 1, y0 + 1, width - 2, height - 2, COLOR_BACK);

    int deltaX = 10;

    ACCESS_EXTRAMEM(StructForSN, s);

    bool selNumber = s->curDigt == 0;

    char buffer[20];
    snprintf(buffer, 19, "%02d", s->number);

    Color colorText = COLOR_FILL;
    Color colorBackground = COLOR_BACK;

    if (selNumber)
    {
        colorText = COLOR_FLASH_01;
        colorBackground = COLOR_FLASH_10;
    }

    int y = y0 + 50;

    Painter::SetColor(colorText);
    int x = Painter::DrawTextOnBackground(x0 + deltaX, y, buffer, colorBackground);

    colorText = COLOR_FLASH_01;
    colorBackground = COLOR_FLASH_10;

    if (selNumber)
    {
        colorText = COLOR_FILL;
        colorBackground = COLOR_BACK;
    }

    snprintf(buffer, 19, "%04d", s->year);

    Painter::SetColor(colorText);
    Painter::DrawTextOnBackground(x + 5, y, buffer, colorBackground);

    // ������ ������� ���������� �� ���������� ����� � OTP-������ ��� ������

    int allShots = OTP::GetSerialNumber(buffer);

    Painter::DrawFormatText(x0 + deltaX, y0 + 130, COLOR_FILL, "������� ���������� ����� %s", buffer[0] == 0 ? "-- ----" : buffer);

    Painter::DrawFormatText(x0 + deltaX, y0 + 100, COLOR_FILL, "�������� ����� ��� %d �������", allShots);
}

static void OnRegSet_SerialNumber(int angle)
{
    typedef int(*pFunc)(int*, int, int);

    pFunc p = angle > 0 ? CircleIncreaseInt : CircleDecreaseInt;

    ACCESS_EXTRAMEM(StructForSN, s);

    if (s->curDigt == 0)
    {
        p(&s->number, 1, 99);
    }
    else
    {
        p(&s->year, 2014, 2050);
    }
    Sound::GovernorChangedValue();
}

// ������� - �/� - ����� -----------------------------------------------------------------------------------------------------------------------------
static const SmallButton bSerialNumber_Exit
(
    &ppSerialNumber,
    COMMON_BEGIN_SB_EXIT,
    OnPress_SerialNumber_Exit,
    DrawSB_Exit
);

static void OnPress_SerialNumber_Exit(void)
{
    Display::RemoveAddDrawFunction();
    FREE_EXTRAMEM();
}

// ������� - �/� - �������� --------------------------------------------------------------------------------------------------------------------------
static const SmallButton bSerialNumber_Change
(
    &ppSerialNumber, 0,
    "��������", "Insert",
    "��������� �������� ������",
    "Inserts the chosen symbol",
    OnPress_SerialNumber_Change,
    Draw_SerialNumber_Change
);

static void OnPress_SerialNumber_Change(void)
{
    ACCESS_EXTRAMEM(StructForSN, s);
    ++s->curDigt;
    s->curDigt %= 2;
    Painter::ResetFlash();
}

static void Draw_SerialNumber_Change(int x, int y)
{
    Painter::SetFont(TypeFont_UGO2);
    Painter::Draw4SymbolsInRect(x + 2, y + 2, SYMBOL_TAB);
    Painter::SetFont(TypeFont_8);
}

// ������� - �/� - ��������� -------------------------------------------------------------------------------------------------------------------------
static const SmallButton bSerialNumber_Save
(
    &ppSerialNumber, 0,
    "���������", "Save",
    "���������� �������� ����� � OTP",
    "Records the serial number in OTP",
    OnPress_SerialNumber_Save,
    Draw_SerialNumber_Save
);

static void OnPress_SerialNumber_Save(void)
{
    ACCESS_EXTRAMEM(StructForSN, s);

    char stringSN[20];

    snprintf(stringSN, 19, "%02d %04d", s->number, s->year);

    if (!OTP::SaveSerialNumber(stringSN))
    {
        Display::ShowWarningBad(FullyCompletedOTP);
    }
}

static void Draw_SerialNumber_Save(int x, int y)
{
    Painter::SetFont(TypeFont_UGO2);
    Painter::Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_SAVE_TO_MEM);
    Painter::SetFont(TypeFont_8);
}



/** @}  @}
 */

        /*
        static void OnChangeRShiftADC(bool active)
        {
            FPGA::SetRShift(A, SET_RSHIFT_A);
            FPGA::SetRShift(B, SET_RSHIFT_B);
        }

        const Choice mcDebugADCrShiftMode =
        {
            Item_Choice, &mpADC_AltRShift, {"�����",      "Mode"},
            {
                "",
                ""
            },
            EmptyFuncBV,
            {                                    {DISABLE_RU,   DISABLE_EN},
                                                 {"��������",   "Real"},
                                                 {"������",     "Hand"}
            },
            (int8*)&set.debug.rShiftADCtype, OnChangeRShiftADC
        };

        // ������� - ��� - ���. �������� - �������� 1� 2��
        static TimeStructGovernor tsRShiftADC;
        static bool IsActiveRShiftADC(void)
        {
            return set.debug.rShiftADCtype == RShiftADC_Hand;
        }

        static void OnChangeRShiftADC0(void)
        {
            FPGA::SetRShift(A, SET_RSHIFT_A);
        }

        const Governor mgDebugRShiftADC00 =
        {
            &mpADC_AltRShift,
            {
                "���� 1� 2��", "Shift 1ch"
            },
            {
                "",
                ""
            },
            IsActiveRShiftADC,
            &set.debug.rShiftADC[0][0], -100, 100, &tsRShiftADC, OnChangeRShiftADC0
        };

        static TimeStructGovernor tsRShiftADC01;
        const Governor mgDebugRShiftADC01 =
        {
            &mpADC_AltRShift,
            {
                "���� 1� 500��", "Shift 1ch 500mV"
            },
            {
                "",
                ""
            },
            IsActiveRShiftADC,
            &set.debug.rShiftADC[1][0], -100, 100, &tsRShiftADC01, OnChangeRShiftADC0
        };

        static void OnChangeRShiftADC1(void)
        {
            FPGA::SetRShift(B, SET_RSHIFT_B);
        }

        // ������� - ��� - ���. ����. ���.
const Page mspDebugADCaltShift;

/// ������� - ��� - ���. ����. ���. - ��������
const Governor mgDebugADCaltShift =
{
    &mspDebugADCaltShift, 0,
    {
        "��������", "Value",
        "",
        ""
    },
    &set.debug.altShift, -2, 2
};

// ������� - ��� - ��� ���� ��� /////////////////////////////////////////////////////////////////////////////////////////////
const Page mspDebugADCaltShift =
{
    Item_Page, &mpADC, 0,
    {
        "��� ���� ���", "ALT SHIFT MEM",
        "",
        ""
    },
    Page_DebugADCaltShift,
    {
        (void*)&mgDebugADCaltShift
    }
};

const Governor mgDebugInfoNumber =
{
    &mspDebugInformation,
    {
        "�����", "Number"
    },
    {
        "��������� ������ ��������� ������",
        "Installation numbers of the serial number"
    },
    EmptyFuncBV,
    &set.debug.infoNumber, 0, 100
};

const Governor mgDebugInfoYear =
{
    &mspDebugInformation,
    {
        "���", "Year"
    },
    {
        "��������� ���� ��������� ������",
        "Installation year serial number"
    },
    EmptyFuncBV,
    &set.debug.infoYear, 2015, 2050
};

const Governor mgDebugInfoVersion =
{
    &mspDebugInformation,
    {
        "������", "Version"
    },
    {
        "��������� ������ ������",
        "Setting the version number"
    },
    EmptyFuncBV,
    &set.debug.infoVer, 10, 100
};

// ������� - ���������� ////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mspDebugInformation =
{
    Item_Page, &pDebug,
    {
        "����������", "INFORMATION",
    },
    {
        "��������� ������ ���������� ��� ���� ������-����������",
        "It allows you to enter information for SERVICE INFORMATION menu"
    },
    EmptyFuncBV, Page_DebugInformation,
    {
        (void*)&mgDebugInfoNumber,
        (void*)&mgDebugInfoYear,
        (void*)&mgDebugInfoVersion
    }
};
*/
