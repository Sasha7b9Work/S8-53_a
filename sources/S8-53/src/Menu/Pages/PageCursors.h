#pragma once
#include "Settings/SettingsTypes.h"


/** @addtogroup Menu
 *  @{
 *  @defgroup PageCursors
 *  @{
 */


void  Cursors_Update();    // �������� ��� ������� ��� ������� ���������, ����� �������� ������� ��������, ���� ��� ������ ����������� �������������.


class PageCursors
{
public:
    
    class PageSet
    {
    public:
        static void *pointer;
    };

    static void *GetPointer();
};


/** @}  @}
 */
