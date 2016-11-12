#include "stm32l1xx.h"
#include "main.h"

__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;
__IO TestStatus DataMemoryProgramStatus = PASSED;
uint32_t NbrOfPage = 0, j = 0, Address = 0;

//**************************************************************************
// Запись параметров по умолчанию
void eeprom_write_default_settings(void)
{
  if(eeprom_read(Isotop_count_cs137_address) == 0x00)
  {
    Settings.Alarm_level = 50;
    Settings.Sound = ENABLE;
    Settings.Sleep_time = 80;
    Settings.Display_reverse = 2;
    Settings.LSI_freq = 37000;
    Settings.Geiger_voltage = 360;
    Settings.Power_comp = 0;
    Settings.Vibro = 0;
    Settings.v4_target_pump = 8;
    Settings.units = 0;
    Settings.Beta_window = 20;
    Settings.Beta_procent = 37;
    Settings.VRef = 1224;
    Settings.Pump_aggressive = 0;
    Settings.Speedup = 0;
    Settings.Isotop = 0;
    Settings.Isotop_count_cs137 = 250;
    Settings.Isotop_count_eu152 = 250;
    Settings.Isotop_count_na22 = 250;
    Settings.Isotop_count_cd109 = 250;
    Settings.Isotop_count_am241 = 250;
    Settings.Isotop_ACAL_cs137 = 250;
    Settings.Isotop_ACAL_eu152 = 250;
    Settings.Isotop_ACAL_na22 = 250;
    Settings.Isotop_ACAL_cd109 = 250;
    Settings.Isotop_ACAL_am241 = 250;
    Settings.AMODUL_spect_start = 1000;
    Settings.AMODUL_spect_multi = 14;
    Settings.AMODUL_spect_mark1 = 10;
    Settings.AMODUL_spect_mark2 = 20;
    Settings.AMODUL_spect_mark3 = 30;
    Settings.AMODUL_spect_mark4 = 40;
    Settings.AMODUL_spect_mark5 = 50;


    eeprom_write_settings();    // Запись
  }
}

//**************************************************************************

void eeprom_write_settings(void)
{

  //Запись параметров в EEPROM
  if(eeprom_read(Alarm_level_address) != Settings.Alarm_level)
    eeprom_write(Alarm_level_address, Settings.Alarm_level);
  if(eeprom_read(Sleep_time_address) != Settings.Sleep_time)
    eeprom_write(Sleep_time_address, Settings.Sleep_time);
  if(eeprom_read(contrast_address) != Settings.contrast)
    eeprom_write(contrast_address, Settings.contrast);
  if(eeprom_read(Display_reverse_address) != Settings.Display_reverse)
    eeprom_write(Display_reverse_address, Settings.Display_reverse);
  if(eeprom_read(Sound_address) != Settings.Sound)
    eeprom_write(Sound_address, Settings.Sound);
  if(eeprom_read(Power_comp_address) != Settings.Power_comp)
    eeprom_write(Power_comp_address, Settings.Power_comp);
  if(eeprom_read(Vibro_address) != Settings.Vibro)
    eeprom_write(Vibro_address, Settings.Vibro);
  if(eeprom_read(Geiger_voltage_address) != Settings.Geiger_voltage)
    eeprom_write(Geiger_voltage_address, Settings.Geiger_voltage);
  if(eeprom_read(v4_target_pump_address) != Settings.v4_target_pump)
    eeprom_write(v4_target_pump_address, Settings.v4_target_pump);
  if(eeprom_read(Beta_window_address) != Settings.Beta_window)
    eeprom_write(Beta_window_address, Settings.Beta_window);
  if(eeprom_read(Beta_procent_address) != Settings.Beta_procent)
    eeprom_write(Beta_procent_address, Settings.Beta_procent);
  if(eeprom_read(VRef_address) != Settings.VRef)
    eeprom_write(VRef_address, Settings.VRef);
  if(eeprom_read(Pump_aggressive_address) != Settings.Pump_aggressive)
    eeprom_write(Pump_aggressive_address, Settings.Pump_aggressive);
  if(eeprom_read(units_address) != Settings.units)
    eeprom_write(units_address, Settings.units);
  if(eeprom_read(Speedup_address) != Settings.Speedup)
    eeprom_write(Speedup_address, Settings.Speedup);

  if(eeprom_read(Isotop_address) != Settings.Isotop)
    eeprom_write(Isotop_address, Settings.Isotop);

  if(eeprom_read(Isotop_count_cs137_address) != Settings.Isotop_count_cs137)
    eeprom_write(Isotop_count_cs137_address, Settings.Isotop_count_cs137);
  if(eeprom_read(Isotop_count_eu152_address) != Settings.Isotop_count_eu152)
    eeprom_write(Isotop_count_eu152_address, Settings.Isotop_count_eu152);
  if(eeprom_read(Isotop_count_na22_address) != Settings.Isotop_count_na22)
    eeprom_write(Isotop_count_na22_address, Settings.Isotop_count_na22);
  if(eeprom_read(Isotop_count_cd109_address) != Settings.Isotop_count_cd109)
    eeprom_write(Isotop_count_cd109_address, Settings.Isotop_count_cd109);
  if(eeprom_read(Isotop_count_am241_address) != Settings.Isotop_count_am241)
    eeprom_write(Isotop_count_am241_address, Settings.Isotop_count_am241);

  if(eeprom_read(Isotop_ACAL_cs137_address) != Settings.Isotop_ACAL_cs137)
    eeprom_write(Isotop_ACAL_cs137_address, Settings.Isotop_ACAL_cs137);
  if(eeprom_read(Isotop_ACAL_eu152_address) != Settings.Isotop_ACAL_eu152)
    eeprom_write(Isotop_ACAL_eu152_address, Settings.Isotop_ACAL_eu152);
  if(eeprom_read(Isotop_ACAL_na22_address) != Settings.Isotop_ACAL_na22)
    eeprom_write(Isotop_ACAL_na22_address, Settings.Isotop_ACAL_na22);
  if(eeprom_read(Isotop_ACAL_cd109_address) != Settings.Isotop_ACAL_cd109)
    eeprom_write(Isotop_ACAL_cd109_address, Settings.Isotop_ACAL_cd109);
  if(eeprom_read(Isotop_ACAL_am241_address) != Settings.Isotop_ACAL_am241)
    eeprom_write(Isotop_ACAL_am241_address, Settings.Isotop_ACAL_am241);


  if(eeprom_read(AMODUL_spect_start_address) != Settings.AMODUL_spect_start)
    eeprom_write(AMODUL_spect_start_address, Settings.AMODUL_spect_start);
  if(eeprom_read(AMODUL_spect_multi_address) != Settings.AMODUL_spect_multi)
    eeprom_write(AMODUL_spect_multi_address, Settings.AMODUL_spect_multi);

  if(eeprom_read(AMODUL_spect_mark1_address) != Settings.AMODUL_spect_mark1)
    eeprom_write(AMODUL_spect_mark1_address, Settings.AMODUL_spect_mark1);
  if(eeprom_read(AMODUL_spect_mark2_address) != Settings.AMODUL_spect_mark2)
    eeprom_write(AMODUL_spect_mark2_address, Settings.AMODUL_spect_mark2);
  if(eeprom_read(AMODUL_spect_mark3_address) != Settings.AMODUL_spect_mark3)
    eeprom_write(AMODUL_spect_mark3_address, Settings.AMODUL_spect_mark3);
  if(eeprom_read(AMODUL_spect_mark4_address) != Settings.AMODUL_spect_mark4)
    eeprom_write(AMODUL_spect_mark4_address, Settings.AMODUL_spect_mark4);
  if(eeprom_read(AMODUL_spect_mark5_address) != Settings.AMODUL_spect_mark5)
    eeprom_write(AMODUL_spect_mark5_address, Settings.AMODUL_spect_mark5);


  if(Settings.LSI_freq != 0x00) // если запустился кварц, попытки сохранения игнорировать
  {
    if(eeprom_read(LSI_freq_address) != Settings.LSI_freq)
      eeprom_write(LSI_freq_address, Settings.LSI_freq);
  }
}

//**************************************************************************
void eeprom_apply_settings(void)
{
  if(eeprom_read(contrast_address) != Settings.contrast)
  {
    display_off();
    delay_ms(200);
    display_on();
  }
  // -------------------------------------------------------------------
  if(eeprom_read(Display_reverse_address) != Settings.Display_reverse)
  {
    display_off();
    delay_ms(200);
    display_on();
  }

  if(eeprom_read(units_address) != Settings.units)
  {
//              Settings.units=0;
  }
  // -------------------------------------------------------------------
  if(eeprom_read(v4_target_pump_address) != Settings.v4_target_pump)
  {
    reset_TIM_prescallers_and_Compare();
  }
  // -------------------------------------------------------------------
  if(eeprom_read(Geiger_voltage_address) != Settings.Geiger_voltage)
  {
//    dac_reload();               //перезагрузить в ЦАП новое напряжение отсечки накачки
  }
  // -------------------------------------------------------------------
  if(eeprom_read(LSI_freq_address) != Settings.LSI_freq)
  {
    if(Settings.LSI_freq != 0x00)       // если запустился кварц, попытки сохранения игнорировать
    {
      eeprom_write(LSI_freq_address, Settings.LSI_freq);
      NVIC_SystemReset();
    }
  }
  // -------------------------------------------------------------------
  if(eeprom_read(Isotop_address) != Settings.Isotop)
  {
    reload_active_isotop_time();
  }
  // -------------------------------------------------------------------
  if(eeprom_read(Isotop_count_cs137_address) != Settings.Isotop_count_cs137)
  {
    reload_active_isotop_time();
  }
  // -------------------------------------------------------------------
  if(eeprom_read(Isotop_count_eu152_address) != Settings.Isotop_count_eu152)
  {
    reload_active_isotop_time();
  }
  // -------------------------------------------------------------------
  if(eeprom_read(Isotop_count_na22_address) != Settings.Isotop_count_na22)
  {
    reload_active_isotop_time();
  }
  // -------------------------------------------------------------------
  if(eeprom_read(Isotop_count_cd109_address) != Settings.Isotop_count_cd109)
  {
    reload_active_isotop_time();
  }
  // -------------------------------------------------------------------
  if(eeprom_read(Isotop_count_am241_address) != Settings.Isotop_count_am241)
  {
    reload_active_isotop_time();
  }
  // -------------------------------------------------------------------

  if(eeprom_read(Isotop_ACAL_cs137_address) != Settings.Isotop_ACAL_cs137)
  {
    reload_active_isotop_time();
  }
  // -------------------------------------------------------------------
  if(eeprom_read(Isotop_ACAL_eu152_address) != Settings.Isotop_ACAL_eu152)
  {
    reload_active_isotop_time();
  }
  // -------------------------------------------------------------------
  if(eeprom_read(Isotop_ACAL_na22_address) != Settings.Isotop_ACAL_na22)
  {
    reload_active_isotop_time();
  }
  // -------------------------------------------------------------------
  if(eeprom_read(Isotop_ACAL_cd109_address) != Settings.Isotop_ACAL_cd109)
  {
    reload_active_isotop_time();
  }
  // -------------------------------------------------------------------
  if(eeprom_read(Isotop_ACAL_am241_address) != Settings.Isotop_ACAL_am241)
  {
    reload_active_isotop_time();
  }

}

//**************************************************************************

void eeprom_read_settings(void)
{
  //Чтение параметров из EEPROM
  Settings.Alarm_level = eeprom_read(Alarm_level_address);
  Settings.Sleep_time = eeprom_read(Sleep_time_address);
  Settings.contrast = eeprom_read(contrast_address);
  Settings.Display_reverse = eeprom_read(Display_reverse_address);
  Settings.Sound = eeprom_read(Sound_address);
  Settings.LSI_freq = eeprom_read(LSI_freq_address);
  Settings.Power_comp = eeprom_read(Power_comp_address);
  Settings.Vibro = eeprom_read(Vibro_address);
  Settings.Geiger_voltage = eeprom_read(Geiger_voltage_address);
  Settings.v4_target_pump = eeprom_read(v4_target_pump_address);
  Settings.units = eeprom_read(units_address);
  Settings.serial0 = eeprom_read(unlock_0_address);
  Settings.serial1 = eeprom_read(unlock_1_address);
  Settings.serial2 = eeprom_read(unlock_2_address);
  Settings.serial3 = eeprom_read(unlock_3_address);
  Settings.Beta_window = eeprom_read(Beta_window_address);
  Settings.Beta_procent = eeprom_read(Beta_procent_address);
  Settings.VRef = eeprom_read(VRef_address);
  Settings.Pump_aggressive = eeprom_read(Pump_aggressive_address);
  Settings.Speedup = eeprom_read(Speedup_address);

  Settings.Isotop = eeprom_read(Isotop_address);
  Settings.Isotop_count_cs137 = eeprom_read(Isotop_count_cs137_address);
  Settings.Isotop_count_eu152 = eeprom_read(Isotop_count_eu152_address);
  Settings.Isotop_count_na22 = eeprom_read(Isotop_count_na22_address);
  Settings.Isotop_count_cd109 = eeprom_read(Isotop_count_cd109_address);

  Settings.Isotop_ACAL_cs137 = eeprom_read(Isotop_ACAL_cs137_address);
  Settings.Isotop_ACAL_eu152 = eeprom_read(Isotop_ACAL_eu152_address);
  Settings.Isotop_ACAL_na22 = eeprom_read(Isotop_ACAL_na22_address);
  Settings.Isotop_ACAL_cd109 = eeprom_read(Isotop_ACAL_cd109_address);

  Settings.AMODUL_spect_start = eeprom_read(AMODUL_spect_start_address);
  Settings.AMODUL_spect_multi = eeprom_read(AMODUL_spect_multi_address);

  Settings.AMODUL_spect_mark1 = eeprom_read(AMODUL_spect_mark1_address);
  Settings.AMODUL_spect_mark2 = eeprom_read(AMODUL_spect_mark2_address);
  Settings.AMODUL_spect_mark3 = eeprom_read(AMODUL_spect_mark3_address);
  Settings.AMODUL_spect_mark4 = eeprom_read(AMODUL_spect_mark4_address);
  Settings.AMODUL_spect_mark5 = eeprom_read(AMODUL_spect_mark5_address);



  // Если не установленны какие-то из важных параметров, то произвести сброс.
  if((Settings.VRef == 0) ||
     (Settings.v4_target_pump == 0) || (Settings.Geiger_voltage == 0) || (Settings.Beta_procent == 0) || (Settings.Beta_window == 0))
  {
    Settings.Geiger_voltage = 360;
    Settings.v4_target_pump = 8;
    Settings.Beta_window = 20;
    Settings.Beta_procent = 37;
    Settings.VRef = 1224;

    eeprom_write_settings();    // Запись
  }
}


//**************************************************************************
void eeprom_erase(void)
{
  DATA_EEPROM_Unlock();         // разблокировка перед записью

  /* Clear all pending flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);

  /*  Data EEPROM Fast Word program of FAST_DATA_32 at addresses defined by 
     DATA_EEPROM_START_ADDR and DATA_EEPROM_END_ADDR */
  Address = DATA_EEPROM_START_ADDR;

  NbrOfPage = ((DATA_EEPROM_END_ADDR - Address) + 1) >> 2;

  /* Erase the Data EEPROM Memory pages by Word (32-bit) */
  for (j = 0; j < NbrOfPage; j++)
  {
    FLASHStatus = DATA_EEPROM_EraseWord(Address + (4 * j));
  }
  DATA_EEPROM_Lock();

  /* Check the correctness of written data */
  while (Address < DATA_EEPROM_END_ADDR)
  {
    if(*(__IO uint32_t *) Address != 0x0)
    {
      DataMemoryProgramStatus = FAILED;
      //ОШИБКА стирания !!!!
      return;
    }
    Address = Address + 4;
  }

}



//************************************************************************
uint32_t eeprom_read(uint32_t address_of_read)
{

  /* Clear all pending flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);

  /*  Data EEPROM Fast Word program of FAST_DATA_32 at addresses defined by 
     DATA_EEPROM_START_ADDR and DATA_EEPROM_END_ADDR */
  Address = DATA_EEPROM_START_ADDR + address_of_read;
  if(Address > DATA_EEPROM_END_ADDR)
  {
    // ОШИБКА вне диапазона eeprom !!!!
    return 0x00;
  }
  // чтение данных
  return *(__IO uint32_t *) Address;
}



//************************************************************************

void eeprom_write(uint32_t address_of_read, uint32_t data)
{

  DATA_EEPROM_Unlock();         // разблокировка перед записью

  /* Clear all pending flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);

  /*  Data EEPROM Fast Word program of FAST_DATA_32 at addresses defined by 
     DATA_EEPROM_START_ADDR and DATA_EEPROM_END_ADDR */
  Address = DATA_EEPROM_START_ADDR + address_of_read;
  if(Address > DATA_EEPROM_END_ADDR)
  {
    // ОШИБКА вне диапазона eeprom !!!!
    DATA_EEPROM_Lock();
    return;
  }
  // Запись данных по адресу
  FLASHStatus = DATA_EEPROM_ProgramWord(Address, data);
  DATA_EEPROM_Lock();

  if(FLASHStatus != FLASH_COMPLETE)
  {
    // ОШИБКА записи eeprom !!!!
    return;
  }
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR);


  // Проверка записанных данных 
  if(*(__IO uint32_t *) Address != data)
  {
    DataMemoryProgramStatus = FAILED;
    // ОШИБКА записи !!!!!
    return;
  }



}
