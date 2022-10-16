#include "defines.h"
#include "Colors.h"
#include "Painter.h"
#include "Hardware/Timer.h"
#include "Settings/Settings.h"
#include "Hardware/FSMC.h"
#include "Log.h"


static bool inverseColors = false;
static Color currentColor = NUM_COLORS;


static enum StateTransmit
{
    StateTransmit_Free,
    StateTransmit_NeedForTransmitFirst,  // ��� ����� ����� �������� ������ ���� - ���������� ������
    StateTransmit_NeedForTransmitSecond, // ��� ����� ����� �������� ������ � ����������� ����� - ������ �� ����������
    StateTransmit_InProcess
} stateTransmit = StateTransmit_Free;


void Painter_SendFrame(bool first)
{
    if (stateTransmit == StateTransmit_Free)
    {
        stateTransmit = (first ? StateTransmit_NeedForTransmitFirst : StateTransmit_NeedForTransmitSecond);
    }
}

void CalculateCurrentColor()
{
    if (currentColor == COLOR_FLASH_10)
    {
        Painter_SetColor(inverseColors ? COLOR_BACK : COLOR_FILL);
    }
    else if (currentColor == COLOR_FLASH_01)
    {
        Painter_SetColor(inverseColors ? COLOR_FILL : COLOR_BACK);
    }
}

void CalculateColor(uint8 *color)
{
    currentColor = (Color)*color;
    if (*color == COLOR_FLASH_10)
    {
        *color = inverseColors ? COLOR_BACK : COLOR_FILL;
    }
    else if (*color == COLOR_FLASH_01)
    {
        *color = inverseColors ? COLOR_FILL : COLOR_BACK;
    }
}

void InverseColor(Color *color)
{
    *color = (*color == COLOR_BLACK) ? COLOR_WHITE : COLOR_BLACK;
}

static void OnTimerFlashDisplay()
{
    inverseColors = !inverseColors;
}

void Painter_ResetFlash()
{
    Timer_Enable(kFlashDisplay, 400, OnTimerFlashDisplay);
    inverseColors = false;
}

void Painter_DrawRectangle(int x, int y, int width, int height)
{
    Painter_DrawHLine(y, x, x + width);
    Painter_DrawVLine(x, y, y + height);
    Painter_DrawHLine(y + height, x, x + width);
    if (x + width < SCREEN_WIDTH)
    {
        Painter_DrawVLine(x + width, y, y + height);
    }
}

void Painter_DrawDashedVLine(int x, int y0, int y1, int deltaFill, int deltaEmtpy, int deltaStart)
{
    if (deltaStart < 0 || deltaStart >= (deltaFill + deltaEmtpy))
    {
        LOG_ERROR("������������ �������� deltaStart = %d", deltaStart);
        return;
    }
    int y = y0;
    if (deltaStart != 0)                 // ���� ����� ����� �������� �� � ������ ������
    {
        y += (deltaFill + deltaEmtpy - deltaStart);
        if (deltaStart < deltaFill)     // ���� ������ ����� ���������� �� �����
        {
            Painter_DrawVLine(x, y0, y - 1);
        }
    }

    while (y < y1)
    {
        Painter_DrawVLine(x, y, y + deltaFill - 1);
        y += (deltaFill + deltaEmtpy);
    }
}

void Painter_DrawDashedHLine(int y, int x0, int x1, int deltaFill, int deltaEmpty, int deltaStart)
{
    if (deltaStart < 0 || deltaStart >= (deltaFill + deltaEmpty))
    {
        LOG_ERROR("������������ �������� deltaStart = %d", deltaStart);
        return;
    }
    int x = x0;
    if (deltaStart != 0)                // ���� ����� ����� �������� �� � ������ ������
    {
        x += (deltaFill + deltaEmpty - deltaStart);
        if (deltaStart < deltaFill)     // ���� ������ ����� ���������� �� �����
        {
            Painter_DrawHLine(y, x0, x - 1);
        }
    }

    while (x < x1)
    {
        Painter_DrawHLine(y, x, x + deltaFill - 1);
        x += (deltaFill + deltaEmpty);
    }
}


static int numberColorsUsed = 0;


void Painter_SendToVCP(uint8 *pointer, int size)
{
}

void Painter_SendToDisplay(uint8 *bytes, int numBytes)
{
    for (int i = 0; i < numBytes; i += 4)
    {
        while (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11) == GPIO_PIN_RESET) {};
        Timer_PauseOnTicks(31);
        *ADDR_CDISPLAY = *bytes++;
        *ADDR_CDISPLAY = *bytes++;
        *ADDR_CDISPLAY = *bytes++;
        *ADDR_CDISPLAY = *bytes++;
    }
}

static void Get4Bytes(uint8 bytes[4])
{
    while (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11) == GPIO_PIN_RESET) {};
    bytes[0] = *ADDR_CDISPLAY;
    bytes[1] = *ADDR_CDISPLAY;
    bytes[2] = *ADDR_CDISPLAY;
    bytes[3] = *ADDR_CDISPLAY;
}

void Painter_SetPalette(Color color)
{
    uint8 command[4];
    command[0] = SET_PALETTE;
    *(command + 1) = color;
    *((uint16*)(command + 2)) = set.display.colors[color];
    Painter_SendToDisplay(command, 4);
    Painter_SendToVCP(command, 4);
}

void Painter_SetColor(Color color)
{
    if (color != currentColor)
    {
        currentColor = color;
        if (currentColor > NUM_COLORS)
        {
            CalculateColor(&color);
        }
        uint8 command[4] = {SET_COLOR};
        command[1] = color;
        Painter_SendToDisplay(command, 4);
        Painter_SendToVCP(command, 2);
    }
}

void Painter_DrawHLine(int y, int x0, int x1)
{
    CalculateCurrentColor();
    uint8 command[8];
    command[0] = DRAW_HLINE;
    *(command + 1) = (int8)y;
    *((int16*)(command + 2)) = (int16)x0;
    *((int16*)(command + 4)) = (int16)x1;
    Painter_SendToDisplay(command, 8);
    Painter_SendToVCP(command, 6);
}

void Painter_DrawVLine(int x, int y0, int y1)
{
    CalculateCurrentColor();
    uint8 command[8];
    command[0] = DRAW_VLINE;
    *((int16*)(command + 1)) = (int16)x;
    *(command + 3) = (int8)y0;
    *(command + 4) = (int8)y1;
    Painter_SendToDisplay(command, 8);
    Painter_SendToVCP(command, 5);
}

void Painter_DrawVPointLine(int x, int y0, int y1, float delta, Color color)
{
    Painter_SetColor(color);
    int8 numPoints = (y1 - y0) / delta;
    uint8 command[6];
    command[0] = DRAW_VPOINT_LINE;
    *((int16*)(command + 1)) = (int16)x;
    *(command + 3) = y0;
    *(command + 4) = delta;
    *(command + 5) = numPoints;
    Painter_SendToDisplay(command, 6);
}


void Painter_DrawHPointLine(int y, int x0, int x1, float delta)
{
    for (int x = x0; x <= x1; x += delta)
    {
        Painter_SetPoint(x, y);
    }
}

void Painter_SetPoint(int x, int y)
{
    uint8 command[4];
    command[0] = SET_POINT;
    *((int16*)(command + 1)) = (int16)x;
    *(command + 3) = (int8)y;
    Painter_SendToDisplay(command, 4);
    Painter_SendToVCP(command, 4);
}

static void DrawMultiVPointLineColorEmulate(int numLines, int y, uint16 x[], int delta, int count, Color color)
{
    for (int i = 0; i < numLines; i++)
    {
        Painter_DrawVPointLine(x[i], y, y + count * delta, delta, color);
    }
}

void Painter_DrawMultiVPointLine(int numLines, int y, uint16 x[], int delta, int count, Color color) 
{
    /*
    BUG
    ���-�� � �������� ������� �������� ��� - ��� ��������� ������ ����� ��� ����������� ������
    � y > 66 ������� ������ � ������������� ��������
    */
    if(numLines > 20) 
    {
        LOG_ERROR("����� ����� ������� ������� %d", numLines);
        return;
    }

    if (y > 66) 
    {
        DrawMultiVPointLineColorEmulate(numLines, y, x, delta, count, color);
        return;
    }

    Painter_SetColor(color);
    uint8 command[60];
    command[0] = DRAW_MULTI_VPOINT_LINES;
    *(command + 1) = numLines;
    *(command + 2) = y;
    *(command + 3) = count;
    *(command + 4) = delta;
    *(command + 5) = 0;
    uint8 *pointer = command + 6;
    for(int i = 0; i < numLines; i++) 
    {
        *((uint16*)pointer) = x[i];
        pointer += 2;
    }
    int numBytes = 1 + 1 + 1 + numLines * 2 + 1 + 1;
    while(numBytes % 4) 
    {
        numBytes++;
    }
    Painter_SendToDisplay(command, numBytes);
    Painter_SendToVCP(command, 1 + 1 + 1 + 1 + 1 + 1 + numLines * 2);
}

void Painter_DrawMultiHPointLine(int numLines, int x, uint8 y[], int delta, int count, Color color)
{
    if (numLines > 20)
    {
        LOG_ERROR("����� ����� ������� ������� %d", numLines);
        return;
    }
    Painter_SetColor(color);
    uint8 command[30];
    command[0] = DRAW_MULTI_HPOINT_LINES_2;
    *(command + 1) = numLines;
    *((uint16*)(command + 2)) = x;
    *(command + 4) = count;
    *(command + 5) = delta;
    uint8 *pointer = command + 6;
    for (int i = 0; i < numLines; i++)
    {
        *pointer = y[i];
        pointer++;
    }
    int numBytes = 1 +     // command
        1 +     // numLines
        2 +     // x
        numLines +    // numLines
        1 +
        1;
    while (numBytes % 4)
    {
        numBytes++;
    }
    Painter_SendToDisplay(command, numBytes);
    Painter_SendToVCP(command, 1 + 1 + 2 + 1 + 1 + numLines);
}

void Painter_DrawLine(int x0, int y0, int x1, int y1)
{
    if (x0 == x1)
    {
        Painter_DrawVLine(x0, y0, y1);
    }
    else if (y0 == y1)
    {
        Painter_DrawHLine(y0, x0, x1);
    }
}

void Painter_FillRegion(int x, int y, int width, int height)
{
    CalculateCurrentColor();
    uint8 command[8];
    command[0] = FILL_REGION;
    *((int16*)(command + 1)) = (int16)x;
    *(command + 3) = (int8)y;
    *((int16*)(command + 4)) = (int16)width;
    *(command + 6) = (int8)height;
    Painter_SendToDisplay(command, 8);
    Painter_SendToVCP(command, 7);
}

void Painter_DrawVolumeButton(int x, int y, int width, int height, int thickness, Color normal, Color bright, Color dark, bool isPressed, bool inShade)
{
    if (inShade)
    {
        thickness = 1;
    }
    Painter_FillRegionC(x + thickness, y + thickness, width - thickness * 2, height - thickness * 2, normal);
    if (isPressed || inShade)
    {
        for (int i = 0; i < thickness; i++)
        {
            Painter_DrawHLineC(y + i, x + i, x + width - i, dark);
            Painter_DrawVLine(x + i, y + 1 + i, y + height - i);
            Painter_DrawVLineC(x + width - i, y + 1 + i, y + height - i, bright);
            Painter_DrawHLine(y + height - i, x + 1 + i, x + width - i);
        }
    }
    else
    {
        for (int i = 0; i < thickness; i++)
        {
            Painter_DrawHLineC(y + i, x + i, x + width - i, bright);
            Painter_DrawVLine(x + i, y + 1 + i, y + height - i);
            Painter_DrawVLineC(x + width - i, y + 1 + i, y + height - i, dark);
            Painter_DrawHLine(y + height - i, x + 1 + i, x + width - i);
        }
    }
}

void Painter_SetBrightnessDisplay(int16 brightness)
{
    float recValue = 1601.0f;
    if (brightness < 100)
    {
        recValue = 64.0f + (600.0f - 63.0f) / 100.0f / 100.0f * brightness * brightness;
    }
    uint8 command[4];
    command[0] = SET_BRIGHTNESS;
    *((uint16*)(command + 1)) = (uint16)recValue;
    Painter_SendToDisplay(command, 4);
}

int NumberColorsInSceneCol()
{
    return numberColorsUsed;
}

void Painter_DrawVLineArray(int x, int numLines, uint8 *y0y1, Color color)
{
    Painter_SetColor(color);
    uint8 command[255 * 2 + 4 + 4];
    command[0] = DRAW_VLINES_ARRAY;
    *((int16*)(command + 1)) = (int16)x;
    if (numLines > 255)
    {
        numLines = 255;
    }
    *(command + 3) = numLines;
    for (int i = 0; i < numLines; i++)
    {
        *(command + 4 + i * 2) = *(y0y1 + i * 2);
        *(command + 4 + i * 2 + 1) = *(y0y1 + i * 2 + 1);
    }
    int numBytes = numLines * 2 + 4;
    while (numBytes % 4)
    {
        numBytes++;
    }
    Painter_SendToDisplay(command, numBytes);
    Painter_SendToVCP(command, 1 + 2 + 1 + 2 * numLines);
}

void Painter_DrawSignal(int x, uint8 data[281], bool modeLines)
{
    uint8 command[284];
    command[0] = modeLines ? DRAW_SIGNAL_LINES : DRAW_SIGNAL_POINTS;
    *((int16*)(command + 1)) = (int16)x;
    for (int i = 0; i < 281; i++)
    {
        *(command + 3 + i) = data[i];
    }
    Painter_SendToDisplay(command, 284);
    Painter_SendToVCP(command, 284);
}

void Painter_LoadPalette()
{
    for (int i = 0; i < NUM_COLORS; i++)
    {
        Painter_SetPalette((Color)i);
    }
}

void Painter_BeginScene(Color color)
{
    if (stateTransmit == StateTransmit_NeedForTransmitFirst || stateTransmit == StateTransmit_NeedForTransmitSecond)
    {
        bool needForLoadFontsAndPalette = stateTransmit == StateTransmit_NeedForTransmitFirst;
        stateTransmit = StateTransmit_InProcess;
        if(needForLoadFontsAndPalette) 
        {
            Painter_LoadPalette();
        }
    }

    Painter_FillRegionC(0, 0, 319, 239, color);
}

static void Painter_RunDisplay(void)
{
    uint8 command[4];
    command[0] = RUN_BUFFER;
    Painter_SendToDisplay(command, 4);
}

void Painter_EndScene()
{
    if (gBF.framesElapsed != 1)
    {
        gBF.framesElapsed = 1;
        return;
    }
    uint8 command[4];
    command[0] = END_SCENE;
    Painter_SendToDisplay(command, 4);
    Painter_SendToVCP(command, 1);
    if (stateTransmit == StateTransmit_InProcess)
    {
        stateTransmit = StateTransmit_Free;
    }

    Painter_RunDisplay();
}

Color GetColor(int x, int y)
{
    uint8 command[4];
    command[0] = GET_POINT;
    *((int16*)(command + 1)) = (int16)x;
    *(command + 3) = (int8)y;
    Painter_SendToDisplay(command, 4);

    Get4Bytes(command);

    return (Color)(command[0] & 0x0f);
}

void Get8Points(int x, int y, uint8 buffer[4])
{
    uint8 command[4];
    command[0] = GET_POINT;
    *((int16*)(command + 1)) = (int16)x;
    *(command + 3) = (int8)y;
    Painter_SendToDisplay(command, 4);
    Get4Bytes(buffer);
}

uint8 Get2Points(int x, int y)
{
    while (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11) == GPIO_PIN_RESET) {};
    *ADDR_CDISPLAY = GET_POINT;
    *ADDR_CDISPLAY = (uint8)x;
    *ADDR_CDISPLAY = (uint8)(x >> 8);
    *ADDR_CDISPLAY = (uint8)y;
    while (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11) == GPIO_PIN_RESET) {};
    return *ADDR_CDISPLAY;
}

void Painter_DrawPicture(int x, int y, int width, int height, uint8 *address)
{
    uint8 command[4];
    command[0] = DRAW_PICTURE;
    *((uint16*)(command + 1)) = x;
    *(command + 3) = y;
    Painter_SendToDisplay(command, 4);
    *((uint16*)(command)) = width;
    *(command + 2) = height;
    *(command + 3) = 0;
    Painter_SendToDisplay(command, 4);
    for (int i = 0; i < width * height / 2 / 4; i++)
    {
        *(command) = *address++;
        *(command + 1) = *address++;
        *(command + 2) = *address++;
        *(command + 3) = *address++;
        Painter_SendToDisplay(command, 4);
    }
}

uint16 Painter_ReduceBrightness(uint16 colorValue, float newBrightness)
{
    return 0;
}

bool Painter_SaveScreenToFlashDrive()
{    
    return true;
}

