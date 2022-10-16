#include "Settings/SettingsTypes.h"
#include "Utils/Measures.h"
#include "Utils/Math.h"
#include "PageMemory.h"
#include "Definition.h"
#include "Menu/MenuItems.h"
#include "Utils/GlobalFunctions.h"
#include "Settings/SettingsTypes.h"
#include "Settings/Settings.h"
#include "Display/Colors.h"
#include "defines.h"
#include "Display/Painter.h"
#include "PageMeasures.h"


/** @addtogroup Menu
 *  @{
 *  @addtogroup PageMeasures
 *  @{
 */

extern const Page pMeasures;
extern const Page mainPage;

static CursCntrl    GetMeasuresCursCntrlActive();       // ����� �������� �� �������� ���� ������ ���������� ����������.
bool PageMeasures::choiceMeasuresIsActive = false;

void DrawSB_MeasTune_Settings(int x, int y)
{
    Painter::SetFont(TypeFont_UGO2);
    Painter::Draw4SymbolsInRect(x + 2, y + 1, '\x62');
    Painter::SetFont(TypeFont_8);
}

void PressSB_MeasTune_Settings()
{
    Measure_ShorPressOnSmallButtonSettings();
}

void DrawSB_MeasTune_Markers(int x, int y)
{
    Painter::SetFont(TypeFont_UGO2);
    Painter::Draw4SymbolsInRect(x + 2, y + 2, '\x60');
    Painter::SetFont(TypeFont_8);
}

void PressSB_MeasTune_Markers()
{
    Measure_ShortPressOnSmallButonMarker();
}

void RotateRegMeasureSetField(int angle)
{
    CursCntrl cursCntrl = GetMeasuresCursCntrlActive();
    CursActive cursActive = MEAS_CURS_ACTIVE;

    int sign = Math_Sign(angle);

    if (cursCntrl == CursCntrl_1 || cursCntrl == CursCntrl_1_2)
    {
        if (cursActive == CursActive_T)
        {
            LIMITATION(MEAS_POS_CUR_T0, MEAS_POS_CUR_T0 - sign, 0, sMemory_GetNumPoints(false) - 1);
        }
        else
        {
            LIMITATION(MEAS_POS_CUR_U0, MEAS_POS_CUR_U0 + sign, 0, 200);
        }
    }
    if (cursCntrl == CursCntrl_2 || cursCntrl == CursCntrl_1_2)
    {
        if (cursActive == CursActive_T)
        {
            LIMITATION(MEAS_POS_CUR_T1, MEAS_POS_CUR_T1 - sign, 0, sMemory_GetNumPoints(false) - 1);
        }
        else
        {
            LIMITATION(MEAS_POS_CUR_U1, MEAS_POS_CUR_U1 + sign, 0, 200);
        }
    }
}

extern const Page mspMeasTune;

const SmallButton sbMeasTuneSettings        // ��������� ���������.
(
    &mspMeasTune, 0,
    "���������", "Setup",
    "��������� ������� ����������� ���������",
    "Allows to choose necessary measurements",
    PressSB_MeasTune_Settings,
    DrawSB_MeasTune_Settings
);

const SmallButton sbMeasTuneMarkers        // ���������/���������� ������� ��� ������ ���������.
(
    &mspMeasTune, 0,
    "������", "Marker",
    "��������� ���������� ������� ��� ����������� �������� ���������",
    "Allows to establish markers for visual control of measurements",
    PressSB_MeasTune_Markers,
    DrawSB_MeasTune_Markers
);

bool IsActiveChoiceMeasuresNumber()
{
    return SHOW_MEASURES;
}

bool IsActiveChoiceMeasuresChannels()
{
    return SHOW_MEASURES;
}

bool IsActivePageMeasuresFields()
{
    return SHOW_MEASURES;
}

bool IsActiveChoiceMeasuresSignal()
{
    return SHOW_MEASURES;
}

bool IsActiveButtonMeasuresTune()
{
    return SHOW_MEASURES;
}

bool IsActiveButtonMeasuresFieldSet()
{
    return MEAS_FIELD_IS_HAND;
}

// ���������
extern const Page pMeasures;

// ��������� -> ����������
const Choice mcMeasuresNumber =
{
    Item_Choice, &pMeasures, IsActiveChoiceMeasuresNumber,
    {
        "����������", "Number"
        ,
        "������������� ������������ ���������� ��������� ���������:\n"
        "\"1\" - ���� ���������\n"
        "\"2\" - ��� ���������\n"
        "\"1�5\" - 1 ������ � ����� �����������\n"
        "\"2�5\" - 2 ������ � ����� ����������� � ������\n"
        "\"3�5\" - 3 ������ � ����� ����������� � ������\n"
        "\"6x1\" - 6 ����� �� ������ ��������� � ������\n"
        "\"6�2\" - 6 ����� �� ��� ��������� � ������"
        ,
        "Sets the maximum number of output measurements:\n"
        "\"1\" - one measurement\n"
        "\"2\" - two measurements\n"
        "\"1x5\" - 1 line with the five dimensions\n"
        "\"2x5\" - two rows with five measurements in each\n"
        "\"3x5\" - 3 lines with five measurements in each"
        "\"6x1\" - 6 lines, one in each dimension\n"
        "\"6x2\" - 6 lines of two dimensions in each\n"
    },
    {                          
        {"1",   "1"},
        {"2",   "2"},
        {"1x5", "1x5"},
        {"2x5", "2x5"},
        {"3x5", "3x5"},
        {"6x1", "6x1"},
        {"6x2", "6x2"}
    },
    (int8*)&MEAS_NUM
};

/// ��������� -> ������
const Choice mcMeasuresChannels =
{
    Item_Choice, &pMeasures, IsActiveChoiceMeasuresChannels,
    {
        "������", "Channels",
        "�� ����� ������� �������� ���������",
        "Which channels to output measurement"
    },
    {   
        {"1",       "1"},
        {"2",       "2"},
        {"1 � 2",   "1 and 2"}
    },
    (int8*)&MEAS_SOURCE
};

// ��������� -> ����������
const Choice mcMeasuresIsShow =
{
    Item_Choice, &pMeasures, 0,
    {
        "����������", "Show",
        "�������� ��� �� �������� ��������� �� �����",
        "Output or output measurements on screen"
    },
    {   
        {"���", "No"},
        {"��",  "Yes"}
    },
    (int8*)&SHOW_MEASURES
};

// ��������� -> ���
const Choice mcMeasuresSignal =
{
    Item_Choice, &pMeasures, IsActiveChoiceMeasuresSignal,
    {
        "���", "View",
        "��������� ��� ��� ���� ������ ������� ��� ���������� ���������� ��� ���������� ���������",
        "Decrease or no zone output signal to avoid overlapping of its measurement results"
    },
    {   
        {"��� ����",    "As is"},
        {"���������",   "Reduce"}
    },
    (int8*)&MODE_VIEW_SIGNALS
};



/**********************************************************************************************************************************************************/
// ��������� -> ����
extern const Page mspMeasuresField;

// ��������� -> ���� -> �������
const Choice mcMeasuresFieldType =
{
    Item_Choice, &mspMeasuresField, 0,
    {
        "�������", "Field",
        "����� �������, �� ������� ����� ������� �������� ��� �������������� ���������",
        "Select an area from which the values will be taken for automatic measurements"
    },
    {   
        {"�����",   "Screen"},
        {"������",  "Memorye"},
        {"�������", "Cursors"}
    },
    (int8*)&MEAS_FIELD
};

CursCntrl GetMeasuresCursCntrlActive()
{
    if(MEAS_CURS_ACTIVE_IS_T)
    {
        return MEAS_CURS_CNTRL_T;
    }
    return MEAS_CURS_CNTRL_U;
}

static void PressSB_MeasTune_Exit()
{
    Display::RemoveAddDrawFunction();
}

static const SmallButton sbExitMeasTune
(
    &mspMeasTune,
    COMMON_BEGIN_SB_EXIT,
    PressSB_MeasTune_Exit,
    DrawSB_Exit
);

// ��������� - ��������� ///////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsMeasTune =
{
    (void*)&sbExitMeasTune,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)&sbMeasTuneMarkers,
    (void*)&sbMeasTuneSettings
};

static const Page mspMeasTune
(
    &pMeasures, IsActiveButtonMeasuresTune,
    "���������", "CONFIGURE",
    "������� � ����� ������ ��������� ���������� � ����� ���������",
    "Transition to rezhm of exact control of quantity and types of measurements",
    Page_SB_MeasTuneMeas, &itemsMeasTune, EmptyFuncVV, EmptyFuncVV, Measure_RotateRegSet
);


// ��������� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const arrayItems itemsMeasures =
{
    (void*)&mcMeasuresIsShow,
    (void*)&mcMeasuresNumber,
    (void*)&mcMeasuresChannels,
    (void*)&mcMeasuresSignal,
    (void*)&mspMeasTune    
};

const Page pMeasures            ///< ���������
(
    &mainPage, 0,
    "���������", "MEASURES",
    "�������������� ���������",
    "Automatic measurements",
    Page_Measures, &itemsMeasures
);

void *PageMeasures::Tune::pointer = (void *)&mspMeasTune;

/** @}  @}
 */
