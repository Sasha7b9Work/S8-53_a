#pragma once

#include "config.h"
#include <stm32f2xx_hal.h>


#ifdef WIN32

#define CRC asdfasdf

#endif

#define SER_NUM "09 2015"
#define NUM_VER "1.0_N1"


typedef signed      char        int8;
typedef signed      char        int8_t;
typedef signed      short   int int16;
typedef unsigned    char        uint8;
typedef unsigned    char        uint8_t;
typedef unsigned    short   int uint16;
typedef unsigned    short   int uint16_t;
typedef unsigned    int         uint;
typedef unsigned long long int  uint64;
typedef unsigned    int         uint32_t;
typedef unsigned    char        uchar;

#ifndef bool
typedef uint8   bool;
#define false   0
#define true    (!false)
#endif


// ��� �����
typedef enum
{
    COLOR_BLACK             = 0x00,
    COLOR_WHITE             = 0x01,
    COLOR_GRID              = 0x02,
    COLOR_DATA_A            = 0x03,
    COLOR_DATA_B            = 0x04,
    COLOR_MENU_FIELD        = 0x05,
    COLOR_MENU_TITLE        = 0x06,
    COLOR_MENU_TITLE_DARK   = 0x07,
    COLOR_MENU_TITLE_BRIGHT = 0x08,
    COLOR_MENU_ITEM         = 0x09,
    COLOR_MENU_ITEM_DARK    = 0x0a,
    COLOR_MENU_ITEM_BRIGHT  = 0x0b,
    COLOR_MENU_SHADOW       = 0x0c,
    COLOR_EMPTY             = 0x0d,
    COLOR_CURSORS_A         = 0x0e,
    COLOR_CURSORS_B         = 0x0f,
    NUM_COLORS,
    COLOR_FLASH_10,
    COLOR_FLASH_01,
    INVERSE
} Color;


#define DEBUG


#define __IO volatile

typedef void    (*pFuncVV)(void);               // ��������� �� �������, ������ �� ����������� � ������ �� ������������.
typedef void    (*pFuncVpV)(void*);             // ��������� �� �������, ����������� ��������� �� void � ������ �� ������������.
typedef bool    (*pFuncBV)(void);
typedef void    (*pFuncVB)(bool);
typedef void    (*pFuncVI)(int);
typedef void    (*pFuncVII)(int, int);
typedef void    (*pFuncVIIC)(int, int, Color);
typedef void    (*pFuncVI16)(int16);
typedef bool    (*pFuncBU8)(uint8);
typedef void    (*pFuncVI16pI16pI16)(int16, int16*, int16*);
typedef float   (*pFuncFU8)(uint8);
typedef char*   (*pFuncCFB)(float, bool);
typedef char*   (*pFuncCFBC)(float, bool, char*);
typedef void    (*pFuncpU8)(uint8*);
typedef void    (*pFuncVpVIIB)(void*, int, int, bool);

#define _GET_BIT(value, bit) (((value) >> bit) & 0x01)
#define _SET_BIT(value, bit) ((value) |= (1 << bit))
#define _CLEAR_BIT(value, bit) ((value) &= (~(1 << bit)))

// ����������� �������� 32 ����
typedef union
{
    uint  word;
    uint8 byte[4]; //-V112
} BitSet32;

// ����������� �������� 64 ����
typedef union
{
    long long unsigned int  dword;
    unsigned int            word[2];
} BitSet64;

typedef struct
{
    int16 rel;
    float abs;
} StructRelAbs;

#define _bitset(bits)                               \
  ((uint8)(                                         \
  (((uint8)((uint)bits / 01)        % 010) << 0) |  \
  (((uint8)((uint)bits / 010)       % 010) << 1) |  \
  (((uint8)((uint)bits / 0100)      % 010) << 2) |  \
  (((uint8)((uint)bits / 01000)     % 010) << 3) |  \
  (((uint8)((uint)bits / 010000)    % 010) << 4) |  \
  (((uint8)((uint)bits / 0100000)   % 010) << 5) |  \
  (((uint8)((uint)bits / 01000000)  % 010) << 6) |  \
  (((uint8)((uint)bits / 010000000) % 010) << 7)))

#define BINARY_U8( bits ) _bitset(0##bits)

#define DISABLE_RU  "����"
#define DISABLE_EN  "Disable"
#define ENABLE_RU   "���"
#define ENABLE_EN   "Enable"

#define ERROR_VALUE_FLOAT   1.111e29f
#define ERROR_VALUE_INT16   SHRT_MAX
#define ERROR_VALUE_UINT8   255
#define ERROR_VALUE_INT     INT_MAX
#define ERROR_STRING_VALUE  "--.--"
#define M_PI                3.14159265358979323846

#define HARDWARE_ERROR HardwareErrorHandler(__FILE__, __FUNCTION__, __LINE__);
void HardwareErrorHandler(const char *file, const char *function, int line);

#include "Globals.h"
