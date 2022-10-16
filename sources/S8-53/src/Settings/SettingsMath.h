#pragma once


/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsMath
 *  @{
 */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SCALE_FFT                   (set.math.scaleFFT)                 ///< SettingMath.scaleFFT
#define SCALE_FFT_IS_LOG            (SCALE_FFT == ScaleFFT_Log)
#define SCALE_FFT_IS_LINEAR         (SCALE_FFT == ScaleFFT_Linear)

#define SOURCE_FFT                  (set.math.sourceFFT)                ///< SettingsMath.sourceFFT
#define SOURCE_FFT_IS_A             (SOURCE_FFT == SourceFFT_A)
#define SOURCE_FFT_IS_B             (SOURCE_FFT == SourceFFT_B)

#define WINDOW_FFT                  (set.math.windowFFT)                ///< SettingsMath.windowFFT
#define WINDOW_FFT_IS_HAMMING       (WINDOW_FFT == WindowFFT_Hamming)
#define WINDOW_FFT_IS_BLACKMAN      (WINDOW_FFT == WindowFFT_Blackman)
#define WINDOW_FFT_IS_HANN          (WINDOW_FFT == WindowFFT_Hann)

#define FFT_MAX_DB                  (set.math.fftMaxDB)                 ///< SettingsMath.fftMaxDB

#define MATH_FUNC                   (set.math.func)                     ///< SettingsMath.func
#define MATH_FUNC_IS_SUM            (MATH_FUNC == Function_Sum)
#define MATH_FUNC_IS_MUL            (MATH_FUNC == Function_Mul)

#define FFT_CUR_CURSOR              (set.math.currentCursor)            ///< SettingsMath.currentCursor
#define FFT_CUR_CURSOR_IS_0         (FFT_CUR_CURSOR == 0)

#define FFT_POS_CURSOR(num)         (set.math.posCur[num])              ///< SettingsMath.currentCursor
#define FFT_POS_CURSOR_0            (FFT_POS_CURSOR(0))
#define FFT_POS_CURSOR_1            (FFT_POS_CURSOR(1))

#define ENABLED_FFT                 (set.math.enableFFT)                ///< SettingsMath.enableFFT

#define MODE_DRAW_MATH              (set.math.modeDraw)                 ///< SettingsMath.modeDraw
#define DISABLED_DRAW_MATH          (MODE_DRAW_MATH == ModeDrawMath_Disable)
#define MODE_DRAW_MATH_IS_TOGETHER  (MODE_DRAW_MATH == ModeDrawMath_Together)
#define MODE_DRAW_MATH_IS_SEPARATE  (MODE_DRAW_MATH == ModeDrawMath_Separate)

#define MATH_MODE_REG_SET           (set.math.modeRegSet)               ///< SettingsMath.modeRegSet
#define MATH_MODE_REG_SET_IS_RSHIFT (MATH_MODE_REG_SET == ModeRegSet_RShift)
#define MATH_MODE_REG_SET_IS_RANGE  (MATH_MODE_REG_SET == ModeRegSet_Range)

#define MATH_MULTIPLIER             (set.math.multiplier)               ///< SettingsMath.multiplier


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ������� ����� ��� ����������� �������.
typedef enum
{
    ScaleFFT_Log,           ///< ��� �������� �������� ��������������� ����� ������ �������.
    ScaleFFT_Linear         ///< ��� �������� �������� �������� ����� ������ �������.
} ScaleFFT;

/// �������� ������� ��� ����������� �������.
typedef enum
{
    SourceFFT_A,            ///< ������ � ����������� ������� ������� ������.
    SourceFFT_B,            ///< ������ � ����������� ������� ������� ������.
    SourceFFT_Both          ///< ������ � ����������� �������� ����� �������.
} SourceFFT;

/// ��� ���� ��� ��������� ������� ����� �������� �������.
typedef enum
{
    WindowFFT_Rectangle,    ///< ����� �������� ������� ������ �� ���������� �� ����.
    WindowFFT_Hamming,      ///< ����� �������� ������� ������ ���������� �� ���� ��������.
    WindowFFT_Blackman,     ///< ����� �������� ������� ������ ���������� �� ���� ��������.
    WindowFFT_Hann          ///< ����� �������� ������� ������ ���������� �� ���� �����.
} WindowFFT;

/// ����������� �������� �� ������������ ���������� ������� �������.
typedef enum
{
    FFTmaxDB_40,            ///< ������������ ���������� �� -40��
    FFTmaxDB_60,            ///< ������������ ���������� �� -60��
    FFTmaxDB_80             ///< ������������ ���������� �� -80��
} FFTmaxDB;

/// ����� ������� ������������.
typedef enum
{
    Function_Sum,           ///< ����� ���� �������.
    Function_Mul            ///< ������������ ���� �������.
} Function;

/// ��� ������������ �������������� ������.
typedef enum
{
    ModeDrawMath_Disable,   ///< ����������� ��������������� ������� ���������.
    ModeDrawMath_Separate,  ///< �������������� ������ ������������ �� ��������� ������.
    ModeDrawMath_Together   ///< �������������� ������ ������������ ������ �������� �������.
} ModeDrawMath;

/// ��� ��������� ����� ���������, ����� �������� �������������� �������.
typedef enum
{
    ModeRegSet_Range,       ///< ����� ��������� ��������� ��������� �� ����������.
    ModeRegSet_RShift       ///< ����� ��������� ��������� ��������� �� ����������.
} ModeRegSet;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    ScaleFFT        scaleFFT;       ///< ������� ����� ��� ����������� �������.
    SourceFFT       sourceFFT;      ///< �������� ������� ��� ������� � ����������� �������.
    WindowFFT       windowFFT;      ///< ����� ��� ����, �� ������� ���������� ������ ����� �������� �������.
    FFTmaxDB        fftMaxDB;       ///< ����������� �������� �� ������������ ���������� ������� �������.
    Function        func;           ///< ���������� �������������� �������.
    uint8           currentCursor;  ///< ����������, ����� �������� ������� ��������� ����� ���������.
    uint8           posCur[2];      ///< ������� ������� �������. ���������� 0...256.
    int8            koeff1add;      ///< ����������� ��� ������ ��������� ��� ��������.
    int8            koeff2add;
    int8            koeff1mul;
    int8            koeff2mul;
    bool            enableFFT;      ///< \c true, ���� ������� ������.
    ModeDrawMath    modeDraw;       ///< ���������� ��� ����� ������� � ������ �������������� �������.
    ModeRegSet      modeRegSet;     ///< ������� ����� ��������� - ������� �� ������� ��� �������� �� ���������.
    Range           range;          ///< ������� �� ���������� ��������������� �������.
    Divider      multiplier;     ///< ��������� �������� ��������������� �������.
    int16           rShift;         ///< �������� �� ������������ ��� ��������������� �������.
} SettingsMath;


/** @}  @}
 */
