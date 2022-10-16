#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "DisplayTypes.h"


/// ���������� ���� �������������.
Color ColorTrig(void);
/// ���� ��������� ��������, inShade - �������� �� ��������.
Color ColorMenuTitle(bool inShade);
/// ���� �������� ����.
Color ColorMenuItem(bool inShade);
/// ���� ��������� ����.
Color ColorBorderMenu(bool inShade);
/// ���������� ����, ����������� � color. ����� ���� ����� ��� ������.
Color ColorContrast(Color color);
/// ������� ���� � ����.
Color LightShadingTextColor(void);


#define ColorMenuField()            COLOR_MENU_FIELD
/// ���� ����� ������� ����, ��� ���� �������� ����. ������������ ��� �������� ������� ������.
#define ColorMenuItemLessBright()   COLOR_MENU_ITEM_DARK
/// ���� ����� ������� ����, ��� ���� ��������� ��������. ������������ ��� �������� ������� ������.
#define ColorMenuTitleBrighter()    COLOR_MENU_TITLE_BRIGHT
/// ���� ����� ������� ����, ��� ���� ��������� ��������. ������������ ��� �������� ������� ������.
#define ColorMenuTitleLessBright()  COLOR_MENU_TITLE_DARK
/// ���� ����� ������� ����, ��� ���� �������� ����. ������������ ��� �������� ������� ������.
#define ColorMenuItemBrighter()     COLOR_MENU_ITEM_BRIGHT
/// Ҹ���� ���� � ����.
#define DarkShadingTextColor()      COLOR_MENU_TITLE_DARK


typedef struct
{
    float   red;
    float   green;
    float   blue;
    float   stepRed;
    float   stepGreen;
    float   stepBlue;
    float   brightness;
    Color   color;
    int8    currentField;
    bool    alreadyUsed;
} ColorType;

/// ������� � ��� �������� �����.
void Color_Log(Color color);

void Color_BrightnessChange(ColorType *colorType, int delta);

void Color_SetBrightness(ColorType *colorType, float brightness);
/// ���� forced == false, �� ������������� ���������� ������ ��� ������ ������ �������
void Color_Init(ColorType *colorType, bool forced);

void Color_ComponentChange(ColorType *colorType, int delta);

const char* NameColorFromValue(uint16 colorValue);

const char* NameColor(Color color);

#define MAKE_COLOR(r, g, b) (((b) & 0x1f) + (((g) & 0x3f) << 5) + (((r) & 0x1f) << 11))
#define R_FROM_COLOR(color) (((uint16)(color) >> 11) & (uint16)0x1f)
#define G_FROM_COLOR(color) (((uint16)(color) >> 5) & (uint16)0x3f)
#define B_FROM_COLOR(color) ((uint16)(color) & 0x1f)

extern Color gColorFill;
extern Color gColorBack;
extern Color gColorGrid;
extern Color gColorChan[4];
