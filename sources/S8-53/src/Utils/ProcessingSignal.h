#pragma once
#include "Measures.h"
#include "defines.h"
#include "FPGA/FPGA_Types.h"


class Processing
{
public:
    /// ���������� ������ ��� ���������.
    static void SetSignal(uint8 *data0, uint8 *data1, DataSettings *ds, int firstPoint, int lastPoint);
    /// �������� ������ ����� �������������� �������.
    static void GetData(uint8 **data0, uint8 **data1, DataSettings **ds);
    /// �������� ������� ������� ����������, �������������� �������� ������� ������� posCurT.
    static float GetCursU(Channel chan, float posCurT);
    /// �������� ������� ������� �������, ��������������� �������� ������� ������� ���������� posCurU.
    static float GetCursT(Channel chan, float posCurU, int numCur);
    /// ���������������� ��������� ��������� ������ ������������� �������� sinX/X.
    static void InterpolationSinX_X(uint8 data[FPGA_MAX_POINTS], TBase tBase);
    /// ���������� ������ ��������������� ���������.
    static char* GetStringMeasure(Measure measure, Channel chan, char buffer[20]);
    /// ��������� ��� ���������.
    static void CalculateMeasures();
    /// ���������� �������� ��������������� �������. ���� ERROR_VALUE_INT - ������ �������� �� �����.
    static int GetMarkerHorizontal(Channel chan, int numMarker);
    /// ���������� �������� ������������� �������. ���� ERROR_VALUE_INT - ������ �������� �� �����.
    static int GetMarkerVertical(Channel chan, int numMarker);
private:
    static float CalculateVoltageMax(Channel chan);
    static float CalculateVoltageMin(Channel chan);
    static float CalculateVoltagePic(Channel chan);
    static float CalculateVoltageMaxSteady(Channel chan);
    static float CalculateVoltageMinSteady(Channel chan);
    static float CalculateVoltageAmpl(Channel chan);
    static float CalculateVoltageAverage(Channel chan);
    static float CalculateVoltageRMS(Channel chan);
    static float CalculateVoltageVybrosPlus(Channel chan);
    static float CalculateVoltageVybrosMinus(Channel chan);
    static float CalculatePeriod(Channel chan);
    /// ����� ��������� ������ ��� ����� ����� �������� � ������ �������.
    static int   CalculatePeriodAccurately(Channel chan);
    static float CalculateFreq(Channel chan);
    static float CalculateTimeNarastaniya(Channel chan);
    static float CalculateTimeSpada(Channel chan);
    static float CalculateDurationPlus(Channel chan);
    static float CalculateDurationMinus(Channel chan);
    static float CalculateSkvaznostPlus(Channel chan);
    static float CalculateSkvaznostMinus(Channel chan);
    /// ���������� ����������� �������� �������������� �������    
    static float CalculateMinRel(Channel chan);
    /// ���������� ����������� �������������� �������� �������������� �������
    static float CalculateMinSteadyRel(Channel chan);
    /// ���������� ������������ �������� �������������� �������
    static float CalculateMaxRel(Channel chan);
    /// ���������� ������������ �������������� �������� �������������� �������
    static float CalculateMaxSteadyRel(Channel chan);
    /// ���������� �������� �������� �������������� �������
    static float CalculateAverageRel(Channel chan);
    static float CalculatePicRel(Channel chan);
    static float CalculateDelayPlus(Channel chan);
    static float CalculateDelayMinus(Channel chan);
    static float CalculatePhazaPlus(Channel chan);
    static float CalculatePhazaMinus(Channel chan);
    /// ����� ����� ����������� ������� � �������������� ������, ���������� �� ������ yLine. numItersection - ���������� ����� �����������, 
    /// ���������� � 1. downToTop - ���� true, ���� ����������� ������� �� ������� ������ ��� ����������� �� "-" � "+".
    static float FindIntersectionWithHorLine(Channel chan, int numIntersection, bool downToUp, uint8 yLine);

    static void CountedToCurrentSettings();

    typedef float (*pFuncFCh)(Channel);

    struct MeasureCalculate
    {
        char        *name;
        pFuncFCh    FuncCalculate;
        pFuncCFBC   FucnConvertate;
        /// ���� true, ����� ���������� ����.
        bool        showSign;
    };

    static const MeasureCalculate measures[Measure_NumMeasures];
};
