#include "defines.h"
#include "Log.h"
#include "Settings/SettingsTypes.h"
#include "Menu/MenuItems.h"
#include "Panel/Panel.h"
#include "FPGA/FPGA.h"
#include "Display/Display.h"
#include "Settings/Settings.h"
#include "Utils/GlobalFunctions.h"


/** @addtogroup Menu
 *  @{
 *  @addtogroup PageChannels
 *  @{
 */

extern const Page pChanA;
extern const Page pChanB;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const Choice mcInputA;                   ///< ����� 1 - ����
void OnChanged_InputA(bool active);
extern const Choice mcCoupleA;                  ///< ����� 1 - �����
void OnChanged_CoupleA(bool active);
extern const Choice mcFiltrA;                   ///< ����� 1 - ������
void OnChanged_FiltrA(bool active);
extern const Choice mcInverseA;                 ///< ����� 1 - ��������
static void OnChanged_InverseA(bool active);
extern const Choice mcMultiplierA;              ///< ����� 1 - ���������

extern const Choice mcInputB;                   ///< ����� 2 - ����
void OnChanged_InputB(bool active);
extern const Choice mcCoupleB;                  ///< ����� 2 - �����
void OnChanged_CoupleB(bool active);
extern const Choice mcFiltrB;                   ///< ����� 2 - ������
void OnChanged_FiltrB(bool active);
extern const Choice mcInverseB;                 ///< ����� 2 - ��������
static void OnChanged_InverseB(bool active);
extern const Choice mcMultiplierB;              ///< ����� 2 - ���������


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const char chanInputRu[] =   "1. \"���\" - �������� ������ �� �����.\n"
                                    "2. \"����\" - �� �������� ������ �� �����.";
extern const char chanInputEn[] =   "1. \"Enable\" - signal output to the screen.\n"
                                    "2. \"Disable\" - no output to the screen.";

extern const char chanCoupleRu[] =  "����� ��� ����� � ���������� �������.\n"
                                    "1. \"����\" - �������� ����.\n"
                                    "2. \"�����\" - �������� ����.\n"
                                    "3. \"�����\" - ���� ������� � �����.";
extern const char chanCoupleEn[] =  "Sets a type of communication with a signal source.\n"
                                    "1. \"AC\" - open input.\n"
                                    "2. \"DC\" - closed input.\n"
                                    "3. \"Ground\" - input is connected to the ground.";

extern const char chanFiltrRu[] = "��������/��������� ������ ��� ����������� ������ �����������.";
extern const char chanFiltrEn[] = "Includes/switches-off the filter for restriction of a pass-band.";

extern const char chanInverseRu[] = "��� \"���\" ������ �� ������ ����� ����������� ������ ������������ U = 0�.";
extern const char chanInverseEn[] = "When \"Enable\" signal on the screen will be reflected symmetrically with respect to U = 0V.";

extern const char chanMultiplierRu[] = "���������� �������:\n\"x1\" - ������ �� �����������.\n\"x10\" - ������ ����������� � 10 ���";
extern const char chanMultiplierEn[] = "Attenuation: \n\"x1\" - the signal is not attenuated.\n\"x10\" - the signal is attenuated by 10 times";


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const Page mainPage;


// ����� 1 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsChanA =
{
    (void*)&mcInputA,       // ����� 1 - ����
    (void*)&mcCoupleA,      // ����� 1 - �����
    (void*)&mcFiltrA,       // ����� 1 - ������
    (void*)&mcInverseA,     // ����� 1 - ��������
    (void*)&mcMultiplierA   // ����� 1 - ���������
};

const Page pChanA           ///< ����� 1
(
    &mainPage, 0,
    "����� 1", "CHANNEL 1",
    "�������� ��������� ������ 1.",
    "Contains settings of the channel 1.",
    Page_Channel0, &itemsChanA
);


// ����� 1 - ���� ------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcInputA =
{
    Item_Choice, &pChanA, 0,
    {
        "����", "Input",
        chanInputRu,
        chanInputEn
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&SET_ENABLED_A, OnChanged_InputA
};

void OnChanged_InputA(bool active)
{
    Panel::EnableLEDChannel0(sChannel_Enabled(A));
}


// ����� 1 - ����� -----------------------------------------------------------------------------------------------------------------------------------
static const Choice mcCoupleA =
{
    Item_Choice, &pChanA, 0,
    {
        "�����",   "Couple",
        chanCoupleRu,
        chanCoupleEn
    },
    {
        {"����",    "AC"},
        {"�����",   "DC"},
        {"�����",   "Ground"}
    },
    (int8*)&SET_COUPLE_A, OnChanged_CoupleA
};

void OnChanged_CoupleA(bool active)
{
    FPGA::SetModeCouple(A, SET_COUPLE_A);
}


// ����� 1 - ������ ----------------------------------------------------------------------------------------------------------------------------------
static const Choice mcFiltrA =
{
    Item_Choice, &pChanA, 0,
    {
        "������", "Filtr",
        chanFiltrRu,
        chanFiltrEn
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&SET_FILTR_A, OnChanged_FiltrA
};

void OnChanged_FiltrA(bool active)
{
    FPGA::EnableChannelFiltr(A, SET_FILTR_A);
}


// ����� 1 - �������� --------------------------------------------------------------------------------------------------------------------------------
static const Choice mcInverseA =
{
    Item_Choice, &pChanA, 0,
    {
        "��������",    "Inverse",
        chanInverseRu,
        chanInverseEn
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&SET_INVERSE_A, OnChanged_InverseA
};

static void OnChanged_InverseA(bool active)
{
    FPGA::SetRShift(A, SET_RSHIFT_A);
}


// ����� 1 - ��������� -------------------------------------------------------------------------------------------------------------------------------
static const Choice mcMultiplierA =
{
    Item_Choice, &pChanA, 0,
    {
        "���������", "Divider",
        chanMultiplierRu,
        chanMultiplierEn
    },
    {
        {"�1",  "x1"},
        {"x10", "x10"}
    },
    (int8*)&SET_DIVIDER(A)
};



// ����� 2 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsChanB =
{
    (void*)&mcInputB,       // ����� 2 - ����
    (void*)&mcCoupleB,      // ����� 2 - �����
    (void*)&mcFiltrB,       // ����� 2 - ������
    (void*)&mcInverseB,     // ����� 2 - ��������
    (void*)&mcMultiplierB   // ����� 2 - ���������
};

const Page pChanB
(
    &mainPage, 0,
    "����� 2", "CHANNEL 2",
    "�������� ��������� ������ 2.",
    "Contains settings of the channel 2.",
    Page_Channel1, &itemsChanB
);


// ����� 2 - ���� ------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcInputB =  ///< ����� 2
{
    Item_Choice, &pChanB, 0,
    {
        "����", "Input",
        chanInputRu,
        chanInputEn
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&SET_ENABLED_B, OnChanged_InputB
};

void OnChanged_InputB(bool active)
{
    Panel::EnableLEDChannel1(sChannel_Enabled(B));
}


// ����� 2 - ����� -----------------------------------------------------------------------------------------------------------------------------------
static const Choice mcCoupleB =
{
    Item_Choice, &pChanB, 0,
    {
        "�����", "Couple",
        chanCoupleRu,
        chanCoupleEn
    },
    {
        {"����",    "AC"},
        {"�����",   "DC"},
        {"�����",   "Ground"}
    },
    (int8*)&SET_COUPLE_B, OnChanged_CoupleB
};

void OnChanged_CoupleB(bool active)
{
    FPGA::SetModeCouple(B, SET_COUPLE_B);
}

// ����� 2 - ������ ----------------------------------------------------------------------------------------------------------------------------------
static const Choice mcFiltrB =
{
    Item_Choice, &pChanB, 0,
    {
        "������", "Filtr",
        chanFiltrRu,
        chanFiltrEn
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&SET_FILTR_B, OnChanged_FiltrB
};

void OnChanged_FiltrB(bool active)
{
    FPGA::EnableChannelFiltr(B, SET_FILTR_B);
}


// ����� 2 - �������� --------------------------------------------------------------------------------------------------------------------------------
static const Choice mcInverseB =
{
    Item_Choice, &pChanB, 0,
    {
        "��������", "Inverse",
        chanInverseRu,
        chanInverseEn
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&SET_INVERSE_B, OnChanged_InverseB
};

static void OnChanged_InverseB(bool active)
{
    FPGA::SetRShift(B, SET_RSHIFT_B);
}


// ����� 2 - ��������� -------------------------------------------------------------------------------------------------------------------------------
static const Choice mcMultiplierB =
{
    Item_Choice, &pChanB, 0,
    {
        "���������", "Divider",
        chanMultiplierRu,
        chanMultiplierEn
    },
    {
        {"�1",  "x1"},
        {"x10", "x10"}
    },
    (int8*)&SET_DIVIDER(B)
};


/** @}  @}
 */
