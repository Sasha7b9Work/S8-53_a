#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "Settings/Settings.h"
#include "Log.h"
#include "Tables.h"
#include "Utils/GlobalFunctions.h"
#include "Display/font/Font.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ��������� ��� �������� ��������� �������� �� �������.
typedef struct
{
    const char* name[2];    ///< �������� ��������� � ��������� ����, ��������� ��� ������ �� �����.
} TBaseStruct;


/// ������ �������� �������� ��������� �� �������.
static const TBaseStruct tBases[TBaseSize] =
{
    {"2\x10��",     "2\x10ns"},
    {"5\x10��",     "5\x10ns"},
    {"10\x10��",    "10\x10ns"},
    {"20\x10��",    "20\x10ns"},
    {"50\x10��",    "50\x10ns"},
    {"0.1\x10���",  "0.1\x10us"},
    {"0.2\x10���",  "0.2\x10us"},
    {"0.5\x10���",  "0.5\x10us"},
    {"1\x10���",    "1\x10us"},
    {"2\x10���",    "2\x10us"},
    {"5\x10���",    "5\x10us"},
    {"10\x10���",   "10\x10us"},
    {"20\x10���",   "20\x10us"},
    {"50\x10���",   "50\x10us"},
    {"0.1\x10��",   "0.1\x10ms"},
    {"0.2\x10��",   "0.2\x10ms"},
    {"0.5\x10��",   "0.5\x10ms"},
    {"1\x10��",     "1\x10ms"},
    {"2\x10��",     "2\x10ms"},
    {"5\x10��",     "5\x10ms"},
    {"10\x10��",    "10\x10ms"},
    {"20\x10��",    "20\x10ms"},
    {"50\x10��",    "50\x10ms"},
    {"0.1\x10�",    "0.1\x10s"},
    {"0.2\x10�",    "0.2\x10s"},
    {"0.5\x10�",    "0.5\x10s"},
    {"1\x10�",      "1\x10s"},
    {"2\x10�",      "2\x10s"},
    {"5\x10�",      "5\x10s"},
    {"10\x10�",     "10\x10s"}
};

/// ������� �������� �������� � ������������ ��� ����� ������
const char* symbolsAlphaBet[0x48] =
{
    /* 0x00 */ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", /* 0x19 */
    /* 0x1a */ " ", "_", "-", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", /* 0x26 */
    /* 0x27 */ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", /* 0x40 */
    //         0x41  0x42  0x43  0x44  0x45  0x46   0x47   - ��� ���������� ����� �������� � ���� �������
    /* 0x41 */ "%y", "%m", "%d", "%H", "%M", "%S", "%N" /* 0x47 */
    //         0x01  0x02  0x03  0x04  0x05  0x06   0x07   - ��� ����� ���������� �������� �������� � set.memory.fileNameMask
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ENumSignalsInSec Tables_NumSignalsInSecToENUM(int enumSignalsInSec)
{
    if(enumSignalsInSec == 1)
    {
        return NumSignalsInSec_1;
    }
    else if(enumSignalsInSec == 2)
    {
        return NumSignalsInSec_2;
    }
    else if(enumSignalsInSec == 5)
    {
        return NumSignalsInSec_5;
    }
    else if(enumSignalsInSec == 10)
    {
        return NumSignalsInSec_10;
    }
    else if(enumSignalsInSec == 25)
    {
        return NumSignalsInSec_25;
    }
    LOG_ERROR("����� �������� � ������� ����� %d", enumSignalsInSec);
    return NumSignalsInSec_1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Tables_ENUMtoNumSignalsInSec(ENumSignalsInSec enumSignalsInSec)
{
    static const int fps[] = {25, 10, 5, 2, 1};
    if(enumSignalsInSec <= NumSignalsInSec_1)
    {
        return fps[enumSignalsInSec];
    }
    LOG_ERROR("������������ �������� %d", (int)enumSignalsInSec);
    return 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char* Tables_GetWarning(Warning warning)
{
    static const char *warnings[Warning_NumWarnings][2] =
    {
        {"������ ����� 1 - �����/���",      "LIMIT CHANNEL 1 - VOLTS/DIV"},
        {"������ ����� 2 - �����/���",      "LIMIT CHANNEL 2 - VOLTS/DIV"},
        {"������ ��������� - �����/���",    "LIMIT SWEEP - TIME/DIV"},
        {"������� ������� ��������",        "SET_ENABLED PEAK. DET."},
        {"������ ����� 1 - \x0d",           "LIMIT CHANNEL 1 - \x0d"},
        {"������ ����� 2 - \x0d",           "LIMIT CHANNEL 2 - \x0d"},
        {"������ ��������� - �������",      "LIMIT SWEEP - LEVEL"},
        {"������ ��������� - \x97",         "LIMIT SWEEP - \x97"},
        {"���. ���. �� �������� �� ���������� ����� 0.5���/���", "PEAK. DET. NOT WORK ON SWEETS LESS THAN 0.5us/div"},
        {"��������� �� ����� �������� �� ������� ���¨�����", "SELF-RECORDER DOES NOT WORK FAST SCANS"},
        {"���� ��������",                   "FILE IS SAVED"},
        {"������ ��������",                 "SIGNAL IS SAVED"},
        {"������ ������",                   "SIGNAL IS DELETED"},
        {"���� ������� ��������",           "MENU DEBUG IS SET_ENABLED"},
        {"��������� ��������� ������, ���� ����������� ������", "WAIT A FEW SECONDS, GOES A MOVEMENT DATA"},
        {"����� �� �����������. ������ ���������� ��� ������", "TIME IS NOT SET. YOU CAN INSTALL IT NOW"},
        {"������ �� ������",                "SIGNAL IS NOT FOUND"},
        {"�� ���������� ��������� 10��/��� ���������� �������-", "AT SCANNER SLOWLY 10ms/div DESIRABLY SET \"SCAN - \x7b\" IN"},
        {"������ \"��������� - \x7b\" � ��������� \"����\" ��� ������-", "SWITCH \"Left\" FOR TO ACCELERATE THE OUTPUT SIGNAL"},
        {"��� ������ �������",              ""},
        {"����� ���� ���������",            "VERY SMALL MEASURES"},
        {"��� ���������� ��������� � ����", "FOR THE INTRODUCTION OF CHANGES"},
        {"��������� ������",                "IN FORCE SWITCH OFF THE DEVICE"},
        {"��������� ���������� ���",        "DISCONNECT CALCULATION OF FFT"},
        {"��������� �������������� �������", "DISCONNECT MATHEMATICAL FUNCTION"},
        {"�������� ���������",              "FIRMWARE SAVED"},
        {"������ OTP ��������� ��������",   "OPT memory fully completed"}
    };
    return warnings[warning][set.common.lang];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char* Tables_GetTBaseString(TBase tBase)
{
    return tBases[tBase].name[set.common.lang];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char* Tables_GetTBaseStringEN(TBase tBase)
{
    return tBases[tBase].name[English];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char* Tables_RangeNameFromValue(Range range)
{
    static const char* names[RangeSize] =
    {
        "Range_2mV",
        "Range_5mV",
        "Range_10mV",
        "Range_20mV",
        "Range_50mV",
        "Range_100mV",
        "Range_200mV",
        "Range_500mV",
        "Range_1V",
        "Range_2V",
        "Range_5V",
        "Range_10V",
        "Range_20V"
    };
    return names[range];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Tables_GetNumChannel(Channel chan)
{
    return (chan == A) ? 1 : 2;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawStr(int index, int x, int y)
{
    const char *str = symbolsAlphaBet[index];
    if (index == INDEX_SYMBOL)
    {
        Painter::FillRegionC(x - 1, y, Font_GetLengthText(str), 9, COLOR_FLASH_10);
    }
    Painter::DrawTextC(x, y, symbolsAlphaBet[index], index == INDEX_SYMBOL ? COLOR_FLASH_01 : COLOR_FILL);
}
