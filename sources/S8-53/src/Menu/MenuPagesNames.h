#pragma once

// ����� ID ���� �������������� � ���� �������
typedef enum
{
    Page_Display,               // ������
    Page_DisplayAccumulation,   // ������� - ����������
    Page_DisplayAverage,        // ������� - ����������
    Page_DisplayGrid,           // ������� - �����
    Page_DisplayRefresh,        // ������� - ����������
    Page_MainPage,              // ������� �������� ����. �� �� ������ ��� ���������
    Page_Debug,                 // �������
    Page_DebugConsole,          // ������� - �������
    Page_DebugADC,              // ������� - ���
    Page_DebugADCbalance,       // ������� - ��� - ������
    Page_DebugADCstretch,       // ������� - ��� - ��������
    Page_DebugADCrShift,        // ������� - ��� - ���. ��������
    Page_DebugADCaltShift,      // ������� - ��� - ���. ����. ���.
    Page_DebugShowRegisters,    // ������� - ��������
    Page_DebugRandomizer,       // ������� - ����-���
    Page_DebugInformation,      // ������� - ����������
    Page_DebugSound,            // ������� - ����
    Page_DebugAltera,           // ������� - �������
    Page_Channel0,              // ����� 1
    Page_Channel1,              // ����� 2
    Page_Cursors,               // �������
    Page_Trig,                  // �����.
    Page_Memory,                // ������
    Page_MemoryExt,             // ������ - �����. ��
    Page_Measures,              // ���������
    Page_MeasuresField,         // ��������� - ����
    Page_Service,               // ������
    Page_ServiceDisplay,        // ������ - �������
    Page_ServiceDisplayColors,  // ������ - ������� - �����
    Page_ServiceCalibrator,     // ������ - ����������
    Page_ServiceEthernet,       // ������ - ETHERNET
    Page_Help,                  // ������
    Page_Time,                  // ���������
    Page_Math,                  // ������ - ����������
    Page_MathFFT,
    Page_TrigAuto,              // ����� - ��� �����
    Page_SB_Curs,               // ������� �������� ������� - ���������
    Page_SB_MeasTuneMeas,       // ������� �������� ��������� - ���������
    Page_SB_MeasTuneField,      // ������� �������� ��������� - ���� - ������
    Page_SB_MemLatest,          // ������� �������� ������ - ���������
    Page_SB_MemInt,             // ������� �������� ������ - ����� ��
    Page_SB_MemExtSetMask,      // ������� �������� ������ - ����� �� - �����
    Page_SB_MemExtSetName,      // ���������� ����� ����������� ����� �� ������ ��� ������� ����� ����� ��� ��������������� ����� ����� �� - ��� �����
    Page_SB_FileManager,        // ������� �������� ������ - ����� �� - �����
    Page_SB_Help,               // ������� �������� HELP
    Page_SB_MathCursorsFFT,     // ������� �������� ������ - ���������� - �������
    Page_SB_MathFunction,       // ������ - ���������� - �������
    Page_SB_Information,        // ������ - ����������
    Page_SB_SerialNumber,       // ������ - �/�
    Page_NumPages,
    Page_NoPage
} NamePage;             // ��� ���������� ������� ����� �������� ������������� SettingsMenu � SSettings.c
