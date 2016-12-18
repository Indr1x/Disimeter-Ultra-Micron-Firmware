#include "stm32l1xx_it.h"
#include "main.h"



uint16_t tmpCC1[2] = { 0, 0 };

extern __IO uint32_t CaptureNumber, PeriodValue;
uint32_t IC1ReadValue1 = 0, IC1ReadValue2 = 0;


// ===============================================================================================
void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
* @brief  This function handles Memory Manage exception.
* @param  None
* @retval None
*/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles Bus Fault exception.
* @param  None
* @retval None
*/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles Usage Fault exception.
* @param  None
* @retval None
*/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles SVCall exception.
* @param  None
* @retval None
*/
void SVC_Handler(void)
{
}

/**
* @brief  This function handles Debug Monitor exception.
* @param  None
* @retval None
*/
void DebugMon_Handler(void)
{
}

/**
* @brief  This function handles PendSVC exception.
* @param  None
* @retval None
*/
void PendSV_Handler(void)
{
}

/**
* @brief  This function handles SysTick Handler.
* @param  None
* @retval None
*/
void SysTick_Handler(void)
{
  extern uint32_t msTicks;
  msTicks++;                    // ��������� �������� �������
}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_xx.s).                                            */
/******************************************************************************/

/**
* @brief  This function handles PPP interrupt request.
* @param  None
* @retval None
*/
/*void PPP_IRQHandler(void)
{
}*/

/**
* @}
*/

// =======================================================
// ���������� �� ������� ������ 0
void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET)
  {
    if(!poweroff_state)
    {
      if(Alarm.Alarm_active && !Alarm.User_cancel)
      {
        Alarm.User_cancel = ENABLE;
        sound_deactivate();
      } else
      {
        if(Power.Display_active)
        {
          key |= 0x1;           // ������ ��nu
        }
      }
      Sound_key_pressed = ENABLE;
      check_wakeup_keys();
    }
    EXTI_ClearITPendingBit(EXTI_Line3);
  }
}

// =======================================================
// ���������� �� ������� ������ 1
void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4) != RESET)
  {
    if(!poweroff_state)
    {
      if(Power.Display_active)
      {
        key |= 0x4;             // ������ -
      }
      Sound_key_pressed = ENABLE;
      check_wakeup_keys();
    }
    EXTI_ClearITPendingBit(EXTI_Line4);
  }
}

// =======================================================
// ���������� �� �������� �� �������� 1 � ������ 2
void EXTI9_5_IRQHandler(void)
{
  extern __IO uint8_t Receive_Buffer[64];
  extern __IO uint32_t Receive_length;
  extern __IO uint32_t length;
  if(EXTI_GetITStatus(EXTI_Line8) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line8);
    if(!poweroff_state)
    {
      if(Settings.AB_mode < 2)
      {
        Detector_massive[Detector_massive_pointer]++;   // ��������� ��������� ������� � ��������  
        ram_Doze_massive[0]++;  // ���������� ��������� ������� ����
      } else
      {
        Detector_AB_massive[0]++;
      }

      if(Power.Pump_active == DISABLE)
      {
        if(last_count_pump_on_impulse > 10)
        {
          pump_on_impulse = ENABLE;
          last_count_pump_on_impulse = 0;
          Pump_now(ENABLE);
        } else
          last_count_pump_on_impulse++;
      }
      if(Settings.Sound && !(Alarm.Alarm_active && !Alarm.User_cancel))
      {
        if(Power.Display_active)
        {
          sound_activate();
        }
      }
    }
  }

  if(EXTI_GetITStatus(EXTI_Line6) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line6);
    if(!poweroff_state)
    {
      if(Power.Display_active)
      {
        key |= 0x2;             // ������ +
      }
      Sound_key_pressed = ENABLE;
      check_wakeup_keys();
    }
  }
#ifdef version_401
  if(EXTI_GetITStatus(EXTI_Line9) != RESET)     // ���������� USB
  {
    EXTI_ClearITPendingBit(EXTI_Line9);
    if(!poweroff_state)
    {
      sound_activate();
      Power.sleep_time = Settings.Sleep_time;
    }
  }
#endif

}


// =======================================================
// ���������� ��� ����� ��������� ������ �������� �������
void TIM9_IRQHandler(void)
{
  if((TIM9->CCER & (TIM_CCx_Enable << TIM_Channel_1)) && !poweroff_state)
  {
    current_pulse_count++;
    pump_counter_avg_impulse_by_1sec[0]++;
    if(COMP->CSR & COMP_CSR_INSEL)      // ���� ���������� �������
    {
      if(Power.Pump_active == DISABLE)
        Pump_now(DISABLE);
    } else
    {
      comp_on();
    }
  }
  TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
}

// ========================================================
// ��������� ����� �� �������
void TIM3_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    if(!poweroff_state)
    {
      if(Alarm.Alarm_active && !Alarm.User_cancel)
      {
        Alarm.Alarm_beep_count++;
        if(Alarm.Alarm_beep_count == 100)
          TIM_SetAutoreload(TIM10, 32);
        if(Alarm.Alarm_beep_count == 200)
        {
          TIM_SetAutoreload(TIM10, 16);
          Alarm.Alarm_beep_count = 0;
        }
      }

      if((Alarm.Alarm_active && Alarm.User_cancel) || !Alarm.Alarm_active)
      {
        if(Power.Sound_active == ENABLE)
        {
          if(Sound_key_pressed) // ������� ������
          {
            if(Alarm.Tick_beep_count > 80)
            {
              Alarm.Tick_beep_count = 0;
              sound_deactivate();
            } else
              Alarm.Tick_beep_count++;

          } else if(Alarm.Tick_beep_count > 6)  // ��� �������
          {
            Alarm.Tick_beep_count = 0;
            sound_deactivate();
          } else
            Alarm.Tick_beep_count++;
        } else
          sound_deactivate();
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������-�

void TIM2_IRQHandler(void)
{
  uint32_t i = 0;
  if(TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
    if(spect_impulse == DISABLE)
    {
      if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
      {
        spect_impulse = ENABLE;
        AMODULE_timstart = TIM_GetCapture2(TIM2);
        AMODULE_fon[0]++;
      }
    } else
    {
      spect_impulse = DISABLE;
      AMODULE_timend = TIM_GetCapture2(TIM2);

      /* Capture computation */
      if(AMODULE_timend > AMODULE_timstart)
      {
        i = (AMODULE_timend - AMODULE_timstart) - 1;
      } else if(AMODULE_timend < AMODULE_timstart)
      {
        i = ((0xFFFF - AMODULE_timstart) + AMODULE_timend) - 1;
      } else
      {
        i = 0;
      }
//////////////////////////////////////////////////      

      i = i - Settings.AMODUL_spect_start;
      i = i / Settings.AMODUL_spect_multi;

      if(i < 100)
      {
        AMODULE_len[i]++;       // ��� ������-�
      }
    }
  }
}


////////////////////////////////////////
// ��������� ���
////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RTC_Alarm_IRQHandler(void)
{                               // ��� ������ 4 �������
  int i;

  EXTI_ClearITPendingBit(EXTI_Line17);
  // ������-�
  if(RTC_GetITStatus(RTC_IT_ALRB) != RESET)
  {
    RTC_ClearITPendingBit(RTC_IT_ALRB);

    if(!poweroff_state)
    {
      Set_next_B_alarm_wakeup();        // ���������� ������ ���������� �� +1 �������

      for (i = 99; i > 0; i--)
      {
        AMODULE_fon[i] = AMODULE_fon[i - 1];
      }
      AMODULE_fon[0] = 0;

      DataUpdate.Need_display_update = ENABLE;

      Power.sleep_time = Settings.Sleep_time;
    }

  }
  // �������� ���� �������
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
  {
    RTC_ClearITPendingBit(RTC_IT_ALRA);
    if(!poweroff_state)
    {
      Set_next_alarm_wakeup();  // ���������� ������ ���������� �� +4 �������

      DataUpdate.Need_display_update = ENABLE;

      // ���������� 4 ��������� �����
      if(Settings.Cal_mode == 1)
      {
        if(Cal_count < 20)
        {
          if(Settings.Second_count > Cal_count_time)
          {
            Cal_count_time += 4;
            Cal_count_mass[Cal_count] += Detector_massive[Detector_massive_pointer];
          } else
          {
            Cal_count_time = 0;
            Cal_count++;
          }
        }
      }

      if(Power.USB_active)
      {
        USB_not_active++;       // ������� ������������ USB
        if(Settings.AB_mode < 2)
          madorc_impulse += Detector_massive[Detector_massive_pointer]; // ������� ��������� ��� �������� �� USB
      }
      // ������� ������� ��� ���������� ���������� ��� (������ 4 ������)
      if(DataUpdate.Batt_update_time_counter > 75)
      {
        DataUpdate.Need_batt_voltage_update = ENABLE;
        DataUpdate.Batt_update_time_counter = 0;
      } else
        DataUpdate.Batt_update_time_counter++;

      // ������� ������� ��� ���������� �������� ��������� �������
      if(DataUpdate.pump_counter_update_time > 14)
      {
        if(!Power.USB_active)
          madorc_impulse = 0;
        pump_counter_avg_impulse_by_1sec[1] = pump_counter_avg_impulse_by_1sec[0];
        pump_counter_avg_impulse_by_1sec[0] = 0;
        DataUpdate.pump_counter_update_time = 0;

        if(pump_counter_avg_impulse_by_1sec[1] == 0)    //������� �� ������ ����� � ��������
        {
//          dac_init();
          Pump_now(DISABLE);
          while (RTC_WakeUpCmd(DISABLE) != SUCCESS);
          RTC_SetWakeUpCounter(0xF96);  // ���������� ������� ���������� = 2 �������
          current_pulse_count = 0;
          while (RTC_WakeUpCmd(ENABLE) != SUCCESS);
        }

      } else
        DataUpdate.pump_counter_update_time++;

      // ������� ����
      if(DataUpdate.days_sec_count >= 24600)    // ������ 24 ���� �����
      {
        DataUpdate.days_sec_count = 0;
        working_days++;

      } else
        DataUpdate.days_sec_count++;
      // ����� ������� ����
      if(DataUpdate.doze_sec_count >= 150)      // ������ 10 ����� (150)
      {
        if(DataUpdate.Need_erase_flash == ENABLE)
        {
          full_erase_flash();
          DataUpdate.Need_erase_flash = DISABLE;
        }
        DataUpdate.Need_update_mainscreen_counters = ENABLE;

        // -----------------------------------------------------
        DataUpdate.doze_count++;
        if(DataUpdate.doze_count >= doze_length)        // ������ �������� �� Flash
          //if(DataUpdate.doze_count>1) // ������ �������� �� Flash
        {
          DataUpdate.doze_count = 0;
          flash_write_page(DataUpdate.current_flash_page);
          DataUpdate.current_flash_page++;
          if(DataUpdate.current_flash_page > (FLASH_MAX_PAGE))  // ���� �� ��������� ���������
            DataUpdate.current_flash_page = 0;
        }
        // -----------------------------------------------------

        for (i = doze_length; i > 0; i--)
        {
          ram_Doze_massive[i] = ram_Doze_massive[i - 1];        // ����� ������� ����
          ram_max_fon_massive[i] = ram_max_fon_massive[i - 1];  // ����� ������� ������������� ����
        }
        ram_Doze_massive[0] = 0;
        ram_max_fon_massive[0] = 0;
        DataUpdate.doze_sec_count = 1;  //// !!!!! 0

      } else
        DataUpdate.doze_sec_count++;
      ////////////////////////////////////////////////////    

      if(Settings.AB_mode == 2)
      {
        AB_fon = calc_ab();

        for (i = 14; i > 0; i--)
        {
          Detector_AB_massive[i] = Detector_AB_massive[i - 1];
        }
        Detector_AB_massive[0] = 0;
      }
      ////////////////////////////////////////////////////    
      // ���������
      if(Settings.AB_mode < 2)
        if(Detector_massive[Detector_massive_pointer] >= 10 && Settings.Speedup == 1)
        {
          auto_speedup_factor = 1;
          if(Detector_massive[Detector_massive_pointer] > 300)  // ������� �� 9 ��� ���� ����� 10 000
          {
            if(auto_speedup_factor != 99)
              auto_speedup_factor = 99;
          } else
          {
            if(Detector_massive[Detector_massive_pointer] > 199)        // ������� �� 9 ��� ���� ����� 10 000
            {
              if(auto_speedup_factor != 30)
                auto_speedup_factor = 30;
            } else
            {
              if(Detector_massive[Detector_massive_pointer] > 99)       // ������� �� 5 ��� ���� ����� 5 000
              {
                if(auto_speedup_factor != 10)
                  auto_speedup_factor = 10;
              } else
              {
                if(Detector_massive[Detector_massive_pointer] > 19)     // ������� �� 3 ��� ���� ����� 1 000
                {
                  if(auto_speedup_factor != 4)
                    auto_speedup_factor = 4;
                } else
                {               // ������� �� 2 ��� ���� ����� 500
                  if(auto_speedup_factor != 2)
                    auto_speedup_factor = 2;
                }
              }
            }
          }

          if(auto_speedup_factor > (Settings.Second_count >> 3))
            auto_speedup_factor = (Settings.Second_count >> 3); // �������� ����, ���� ������������� ���������
          if(auto_speedup_factor != 1)
            recalculate_fon();  // �������� ����, ���� ������������� ���������

        } else
        {                       // ���� ��������� �� ���������
          if(auto_speedup_factor != 1)
          {
            auto_speedup_factor = 1;
            recalculate_fon();
          } else
          {
            if(Settings.AB_mode < 2)
              fon_level += Detector_massive[Detector_massive_pointer];
          }
        }

      if(Settings.AB_mode < 2)
      {
        Detector_massive_pointer++;
        if(Detector_massive_pointer >= (Settings.Second_count >> 2))
        {
          if(auto_speedup_factor == 1)
            fon_level -= Detector_massive[0];
          Detector_massive[0] = 0;
          Detector_massive_pointer = 0;
        } else
        {
          if(auto_speedup_factor == 1)
            fon_level -= Detector_massive[Detector_massive_pointer];
          Detector_massive[Detector_massive_pointer] = 0;
        }
        if(fon_level > ram_max_fon_massive[0])
          ram_max_fon_massive[0] = fon_level;   // ���������� ������� ������������� ����
      }
      DataUpdate.Need_fon_update = ENABLE;
      ////////////////////////////////////////////////////

      if(Power.sleep_time > 4)
      {
        Power.sleep_time -= 4;
      } else
      {
        Power.sleep_time = 0;
      }
    }
    if(Pump_on_alarm == ENABLE)
    {
      if(Settings.Pump_aggressive == ENABLE)
      {
        Pump_now(ENABLE);
      } else
      {
        if(Pump_on_alarm_count > 1)
        {
          Pump_now(ENABLE);     // ������������ ������� ������ �� ������ �������
          Pump_on_alarm_count = 0;
        } else
        {
          Pump_on_alarm_count++;
        }
      }
    }
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RTC_WKUP_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line20);
  if(!poweroff_state)
  {
    if(RTC_GetITStatus(RTC_IT_WUT) != RESET)
    {
      RTC_ClearITPendingBit(RTC_IT_WUT);
      if(!Power.Pump_active)
      {
        Pump_now(ENABLE);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void COMP_IRQHandler(void)
{
  uint32_t i;
  extern uint16_t current_pulse_count;
  if(EXTI_GetITStatus(EXTI_Line22) != RESET)
  {
    if(!poweroff_state)
    {
      // ������������ ������ ������ ���������, ��������� �������
      {
        Pump_now(DISABLE);
        if(!pump_on_impulse)
        {
          i = RTC->WUTR;
          if(current_pulse_count > 20)  // ���� ���������� ������� �������� ���� �����������, ����� �������� �������.
          {
            if(i > 0x80)
            {
#ifdef version_401              // ��� ������ 4+ ������ �� 4 ��� ������������ �������
              i >>= 2;          // ���������� ������� �� 4
#else
              i >>= 4;          // ���������� ������� �� 16
#endif
            } else
            {
              i = 0x8;          // ���� ������ ������, �� = 4 ��
            }
          } else
          {
            if(i < 0x8)
              i = 0x8;
            if(current_pulse_count > 2) // ���� ���������� ��������� ������, �� ���������� �� ����������, �������� �������.
            {
              if(i > 0x0010)
                i >>= 1;        // ������� �� 2
            } else
#ifdef version_401              // ��� ������ 4+ ������� ������� ����� ���������
            {                   // ���������� ��������� ������� ����, ������ ����� ��������� �������� ����� ����������.
              i <<= 1;          // �������� �� 2
              if(i > 0x1E00)
                i = 0x2000;     // ������ 4 �������
            }
#else
            {                   // ���������� ��������� ������� ����, ������ ����� ��������� �������� ����� ����������.
              if(i < 0x7FFF)    //���� ������ �������� �� ���������
              {
                i <<= 1;        // �������� �� 2
              } else
              {
                // ���� �������� �� 2 ��� ������, ������ ���������� �� �������
                i = i + 0x2000; // + 4 �������
                if(i > 0xFFFF)
                  i = 0xFFFF;   // ������ 32 �������
              }
            }
#endif

          }
#ifdef version_401              // ��� ������ 4+
          if(i == 0x2000)
          {
            RTC_ITConfig(RTC_IT_WUT, DISABLE);
            RTC_WakeUpCmd(DISABLE);
            Pump_on_alarm = ENABLE;
          } else
          {
            RTC_ITConfig(RTC_IT_WUT, ENABLE);
            Pump_on_alarm = DISABLE;
#endif
            if(RTC->WUTR != i)
            {
              while (RTC_WakeUpCmd(DISABLE) != SUCCESS);
              RTC_SetWakeUpCounter(i);  // ���������� ������� ����������
              while (RTC_WakeUpCmd(ENABLE) != SUCCESS);
            }
#ifdef version_401              // ��� ������ 4+
          }
#endif
          current_pulse_count = 0;
        } else
        {
          //last_count_pump_on_impulse = current_pulse_count;
          pump_on_impulse = DISABLE;
        }
      }
    }
    EXTI_ClearITPendingBit(EXTI_Line22);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB Low Priority interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_IRQHandler(void)
{
  USB_Istr();
}

/*******************************************************************************
* Function Name  : USB_FS_WKUP_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void USB_FS_WKUP_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line18);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
