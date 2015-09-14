#include <stdio.h>
#include <stdint.h>
#include "STM32L1xx.h"                  // Device header

#include "main.h"
#include "delay.h"
#include "io_ports.h"
#include "rtc.h"
#include "timers.h"
#include "ext2760.h"
#include "interrupt.h"
#include "menu.h"
#include "keys.h"
#include "eeprom.h"
#include "adc.h"
#include "dac.h"
#include "comp.h"
#include "usb.h"
#include "clock.h"
#include "power.h"
#include "stm32l1xx_it.h"
#include "flash_save.h"


uint16_t key; // ������ ������� ������ [012]
uint32_t ix;
uint32_t ix_update;

uint16_t Detector_massive[120+1];
uint32_t ram_Doze_massive[doze_length+1]; // 1 ������ = 10 �����, �� ���������� �����
uint32_t ram_max_fon_massive[doze_length+1]; // 1 ������ = 10 �����, �� ���������� �����
uint16_t USB_maxfon_massive_pointer=0;
uint16_t USB_doze_massive_pointer=0;
uint16_t current_pulse_count=0;
uint8_t pump_count=0;

uint32_t Doze_day_count=0;
uint32_t Doze_week_count=0;
uint32_t Doze_hour_count=0;
uint32_t Doze_month_count=0;
uint32_t Max_fon=0;
uint8_t  main_menu_stat=1;
uint16_t Detector_massive_pointer=0;
uint8_t  auto_speedup_factor=0;
uint32_t USB_not_active=0;
uint32_t last_count_pump_on_impulse=0;
FunctionalState pump_on_impulse=DISABLE;
uint32_t menu_select=0;
#ifdef debug
uint32_t debug_wutr=0;
#endif
FunctionalState enter_menu_item=DISABLE;
uint8_t screen=1;
uint8_t stat_screen_number=0;
uint16_t pump_counter_avg_impulse_by_1sec[2];
uint32_t fon_level=0;
FunctionalState poweroff_state=DISABLE;
FunctionalState hidden_menu=DISABLE;
FunctionalState Pump_on_alarm=DISABLE;

uint32_t working_days=0;

uint32_t madorc_impulse=0;

FunctionalState Sound_key_pressed=DISABLE;

DataUpdateDef DataUpdate;
ADCDataDef ADCData;
SettingsDef Settings;
AlarmDef Alarm;
PowerDef Power;
#ifdef debug
WakeupDef Wakeup;
#endif

void sleep_mode(FunctionalState sleep)
{ 
  if(Settings.Sleep_time>0 && !Power.USB_active)
  {
		Power.Pump_deny=ENABLE;
		if(Power.Pump_active)Pump_now(DISABLE);
		
		set_msi();
    if(sleep)
    {
			RTC_ITConfig(RTC_IT_WUT, DISABLE);

			Power.led_sleep_time=0;
			GPIO_SetBits(GPIOC,GPIO_Pin_13);// ��������� ���������  				

      display_off(); // ��������� �������
 			GPIO_ResetBits(GPIOA,GPIO_Pin_7);// ��������� ����� 1.8 ������, � ������ ������������ �����

			delay_ms(1000); // ��������� ��������� ����������
			DataUpdate.Need_batt_voltage_update=ENABLE; // ��������� ������ ���
			adc_check_event(); // ��������� ��������������
			delay_ms(100); // ��������� ��������� ����������

			PWR_FastWakeUpCmd(DISABLE);
			PWR_UltraLowPowerCmd(ENABLE); 
			PWR_PVDCmd(DISABLE);
			RTC_ITConfig(RTC_IT_WUT, ENABLE);
    }
    else
    {
			RTC_ITConfig(RTC_IT_WUT, DISABLE);
			GPIO_SetBits(GPIOA,GPIO_Pin_7);// ����������� � ����� 3 ������
			delay_ms(400); // ��������� ��������� ����������
      display_on(); // �������� �������
			DataUpdate.Need_batt_voltage_update=ENABLE; // ��������� ������ ���
			DataUpdate.Need_display_update=ENABLE;
			adc_check_event(); // ��������� ��������������
			RTC_ITConfig(RTC_IT_WUT, ENABLE);
			sound_deactivate();
    }
		Power.Pump_deny=DISABLE;
  } 
}


void geiger_calc_fon(void)
{
	DataUpdate.Need_fon_update=DISABLE;  
	DataUpdate.Need_display_update=ENABLE;
  if(fon_level>Settings.Alarm_level && Settings.Alarm_level>0 && Alarm.Alarm_active==DISABLE)
  {
    Alarm.Alarm_active=ENABLE;
		Alarm.User_cancel=DISABLE;
		if(Power.Display_active==DISABLE)
		{
			screen=1;
			Power.sleep_time=Settings.Sleep_time;
			Power.led_sleep_time=Settings.Sleep_time-3;
			sleep_mode(DISABLE);
			sound_activate();
		} else sound_activate();
    
  }
  if((Alarm.Alarm_active && fon_level<Settings.Alarm_level) || (Alarm.Alarm_active && Settings.Alarm_level==0))
  {
		sound_deactivate();
    Power.Sound_active=DISABLE;
    Alarm.Alarm_active=DISABLE;
    Alarm.User_cancel=DISABLE;
    Alarm.Alarm_beep_count=0;
    
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
int main(void)

{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x3000);  

	set_msi();
	DBGMCU_Config(DBGMCU_SLEEP | DBGMCU_STANDBY | DBGMCU_STOP, DISABLE);
		
  set_bor();
	Power.sleep_now=DISABLE;
	
	DataUpdate.Need_erase_flash=ENABLE;
	
  Settings.Geiger_voltage=360; // ���������� �� ������� 360 �����
  Settings.Pump_Energy=350;    // ������� ������� 350 ���
	DataUpdate.current_flash_page=0;
	
	io_init(); // ������������� ������ ��

	eeprom_write_default_settings(); // ��������, �������� �� EEPROM
  eeprom_read_settings(); // ������ �������� �� EEPROM
  screen=1;
	Power.USB_active=DISABLE;
	Power.sleep_time=Settings.Sleep_time;
  Power.Display_active=ENABLE;
	
	ADCData.DAC_voltage_raw=0x610;
		
  dac_init();
	comp_init();
	comp_on();
	timer9_Config(); // ������������� ������ �������	
	timer10_Config();
	tim2_Config();
	sound_activate();
	delay_ms(100);
	sound_deactivate();
//--------------------------------------------------------------------
	RTC_Config();	   // ������������� ����
//--------------------------------------------------------------------
// ������������� �������
//--------------------------------------------------------------------
	delay_ms(50); // ��������� ��������� ����������
  display_on(); 
  LcdInit(); 
  LcdClear(); 
//--------------------------------------------------------------------
  adc_init();
  delay_ms(100);
  adc_calibration();
	delay_ms(10);
//--------------------------------------------------------------------
  EXTI8_Config();
#ifdef version_401
  EXTI9_Config();
#endif
	EXTI3_Config();
  EXTI4_Config();
  EXTI6_Config();
		
	DataUpdate.Need_batt_voltage_update=ENABLE;
	
	if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6))hidden_menu=ENABLE; // �������� ��������� ������� ����
	
	delay_ms(500); // ��������� ��������� ����������
		
  while(1) 
/////////////////////////////////
  {
		if(DataUpdate.Need_fon_update==ENABLE)	geiger_calc_fon();
    if(key>0)																keys_proccessing();
		if(DataUpdate.Need_batt_voltage_update)	adc_check_event();

		////////////////////////////////////////////////////

		
		if((Power.sleep_time>0)&&(!Power.Display_active))sleep_mode(DISABLE); // ���� ������� ��� ��������, � ������� ��� ��� �����������, ��������� ���������� � �������� �������
    
		if(Power.Display_active)
    {
			if(Power.sleep_time==0 && !Alarm.Alarm_active) sleep_mode(ENABLE);  // ������� ��� �������� �� ����, � ������� ��� �������, �� ��������� ��� � �������� ����������
			if(DataUpdate.Need_display_update==ENABLE)
			{
				DataUpdate.Need_display_update=DISABLE;
				LcdClear_massive();
				if (screen==1)main_screen();
				if (screen==2)menu_screen();
				if (screen==3)stat_screen();
			}
///////////////////////////////////////////////////////////////////////////////
		}
#ifdef version_401
		if((!Power.USB_active) && (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))){
			usb_activate(0x0); // ���� ������� USB ������ ���������� �������� USB
		}
#endif

		if(!Power.USB_active)		// ���� USB �� �������, ����� ������� � ���
		{
			if(current_pulse_count<30)      // ���� ������� �� �����������, �� ����� ���� � ���
			{
				if(!Power.Pump_active && !Power.Sound_active)
				{
					PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);    // ��������� � ���
#ifdef debug
 					Wakeup.total_wakeup++;
					DataUpdate.Need_display_update=ENABLE;
#endif

				} else
				{
						PWR_EnterSleepMode(PWR_Regulator_ON, PWR_SLEEPEntry_WFI);
#ifdef debug
  					Wakeup.total_wakeup++;
						DataUpdate.Need_display_update=ENABLE;
#endif
				}
			}
		}else USB_work(); 		// ���� USB �������, ����������� �������� ������
#ifdef debug
 					Wakeup.total_cycle++;
					DataUpdate.Need_display_update=ENABLE;
#endif

  }
/////////////////////////////////////////////////////////////////////////////// 
}
