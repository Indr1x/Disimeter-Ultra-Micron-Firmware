#include <stdio.h>
#include <stdint.h>
#include "STM32L1xx.h"                  // Device header
#include "main.h"


// ===============================================================================================

void Pump_now(FunctionalState pump)
{

	if(pump==ENABLE && !Power.Pump_deny)
	{
		Power.Pump_active=ENABLE;
		dac_on();  // �������� ���
		TIM9->EGR |= 0x0001;  // ������������� ��� UG ��� ��������������� ������ ��������
		TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
		
		TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);
		TIM_CCxCmd(TIM9, TIM_Channel_1, TIM_CCx_Enable); // ��������� �������	

		comp_on(); // �������� ����������
	} else {
		TIM_ITConfig(TIM9, TIM_IT_Update, DISABLE);
		TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
		TIM_CCxCmd(TIM9, TIM_Channel_1, TIM_CCx_Disable); // ��������� �������
				//pump_counter_avg_impulse_by_1sec[0]++;
		comp_off();              // ��������� ����������
		dac_off(); // ��������� ���
		Power.Pump_active=DISABLE;
	}
}

// ===============================================================================================


void check_wakeup_keys(void)
{
		if((Power.led_sleep_time>0)&&(Power.Display_active)) // ���������� ����������
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);// �������� ��������� 
		} else {
			GPIO_SetBits(GPIOC,GPIO_Pin_13);// ��������� ���������  				
		}			

	if ((!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)) || Power.Display_active)
	{
		if((Settings.Sound == 1) || (Settings.Sound == 2))sound_activate();
    Power.sleep_time=Settings.Sleep_time;
		Power.led_sleep_time=Settings.Sleep_time-3;
	}
	
}

// ===============================================================================================
// ������
//----------------------------------------------------------------
FunctionalState check_license(void)
{
	#define lic_num 14
	const uint32_t license[lic_num] = {
																0x42C86A97, // Shodan handmade black 	0D473130 35383935 00490032
																0x43B26A93, // Shodan handmade black 	0E473130 35383935 0033002E
																0x44B26AAA, // Shodan handmade white 	0F473130 35383935 00330045
																0x43A86A98, // Shodan handmade white 	0E473130 35383935 00290033
																0x43A96A98, // Nusik1975             	0E473130 35383935 002A0033
																0x44C36A84, // Nusik1975 						 	0F473130 35383935 0044001F
																0x44AD6A8F, // Nusik1975 							0F473130 35383935 002E002A
																0x41F062A9, // Nusik1975 							18473034 29313236 0078003F
																0x47A06C84, // FullName 							13473330 34363934 00230020
																0x4AC46791, // FullName 							17473334 33353436 00480027	
																0x4AC46790, // FullName 							17473334 33353436 00480026
																0x4A9E67AC, // FullName 							17473334 33353436 00220042
																0x47A06C88, // FullName 							13473330 34363934 00230024
																0x42C06A9E  // Ivanjust              	0D473130 35383935 00410039
															 };

	uint32_t i=0, CPU_serial=0, EEPROM_serial=0, tmp=0;
	FunctionalState found=DISABLE;
	
	CPU_serial+=U_ID_0;
	CPU_serial+=U_ID_1;
	CPU_serial+=U_ID_2;

	tmp=Settings.serial0 & 0xff;
	tmp=tmp<<24;
	EEPROM_serial+=tmp;

	tmp=Settings.serial1 & 0xff;
	tmp=tmp<<16;
	EEPROM_serial+=tmp;

	tmp=Settings.serial2 & 0xff;
	tmp=tmp<<8;
	EEPROM_serial+=tmp;

	tmp=Settings.serial3 & 0xff;
	EEPROM_serial+=tmp;

	if (CPU_serial == EEPROM_serial)
	{
		found=ENABLE;
	} 
	else
	{
		for (i=0;i<lic_num;i++) if( CPU_serial == license[i]) found=ENABLE;
	}
	
	return found;
	
}




// ===============================================================================================
float convert_mkr_sv(uint32_t mkrn)
{
	float sv=0;
	sv=mkrn;
	sv*=0.0098;
	return sv;
}



// ===============================================================================================
void recalculate_fon(void)
{
	int i,pointer;
	int massive_len=Settings.Second_count>>2; // 50@200 62@250
	int recalc_len=massive_len/auto_speedup_factor; // 62/9 = 6.8
	float tmp;
	
	fon_level=0;				  
					
	for(i=0;i<recalc_len;i++)
	{
		if(Detector_massive_pointer>=i)
		{
			pointer=Detector_massive_pointer-i;
		}else
		{
			pointer=massive_len-(i-Detector_massive_pointer);
		}
		fon_level+=Detector_massive[pointer];
	}
	tmp=fon_level; // ��� 6-�� ����� (��� ��������� 9)... 24 000
	//tmp=tmp/recalc_len;
	//tmp=tmp*(massive_len/auto_speedup_factor);
	tmp=tmp*auto_speedup_factor;
	tmp=tmp+(((tmp/recalc_len)/auto_speedup_factor)*(massive_len % auto_speedup_factor)); // ������ 24000/6=4000; ������� �� ������� 8
																																												// (4000/9*)8=3552; 24000+3552=27552
	fon_level=(uint32_t)tmp;
}

/*

// ===============================================================================================
void RTC_tick_processing(void)
{
	uint32_t i;
	
	DataUpdate.RTC_tick_update=DISABLE;
	
		if(!poweroff_state)
		{
			DataUpdate.Need_display_update=ENABLE;
				
			if(Power.USB_active)
			{
				USB_not_active++; // ������� ������������ USB
				madorc_impulse+=Detector_massive[Detector_massive_pointer]; // ������� ��������� ��� �������� �� USB
			}
			
			// ������� ������� ��� ���������� ���������� ��� (������ 4 ������)
			if(DataUpdate.Batt_update_time_counter>75) 
			{
				DataUpdate.Need_batt_voltage_update=ENABLE;
				DataUpdate.Batt_update_time_counter=0;
			} else DataUpdate.Batt_update_time_counter++;
			
			// ������� ������� ��� ���������� �������� ��������� �������
			if(DataUpdate.pump_counter_update_time>14) 
			{
#ifdef debug
				Wakeup.total_wakeup=0;
				Wakeup.total_cycle=0;
				Wakeup.rtc_wakeup=0;
				Wakeup.tim9_wakeup=0;
				Wakeup.pump_wakeup=0;
				Wakeup.comp_wakeup=0;
				Wakeup.sensor_wakeup=0;
#endif

				if(!Power.USB_active)madorc_impulse=0;
				pump_counter_avg_impulse_by_1sec[1]=pump_counter_avg_impulse_by_1sec[0];
				pump_counter_avg_impulse_by_1sec[0]=0;
				DataUpdate.pump_counter_update_time=0;

				if((Power.led_sleep_time>0)&&(Power.Display_active)) // ���������� ����������
				{
					GPIO_ResetBits(GPIOC,GPIO_Pin_13);// �������� ��������� 
				} else {
					GPIO_SetBits(GPIOC,GPIO_Pin_13);// ��������� ���������  				
				}			
								
				if(pump_counter_avg_impulse_by_1sec[1]==0) //������� �� ������ ����� � ��������
				{
					dac_init();
					Pump_now(DISABLE);
					while(RTC_WakeUpCmd(DISABLE)!=SUCCESS);
					RTC_SetWakeUpCounter(0xF96); 			// ���������� ������� ���������� = 2 �������
					current_pulse_count=0;
					while(RTC_WakeUpCmd(ENABLE)!=SUCCESS);
				}

			} else DataUpdate.pump_counter_update_time++;
	
			// ������� ����
			if(DataUpdate.days_sec_count>=24600) // ������ 24 ���� �����
			{
				DataUpdate.days_sec_count=0;
				working_days++;
				
			} else DataUpdate.days_sec_count++;
			// ����� ������� ����
			if(DataUpdate.doze_sec_count>=150) // ������ 10 ����� (150)
			{
				if(DataUpdate.Need_erase_flash==ENABLE){full_erase_flash();DataUpdate.Need_erase_flash=DISABLE;}
				DataUpdate.Need_update_mainscreen_counters=ENABLE;

				// -----------------------------------------------------
				DataUpdate.doze_count++;
				if(DataUpdate.doze_count>=doze_length) // ������ �������� �� Flash
				{
					DataUpdate.doze_count=0;
					flash_write_page(DataUpdate.current_flash_page);
					DataUpdate.current_flash_page++;
					if(DataUpdate.current_flash_page > (FLASH_MAX_PAGE)) // ���� �� ��������� ���������
						DataUpdate.current_flash_page=0;
				}
				// -----------------------------------------------------

				for(i=doze_length;i>0;i--)
				{
					ram_Doze_massive[i]=ram_Doze_massive[i-1];                        // ����� ������� ����
					ram_max_fon_massive[i]=ram_max_fon_massive[i-1];                  // ����� ������� ������������� ����
				}
				ram_Doze_massive[0]=0;
				ram_max_fon_massive[0]=0;
				DataUpdate.doze_sec_count=1; //// !!!!! 0

			} else DataUpdate.doze_sec_count++;
			////////////////////////////////////////////////////	

			
			////////////////////////////////////////////////////    
				if(Detector_massive[Detector_massive_pointer]>9)
				{	
					if(Detector_massive[Detector_massive_pointer]>199) // ������� �� 9 ��� ���� ����� 10 000
					{ 
						if(auto_speedup_factor!=10)auto_speedup_factor=9;
					} else
					{
						if(Detector_massive[Detector_massive_pointer]>99) // ������� �� 5 ��� ���� ����� 5 000
						{ 
							if(auto_speedup_factor!=5)auto_speedup_factor=5;
						} else
						{
							if(Detector_massive[Detector_massive_pointer]>19) // ������� �� 3 ��� ���� ����� 1 000
							{ 
								if(auto_speedup_factor!=3)auto_speedup_factor=3;
							} else
							{ // ������� �� 2 ��� ���� ����� 500
								if(auto_speedup_factor!=2)auto_speedup_factor=2;
							}
						}
					}
					
					if(auto_speedup_factor!=1)recalculate_fon(); // �������� ����, ���� ������������� ���������
					
				} else
				{ // ���� ��������� �� ���������
					if(auto_speedup_factor!=1){auto_speedup_factor=1;recalculate_fon();}
					else
					{	fon_level+=Detector_massive[Detector_massive_pointer];}
				}

				Detector_massive_pointer++;
				if(Detector_massive_pointer>=(Settings.Second_count>>2))	
				{
					if(auto_speedup_factor==1)fon_level-=Detector_massive[0];
					Detector_massive[0]=0;
					Detector_massive_pointer=0;
				}else
				{
					if(auto_speedup_factor==1)fon_level-=Detector_massive[Detector_massive_pointer];
					Detector_massive[Detector_massive_pointer]=0;
				}
				if(fon_level>ram_max_fon_massive[0])ram_max_fon_massive[0]=fon_level; // ���������� ������� ������������� ����
			
				DataUpdate.Need_fon_update=ENABLE;
			////////////////////////////////////////////////////
		
			if(Power.sleep_time>4){Power.sleep_time-=4;}
			else{Power.sleep_time=0;}
			
			if(Power.led_sleep_time>4){Power.led_sleep_time-=4;}
			else{Power.led_sleep_time=0;}
		}	
}
*/


// ===============================================================================================
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



// ===============================================================================================
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
// ===============================================================================================
