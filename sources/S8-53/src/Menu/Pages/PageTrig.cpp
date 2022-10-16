#include "defines.h"
#include "Menu/MenuItems.h"
#include "Settings/Settings.h"
#include "Utils/GlobalFunctions.h"
#include "FPGA/FPGA.h"
#include "Settings/Settings.h"
#include "Utils/GlobalFunctions.h"


/** @addtogroup Menu
 *  @{
 *  @addtogroup PageTrig
 *  @{
 */

extern const Page pTrig;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const Choice mcMode;                     ///< ����� - �����
void          OnPress_Mode(bool active);
extern const Choice mcSource;                   ///< ����� - ��������
static void OnChanged_Source(bool active);
extern const Choice mcPolarity;                 ///< ����� - ����������
static void OnChanged_Polarity(bool active);
extern const Choice mcInput;                    ///< ����� - ����
static void OnChanged_Input(bool active);
extern const Page   mpAutoFind;                 ///< ����� - �����
extern const Choice mcAutoFind_Mode;            ///< ����� - ����� - �����
extern const Button mbAutoFind_Search;          ///< ����� - ����� - �����
static bool  IsActive_AutoFind_Search();
static void   OnPress_AutoFind_Search();

extern const Page mainPage;

// ����� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsTrig =
{
    (void*)&mcMode,         // ����� - �����
    (void*)&mcSource,       // ����� - ��������
    (void*)&mcPolarity,     // ����� - ����������
    (void*)&mcInput,        // ����� - ����
    (void*)&mpAutoFind      // ����� - �����
};

const Page pTrig              ///< �����
(
    &mainPage, 0,
    "�����", "TRIG",
    "�������� ��������� �������������.",
    "Contains synchronization settings.",
    Page_Trig, &itemsTrig
);


// ����� - ����� -------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcMode =
{
    Item_Choice, &pTrig, 0,
    {
        "�����", "Mode"
        ,
        "����� ����� �������:\n"
        "1. \"����\" - ������ ���������� �������������.\n"
        "2. \"������\" - ������ ���������� �� ������ �������������.\n"
        "3. \"�����������\" - ������ ���������� �� ���������� ������ ������������� ���� ���. ��� ���������� ��������� ����� ������ ������ ����/����."
        ,
        "Sets the trigger mode:\n"
        "1. \"Auto\" - start automatically.\n"
        "2. \"Standby\" - the launch takes place at the level of synchronization.\n"
        "3. \"Single\" - the launch takes place on reaching the trigger levelonce. For the next measurement is necessary to press the START/STOP."
    },
    {
        {"���� ",       "Auto"},
        {"������",      "Wait"},
        {"�����������", "Single"}
    },
    (int8*)&START_MODE, OnPress_Mode
};

void OnPress_Mode(bool active)
{
    FPGA::Stop(false);
    if (!START_MODE_IS_SINGLE)
    {
        FPGA::Start();
    }
}


// ����� - �������� ----------------------------------------------------------------------------------------------------------------------------------
static const Choice mcSource =
{
    Item_Choice, &pTrig, 0,
    {
        "��������", "Source",
        "����� ��������� ������� �������������.",
        "Synchronization signal source choice."
    },
    {
        {"����� 1", "Channel 1"},
        {"����� 2", "Channel 2"},
        {"�������", "External"}
    },
    (int8*)&TRIG_SOURCE, OnChanged_Source
};

static void OnChanged_Source(bool active)
{
    FPGA::SetTrigSource(TRIG_SOURCE);
}


// ����� - ���������� --------------------------------------------------------------------------------------------------------------------------------
static const Choice mcPolarity =
{
    Item_Choice, &pTrig, 0,
    {
        "����������", "Polarity"
        ,
        "1. \"�����\" - ������ ���������� �� ������ ��������������.\n"
        "2. \"����\" - ������ ���������� �� ����� ��������������."
        ,
        "1. \"Front\" - start happens on the front of clock pulse.\n"
        "2. \"Back\" - start happens on a clock pulse cut."
    },
    {
        {"�����",   "Front"},
        {"����",    "Back"}
    },
    (int8*)&TRIG_POLARITY, OnChanged_Polarity
};

static void OnChanged_Polarity(bool active)
{
    FPGA::SetTrigPolarity(TRIG_POLARITY);
}


// ����� - ���� --------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcInput =
{
    Item_Choice, &pTrig, 0,
    {
        "����", "Input"
        ,
        "����� ����� � ���������� �������������:\n"
        "1. \"��\" - ������ ������.\n"
        "2. \"��\" - �������� ����.\n"
        "3. \"���\" - ������ ������ ������.\n"
        "4. \"���\" - ������ ������� ������."
        ,
        "The choice of communication with the source of synchronization:\n"
        "1. \"SS\" - a full signal.\n"
        "2. \"AS\" - a gated entrance.\n"
        "3. \"LPF\" - low-pass filter.\n"
        "4. \"HPF\" - high-pass filter frequency."
    },
    {
        {"��",  "Full"},
        {"��",  "AC"},
        {"���", "LPF"},
        {"���", "HPF"}
    },
    (int8*)&TRIG_INPUT, OnChanged_Input
};

static void OnChanged_Input(bool active)
{
    FPGA::SetTrigInput(TRIG_INPUT);
}


// ����� - ����� -------------------------------------------------------------------------------------------------------------------------------------
static const arrayItems itemsAutoFind =
{
    (void*)&mcAutoFind_Mode,     // ����� - ����� - �����
    (void*)&mbAutoFind_Search     // ����� - ����� - �����    
};

static const Page mpAutoFind
(
    &pTrig, 0,
    "�����", "SEARCH",
    "���������� �������������� ������� ������ �������������.",
    "Office of the automatic search the trigger level.",
    Page_TrigAuto, &itemsAutoFind
);


// ����� - ����� - ����� -----------------------------------------------------------------------------------------------------------------------------
static const Choice mcAutoFind_Mode =
{
    Item_Choice, &mpAutoFind, 0,
    {
        "�����", "Mode"
        ,
        "����� ������ ��������������� ������ �������������:\n"
        "1. \"������\" - ����� ������������ �� ������� ������ \"�����\" ��� �� ��������� � ������� 0.5� ������ �����, ���� ����������� \"������\x99��� ���� �����\x99�����������\".\n"
        "2. \"��������������\" - ����� ������������ �������������."
        ,
        "Selecting the automatic search of synchronization:\n"
#pragma push
#pragma diag_suppress 192
        "1. \"Hand\" - search is run on pressing of the button \"Find\" or on deduction during 0.5s the ����� button if it is established \"SERVICE\x99Mode long �����\x99\x41utolevel\".\n"
#pragma pop
        "2. \"Auto\" - the search is automatically."
    },
    {
        {"������",          "Hand"},
        {"��������������",  "Auto"}
    },
    (int8*)&TRIG_MODE_FIND
};


// ����� - ����� - ����� -----------------------------------------------------------------------------------------------------------------------------
static const Button mbAutoFind_Search
(
    &mpAutoFind, IsActive_AutoFind_Search,
    "�����", "Search",
    "���������� ����� ������ �������������.",
    "Runs for search synchronization level.",
    OnPress_AutoFind_Search
);

static bool IsActive_AutoFind_Search(void)
{
    return TRIG_MODE_FIND_IS_HAND;
}

static void OnPress_AutoFind_Search(void)
{
    FPGA::FindAndSetTrigLevel();
}


/** @}  @}
 */
