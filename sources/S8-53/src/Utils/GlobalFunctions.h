#pragma once


#include "defines.h"

                                                
char*   FloatFract2String(float value, bool alwaysSign, char bufferOut[20]);

char*   Float2String                            //  ����������� value ���� float � ��������� ������.
                                                //  @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ������������ ����.
                                                //  @retval ��������� �� ������ � ������.
                    (float value,               //  ��������.
                    bool alwaysSign,            //  ���� ���������� � true, ����� ������ ������ ����� ����, ���� ���������� � false, ������ ���� ����� �������������.
                    int numDigits,              //  ����� �������� ��������.
                    char bufferOut[20]
                    );                         
char*   Bin2String                              //  ����������� value � ��������� ������. ��� ���� ��������� ��� 8 ��������.
                                                //  @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����.
                    (uint8 value,
                    char buffer[9]);
char*   Bin2String16                            // ����������� value � ��������� ������
                                                // @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����.
                    (uint16 value,
                    char buffer[19]);
char*   Hex8toString                            // ����������� value � ��������� ������ � ����������������� ����.
                                                // @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����.
                    (uint8 value,
                    char buffer[3]);
char*   Int2String                              // ����������� value � ��������� ������.
                                                // @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����.
                    (int value,                 // ��������.
                    bool alwaysSign,            // ���� ���������� � true, ���� ����� ���������� ������.
                    int numMinFields,           // ����������� ����� ���������� ���������. ���� ��� ������ ����� ������� �� ���������, ������ ����������� ������.
                    char buffer[20]
                    );
bool    String2Int(char *str, int *value);
char*   Voltage2String                          // ����������� voltage ����� � ��������� ������.
                                                // @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ������������ ����.
                        (float voltage,         // �������� ���������� � �������.
                        bool alwaysSign,        // ���� ����������� � true, ���� ��������� ������.
                        char buffer[20]
                        );                      
char*   Time2String                             // ����������� time ������ � ��������� ������.
                    (float time,                // ����� � ��������. ����� ���� �������������.
                    bool alwaysSign,            // ���� ���������� � true, ���� ������������ ������.
                    char buffer[20]
                    );
char*   Freq2String(float freq, bool, char bufferOut[20]);      // ����������� freq ���� � ��������� ������.
char*   Phase2String(float phase, bool, char bufferOut[20]);    // ����������� ������� � ������.
char*   Float2Db(float value, int numDigits, char bufferOut[20]);   // ����������� �������� � ��������� ������.
bool    IntInRange                              // ���������� true, ���� value ������ � �������� [min; max].
                   (int value,                  // ����������� ��������.
                   int min,                     // ������ ������� ���������.
                   int max                      // ������� ������� ���������.
                   );
float   MaxFloat(float val1, float val2, float val3);                   // ���������� ������������ �������� �� ���.
int8    CircleIncreaseInt8(int8 *val, int8 min, int8 max);              // ����������� �������� �� ������ val �� 1. �����, ���� ��������� ��������� max, ������������ ��� � min.
int16   CircleIncreaseInt16(int16 *val, int16 min, int16 max);
int8    CircleDecreaseInt8(int8 *val, int8 min, int8 max);              // �������� �������� �� ������ val �� 1. �����, ���� ��������� ������ min, ������������ ��� max.
int16   CircleDecreaseInt16(int16 *val, int16 min, int16 max);
int     CircleIncreaseInt(int *val, int min, int max);
int     CircleDecreaseInt(int *val, int min, int max);
float   CircleAddFloat(float *val, float delta, float min, float max);  // ����������� �������� �� ������ val �� delta. �����, ���� ��������� ������ max, ������������ ��� min.
float   CircleSubFloat(float *val, float delta, float min, float max);  // ��������� �������� �� ������ val �� delta. �����, ���� ��������� ������ min, ������������ ��� masx.
void    AddLimitationFloat                                              // ��������� � �������� �� ������ val delta. ���� ��������� �� ����������� � �������� [min; max], ����������.
                            (float *val,                                // �� ����� ������ �������� ��������.
                            float delta,                                // � ��� ������.
                            float min,                                  // ������ ������� ���������.
                            float max                                   // ������� ������� ���������.
                            );
void    SwapInt(int *value0, int *value1);                      // ���������� ������� ���������� ������ �� ������� value0 � value1.
void    SortInt(int *value0, int *value1);                      // ��������� ���������� value0 � value1 � ������� �����������.
char    GetSymbolForGovernor(int value);                        // ���������� ����������� ����������, ��������������� ��� �������� ���������.
void    EmptyFuncVV();                                      // �������-��������. ������ �� ������.
void    EmptyFuncVI(int);
void    EmptyFuncVpV(void *);                                   // �������-��������. ������ �� ������.
void    EmptyFuncpVII(void *, int, int);                        // �������-��������. ������ �� ������.
void    EmptyFuncVI16(int16);                                   // �������-��������. ������ �� ������.
void    EmptyFuncVB(bool);                                      // �������-��������. ������ �� ������.
bool    EmptyFuncBV();
void    IntToStrCat(char *_buffer, int _value);
