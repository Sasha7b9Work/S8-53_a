#pragma once


#include "defines.h"
#include "SettingsTypes.h"
#include "Panel/Controls.h"


// ��������� �����������
typedef struct
{
    int16               timeShowLevels;             // �����, � ������� �������� ����� ���������� ������ ��������
    int16               shiftInMemory;              // ���������� �������� ������ ���� ����� ������������ �������� ����� ������. ����� ��� ����������� ����������� ������� � ����.
    int16               timeMessages;               // ����� � ��������, �� ������� ��������� ������� �� ������
    int16               brightness;                 // ������� ������� (������ ��� ��������)
    int16               brightnessGrid;             // ������� ����� �� 0 �� 100
    uint16              colors[16];
    ModeDrawSignal      modeDrawSignal;             // ����� ��������� �������
    TypeGrid            typeGrid;                   // ��� �����
    NumAccumulation     numAccumulation;            // ����� ���������� ������� �� ������
    NumAveraging        numAve;                     // ����� ���������� �������
    ModeAveraging       modeAve;                    // ��� ���������� �� ����������
    NumMinMax           numMinMax;                  // ����� ��������� ��� ����������� ��������� � ����������
    DisplaySmoothing    smoothing;                  // ����� ����� ��� ����������� �������
    NumSignalsInSec     numSignalsInSec;            // ����� ���������� ������� � �������
    Channel             lastAffectedChannel;        // ����� �������� ����� ���������� ������, ������� ��������� �������. ����� ��� ����, ����� �����, ����� ������ �������� �������.
    ModeAccumulation    modeAccumulation;           // ����� ����� ���������� ��������
    AltMarkers          altMarkers;                 // ����� ����������� �������������� ������� �������� ��������
    MenuAutoHide        menuAutoHide;               // ����� ������� ������� ����� ���������� ������� ������� ������� ���� 
    bool                showFullMemoryWindow;       // ���������� �� ���� ������ ������ ������.
    bool                showStringNavigation;       // ���������� �� ������ �������� ��������� ����.
} SettingsDisplay;


// ��������� �������
typedef struct
{
    float           stretchADC;         	    // ����������� �����������.
    int16           rShiftRel;
    int16           rShiftAdd[RangeSize][2];    // ���������� �������� ��� ��������� (0) � ��������� (1) ������.
    ModeCouple      modeCouple;         	    // ����� �� �����.
    Multiplier      multiplier;         	    // ���������.
    Range           range;              	    // ������� �� ����������.
    bool            enable;             	    // ������� �� �����.
    bool            inverse;            	    // ������������ �� �����.
    bool            filtr;              	    // ������
    int8            balanceShiftADC;    	    // ���������� �������� ��� ������������ ���.
} SettingsChannel;


// ��������� �������������
typedef struct
{
    StartMode           startMode;          // ����� �������.
    TrigSource          source;             // ��������.
    TrigPolarity        polarity;           // ��� �������������.
    TrigInput           input;              // ���� �������������.
    int16               levelRel[3];        // ������� ������������� ��� ��� ����������.
    ModeLongPressTrig   modeLongPressTrig;  // ����� ������ ����������� ������� ������ �����.
    TrigModeFind        modeFind;           // ����� ������������� - ������� ��� �������������.
} SettingsTrig;


// ��������� ���������
typedef struct
{
    TBase           tBase;                  // ������� �� �������.
    int16           tShiftRel;              // �������� �� �������
    FunctionTime    timeDivXPos;
    TPos            tPos;
    SampleType      sampleType;
    PeackDetMode    peakDet;
    bool            selfRecorder;           // ������� �� ����� ���������.
    FPGA_NUM_POINTS oldNumPoints;           // ����� ������������� � ����� �������� ���������, ������������� ���������� ����� � 1024, � ���� ���������� ��, ��� ����, ����� ����� ������������
} SettingsTime;


// ��������� ��������
typedef struct
{
    CursCntrl           cntrlU[NumChannels];                    // �������� ������� ����������.
    CursCntrl           cntrlT[NumChannels];                    // �������� ������� ����������.
    Channel             source;                                 // �������� - � ������ ������ ��������� �������.
    float               posCurU[NumChannels][2];                // ������� ������� �������� ���������� ����� �������.
    float               posCurT[NumChannels][2];                // ������� ������� �������� ������� ����� �������.
    float               deltaU100percents[2];                   // ���������� ����� ��������� ���������� ��� 100%, ��� ����� �������.
    float               deltaT100percents[2];                   // ���������� ����� ��������� ������� ��� 100%, ��� ����� �������.
    CursMovement        movement;                               // ��� ������������ �������� - �� ������ ��� �� ���������.
    CursActive          active;                                 // ����� ������� ������ �������.
    CursLookMode        lookMode[2];                            // ������ �������� �� ��������� ��� ���� ��� ��������.
    bool                showFreq;                               // ������������� � true ��������, ��� ����� ���������� �� ������ �������� 1/dT ����� ���������.
    bool                showCursors;                            // ���������� �� �������
} SettingsCursors;

typedef  struct
{
    bool isActiveModeSelect;
} StructMemoryLast;

// ��������� ����->������
typedef struct
{
#define MAX_SYMBOLS_IN_FILE_NAME 35
    FPGA_NUM_POINTS fpgaNumPoints;              // ����� �����.
    ModeWork        modeWork;                   // ����� ������.
    FileNamingMode  fileNamingMode;             // ����� ���������� ������.
    char            fileNameMask[MAX_SYMBOLS_IN_FILE_NAME]; // ����� ����� ��� ��������������� ���������� ������\n
         // ������� ����������.\n
         // %y('\x42') - ���, %m('\x43') - �����, %d('\x44') - ����, %H('\x45') - ����, %M('\x46') - ������, %S('\x47') - �������\n
         // %Nn('\x48''n') - ���������� �����, ������ �������� �� ����� n ���������, ��������, 7 � %3N ����� ������������� � 007\n
         // �������\n
         // name_%4N_%y_%m_%d_%H_%M_%S ����� ������������ ����� ���� name_0043_2014_04_25_14_45_32\n
         // ��� ���� �������� ��������, ��� ���� ������������ %4N ����� ����� ��������� ����������, ��, ������ �����, ���� �������� ����� ������ ����� 0001, �.�. ��� ����������� ������ ��������������� ������ ������� �� ����.
    char            fileName[MAX_SYMBOLS_IN_FILE_NAME];     // ��� ����� ��� ������ ������� �������
    int8                indexCurSymbolNameMask; // ������ �������� ������� � ������ ������� ����� ��� ������ �����.
    StructMemoryLast    strMemoryLast;
    ModeShowIntMem      modeShowIntMem;         // ����� ������� ���������� � ������ ����������� ��
    bool                flashAutoConnect;       // ���� true, ��� ���������� ���� ������������� ��������� NC (������ ���������)
    ModeBtnMemory       modeBtnMemory;     
    ModeSaveSignal      modeSaveSignal;         // � ����� ���� ��������� ������.
} SettingsMemory;
                                    
typedef struct
{
    ScaleFFT        scaleFFT;
    SourceFFT       sourceFFT;
    WindowFFT       windowFFT;
    FFTmaxDB        fftMaxDB;
    Function        func;
    uint8           currentCursor;          // ����������, ����� �������� ������� ��������� ����� ���������
    uint8           posCur[2];              // ������� ������� �������. ���������� 0...256.
    int8            koeff1add;              // ����������� ��� ������ ��������� ��� ��������.
    int8            koeff2add;
    int8            koeff1mul;
    int8            koeff2mul;
    bool            enableFFT;
    ModeDrawMath    modeDraw;               // ���������� ��� ����� ������� � ������ �������������� �������
    ModeRegSet      modeRegSet;             // ������� ����� ��������� - ������� �� ������� ��� �������� �� ���������
    Range           range;
    Multiplier      multiplier;
    int16           rShift;
} SettingsMath;

// ��� ��������� �������� ����� ���� -> ������
typedef struct
{
    bool            screenWelcomeEnable;    // ����� �� ������������ ����� ����������� ��� ��������� �������.
    bool            soundEnable;            // �������� �� �����.
    CalibratorMode  calibrator;             // ����� ������ �����������.
    int8            IPaddress;              // IP-����� (��������)
    ColorScheme     colorScheme;            //
} SettingsService;

typedef struct
{
    uint8 mac0;
    uint8 mac1;
    uint8 mac2;
    uint8 mac3;
    uint8 mac4;
    uint8 mac5;

    uint8 ip0;
    uint8 ip1;
    uint8 ip2;
    uint8 ip3;

    uint16 port;

    uint8 mask0;
    uint8 mask1;
    uint8 mask2;
    uint8 mask3;

    uint8 gw0;
    uint8 gw1;
    uint8 gw2;
    uint8 gw3;

    bool enable;
} SettingsEthernet;
                                    
typedef struct
{
    int     countEnables;               // ���������� ���������. ������������� ��� ������ ���������
    int     countErasedFlashData;       // ������� ��� �������� ������ ������ � ���������
    int     countErasedFlashSettings;   // ������� ��� �������� ������ � ����������
    int     workingTimeInSecs;          // ����� ������ � ��������
    Language lang;                      // ���� ����
} SettingsCommon;

typedef struct
{
    bool    all;                                // ���������� �������� ���� ���������.
    bool    flag;                               // �������� �� ���� ����������.
    bool    rShift0;
    bool    rShift1;
    bool    trigLev;
    bool    range[2];
    bool    chanParam[2];
    bool    trigParam;
    bool    tShift;
    bool    tBase;
} OutputRegisters;


// ��������� ���������
typedef  struct
{
    int16           numStrings;                 // ����� ����� � �������.
    int8            sizeFont;                   // ������ ������ ������� - 0 - 5, 1 - 8,
    bool            consoleInPause;             // ������� ����, ��� ������� ��������� � ������ �����. ����� ����� ��������, ��� ����� ��������� ��� �� ���������� � �� ���������.
    BalanceADCtype  balanceADCtype;             // ��� ������������.
    int16           balanceADC[2];              // �������� ��������������� �������� ��� ��� ������ ������������.
    StretchADCtype  stretchADCtype;             // ��� �������� ������.
    int16           stretchADC[2];              // �������� �������� ������ ��� ������� ������.
    //RShiftADCtype   rShiftADCtype;
    //int16           rShiftADC[RangeSize][2];    // �������������� �������� ��� ������� � ������ ������� ����������. 0 - range == Range_2mV, 1 - ��� ���������
    int16           numMeasuresForGates;        // ����� ��������� ��� �����.
    int16           shiftT0;                    // �������������� �������� �� ������� ��� ������ �������� ������ �������������.
    bool            showStats;                  // ���������� ���������� �� ������ (fps, ��������).
    int16           numAveForRand;              // �� �������� ���������� ��������� ������ � ������ �������������.
    bool            viewAlteraWrittingData;     // ���������� �� ������, ������ � �������.
    bool            viewAllAlteraWrittingData;  // ���������� �� ��� ������, ������ � ������� (���� false, �� ��������� ������ ������� ����� START, STOP �� ������������).
    int16           altShift;                   // ���������� �������� ��� ���������� ������� �������������� ������ �������������.
    OutputRegisters showRegisters;
} SettingsDebug;

// �������� ������ ��� ��������� �������.
typedef struct
{
    SettingsDisplay     display;                    // ��������� �����������          (���� �������)
    SettingsTime        time;                       // ��������� ���������            (���� ���¨����)
    SettingsCursors     cursors;                    // ��������� ��������� ���������  (���� �������)
    SettingsMemory      memory;                     // ��������� ������� ������       (���� ������)
    SettingsMath        math;                       // ��������� ������ �������������� ���������
    SettingsService     service;                    // �������������� ���������       (���� ������)
    SettingsEthernet    eth;
    SettingsCommon      common;                     // ��������� ���������
    SettingsDebug       debug;                      // ��������� ������ �������       (���� �������)
    int temp;
} Settings;

extern Settings set;

void    Settings_Load(void);    // ��������� ���������
