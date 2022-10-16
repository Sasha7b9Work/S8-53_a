#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsService
 *  @{
 */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SOUND_ENABLED       (set.service.soundEnabled)          ///< SettingsService.soundEnabled

#define CALIBRATOR          (set.service.calibrator)            ///< SettingsService.calibrator
#define CALIBRATOR_IS_FREQ  (CALIBRATOR == Calibrator_Freq)
#define CALIBRATOR_IS_DC    (CALIBRATOR == Calibrator_DC)

#define IP_ADDRESS          (set.service.IPaddress)             ///< SettingsService.IPaddress

#define COLOR_SCHEME                    (set.service.colorScheme)
#define IS_COLOR_SCHEME_WHITE_LETTERS   (COLOR_SCHEME == ColorScheme_WhiteLetters)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ����� ������ �����������.
typedef enum
{
    Calibrator_Freq,            ///< �� ������ ����������� 4�, 1���.
    Calibrator_DC,              ///< �� ������ ����������� 4� ����������� ����������.
    Calibrator_GND              ///< �� ������ ����������� 0�.
} CalibratorMode;

/// �������� �����
typedef enum
{
    ColorScheme_WhiteLetters,   ///< � ���� ������ ��������� ��������� ���� ������� ����� - �� ����� ������ ����� �����.
    ColorScheme_BlackLetters    ///< � ���� ������ ��������� ��������� ���� ������� ������ - �� ����� ������� ��������.
} ColorScheme;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ��������� ���� ������.
typedef struct
{ //-V802
    bool            screenWelcomeEnable;    ///< ����� �� ������������ ����� ����������� ��� ��������� �������. \todo ������ ���� ��������.
    bool            soundEnabled;           ///< �������� �� �����.
    CalibratorMode  calibrator;             ///< ����� ������ �����������.
    int8            IPaddress;              ///< IP-����� (��������).
    ColorScheme     colorScheme;            ///< �������� ������.
} SettingsService;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool sService_MathEnabled();

float sService_MathGetFFTmaxDBabs();

/** @}  @}
 */
