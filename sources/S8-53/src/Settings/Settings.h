#pragma once
#include "SettingsTypes.h"
#include "Utils/Measures.h"
#include "Menu/MenuItems.h"
#include "Panel/Controls.h"
#include "SettingsChannel.h"
#include "SettingsDisplay.h"
#include "SettingsMemory.h"
#include "SettingsTime.h"
#include "SettingsTrig.h"
#include "SettingsService.h"
#include "SettingsCursors.h"
#include "SettingsDebug.h"
#include "SettingsMemory.h"
#include "SettingsMeasures.h"
#include "SettingsMath.h"


/** @defgroup Settings
 *  @{
 */


#define RSHIFT_ADD(ch, range, closed) set.chan[ch].rShiftAdd[range][closed]


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /// ��������� �������
typedef struct
{
    float       stretchADC;                 ///< ����������� �����������.
    int16       rShiftRel;
    int16       rShiftAdd[RangeSize][2];    ///< ���������� �������� ��� ��������� (0) � ��������� (1) ������.
    ModeCouple  modeCouple;                 ///< ����� �� �����.
    Divider     divider;                    ///< ���������.
    Range       range;                      ///< ������� �� ����������.
    bool        enable;                     ///< ������� �� �����.
    bool        inverse;                    ///< ������������ �� �����.
    bool        filtr;                      ///< ������
    int8        balanceShiftADC;            ///< ���������� �������� ��� ������������ ���.
} SettingsChannel;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAC_ADDR0       (set.eth.mac0)
#define MAC_ADDR1       (set.eth.mac1)
#define MAC_ADDR2       (set.eth.mac2)
#define MAC_ADDR3       (set.eth.mac3)
#define MAC_ADDR4       (set.eth.mac4)
#define MAC_ADDR5       (set.eth.mac5)

#define IP_ADDR0        (set.eth.ip0)
#define IP_ADDR1        (set.eth.ip1)
#define IP_ADDR2        (set.eth.ip2)
#define IP_ADDR3        (set.eth.ip3)

#define PORT            (set.eth.port)

#define NETMASK_ADDR0   (set.eth.mask0)
#define NETMASK_ADDR1   (set.eth.mask1)
#define NETMASK_ADDR2   (set.eth.mask2)
#define NETMASK_ADDR3   (set.eth.mask3)

#define GW_ADDR0        (set.eth.gw0)
#define GW_ADDR1        (set.eth.gw1)
#define GW_ADDR2        (set.eth.gw2)
#define GW_ADDR3        (set.eth.gw3)

#define ETH_ENABLE      (set.eth.enable)


typedef struct
{
    uint8 mac0;
    uint8 mac1;
    uint8 mac2;
    uint8 mac3;
    uint8 mac4;
    uint8 mac5;

    uint8 ip0;
    uint8 ip1;
    uint8 ip2;
    uint8 ip3;

    uint16 port;

    uint8 mask0;
    uint8 mask1;
    uint8 mask2;
    uint8 mask3;

    uint8 gw0;
    uint8 gw1;
    uint8 gw2;
    uint8 gw3;

    bool enable;
} SettingsEthernet;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LANG            (set.common.lang)       ///< SettingsCommon.lang
#define LANG_RU         (LANG == Russian)
#define LANG_EN         (LANG == English)
                                    
typedef struct
{
    int     countEnables;               ///< ���������� ���������. ������������� ��� ������ ���������.
    int     countErasedFlashData;       ///< ������� ��� �������� ������ ������ � ���������.
    int     countErasedFlashSettings;   ///< ������� ��� �������� ������ � ����������.
    int     workingTimeInSecs;          ///< ����� ������ � ��������.
    Language lang;                      ///< ���� ����.
} SettingsCommon;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    bool    all;            ///< ���������� �������� ���� ���������.
    bool    flag;           ///< �������� �� ���� ����������.
    bool    rShiftA;
    bool    rShiftB;
    bool    trigLev;
    bool    range[2];
    bool    chanParam[2];
    bool    trigParam;
    bool    tShift;
    bool    tBase;
} OutputRegisters;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NUM_STRINGS                         (set.debug.numStrings)

#define SIZE_FONT_CONSOLE                   (set.debug.sizeFont)

#define CONSOLE_IN_PAUSE                    (set.debug.consoleInPause)

#define BALANCE_ADC_TYPE                    (set.debug.balanceADCtype)
#define BALANCE_ADC_TYPE_IS_HAND            (BALANCE_ADC_TYPE == BalanceADC_Hand)

#define BALANCE_ADC(ch)                     (set.debug.balanceADC[ch])
#define BALANCE_ADC_A                       (BALANCE_ADC(A))
#define BALANCE_ADC_B                       (BALANCE_ADC(B))

#define DEBUG_STRETCH_ADC_TYPE              (set.debug.stretchADCtype)
#define DEBUG_STRETCH_ADC_TYPE_IS_DISABLED  (DEBUG_STRETCH_ADC_TYPE == StretchADC_Disable)
#define DEBUG_STRETCH_ADC_TYPE_IS_HAND      (DEBUG_STRETCH_ADC_TYPE == StretchADC_Hand)
#define DEBUG_STRETCH_ADC_TYPE_IS_SETTINGS  (DEBUG_STRETCH_ADC_TYPE == StretchADC_Settings)

#define DEBUG_STRETCH_ADC(ch)               (set.debug.stretchADC[ch])
#define DEBUG_STRETCH_ADC_A                 (DEBUG_STRETCH_ADC(A))
#define DEBUG_STRETCH_ADC_B                 (DEBUG_STRETCH_ADC(B))

#define NUM_MEAS_FOR_GATES                  (set.debug.numMeasuresForGates)

#define ADD_SHIFT_T0                        (set.debug.shiftT0)

#define SHOW_STATS                          (set.debug.showStats)

#define NUM_AVE_FOR_RAND                    (set.debug.numAveForRand)


/// ���������� ���������.
typedef  struct
{
    int16           numStrings;                 ///< ����� ����� � �������.
    int8            sizeFont;                   ///< ������ ������ ������� - 0 - 5, 1 - 8,
    bool            consoleInPause;             ///< \brief ������� ����, ��� ������� ��������� � ������ �����. ����� ����� ��������, ��� ����� 
                                                    /// ��������� ��� �� ���������� � �� ���������.
    BalanceADCtype  balanceADCtype;             ///< ��� ������������.
    int16           balanceADC[2];              ///< �������� ��������������� �������� ��� ��� ������ ������������.
    StretchADCtype  stretchADCtype;             ///< ��� �������� ������.
    int16           stretchADC[2];              ///< �������� �������� ������ ��� ������� ������.
    //RShiftADCtype   rShiftADCtype;
    //int16           rShiftADC[RangeSize][2];    // �������������� �������� ��� ������� � ������ ������� ����������. 0 - range == Range_2mV, 1 - ��� ���������
    int16           numMeasuresForGates;        ///< ����� ��������� ��� �����.
    int16           shiftT0;                    ///< �������������� �������� �� ������� ��� ������ �������� ������ �������������.
    bool            showStats;                  ///< ���������� ���������� �� ������ (fps, ��������).
    int16           numAveForRand;              ///< �� �������� ���������� ��������� ������ � ������ �������������.
    bool            viewAlteraWrittingData;     ///< ���������� �� ������, ������ � �������.
    bool            viewAllAlteraWrittingData;  ///< \brief ���������� �� ��� ������, ������ � ������� (���� false, �� ��������� ������ ������� ����� 
                                                    /// START, STOP �� ������������).
    int16           altShift;                   ///< ���������� �������� ��� ���������� ������� �������������� ������ �������������.
    OutputRegisters showRegisters;
} SettingsDebug;

typedef struct
{
    int8        posActItem[Page_NumPages];      ///< ������� �������� ������. bit7 == 1 - item is opened, 0x7f - ��� ��������� ������
    int8        currentSubPage[Page_NumPages];  ///< ����� ������� �����������.
    bool        pageDebugActive;                ///< ������� �� ������ ������� � ����.
    unsigned    isShown : 1;                    ///< ���� ��������.
} SettingsMenu;



int8 MenuPosActItem(NamePage namePage);                         ///< ���������� ������� ��������� ������ �� �������� namePage.
void SetMenuPosActItem(NamePage namePage, int8 pos);            ///< ���������� ������� ��������� ������ �� �������� namePage.
int8 MenuCurrentSubPage(NamePage namePage);                     ///< ���������� ����� ������� ����������� �������� namePage.
void SetMenuCurrentSubPage(NamePage namePage, int8 posSubPage); ///< ������������� ����� ������� ����������� � �������� namePage.
bool MenuIsShown();                                             ///< ���������� �� ���� �� ������.
void ShowMenu(bool show);                                       ///< ����������/������ ����.
bool MenuIsMinimize();                                          ///< ���� true - ���� ��������� � �������������� ������.
bool MenuPageDebugIsActive();                                   ///< ������� �� �������� �������.
void SetMenuPageDebugActive(bool active);                       ///< �������/��������� �������� �������� �������.
void CurrentPageSBregSet(int angle);                            ///< ��������� ����� ��������� �� ������� �������� ����� ������.
const SmallButton*  GetSmallButton(PanelButton button);         ///< ������� ��������� �� ����� ������, ��������������� ������ ������ ������.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// �������� ������ ��� ��������� �������.
typedef struct
{
    uint                size;
    SettingsDisplay     display;            ///< ��������� �����������          (���� �������).
    SettingsChannel     chan[NumChannels];  ///< ��������� �������              (���� ����� 1 � ����� 2).
    SettingsTrig        trig;               ///< ��������� �������������        (���� �����).
    SettingsTime        time;               ///< ��������� ���������            (���� ���¨����).
    SettingsCursors     cursors;            ///< ��������� ��������� ���������  (���� �������).
    SettingsMemory      memory;             ///< ��������� ������� ������       (���� ������).
    SettingsMeasures    measures;           ///< ��������� ���������            (���� ���������).
    SettingsMath        math;               ///< ��������� ������ �������������� ���������.
    SettingsService     service;            ///< �������������� ���������       (���� ������).
    SettingsEthernet    eth;                ///< ��������� ��� ���������� �� ��������� ����.
    SettingsCommon      common;             ///< ��������� ���������.
    SettingsMenu        menu;               ///< ��������� ����.
    SettingsDebug       debug;              ///< ��������� ������ �������       (���� �������).
    uint                crc32;              ///< ����������� �����. ������������ ��� �������� ������������ ���������� ��������
    //int temp[5];
    static void Load(bool _default);  ///< \brief ��������� ���������. ���� _default == true, ����������� ��������� �� ���������, ����� �������� 
                                      ///< ��������� ��������� �� ���, � � ������ ������� - ���� ��������� �� ���������.
    static void Save();               ///< ��������� ��������� �� ����-������.
    static bool DebugModeEnable();    ///< ���������� true, ���� ������� ����� �������.
} Settings;

extern Settings set;


/** @}
 */
