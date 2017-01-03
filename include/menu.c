#include <stdio.h>
#include <string.h>
#include "main.h"
/* *INDENT-OFF* */
MenuItem Menu_list[max_struct_index] = {
  
//������   �����		���� �������� 0		���� 1		���� ������ ��� 1	������ ����� ���� ��������		�������		��������	������	������� �� ����������	�� ���������� 
{0x00, LANG_ALARM,		LANG_OFF,			"",			LANG_UMKR,			&Settings.Alarm_level,			0,			10000,		60,		&plus_alarm,			&minus_alarm},
{0x00, LANG_SLEEP,		LANG_OFF,			"",			LANG_USEC,			&Settings.Sleep_time,			10,			10240,		40,		&plus_sleep,			&minus_sleep},
{0x00, LANG_SOUND,		LANG_OFF,			LANG_ON,	LANG_KEY,			&Settings.Sound,				0,			2,			0,		&plus_one,				&minus_one},
#ifdef version_401
{0x00, LANG_VIBRO,		LANG_OFF,			LANG_ON,	LANG_ALARM2,		&Settings.Vibro,				0,			2,			0x00,	&plus_one,				&minus_one},
#else
{0x00, LANG_USBMODE,	LANG_OFF,			LANG_ON,	"",					&Settings.USB,					0x00,		0x00,		0x00,	&usb_activate,			&usb_deactivate},
#endif
{0x00, LANG_CLEARDO,	"*",				"*",		"*",				0x00,							0x00,		0x00,		0x00,	&plus_doze_reset,		0x00},
{0x00, LANG_REBOOT,		"*",				"*",		"*",				0x00,							0x00,		0x00,		0x00,	&plus_reboot,			&minus_poweroff},
{0x00, LANG_UNITS,		LANG_UR,			LANG_UZV,	"",					&Settings.units,				0x00,		0x01,		0x00,	&plus_one,				&minus_one},
{0x00, LANG_CLEAR_FON,	"*",				"*", 		"*",				0x00,							0x00,		0x00,		0x00,	&plus_rad_reset,		0x00},
{0x00, LANG_BETA_MEAS,	"*",				"*",		"*",				0x00,							0x00,		0x00,		0x00,	&plus_ab_engage,		0x00},
//{0x00, LANG_SCINT_MEAS,	"*",				"*",		"*",				0x00,							0x00,		0x00,		0x00,	&plus_amodul_engage,		0x00},
{0x01, LANG_SPEED,		LANG_OFF,			LANG_ON,	"",					&Settings.Speedup,				0x00,		0x01,		0x00,	&plus_one,				&minus_one},
// �������� �� ������ if(menu_struct_index == 10) ! ��������� � ���� ��� ��������� ������� ������� ����!
{0x01, LANG_ISOTOP,		"",			        "",	        "",					&Settings.Isotop,				0x00,		0x08,		0x00,	&plus_one,				&minus_one},

// ��������� ������ ����
{0x01, LANG_CONTRAST,	"",					"",			"%u",				&Settings.contrast,				0,			15,			0,		&plus_one,				&minus_one},
{0x01, LANG_REVERSE,	LANG_OFF,			"",			"%u",				&Settings.Display_reverse,		0,			5,			0,		&plus_one,				&minus_one},
{0x01, "LSI",			LANG_QUARTZ,		"",			LANG_UHZ,			&Settings.LSI_freq,				26000,		56000,		38000,	&plus_500,				&minus_500},
{0x01, LANG_V4PUMP,		"",					"",			LANG_UV4PUMP,		&Settings.v4_target_pump,		4,			14,			11,		&plus_one,				&minus_one},
{0x01, LANG_VOLTAGE,	"",					"",			LANG_UV,			&Settings.Geiger_voltage,		300,		450,		380,	&plus_ten,				&minus_ten},
// �������� �� ���� ���� if(menu_struct_index == 16) ! ��������� � ���� ��� ��������� ������� ������� ����!
{0x01, LANG_BWINDOW,	"",					"",			LANG_BWINDOW_,		&Settings.Beta_window,			1,			100,		20,		&plus_one,				&minus_one},
{0x01, LANG_BPROCENT,	"",					"",			LANG_BPROCENT_,		&Settings.Beta_procent,			1,			100,		37,		&plus_one,				&minus_one},
{0x01, LANG_REF_VOLT,	"",					"",			LANG_REF_VOLT_,		&ADCData.Power_voltage,			1202,		1242,		1224,	&plus_one_ref,			&minus_one_ref},
{0x01, LANG_PUMP_AGR,	LANG_OFF,			LANG_ON,	"",	            	&Settings.Pump_aggressive,		0,	    	1,  		0,  	&plus_one,		    	&minus_one},

{0x01, LANG_ISOTOP_CS137,"",				"",			LANG_ACAL,			&Settings.Isotop_ACAL_cs137,			10,	    	1450,		250,	&plus_ten,				&minus_ten},
{0x01, LANG_ISOTOP_EU152,"",				"",			LANG_ACAL,			&Settings.Isotop_ACAL_eu152,			10,	    	1450,		250,	&plus_ten,				&minus_ten},
{0x01, LANG_ISOTOP_NA22, "",				"",			LANG_ACAL,			&Settings.Isotop_ACAL_na22,	    		10,	    	1450,		250,	&plus_ten,				&minus_ten},
{0x01, LANG_ISOTOP_CD109,"",				"",			LANG_ACAL,			&Settings.Isotop_ACAL_cd109,			10,	    	1450,		250,	&plus_ten,				&minus_ten},
{0x01, LANG_ISOTOP_AM241,"",				"",			LANG_ACAL,			&Settings.Isotop_ACAL_am241,			10,	    	1450,		250,	&plus_ten,				&minus_ten},
{0x01, LANG_ISOTOP_TI44, "",				"",			LANG_ACAL,			&Settings.Isotop_ACAL_ti44,	    		10,	    	1450,		250,	&plus_ten,				&minus_ten},
{0x01, LANG_ISOTOP_Y88,  "",				"",			LANG_ACAL,			&Settings.Isotop_ACAL_y88,		    	10,	    	1450,		250,	&plus_ten,				&minus_ten},
{0x01, LANG_ISOTOP_BA133,"",				"",			LANG_ACAL,			&Settings.Isotop_ACAL_ba133,			10,	    	1450,		250,	&plus_ten,				&minus_ten},
{0x01, LANG_ISOTOP_TH228,"",				"",			LANG_ACAL,			&Settings.Isotop_ACAL_th228,			10,	    	1450,		250,	&plus_ten,				&minus_ten},

{0x01, LANG_SPECT_START,"",				    "",			"%u",	    		&Settings.AMODUL_spect_start,			10,	    	20000,		1000,	&plus_ten,				&minus_ten},
{0x01, LANG_SPECT_MULTIP,"",				"",			"%u",		    	&Settings.AMODUL_spect_multi,			1,	    	200,	   	70,	    &plus_one,				&minus_one},
{0x01, LANG_SPECT_MARK1,"",				    "",			"%u",	    		&Settings.AMODUL_spect_mark1,			1,	    	100,		10, 	&plus_one,				&minus_one},
{0x01, LANG_SPECT_MARK2,"",				    "",			"%u",	    		&Settings.AMODUL_spect_mark2,			1,	    	100,		20,	    &plus_one,				&minus_one},
{0x01, LANG_SPECT_MARK3,"",				    "",			"%u",	    		&Settings.AMODUL_spect_mark3,			1,	    	100,		30,	    &plus_one,				&minus_one},
{0x01, LANG_SPECT_MARK4,"",				    "",			"%u",	    		&Settings.AMODUL_spect_mark4,			1,	    	100,		40,	    &plus_one,				&minus_one},
{0x01, LANG_SPECT_MARK5,"",				    "",			"%u",	    		&Settings.AMODUL_spect_mark5,			1,	    	100,		50,	    &plus_one,				&minus_one}

};
//////////////////////////////////////////////////////////////////////////////////////////////////
/* *INDENT-ON* */


void main_screen()
{
  RTC_TimeTypeDef RTC_TimeStructure;
  RTC_DateTypeDef RTC_DateStructure;


  uint32_t battery_procent, i = 0, x = 0;

  //������ �������� ��������� 3.5� = 0% 4.0� = 100%
  if((Settings.AB_mode == 0) && (Settings.AMODUL_mode == 0))
  {
    battery_procent = ADCData.Batt_voltage;
    battery_procent -= 3500;
    battery_procent /= 5;
    if(ADCData.Batt_voltage < 3500)
    {
      LcdBatt(82, 19, 82 + 10, 19 + 19, 0);
    }                           //������ ���������ADCData.Batt_voltage
    else
      LcdBatt(84, 19, 84 + 10, 19 + 19, battery_procent);       //������ ���������ADCData.Batt_voltage
  }

  if(main_menu_stat > 8)
    main_menu_stat = 1;
  if(main_menu_stat < 1)
    main_menu_stat = 8;

  if(DataUpdate.Need_update_mainscreen_counters == ENABLE)      // ���� ��������� ���������� ���������
  {
    DataUpdate.Need_update_mainscreen_counters = DISABLE;
    Max_fon = 0;
    Doze_day_count = 0;
    Doze_week_count = 0;
    Doze_month_count = 0;
    Doze_hour_count = 0;
    Doze_2month_count = 0;

    for (i = doze_length_2month; i > 0; i--)
    {
      if(i < doze_length_hour)
        Doze_hour_count += flash_read_massive(i, dose_select);  // ������ ��������� ����
      if(i < doze_length_day)
        Doze_day_count += flash_read_massive(i, dose_select);   // ������ ������� ����
      if(i < doze_length_week)
      {
        Doze_week_count += flash_read_massive(i, dose_select);  // ������ ��������� ����
        x = flash_read_massive(i, max_fon_select);
        if(x > Max_fon)
          Max_fon = x;          // ������ ������������� ����
      }
      if(i < doze_length_month)
        Doze_month_count += flash_read_massive(i, dose_select); // ������ �������� ����
      if(i < doze_length_2month)
        Doze_2month_count += flash_read_massive(i, dose_select);        // ������ �������� ����
    }
  }

  if((Settings.AB_mode == 0) && (Settings.AMODUL_mode == 0))
  {
    switch (main_menu_stat)
    {
    case 0x01:
      sprintf(lcd_buf, LANG_TIME);      // ����� � ����� �������� ��������
      LcdString(1, 4);          // // ������� ������� ������� ���������� ������
      sprintf(lcd_buf, LANG_DATE);      // ����� � ����� �������� ��������
      LcdString(1, 5);          // // ������� ������� ������� ���������� ������

      RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
      RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);

      sprintf(lcd_buf, "%0.2d.%0.2d.%0.2d", RTC_DateStructure.RTC_Date, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Year);
      LcdString(7, 5);          // // ������� ������� ������� ���������� ������
      sprintf(lcd_buf, "%0.2d:%0.2d:%0.2d", RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
      LcdString(7, 4);          // // ������� ������� ������� ���������� ������

      break;
      // -----------------------------------------
    case 0x02:
      sprintf(lcd_buf, LANG_MAXFON);    // ����� � ����� �������� ��������
      LcdString(1, 4);          // // ������� ������� ������� ���������� ������

      if(!Settings.units)
      {
        sprintf(lcd_buf, LANG_9UMKR, Max_fon);  // ����� � ����� �������� ��������
      } else
      {
        sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv(Max_fon)); // ����� � ����� �������� ��������
      }
      LcdString(1, 5);          // // ������� ������� ������� ���������� ������
      break;
      // -----------------------------------------
    case 0x03:
      sprintf(lcd_buf, LANG_DOSE10M);   // ����� � ����� �������� ��������
      LcdString(1, 4);          // // ������� ������� ������� ���������� ������

      if(flash_read_massive(doze_length_10m, dose_select) > 0)
      {
        //��� �� ��� massive/(3600/����� �����)
        if(!Settings.units)
        {
          sprintf(lcd_buf, LANG_9UMKR, (flash_read_massive(doze_length_10m, dose_select) * (Settings.Second_count >> 2)) / 900);        // ����� � ����� �������� ��������
        } else
        {
          sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((flash_read_massive(doze_length_10m, dose_select) * (Settings.Second_count >> 2)) / 900));       // ����� � ����� �������� ��������
        }
      } else
      {
        sprintf(lcd_buf, LANG_DOSECALC);        // ����� � ����� �������� ��������
      }
      LcdString(1, 5);          // // ������� ������� ������� ���������� ������
      break;
      // -----------------------------------------
    case 0x04:
      sprintf(lcd_buf, LANG_DOSEHOUR);  // ����� � ����� �������� ��������
      LcdString(1, 4);          // // ������� ������� ������� ���������� ������

      if(flash_read_massive(doze_length_hour, dose_select) > 0)
      {
        if(!Settings.units)
        {
          sprintf(lcd_buf, LANG_9UMKR, ((Doze_hour_count * (Settings.Second_count >> 2)) / 900));       // ����� � ����� �������� ��������
        } else
        {
          sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Doze_hour_count * (Settings.Second_count >> 2)) / 900));        // ����� � ����� �������� ��������
        }
      } else
      {
        sprintf(lcd_buf, LANG_DOSECALC);        // ����� � ����� �������� ��������
      }
      LcdString(1, 5);          // // ������� ������� ������� ���������� ������
      break;
      // -----------------------------------------
    case 0x05:
      sprintf(lcd_buf, LANG_DOSE24H);   // ����� � ����� �������� ��������
      LcdString(1, 4);          // // ������� ������� ������� ���������� ������         

      if(flash_read_massive(doze_length_day, dose_select) > 0)  // ����
      {
        if(!Settings.units)
        {
          sprintf(lcd_buf, LANG_9UMKR, ((Doze_day_count * (Settings.Second_count >> 2)) / 900));        // ����� � ����� �������� ��������
        } else
        {
          sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Doze_day_count * (Settings.Second_count >> 2)) / 900)); // ����� � ����� �������� ��������
        }
      } else
      {
        sprintf(lcd_buf, LANG_DOSECALC);        // ����� � ����� �������� ��������
      }

      LcdString(1, 5);          // // ������� ������� ������� ���������� ������
      break;
      // -----------------------------------------
    case 0x06:
      sprintf(lcd_buf, LANG_DOSEWEEK);  // ����� � ����� �������� ��������
      LcdString(1, 4);          // // ������� ������� ������� ���������� ������

      if(flash_read_massive(doze_length_week, dose_select) > 0) // ������
      {
        if(!Settings.units)
        {
          sprintf(lcd_buf, LANG_9UMKR, ((Doze_week_count * (Settings.Second_count >> 2)) / 900));       // ����� � ����� �������� ��������
        } else
        {
          sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Doze_week_count * (Settings.Second_count >> 2)) / 900));        // ����� � ����� �������� ��������
        }
      } else
      {
        sprintf(lcd_buf, LANG_DOSECALC);        // ����� � ����� �������� ��������
      }

      LcdString(1, 5);          // // ������� ������� ������� ���������� ������
      break;
      // -----------------------------------------


// -----------------------------------------
    case 0x07:
      sprintf(lcd_buf, LANG_DOSEMONTH); // ����� � ����� �������� ��������
      LcdString(1, 4);          // // ������� ������� ������� ���������� ������

      if(flash_read_massive(doze_length_month, dose_select) > 0)        // ������
      {
        if(!Settings.units)
        {
          sprintf(lcd_buf, LANG_9UMKR, ((Doze_month_count * (Settings.Second_count >> 2)) / 900));      // ����� � ����� �������� ��������
        } else
        {
          sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Doze_month_count * (Settings.Second_count >> 2)) / 900));       // ����� � ����� �������� ��������
        }
      } else
      {
        sprintf(lcd_buf, LANG_DOSECALC);        // ����� � ����� �������� ��������
      }

      LcdString(1, 5);          // // ������� ������� ������� ���������� ������
      break;
      // -----------------------------------------

      // -----------------------------------------
    case 0x08:
      sprintf(lcd_buf, LANG_DOSE2MONTH);        // ����� � ����� �������� ��������
      LcdString(1, 4);          // // ������� ������� ������� ���������� ������

      if(flash_read_massive(doze_length_2month, dose_select) > 0)       // ������
      {
        if(!Settings.units)
        {
          sprintf(lcd_buf, LANG_9UMKR, ((Doze_2month_count * (Settings.Second_count >> 2)) / 900));     // ����� � ����� �������� ��������
        } else
        {
          sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Doze_2month_count * (Settings.Second_count >> 2)) / 900));      // ����� � ����� �������� ��������
        }
      } else
      {
        sprintf(lcd_buf, LANG_DOSECALC);        // ����� � ����� �������� ��������
      }

      LcdString(1, 5);          // // ������� ������� ������� ���������� ������
      break;
      // -----------------------------------------

    default:
      break;
    }
  } else
  {
    // ����� "����� �-�"
    if(Settings.AB_mode > 0)
      Draw_AB_digit(4, 1, 0);

    // ����� "������-�"
    if(Settings.AMODUL_mode > 0)
    {
      if(Settings.AMODUL_unit < 2)
      {
        Draw_AMODUL_digit(1, 1, 0);

        sprintf(lcd_buf, LANG_AMODUL);  // ����� � ����� �������� ��������
        LcdString(1, 4);        // // ������� ������� ������� ���������� ������

        sprintf(lcd_buf, LANG_TIME);    // ����� � ����� �������� ��������
        LcdString(1, 5);        // // ������� ������� ������� ���������� ������
        sprintf(lcd_buf, LANG_USEC, Settings.AMODUL_time);      // ����� � ����� �������� ��������
        LcdString(7, 5);        // // ������� ������� ������� ���������� ������
      }
    }
  }

  if(Settings.Cal_mode == 1)
  {
    sprintf(lcd_buf, "%2i  %5i", Cal_count, Cal_count_time);    // ����� � ����� �������� ��������
    LcdString(1, 1);            // // ������� ������� ������� ���������� ������

    sprintf(lcd_buf, LANG_FON_UMKZV, convert_mkr_sv(Cal_count_mass[Cal_count]));        // ����� � ����� �������� ��������
    LcdString(1, 2);            // // ������� ������� ������� ���������� ������    
  } else
  {
    if(Settings.AMODUL_mode == 0)
      Draw_fon_digit(1, 1, 0);
  }

  if(Settings.AMODUL_mode > 0)
  {
    if(Settings.AMODUL_unit < 2)
    {
      Draw_AMODUL_graph(2, 94, 67 - 25, 67);
    } else
    {
      sprintf(lcd_buf, LANG_SPECT_MARK_TEXT1);  // ����� � ����� �������� ��������
      LcdString(1, 1);          // // ������� ������� ������� ���������� ������

      sprintf(lcd_buf, LANG_SPECT_MARK_TEXT2);  // ����� � ����� �������� ��������
      LcdString(1, 2);          // // ������� ������� ������� ���������� ������

      sprintf(lcd_buf, LANG_SPECT_MARK_TEXT3);  // ����� � ����� �������� ��������
      LcdString(1, 3);          // // ������� ������� ������� ���������� ������


      Draw_AMODUL_graph_spectr(2, 96, 67 - 38, 67, 0);
    }

  } else
  {
    Draw_fon_graph(2, 94, 67 - 25, 67);
  }

  if(auto_speedup_factor > 1)
  {
    Draw_speedup(2, 94, 67 - 25, 67);
    sprintf(lcd_buf, "x%2u", auto_speedup_factor);      // ����� � ����� �������� ��������
    LcdString(12, 3);           // // ������� ������� ������� ���������� ������
  }
  LcdUpdate();                  // ���������� ������ �� ��������������� �����-������ �� �������

}

//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
void menu_screen()
{
  char para_string[20];
  char tmp_string[20];
  uint16_t menu_page, i, j;
  //���������� ����

  sprintf(lcd_buf, LANG_MENU);
  LcdStringInv(1, 1);

  if(menu_select == 0)
  {
    menu_page = 0;
  } else
  {

    if(hidden_menu)
    {
      menu_page = (menu_select - 1) / (max_string_count - start_offset);        // ����������� �������� ���� (������)
    } else
    {
      if(menu_select <= max_public_string_count)
      {
        menu_page = (menu_select - 1) / (max_string_count - start_offset);      // ����������� �������� ���� (���������)
      } else
      {
        menu_page = 0;
      }
    }
  }

  for (i = 0; i < (max_string_count - start_offset); i++)
  {
    uint32_t fill_len = 0;
    uint32_t para_len = 0;
    uint32_t text_len = 0;
    uint32_t menu_struct_index = 0;
    float tmp;
    uint32_t tmpi;

    menu_struct_index = (menu_page * (max_string_count - start_offset)) + i;    // ���������� ����� � ���������
    if(menu_struct_index >= max_struct_index)
      break;                    // ���� ���� ���������
    if((menu_struct_index >= max_public_string_count) && (!hidden_menu))
      break;                    // ���� �� �������� ���������� ����


    // ����������� ������� ������, ����� ������� ����� �������� ��������� ������� �� ������ ������ � ���������� (�������� �� ������� ����)

    // ��������� �������� ��������� "10���"
    switch (*Menu_list[menu_struct_index].Parameter_value)
    {
    case 0:                    // ���� �������� ��������� ����� ����, ���� ��� �� ���������������� �� ���� ������
      if(Menu_list[menu_struct_index].Param_is_0[0] != '\0')
      {
        sprintf(para_string, Menu_list[menu_struct_index].Param_is_0);
        break;
      }

    case 1:                    // ���� �������� ��������� ����� �������, ���� ��� �� ���������������� �� ���� ������
      if(Menu_list[menu_struct_index].Param_is_1[0] != '\0')
      {
        sprintf(para_string, Menu_list[menu_struct_index].Param_is_1);
        break;
      }

    default:                   // �� ���� ��������� ������� ������� �� �������
      sprintf(para_string, Menu_list[menu_struct_index].Param_is_N, *Menu_list[menu_struct_index].Parameter_value);
      break;
    }

    // �������� �� ����
    if((menu_struct_index == 0) && Settings.units)
      sprintf(para_string, LANG_UMKZV, convert_mkr_sv(*Menu_list[menu_struct_index].Parameter_value));

    // �������� �� ������
    if(menu_struct_index == 10)
    {
      tmpi = *Menu_list[menu_struct_index].Parameter_value;
      switch (tmpi)
      {
      case 0x0:
        sprintf(para_string, LANG_ISOTOP_CS137);
        break;
      case 0x1:
        sprintf(para_string, LANG_ISOTOP_EU152);
        break;
      case 0x2:
        sprintf(para_string, LANG_ISOTOP_NA22);
        break;
      case 0x3:
        sprintf(para_string, LANG_ISOTOP_CD109);
        break;
      case 0x4:
        sprintf(para_string, LANG_ISOTOP_AM241);
        break;
      case 0x5:
        sprintf(para_string, LANG_ISOTOP_Y88);
        break;
      case 0x6:
        sprintf(para_string, LANG_ISOTOP_TI44);
        break;
      case 0x7:
        sprintf(para_string, LANG_ISOTOP_BA133);
        break;
      case 0x8:
        sprintf(para_string, LANG_ISOTOP_TH228);
        break;
      }
    }
    // �������� �� ���� ����
    if(menu_struct_index == 16)
    {
      tmp = *Menu_list[menu_struct_index].Parameter_value;
      tmp = tmp / 10;
      sprintf(para_string, LANG_BWINDOW_, tmp);
    }


    para_len = strlen(para_string);     // ������ ���������
    text_len = strlen(Menu_list[menu_struct_index].Text);       // ����� ������
    fill_len = max_string_len - para_len - text_len;    // ������� ��������� ������ ��������

    sprintf(tmp_string, Menu_list[menu_struct_index].Text);     // ����� ����� �������             "���"
    for (j = 0; j < fill_len; j++)
      strcat(tmp_string, " ");  // �������� ��������� ����������   "���      "

    // ����� �� �����
    // ���� ������ �� ������, �� ������������. �� ���� �� ����� � ����� ����, �� ������������ ������ ��������
    sprintf(lcd_buf, tmp_string);       // ������� � ������ �� ����� "���      "
    if(menu_select == menu_struct_index + 1 && enter_menu_item == DISABLE)      // ����������� ���������
    {
      LcdStringInv(1, i + start_offset + 1);
    } else
    {
      LcdString(1, i + start_offset + 1);
    }

    sprintf(lcd_buf, para_string);      // ������� � ������ �� �������� "10 ���"
    if(menu_select == menu_struct_index + 1)    // ����������� ���������
    {
      LcdStringInv(1 + text_len + fill_len, i + start_offset + 1);
    } else
    {
      LcdString(1 + text_len + fill_len, i + start_offset + 1);
    }

  }

  LcdUpdate();

}

//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
void stat_screen()
{
  switch (stat_screen_number)
  {
  case 0:
    sprintf(lcd_buf, LANG_STAT);
    LcdStringInv(1, 1);

    sprintf(lcd_buf, LANG_VOLTAGE);     // ������� �� �������
    LcdString(1, 2);            // // ������� ������� ������� ���������� ������ �� ������ 8

    sprintf(lcd_buf, LANG_AKB3VVV);     // ������� �� �������
    LcdString(1, 3);            // // ������� ������� ������� ���������� ������ �� ������ 8

    sprintf(lcd_buf, "%1i.%02i", ADCData.Batt_voltage / 1000, (ADCData.Batt_voltage % 1000) / 10);      // ������� �� �������
    LcdString(1, 4);            // // ������� ������� ������� ���������� ������ �� ������ 8

    sprintf(lcd_buf, "|%1i.%02i", ADCData.Power_voltage / 1000, (ADCData.Power_voltage % 1000) / 10);   // ������� �� �������
    LcdString(6, 4);            // // ������� ������� ������� ���������� ������ �� ������ 8

    sprintf(lcd_buf, "|%3is", Settings.Second_count);   // ������� �� �������
    LcdString(12, 4);           // // ������� ������� ������� ���������� ������ �� ������ 8

    sprintf(lcd_buf, LANG_PUMP);        // ������� �� �������
    LcdString(1, 6);            // // ������� ������� ������� ���������� ������ �� ������ 8

    sprintf(lcd_buf, LANG_IMPMINAR);    // ������� �� �������
    LcdString(1, 7);            // // ������� ������� ������� ���������� ������ �� ������ 8

    if(pump_counter_avg_impulse_by_1sec[1] == 0)
    {
      sprintf(lcd_buf, LANG_CALC2);
    }                           // ������� �� �������
    else
      sprintf(lcd_buf, "%5i ", pump_counter_avg_impulse_by_1sec[1]);    // ������� �� �������
    LcdString(1, 8);            // // ������� ������� ������� ���������� ������ �� ������ 8

    sprintf(lcd_buf, LANG_4IDN, working_days);  // ������� �� �������
    LcdString(9, 8);            // // ������� ������� ������� ���������� ������ �� ������ 8
    break;

  case 1:

    sprintf(lcd_buf, LANG_ABOUT);
    LcdStringInv(1, 1);

    sprintf(lcd_buf, LANG_DOZIK);
    LcdString(1, 3);
    sprintf(lcd_buf, LANG_AUTHOR);
    LcdString(1, 4);
    sprintf(lcd_buf, LANG_CITY);
    LcdString(1, 5);
    sprintf(lcd_buf, LANG_SITE);
    LcdString(1, 6);
    sprintf(lcd_buf, LANG_BUILD);
    LcdString(1, 7);
    sprintf(lcd_buf, "     %s", __DATE__);
    LcdString(1, 8);
    break;

  default:
    stat_screen_number = 0;
    break;
  }
  LcdUpdate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
