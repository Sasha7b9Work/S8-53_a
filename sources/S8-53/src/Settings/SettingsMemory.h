#pragma once
#include "defines.h"


/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsMemory
 *  @{
 */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ENUM_POINTS                 (set.memory.fpgaNumPoints)                      ///< SettingsMemory.fpgaNumPoints
#define ENUM_POINTS_IS_281          (ENUM_POINTS == FNP_281)
#define ENUM_POINTS_IS_1024         (ENUM_POINTS == FNP_1024)

#define MODE_WORK                   (set.memory.modeWork)                           ///< SettingsMemory.modeWork
#define MODE_WORK_IS_DIRECT         (MODE_WORK == ModeWork_Direct)
#define MODE_WORK_IS_LATEST         (MODE_WORK == ModeWork_Latest)
#define MODE_WORK_IS_MEMINT         (MODE_WORK == ModeWork_MemInt)

#define FILE_NAMING_MODE            (set.memory.fileNamingMode)                     ///< SettingsMemory.fileNamingMode
#define FILE_NAMING_MODE_IS_MASK    (FILE_NAMING_MODE == FileNamingMode_Mask)
#define FILE_NAMING_MODE_IS_HAND    (FILE_NAMING_MODE == FileNamingMode_Manually)

#define FILE_NAME_MASK              (set.memory.fileNameMask)                       ///< SettingsMemory.fileNameMask

#define FILE_NAME                   (set.memory.fileName)                           ///< SettingsMemory.fileName

#define INDEX_SYMBOL                (set.memory.indexCurSymbolNameMask)             ///< SettingsMemory.indexCurSymbolNameMask

#define MODE_SHOW_MEMINT            (set.memory.modeShowIntMem)                     ///< SettingsMemory.modeShowIntMem
#define MODE_SHOW_MEMINT_IS_SAVED   (MODE_SHOW_MEMINT == ModeShowIntMem_Saved)
#define MODE_SHOW_MEMINT_IS_DIRECT  (MODE_SHOW_MEMINT == ModeShowIntMem_Direct)

#define FLASH_AUTOCONNECT           (set.memory.flashAutoConnect)                   ///< SettingsMemory.flashAutoConnect

#define MODE_BTN_MEMORY             (set.memory.modeBtnMemory)                      ///< SettingsMemory.modeBtnMemory
#define MODE_BTN_MEMORY_IS_SAVE     (MODE_BTN_MEMORY == ModeBtnMemory_Save)

#define MODE_SAVE_SIGNAL            (set.memory.modeSaveSignal)                     ///< SettingsMemory.modeSaveSignal
#define MODE_SAVE_SIGNAL_IS_BMP     (MODE_SAVE_SIGNAL == ModeSaveSignal_BMP)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ����� ������.
typedef enum
{
    ModeWork_Direct,        ///< �������� �����.
    ModeWork_Latest,        ///< � ���� ������ ����� ����������� ��������� ���������� ���������.
    ModeWork_MemInt,        ///< � ���� ������ ����� ��������� �� flash-������ ��������� ������������� ����� ����������.
} ModeWork;


/// ����� ������������ ������.
typedef enum
{
    FileNamingMode_Mask,        ///< ��������� �� �����.
    FileNamingMode_Manually     ///< ��������� �������.
} FileNamingMode;

/// ��� ���������� � ������ ����� �� - ��������� ��� ���������� ������.
typedef enum
{
    ModeShowIntMem_Direct,  ///< ���������� ������ ��������� �������.
    ModeShowIntMem_Saved,   ///< ���������� ���������� ������.
    ModeShowIntMem_Both     ///< ���������� ������ ��������� ������� � ���������� ������.
} ModeShowIntMem;

/// ��� ������ ��� ������� ������ ������.
typedef enum
{
    ModeBtnMemory_Menu,     ///< ����� ������������ ��������������� �������� ����.
    ModeBtnMemory_Save      ///< ���������� ����������� ������ �� ������.
} ModeBtnMemory;

/// ��� ��������� ������ �� ������.
typedef enum
{
    ModeSaveSignal_BMP,     ///< ��������� ������ �� ������ � ������� .bmp.
    ModeSaveSignal_TXT      ///< ��������� ������ �� ������ � ���������� ����.
} ModeSaveSignal;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef  struct
{
    bool isActiveModeSelect;
} StructMemoryLast;

/// ��������� ����->������
typedef struct
{
#define MAX_SYMBOLS_IN_FILE_NAME 35
    ENUM_POINTS_FPGA    fpgaNumPoints;                          ///< ����� �����.
    ModeWork            modeWork;                               ///< ����� ������.
    FileNamingMode      fileNamingMode;                         ///< ����� ���������� ������.
    char                fileNameMask[MAX_SYMBOLS_IN_FILE_NAME]; ///< ����� ����� ��� ��������������� ���������� ������\n
         // ������� ����������.\n
         // %y('\x42') - ���, %m('\x43') - �����, %d('\x44') - ����, %H('\x45') - ����, %M('\x46') - ������, %S('\x47') - �������\n
         // %Nn('\x48''n') - ���������� �����, ������ �������� �� ����� n ���������, ��������, 7 � %3N ����� ������������� � 007\n
         // �������\n
         // name_%4N_%y_%m_%d_%H_%M_%S ����� ������������ ����� ���� name_0043_2014_04_25_14_45_32\n
         // ��� ���� �������� ��������, ��� ���� ������������ %4N ����� ����� ��������� ����������, ��, ������ �����, ���� �������� ����� ������ ����� 0001, �.�. ��� ����������� ������ ��������������� ������ ������� �� ����.
    char                fileName[MAX_SYMBOLS_IN_FILE_NAME];     ///< ��� ����� ��� ������ ������� �������
    int8                indexCurSymbolNameMask;                 ///< ������ �������� ������� � ������ ������� ����� ��� ������ �����.
    StructMemoryLast    strMemoryLast;
    ModeShowIntMem      modeShowIntMem;                         ///< ����� ������� ���������� � ������ ����������� ��
    bool                flashAutoConnect;                       ///< ���� true, ��� ���������� ���� ������������� ��������� NC (������ ���������)
    ModeBtnMemory       modeBtnMemory;
    ModeSaveSignal      modeSaveSignal;                         ///< � ����� ���� ��������� ������.
} SettingsMemory;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sMemory_GetNumPoints(bool forCalculate);

ENUM_POINTS_FPGA sMemory_IntNumPoints2FPGA_NUM_POINTS(int numPoints);


/** @}  @}
 */
