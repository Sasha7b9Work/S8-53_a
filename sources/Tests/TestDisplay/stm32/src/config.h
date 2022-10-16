#pragma once

// Select one of teh two devices
#define BOARD_S8_53
//#define BOARD_TE207

#if ((defined BOARD_S8_53) && (defined BOARD_TE207))
    #error ("�� ������ ������� ������ ���� ����������");
#endif

#if (!defined BOARD_S8_53) && (!defined BOARD_TE207)
    #error ("�� ������ ������� ���� ����������");
#endif

#ifdef BOARD_S8_53
    #define SPEACKER_ENABLE
    #define DISPLAY_ENABLE
#endif

#ifdef BOARD_TE207
    #define DISPLAY_ENABLE
    //#define SPEACKER_ENABLE
#endif

#if  (defined BOARD_S8_53)
    #define ADC_ENABLE
    #define SPI_ENABLE
    #define SOFTWARE_SPI_ENABLE
#endif  // (defined BOARD_S8_53)

#ifdef SPEACKER_ENABLE
    #define DAC_ENABLE
#endif  // SPEACKER_ENABLE

#define OTG_FS_USBD_ENABLE

#ifdef FlashDrive_ENABLE
    #if defined BOARD_S8_53
        #define OTG_HS_USBH_ENABLE
    #endif  // defined BOARD_S8_53
#endif  // FlashDrive_ENABLE

#if (defined BOARD_TE207) && (defined VCP_ENABLE) && (defined FlashDrive_ENABLE)
    #error ("�� ����� ��207 �����-���� � ����������� ���-���� �� ����� �������������� ������������");
#endif  // (defined BOARD_TE207) && (defined VCP_ENABLE) && (defined FlashDrive_ENABLE)

#if (defined BOARD_TE207) && (defined SPI_ENABLE)
    #error ("�� ����� ��207 ���� SPI");
#endif
