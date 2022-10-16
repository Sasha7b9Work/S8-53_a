#pragma once
#include "Panel/Controls.h"
#include "MenuItems.h"


/** @defgroup Menu
 *  @{
 */


class Menu
{
public:
    /// ���������� ����� �������� ����, ���������������� ������ button.
    static void* ItemUnderButton(PanelButton button);
    /// ���������� true, ���� ������� ���� item ������ (��������� �� �� ����� ������� ����. ��� �������, ��� ��������, ��� ������� �������������� ������� ���� ����� Choice ��� Governor.
    static bool IsShade(void* item);

    static bool IsPressed(void* item);

    static void Draw();
    /// ������� ������ ���������� � ������� �����.
    static void UpdateInput();
    /// ������� ��������� ��������� ������� ������ (����� 0.5 ���.).
    static void ShortPressureButton(PanelButton button);
    /// ������� ��������� �������� ������� ������ (����� 0.5 ���.).
    static void LongPressureButton(PanelButton button);
    /// ������� ����������, ����� ������ ��������� �� �������� � ������� ���������.
    static void PressButton(PanelButton button);
    /// ������� ����������, ����� ������ ��������� �� �������� � ������� ���������.
    static void ReleaseButton(PanelButton button);
    /// ������� ��������� �������� ����� ��������� ������.
    static void RotateRegSetRight();
    /// ������� ��������� �������� ����� ��������� �����.
    static void RotateRegSetLeft();
    /// ���������� ����� ��������������� �������� ���� � ������������ � �����������.
    static void SetAutoHide(bool active);
    /// ���������� ����� ������ ����, ������������ ��� ������� � ������ ������ �������.
    static void *ItemUnderKey();
    /// ���������� ���� � �������� ������ ���� � ��������� ����, ������� � ������ �� �����.
    static char *StringNavigation(char buffer[100]);

    static void OpenItemTime();
    /// ���������� true, ���� ������� ���� item �������� �������, �.�. ����� ���� �����.
    static bool ItemIsActive(void *item);
    /// ���������� ���������� ��������� � �������� �� ������ page.
    static int NumItemsInPage(const Page * const page);
    /// ���������� ����� ������� ���������� �������� �� ������ page.
    static int NumCurrentSubPage(Page *page);
    /// D��������� ����� ���������� � �������� �� ������ page.
    static int NumSubPages(const Page *page);
    /// ���������� ��� �������� ���� �� ������ address.
    static TypeItem TypeMenuItem(void *address);
    /// ���������� ��� ��������� �������� ����.
    static TypeItem TypeOpenedItem();
    /// ���������� ����� ��������� �������� ����.
    static void *OpenedItem();
    /// ���������� ����� �������� �������� ���� (�������, ��� �������, �������� �������, ������ �������� ���� ������ ���������.
    static void *CurrentItem();
    /// ���������� ����� �������� ���� �������� ��������.
    static void *Item(const Page *page, int numElement);
    /// ���������� true, ���� ������� ������� �������� � ������ namePage ������.
    static bool CurrentItemIsOpened(NamePage namePage);
    /// ���������� ������� �������� �������� ������� page.
    static int8 PosCurrentItem(const Page *page);
    /// �������/��������� ������� ����� ��������.
    static void SetCurrentItem(const void *item, bool active);
    /// ���������� ����� ��������, �������� ����������� ������� �� ������ item.
    static Page* Keeper(const void *item);
    /// ���������� ��� �������� page.
    static NamePage GetNamePage(const Page *page);

    static NamePage GetNameOpenedPage();

    static void OpenPageAndSetItCurrent(void *page);

    static bool ChangeOpenedItem(void *item, int delta);
    /// ��������� ��� ����������� �������� Governor, GovernorColor ��� Choice �� ������ item � ����������� �� ����� delta
    static void ChangeItem(void *item, int delta);
    /// ���������� ������ � �������� ��������� �������� Choice ��� NamePage �� ������ item.
    static int HeightOpenedItem(void *item);
    /// ���������� �������� �������� �� ������ item, ��� ��� �������� �� ������� �������.
    static const char* TitleItem(void *item);
    /// ���������� ������� ������� �������� �������� �� ������ page �� ������. ���� ������� ����������� 0, ��� ����� 0, ���� ������� ����������� 1, ��� ����� 5 � �.�.
    static int PosItemOnTop(Page *page);
    /// ���������� true, ���� button - �������������� ������� [1..5].
    static bool IsFunctionalButton(PanelButton button);
    /// ������� �������� ������� ����.
    static void CloseOpenedItem();

    static void OpenItem(const void *item, bool open);          // �������/������� ������� ���� �� ������ item.

    static bool ItemIsOpened(void *item);                       // ���������� true, ���� ������� ���� �� ������ item ������.

    static void ChangeSubPage(const Page *page, int delta);

    static void ShortPressOnPageItem(Page *page, int numItem);   // �������� ������� ��������� ������� ������ ��� ������ numItem �������� page;

    static Page *PagePointerFromName(NamePage namePage);

    static bool PageIsSB(const Page *page);

    static SmallButton *SmallButonFromPage(Page *page, int numButton);

    static void ChangeStateFlashDrive();

private:
    /// ��������� ��������� ������� ������.
    static void ProcessingShortPressureButton();
    /// ��������� �������� ������� ������.
    static void ProcessingLongPressureButton();
    /// ��������� ��������� ������ ����.
    static void ProcessingPressButton();
    /// ��������� �������� ������ �����.
    static void ProcessingReleaseButton();
    /// ��������� �������� ����� ���������.
    static void ProcessingRegulatorSet();
    /// ��������/��������� ��������� ����� ���������, ���� ����������.
    static void SwitchSetLED();
    /// ��������� ��������� ������� �� ������� NamePage � ������� page.
    static void ShortPress_Page(void *page);
    /// ��������� ��������� ������� �� ������� Choice � ������� choice.
    static void ShortPress_Choice(void *choice);

    static void ShortPress_Time(void *time);
    /// ��������� ��������� ������� �� ������� Button � ������� button.
    static void ShortPress_Button(void *button);
    /// ��������� ��������� ������� �� ������� Governor � ������� governor.
    static void ShortPress_Governor(void *governor);
    /// ��������� ��������� ������� �� ������� GovernorColor � ������� governorColor.
    static void ShortPress_GovernorColor(void *governorColor);

    static void ShortPress_IP(void *item);

    static void ShortPress_MAC(void *item);

    static void ShortPress_ChoiceReg(void *choice);

    static void ShortPress_SmallButton(void *smallButton);
    /// ��������� �������� ������� �� ������� ���� item.
    static void FuncOnLongPressItem(void *item);

    static void FuncOnLongPressItemTime(void *item);
    /// ��������� �������� ������� �� ������� Button � ������� button.
    static void FuncOnLongPressItemButton(void *button);
    /// ���������� ������� ��������� ��������� ������� �� ������� ���� item.
    static void ExecuteFuncForShortPressOnItem(void *item);
    /// ���������� ������� ��������� �������� ������� �� ������� ���� item.
    static void ExecuteFuncForLongPressureOnItem(void *item);

    static bool NeedForFireSetLED();

    static void DrawOpenedPage(Page *page, int layer, int yTop);

    static void DrawTitlePage(Page *page, int layer, int yTop);

    static void DrawItemsPage(Page *page, int layer, int yTop);

    static void DrawPagesUGO(Page *page, int right, int bottom);

    static int CalculateX(int layer);

    static void ResetItemsUnderButton();

    static int ItemOpenedPosY(void *item);

    static void *RetLastOpened(Page *_page, TypeItem *_type);
    
    static void OpenFileManager();
    /// ��������� ������� ������� ��������������� �������� ����.
    static void OnTimerAutoHide();
    
    static void ProcessButtonForHint(PanelButton button);
};

/** @}
 */
