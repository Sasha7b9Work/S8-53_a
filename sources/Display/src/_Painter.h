#pragma once
#include "GenericTypeDefs.h"
#include "Graphics/Primitive.h"


/// ��������� ���� valueColor ����� ����� numColor
void Painter_SetPalette(BYTE numColor, SHORT valueColor);
/// ������������� ������� ���� ���������
void Painter_SetColor(BYTE numColor);
/// ������ ������������� ������� ������ ������
void Painter_FillRegion(SHORT x, SHORT y, SHORT width, SHORT height);
/// ������� ������ ������
void Painter_DrawText(SHORT x, SHORT y, UXCHAR *text);
///
void Painter_EndScene(void);
