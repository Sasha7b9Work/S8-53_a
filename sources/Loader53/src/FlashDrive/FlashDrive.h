#pragma once
#include "defines.h"
#include "main.h"


void FDrive_Init(void);
bool FDrive_Update(void);
bool FDrive_FileExist(char *fileName);
int FDrive_OpenFileForRead(char *fileName);
/// ��������� �� ��������� ����� numBytes ����. ���������� ����� ������� ��������� ����
int FDrive_ReadFromFile(int numBytes, uint8 *buffer);
void FDrive_CloseOpenedFile(void);
