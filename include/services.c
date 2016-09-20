#include <stdio.h>
#include <stdint.h>
#include "STM32L1xx.h"          // Device header
#include "main.h"

#define DOR_OFFSET                 ((uint32_t)0x0000002C)

// ===============================================================================================

void reload_active_isotop_time()
{
  switch (Settings.Isotop)
  {
  case 0x0:
    Settings.Second_count = Settings.Isotop_count_cs137;
    break;
  case 0x1:
    Settings.Second_count = Settings.Isotop_count_eu152;
    break;
  case 0x2:
    Settings.Second_count = Settings.Isotop_count_na22;
    break;
  case 0x3:
    Settings.Second_count = Settings.Isotop_count_cd109;
    break;
  }
  plus_rad_reset(0x00);
}

// ===============================================================================================

void Pump_now(FunctionalState pump)
{

  if(pump == ENABLE && !Power.Pump_deny)
  {
    while (PWR_GetFlagStatus(PWR_FLAG_VREFINTRDY) == DISABLE);
    Power.Pump_active = ENABLE;
//    dac_on();                   // Включаем ЦАП
    TIM9->EGR |= 0x0001;        // Устанавливаем бит UG для принудительного сброса счетчика
    TIM_ClearITPendingBit(TIM9, TIM_IT_Update);

    TIM_CCxCmd(TIM9, TIM_Channel_1, TIM_CCx_Enable);    // разрешить накачку   
    TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);

    comp_on();                  // Включаем компаратор
  } else
  {
    TIM_CCxCmd(TIM9, TIM_Channel_1, TIM_CCx_Disable);   // запретить накачку
    TIM_ITConfig(TIM9, TIM_IT_Update, DISABLE);
    //pump_counter_avg_impulse_by_1sec[0]++;
    comp_off();                 // Выключаем компаратор
//    dac_off();                  // Выключаем ЦАП
    TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
    Power.Pump_active = DISABLE;
  }
}

// ===============================================================================================


void check_wakeup_keys(void)
{
  if((Power.led_sleep_time > 0) && (Power.Display_active))      // Управление подсветкой
  {
    GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Включаем подсветку 
  } else
  {
    GPIO_SetBits(GPIOC, GPIO_Pin_13);   // Выключаем подсветку                                  
  }

  if((!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)
      && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)) || Power.Display_active)
  {
    if((Settings.Sound == 1) || (Settings.Sound == 2))
      sound_activate();
    Power.sleep_time = Settings.Sleep_time;
    Power.led_sleep_time = Settings.Sleep_time - 3;
  }

}

// ===============================================================================================
// лицухи
//----------------------------------------------------------------
/*
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

*/
// ===============================================================================================
float convert_mkr_sv(uint32_t mkrn)
{
  float sv = 0;
  sv = mkrn;
  sv *= 0.0098;
  return sv;
}




// ===============================================================================================
uint32_t calc_ab(void)
{
  uint32_t i;
  float gamma_level = 0;
  float AB_level = 0;
  float pi4 = 0.78539815;       // Пи/4
  float S = 0;                  //
  float S_multipiller = 0;      //
// fon_level - гамма фон мкР/ч
// fon_level/(Settings.Second_count/60) - частиц в минуту по гамме
  for (i = 0; i < 15; i++)
  {
    AB_level += Detector_AB_massive[i]; // подсчет импульсов за минуту
  }
  gamma_level = (float) fon_level / ((float) Settings.Second_count / 60);       // 198 имп/м

  if(AB_level <= gamma_level)
    return 0;

  AB_level -= gamma_level;

  // Компенсация процента регистрации счетчика
  AB_level *= 100;
  AB_level = AB_level / (float) Settings.Beta_procent;


  S = pi4 * ((float) Settings.Beta_window / 10) * ((float) Settings.Beta_window / 10);  //площадь отверстия
  S_multipiller = 100 / S;      // на сколько надо умножить частицы чтобы выйки на "частиц на см2 за минуту"
  S = AB_level * S_multipiller;

  return (uint32_t) S;
}


// ===============================================================================================
void recalculate_fon(void)
{
  uint32_t i, pointer;
  uint32_t massive_len = Settings.Second_count >> 2;    // 50@200 62@250
  uint32_t recalc_len = massive_len / auto_speedup_factor;      // 62/9 = 6.8

  fon_level = 0;

  for (i = 0; i < recalc_len; i++)
  {
    if(Detector_massive_pointer >= i)
    {
      pointer = Detector_massive_pointer - i;
    } else
    {
      pointer = massive_len - (i - Detector_massive_pointer);
    }
    fon_level += Detector_massive[pointer];
  }

  fon_level = (fon_level * auto_speedup_factor) + ((fon_level / recalc_len) * (massive_len % auto_speedup_factor));     // фон 6-ти ячеек * 9 + ячейка 24000/6=4000; остаток от деления 8
  // (4000/9*)8=3552; 24000+3552=27552
}


// ===============================================================================================
void sleep_mode(FunctionalState sleep)
{
  if(Settings.Sleep_time > 0 && !Power.USB_active)
  {
    Power.Pump_deny = ENABLE;
    if(Power.Pump_active)
      Pump_now(DISABLE);

    set_msi();
    if(sleep)
    {
      RTC_ITConfig(RTC_IT_WUT, DISABLE);

      Power.led_sleep_time = 0;
      GPIO_SetBits(GPIOC, GPIO_Pin_13); // Выключаем подсветку                                  

      display_off();            // выключить дисплей
      GPIO_ResetBits(GPIOA, GPIO_Pin_7);        // Фиксируем режим 1.8 вольта, с низким потреблением ножки

      delay_ms(1000);           // подождать установки напряжения
      DataUpdate.Need_batt_voltage_update = ENABLE;     // разрешить работу АЦП
      adc_check_event();        // запустить преобразование
      delay_ms(100);            // подождать установки напряжения

      //PWR_FastWakeUpCmd(ENABLE);
      PWR_UltraLowPowerCmd(ENABLE);
      PWR_PVDCmd(DISABLE);
      RTC_ITConfig(RTC_IT_WUT, ENABLE);
    } else
    {
      RTC_ITConfig(RTC_IT_WUT, DISABLE);
      GPIO_SetBits(GPIOA, GPIO_Pin_7);  // Переключаем в режим 3 вольта
      delay_ms(400);            // подождать установки напряжения
      display_on();             // включить дисплей
      DataUpdate.Need_batt_voltage_update = ENABLE;     // разрешить работу АЦП
      DataUpdate.Need_display_update = ENABLE;
      adc_check_event();        // запустить преобразование
      RTC_ITConfig(RTC_IT_WUT, ENABLE);
      sound_deactivate();
    }
    Power.Pump_deny = DISABLE;
  }
}



// ===============================================================================================
void geiger_calc_fon(void)
{
  DataUpdate.Need_fon_update = DISABLE;
  DataUpdate.Need_display_update = ENABLE;
  if(fon_level > Settings.Alarm_level && Settings.Alarm_level > 0 && Alarm.Alarm_active == DISABLE)
  {
    Alarm.Alarm_active = ENABLE;
    Alarm.User_cancel = DISABLE;
    if(Power.Display_active == DISABLE)
    {
      screen = 1;
      Power.sleep_time = Settings.Sleep_time;
      Power.led_sleep_time = Settings.Sleep_time - 3;
      sleep_mode(DISABLE);
      sound_activate();
    } else
      sound_activate();

  }
  if((Alarm.Alarm_active && fon_level < Settings.Alarm_level) || (Alarm.Alarm_active && Settings.Alarm_level == 0))
  {
    sound_deactivate();
    Power.Sound_active = DISABLE;
    Alarm.Alarm_active = DISABLE;
    Alarm.User_cancel = DISABLE;
    Alarm.Alarm_beep_count = 0;

  }
}

// ===============================================================================================
