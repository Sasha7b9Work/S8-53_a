#include "defines.h"
#include "Panel/Controls.h"
#include "Menu.h" 
#include "Settings/Settings.h"
#include "Pages/Definition.h"
#include "Pages/PageMemory.h"
#include "Display/DisplayTypes.h"
#include "MenuItems.h"
#include "Menu/Pages/PageMeasures.h"
#include "defines.h"
#include "MenuItemsLogic.h"
#include "Tables.h"
#include "Display/Display.h"
#include "Utils/GlobalFunctions.h"
#include "Utils/Measures.h"
#include "Utils/Math.h"
#include "Settings/Settings.h"
//#include "FPGA/DataStorage.h"
#include "Hardware/Timer.h"
#include "Log.h"
#include "FPGA/FPGA.h"
#include "Hardware/Hardware.h"
#include "Hardware/Sound.h"
#include "Panel/Panel.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void OnChanged_InputA(bool active);
extern void OnChanged_InputB(bool active);
                                                
/// ���� ��������� �������� ������� ������, �� ����� �������� ��� ���� ������ �� ��������� �����  �������.
static PanelButton shortPressureButton = B_Empty;
/// ���� ��������� ������� ������� ������, �� ����� �������� ��� ���� ������ �� ��������� ����� �������.
static PanelButton longPressureButton = B_Empty;
/// ��� ������� ������ � ��� ������������ � ��� ���������� � �������� ��� �� �������� ������� ������� ������.
static PanelButton pressButton = B_Empty;
/// ��� ���������� ������ � ��� ������������ � ��� ���������� � �������� ��� �� ���������  ������� ���������� ������.
static PanelButton releaseButton = B_Empty;
/// ����, �� ������� ����� ��������� ����� ��������� - �������� �������� ���������� �������, ���� - ����������� - "-" - �����, "+" - ������
static int angleRegSet = 0;

static const int stepAngleRegSet = 2;
/// ����� �������� ����� �������� ����, ���������������� �������������� ������� [1..5], ���� ��� ��������� � ������ ���������, � 0, ���� �� ���� 
/// ������ �� ������.
static void* itemUnderKey = 0;

#define SIZE_BUFFER_FOR_BUTTONS 5
static PanelButton bufferForButtons[SIZE_BUFFER_FOR_BUTTONS] = {B_Empty, B_Empty, B_Empty, B_Empty, B_Empty};
static const PanelButton sampleBufferForButtons[SIZE_BUFFER_FOR_BUTTONS] = {B_F5, B_F4, B_F3, B_F2, B_F1};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Menu::UpdateInput()
{
    ProcessingShortPressureButton();
    ProcessingLongPressureButton();
    ProcessingRegulatorSet();
    ProcessingPressButton();
    ProcessingReleaseButton();
    SwitchSetLED();
    
    if(NEED_OPEN_FILE_MANAGER)
    {
        NEED_OPEN_FILE_MANAGER = 0;
        OpenFileManager();       
    }
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPressureButton(PanelButton button)
{
    if (!SHOW_HELP_HINTS)
    {
        if(button == B_Help)
        {
            SHOW_HELP_HINTS++;
            gStringForHint = 0;
            gItemHint = 0;
        }
        shortPressureButton = button;
    }
};


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::LongPressureButton(PanelButton button)
{
    if (SHOW_HELP_HINTS == 0)
    {
        longPressureButton = button;
        Display::Redraw();
    }
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ProcessButtonForHint(PanelButton button)
{
    if (button == B_Menu)
    {
        gStringForHint = set.common.lang == Russian ?
            "������ ���� ��������� ��������� �������:\n"
            "1. ��� �������� ���� ������� ���� ������� � ���������� � ������� 0.5� ��������� ����.\n"
            "2. ��� �������� ���� ��������� ������ � ������� 0.5� ��������� ����.\n"
            "3. ��� ��������� \"������\x99����� �� ����\x99���������\" ������� ���������� �������� ����������� ������ ����. ���� ������� �������� �������� ��������, ���� �����������.\n"
            "4. ��� ��������� \"������\x99����� �� ����\x99�����������\" ������� ���������� �������� �������� ������ ����. ���� ������� �������� ��������� � ������� ������, ���������� ������� �� ���������� ������� ����.\n"
            "5. ���� ���� ��������� � ������ ����� ������, �� ������� ��������� ��������."
            :
        "MENU button performs the following functions:\n"
            "1. At the closed menu pressing or pressing with deduction during 0.5s opens the menu.\n"
            "2. At the open menu deduction of the button during 0.5s closes the menu.\n"
#pragma push
#pragma diag_suppress 192
            "3. At control \"SERVICE\x99Mode btn MENU\x99\x43lose\" current becomes the page of the previous level of the menu. If the root page is current, the menu is closed.\n"
#pragma pop
            "4. At control \"SERVICE\x99Mode btn MENU\x99Toggle\" current becomes the page of the current level of the menu. If the current page the last in the current level, happens transition to the previous level of the menu.\n"
            "5. If the menu is in the mode of small buttons, pressing closes the page.";

    } else if (button == B_Cursors)
    {
        gStringForHint = set.common.lang == Russian ? 
            "������ ������� ��������� ���� ��������� ���������."
            :
            "������� button to open the menu cursor measurements.";
    }
    else if (button == B_Display)
    {
        gStringForHint = set.common.lang == Russian ?
            "������ ������� ��������� ���� �������� �������."
            :
            "DISPLAY button opens the display settings menu.";
    }
    else if (button == B_Memory)
    {
        gStringForHint = set.common.lang == Russian ?
            "1. ��� ��������� \"������\x99����� ��\x99��� �� ������\x99����\" ��������� ���� ������ � �������.\n"
            "2. ��� ��������� \"������\x99����� ��\x99��� �� ������\x99����������\" ��������� ������ �� ����-����."
            :
            "1. When setting \"MEMORY-EXT\x99STORAGE\x99Mode btn MEMORY\x99Menu\" opens a menu of memory\n"
            "2. When setting \"MEMORY-EXT\x99STORAGE\x99Mode btn MEMORY\x99Save\" saves the signal to the flash drive";
    }
    else if (button == B_Measures)
    {
        gStringForHint = set.common.lang == Russian ?
            "������ ����� ��������� ���� �������������� ���������."
            :
            "����� button opens a menu of automatic measurements.";
    }
    else if (button == B_Help)
    {
        gStringForHint = set.common.lang == Russian ?
            "1. ������ ������ ��������� ���� ������.\n"
            "2. ������� � ��������� ������ ������ � ������� 0.5� �������� � ��������� ����� ������ ���������."
            :
            "1. ������ button opens the help menu.\n"
            "2. Pressing and holding the ������ for 0.5s enables and disables output mode hints.";
    }
    else if (button == B_Service)
    {
        gStringForHint = set.common.lang == Russian ?
            "������ ������ ��������� ���� ��������� ������������."
            :
            "������ button opens a menu of service options.";
    }
    else if (button == B_Start)
    {
        gStringForHint = set.common.lang == Russian ?
            "������ ����/�TO� ��������� � ������������� ������� ����� ����������."
            :
            "����/�TO� button starts and stops the process of gathering information.";
    }
    else if (button == B_Channel0)
    {
        gStringForHint = set.common.lang == Russian ?
            "1. ������ �����1 ��������� ���� �������� ������ 1.\n"
            "2. ������� � ��������� ������ �����1 � ������� 0.5� ������������� �������� ������ 1 �� ��������� 0�."
            :
            "1. �����1 button opens the settings menu of the channel 1.\n"
            "2. Pressing and holding the button �����1 for 0.5c for the offset of the vertical channel 1 0V.";
    }
    else if (button == B_Channel1)
    {
        gStringForHint = set.common.lang == Russian ?
            "1. ������ �����2 ��������� ���� �������� ������ 2.\n"
            "2. ������� � ��������� ������ �����2 � ������� 0.5� ������������� �������� ������ 2 �� ��������� 0�."
            :
            "1. �����2 button opens the settings menu of the channel 2.\n"
            "2. Pressing and holding the button �����2 for 0.5c for the offset of the vertical channel 2 0V.";
    }
    else if (button == B_Time)
    {
        gStringForHint = set.common.lang == Russian ?
            "1. ������ ���� ��������� ���� �������� ���������.\n"
            "2. ������� � ��������� ������ ���� � ������� 0.5� ������������� �������� �� ����������� 0�."
            :
            "1. ���� button open the settings menu sweep.\n"
            "2. Pressing and holding the button ���� for 0.5s Is the offset horizontal 0s.";
    }
    else if (button == B_Trig)
    {
        gStringForHint = set.common.lang == Russian ?
            "1. ������ ����� ��������� ���� �������� �������������.\n"
            "2. ������� � ��������� � ������� 0.5� ������ ����� ��� ��������� \"������\x99��� ���� �����\x99�����������\" ���������� �������������� ��������� ������ �������������.\n"
            "3. ������� � ��������� � ������� 0.5� ������ ����� ��� ��������� \"������\x99��� ���� �����\x99����� ������\" ������������� ������� ������������� 0�."
            :
            "1. ����� button opens a menu settings synchronization.\n"
#pragma push
#pragma diag_suppress 192
            "2. Pressing and holding the button ����� for 0.5s when setting \"SERVICE\x99Mode long TRIG\x99\x41utolevel\" automatically adjust the trigger level.\n"
#pragma pop
            "3. Pressing and holding the button ����� for 0.5s when setting \"SERVICE\x99Mode long TRIG\x99SReset trig level\" sets the trigger level 0V.";
    }
    else
    {
        shortPressureButton = button;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::PressButton(PanelButton button)
{
    Sound::ButtonPress();
    if (SHOW_HELP_HINTS)
    {
        ProcessButtonForHint(button);
        return;
    }

    if (pressButton == B_Start)
    {
        pressButton = button;
    } 
    else if (!MenuIsShown())
    {
        for (int i = SIZE_BUFFER_FOR_BUTTONS - 1; i > 0; i--)
        {
            bufferForButtons[i] = bufferForButtons[i - 1];
        }
        bufferForButtons[0] = button;
      
        if (memcmp(bufferForButtons, sampleBufferForButtons, SIZE_BUFFER_FOR_BUTTONS) == 0)
        {
            SHOW_DEBUG_MENU = 1;
            Display::ShowWarningGood(MenuDebugEnabled);
        }
    }
    pressButton = button;
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ReleaseButton(PanelButton button)
{
    Sound::ButtonRelease();
    if (SHOW_HELP_HINTS == 0)
    {
        releaseButton = button;
    }
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::RotateRegSetRight(void)
{   
    if (SHOW_HELP_HINTS == 0)
    {
        angleRegSet++;
        Display::Redraw();
    }
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::RotateRegSetLeft(void)
{
    if (SHOW_HELP_HINTS == 0)
    {
        angleRegSet--;
        Display::Redraw();
    }
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
void* Menu::ItemUnderKey(void)
{
    return itemUnderKey;
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::SetAutoHide(bool active)
{
    if(!MenuIsShown())
    {
        return;
    }
    if(sDisplay_TimeMenuAutoHide() == 0)
    {
        Timer::Disable(kMenuAutoHide);
    }
    else
    {
        Timer::Enable(kMenuAutoHide, sDisplay_TimeMenuAutoHide(), OnTimerAutoHide);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char* Menu::StringNavigation(char buffer[100])
{
    if(SHOW_STRING_NAVIGATION && MenuIsShown())
    {
        buffer[0] = 0;
        const char *titles[10] = {0};
        int numTitle = 0;
        void *item = OpenedItem();
        if(IsMainPage(item))
        {
            return 0;
        }
        while(!IsMainPage(item))
        {
            titles[numTitle++] = TitleItem(item);
            item = Keeper(item);
        }
        for(int i = 9; i >= 0; i--)
        {
            if(titles[i])
            {
                strcat(buffer, titles[i]);
                if(i != 0)
                {
                    strcat(buffer, " - ");
                }
            }
        }
        return buffer;
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnTimerAutoHide()
{
    ShowMenu(false);
    Timer::Disable(kMenuAutoHide);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ProcessingShortPressureButton()
{
    if(shortPressureButton != B_Empty)
    {
        if (shortPressureButton == B_Memory && MODE_BTN_MEMORY_IS_SAVE && FLASH_DRIVE_IS_CONNECTED == 1)
        {
            EXIT_FROM_SET_NAME_TO = MenuIsShown() ? RETURN_TO_MAIN_MENU : RETURN_TO_DISABLE_MENU;
            Memory_SaveSignalToFlashDrive();
            shortPressureButton = B_Empty;
            return;
        }
        Display::Redraw();
        Menu::SetAutoHide(true);

        PanelButton button = shortPressureButton;

        do
        {
            if(button == B_Menu)                                   // ���� ������ ������ ���� � �� �� ��������� � ����� ��������� ���������.
            {
                if(!MenuIsShown())
                {
                    ShowMenu(true);
                }
                else
                {
                    CloseOpenedItem();
                }
            }
            else if (MenuIsShown() && IsFunctionalButton(button))       // ���� ���� �������� � ������ �������������� �������
            {
                void *item = ItemUnderButton(button);
                if (SHOW_HELP_HINTS)
                {
                    SetItemForHint(item);
                }
                else
                {
                    ExecuteFuncForShortPressOnItem(item);
                }
            }
            else                                                        // ���� ���� �� ��������.
            {
                NamePage name = GetNamePage((const Page *)OpenedItem());
                if(button == B_Channel0 && name == Page_Channel0)
                {
                    SET_ENABLED_A = !sChannel_Enabled(A);
                    OnChanged_InputA(true);
                    break;
                }
                if(button == B_Channel1 && name == Page_Channel1)
                {
                    SET_ENABLED_B = !sChannel_Enabled(B);
                    OnChanged_InputB(true);
                    break;
                }

                const void *page = PageForButton(button);
                if(page)
                {
                    SetCurrentItem(page, true);
                    OpenItem(page, true);
                    ShowMenu(true);
                }
            }
        } while(false);

        shortPressureButton = B_Empty;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ProcessingLongPressureButton(void)
{
    if(longPressureButton != B_Empty)
    {
        Display::Redraw();
        Menu::SetAutoHide(true);

        if(longPressureButton == B_Time)
        {
            FPGA::SetTShift(0);
        }
        else if(longPressureButton == B_Trig)
        {
            FPGA::SetTrigLev(TRIG_SOURCE, TrigLevZero);
        }
        else if(longPressureButton == B_Channel0)
        {
            FPGA::SetRShift(A, RShiftZero);
        }
        else if(longPressureButton == B_Channel1)
        {
            FPGA::SetRShift(B, RShiftZero);
        }
        else if(longPressureButton == B_Menu)
        {
                ShowMenu(!MenuIsShown());
        }
        else if(MenuIsShown() && IsFunctionalButton(longPressureButton))
        {
            void *item = ItemUnderButton(longPressureButton);
            ExecuteFuncForLongPressureOnItem(item);
        }
        longPressureButton = B_Empty;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ProcessingRegulatorSet(void)
{
    if (angleRegSet == 0)
    {
        return;
    }

    if (MenuIsShown() || TypeMenuItem(OpenedItem()) != Item_Page)
    {
        void *item = CurrentItem();
        TypeItem type = TypeMenuItem(item);
        if (TypeMenuItem(OpenedItem()) == Item_Page && (type == Item_ChoiceReg || type == Item_Governor || type == Item_IP || type == Item_MAC))
        {
            if (angleRegSet > stepAngleRegSet || angleRegSet < -stepAngleRegSet)
            {
                ChangeItem(item, angleRegSet);
                angleRegSet = 0;
            }
            return;
        }
        else
        {
            item = OpenedItem();
            type = TypeMenuItem(item);
            if (MenuIsMinimize())
            {
                CurrentPageSBregSet(angleRegSet);
            }
            else if (type == Item_Page || type == Item_IP || type == Item_MAC || type == Item_Choice || type == Item_ChoiceReg || type == Item_Governor)
            {
                if (ChangeOpenedItem(item, angleRegSet))
                {
                    angleRegSet = 0;
                }
                return;
            }
            else if (type == Item_GovernorColor)
            {
                ChangeItem(item, angleRegSet);
            }
            else if (type == Item_Time)
            {
                angleRegSet > 0 ? ItemTime_IncCurrentPosition((Time *)item) : ItemTime_DecCurrentPosition((Time *)item);
            }
        }
    }

    angleRegSet = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ProcessingPressButton(void)
{
    if (pressButton == B_Start && !MODE_WORK_IS_LATEST)
    {
        FPGA::OnPressStartStop();
    } 
    else if((pressButton >= B_F1 && pressButton <= B_F5) || pressButton == B_Menu)
    {
        if (pressButton != B_Menu)
        {
            itemUnderKey = ItemUnderButton(pressButton);
        }
    }
    pressButton = B_Empty;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ProcessingReleaseButton(void)
{
    if(releaseButton >= B_F1 && releaseButton <= B_F5 || pressButton == B_Menu)
    {
        itemUnderKey = 0;
        releaseButton = B_Empty;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_Page(void *item)
{
    Page *page = (Page *)item;
    if (page->funcOnPress)
    {
        page->funcOnPress();
    }
    if (!ItemIsActive(page))
    {
        return;
    }
    SetCurrentItem(page, true);
    OpenItem((Page*)page, !ItemIsOpened((Page*)page));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_Choice(void *choice)
{
    if (!ItemIsActive(choice))
    {
        ((Choice *)choice)->FuncOnChanged(false);
    }
    else if (!ItemIsOpened(choice))
    {
        SetCurrentItem(choice, CurrentItem() != choice);       
        ((Choice *)choice)->StartChange(1);
    }
    else
    {
        ((Choice *)choice)->ChangeValue(-1);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_ChoiceReg(void *choice)
{
    if(!ItemIsActive(choice)) 
    {
        ((Choice *)choice)->FuncOnChanged(false);
    } 
    else if(OpenedItem() != choice) 
    {
        SetCurrentItem(choice, CurrentItem() != choice);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::FuncOnLongPressItemButton(void *button)
{
    ShortPress_Button(button);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_Button(void *button)
{
    if(!ItemIsActive(button))
    {
        return;
    }
    SetCurrentItem(button, true);
    ((Button*)button)->funcOnPress();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::FuncOnLongPressItem(void *item)
{
    if (CurrentItem() != item)
    {
        SetCurrentItem(item, true);
    }
    OpenItem(item, !ItemIsOpened(item));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::FuncOnLongPressItemTime(void *time)
{
    if (CurrentItem() != time)
    {
        SetCurrentItem(time, true);
    }
    if(ItemIsOpened(time) && *((Time*)time)->curField == iSET)
    {
        ItemTime_SetNewTime((Time *)time);
    }
    OpenItem(time, !ItemIsOpened(time));
    ItemTime_SetOpened((Time *)time);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_Time(void *time)
{
    if(!ItemIsOpened(time))
    {
        SetCurrentItem(time, true);
        ItemTime_SetOpened((Time *)time);
        OpenItem(time, true);
    }
    else
    {
        ItemTime_SelectNextPosition((Time *)time);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_Governor(void *governor)
{
    Governor *gov = (Governor*)governor;
    if(!ItemIsActive(governor))
    {
        return;
    }
    if(OpenedItem() == gov)
    {
        Governor_NextPosition(gov);
    }
    else
    {
        SetCurrentItem(gov, CurrentItem() != gov);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_IP(void *item)
{
    if (OpenedItem() == item)
    {
        IPaddress_NextPosition((IPaddress*)item);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_MAC(void *item)
{
    if (OpenedItem() == item)
    {
        CircleIncreaseInt8(&gCurDigit, 0, 5);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_GovernorColor(void *governorColor)
{
    if(!ItemIsActive(governorColor))
    {
        return;
    }
    GovernorColor *governor = (GovernorColor*)governorColor;
    if(OpenedItem() == governor)
    {
        CircleIncreaseInt8(&(governor->colorType->currentField), 0, 3);
    }
    else
    {
        FuncOnLongPressItem(governorColor);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_SmallButton(void *smallButton)
{
    SmallButton *sb = (SmallButton *)smallButton;
    if (sb)
    {
        pFuncVV func = sb->funcOnPress;
        if (func)
        {
            func();
            itemUnderKey = smallButton;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ExecuteFuncForShortPressOnItem(void *item)
{
    typedef void(*pFuncMenuVpV)(void*);

    static const pFuncMenuVpV shortFunction[Item_NumberItems] =
    {
        0,                                  // Item_None
        &Menu::ShortPress_Choice,           // Item_Choice
        &Menu::ShortPress_Button,           // Item_Button
        &Menu::ShortPress_Page,             // Item_Page
        &Menu::ShortPress_Governor,         // Item_Governor
        &Menu::ShortPress_Time,             // Item_Time
        &Menu::ShortPress_IP,               // Item_IP
        0,                                  // Item_SwitchButton
        &Menu::ShortPress_GovernorColor,    // Item_GovernorColor
        0,                                  // Item_Formula
        &Menu::ShortPress_MAC,              // Item_MAC
        &Menu::ShortPress_ChoiceReg,        // Item_ChoiceReg
        &Menu::ShortPress_SmallButton       // Item_SmallButton
    };
 
    pFuncMenuVpV func = shortFunction[TypeMenuItem(item)];

    if (func)
    {
        (func)(item);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ExecuteFuncForLongPressureOnItem(void *item)
{
    typedef void(*pFuncMenuVpV)(void*);

    static const pFuncMenuVpV longFunction[Item_NumberItems] =
    {
        0,                                  // Item_None
        &Menu::FuncOnLongPressItem,         // Item_Choice
        &Menu::FuncOnLongPressItemButton,   // Item_Button
        &Menu::FuncOnLongPressItem,         // Item_Page
        &Menu::FuncOnLongPressItem,         // Item_Governor
        &Menu::FuncOnLongPressItemTime,     // Item_Time
        &Menu::FuncOnLongPressItem,         // Item_IP
        0,                                  // Item_SwitchButton
        &Menu::FuncOnLongPressItem,         // Item_GovernorColor
        0,                                  // Item_Formula
        &Menu::FuncOnLongPressItem,         // Item_MAC
        &Menu::FuncOnLongPressItem,         // Item_ChoiceReg
        &Menu::ShortPress_SmallButton       // Item_SmallButton
    };

    if (ItemIsActive(item))
    {
        pFuncMenuVpV func = longFunction[TypeMenuItem(item)];
        if (func)
        {
            (func)(item);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ChangeStateFlashDrive()
{
    if(FLASH_DRIVE_IS_CONNECTED == 0)
    {
        if(GetNameOpenedPage() == Page_SB_FileManager)
        {
            ShortPressOnPageItem((Page *)OpenedItem(), 0);
        }
    }
    else if(FLASH_AUTOCONNECT)
    {
        NEED_OPEN_FILE_MANAGER = 1;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
extern const Page pService;

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OpenItemTime(void)
{
    Display::ShowWarningGood(TimeNotSet);
    Menu::ShortPressureButton(B_Service);
    Menu::UpdateInput();
    Display::Update();
    for (int i = 0; i < 2; i++)
    {
        Menu::RotateRegSetRight();
        Menu::UpdateInput();
        Display::Update();
    }
    Menu::ShortPressureButton(B_F4);
    Menu::UpdateInput();
    Display::Update();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Menu::NeedForFireSetLED()    // ���������� true, ���� �������� ��������� ������ ������
{
    if (!MenuIsShown())
    {
        return false;
    }
    NamePage name = GetNameOpenedPage();

    if (name == Page_SB_MeasTuneMeas && MEAS_NUM == MN_1 && !PageMeasures::choiceMeasuresIsActive)
    {
        return false;
    }

    if (
        name == Page_SB_MathCursorsFFT                          ||
        name == Page_SB_MeasTuneMeas                            ||
        name == Page_SB_MemLatest                               || 
        name == Page_SB_MemInt                                  ||
        (name == Page_SB_MathFunction && !DISABLED_DRAW_MATH)   ||
        name == Page_SB_Curs && sCursors_NecessaryDrawCursors()
        )
    {
        return true;
    }
    
    TypeItem typeCurrentItem = TypeMenuItem(CurrentItem());
    if (typeCurrentItem == Item_Governor    ||
        typeCurrentItem == Item_ChoiceReg)
    {
        return true;
    }

    TypeItem typeOpenedItem = TypeOpenedItem();
    if (typeOpenedItem == Item_Choice       ||
        (typeOpenedItem == Item_Page && NumSubPages((Page *)OpenedItem()) > 1)
        )
    {
        return true;
    }
    
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::SwitchSetLED(void)
{
    static bool first = true;
    static bool prevState = false;  // true - �����, false - �� �����

    bool state = NeedForFireSetLED();

    if (first)
    {
        first = false;
        Panel::EnableLEDRegSet(state);
        prevState = state;
    }
    else if (prevState != state)
    {
        Panel::EnableLEDRegSet(state);
        prevState = state;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OpenFileManager()
{
    angleRegSet = 0;
    for (int i = 0; i < 10; i++)
    {
        ShortPressureButton(B_Menu);
        UpdateInput();
        Display::Update(false);
    }

    if (!MenuIsShown())
    {
        ShortPressureButton(B_Menu);
        UpdateInput();
        Display::Update(false);
    }

    for (int i = 0; i < 5 * stepAngleRegSet + 1; i++)
    {
        RotateRegSetLeft();
        UpdateInput();
        Display::Update(false);
    }

    angleRegSet = 0;

    for (int i = 0; i < 2 * stepAngleRegSet + 1; i++)
    {
        RotateRegSetRight();
        UpdateInput();
        Display::Update(false);
    }

    angleRegSet = 0;

    ShortPressureButton(B_F2);
    UpdateInput();
    Display::Update(false);

    ShortPressureButton(B_F4);
    UpdateInput();
    Display::Update(false);

    for (int i = 0; i < stepAngleRegSet + 1; i++)
    {
        RotateRegSetLeft();
        UpdateInput();
        Display::Update(false);
    }

    for (int i = 0; i < 2; i++)
    {
        ShortPressureButton(B_F1);
        UpdateInput();
        Display::Update(false);
    }
}
