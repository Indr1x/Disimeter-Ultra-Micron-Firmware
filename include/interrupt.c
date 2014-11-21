#include "main.h"



// =======================================================
// ������������� ���������� ������� 1
void EXTI8_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  EXTI_InitTypeDef   EXTI_InitStructure;
  
	GPIO_StructInit(&GPIO_InitStructure);
	EXTI_StructInit(&EXTI_InitStructure);
	
  // ��������� �����
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); // ������ ������������ �� ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;        // ����� ����� "����"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;    // ��� ��������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           // ����� ����� � �����
  GPIO_Init(GPIOA, &GPIO_InitStructure);              // ���������� ������������
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // ������ ������������ �� SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource8); // ���������� EXTI � �����
  
  // ��������� EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line8;             // ����� EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    // ����� ����������
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; // ������� �� ������������ ������
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;              // ��������
  EXTI_Init(&EXTI_InitStructure);                        // ���������� ������������
  
  // ��������� ����� ����������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;           // �����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

// =======================================================
// ������������� ���������� �� ������� ������ 0
void EXTI3_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  EXTI_InitTypeDef   EXTI_InitStructure;
	
	GPIO_StructInit(&GPIO_InitStructure);
	EXTI_StructInit(&EXTI_InitStructure);

  
  // ��������� �����
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); // ������ ������������ �� ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;        // ����� ����� "����"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        // �������� � +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;           // ����� ����� � �����
  GPIO_Init(GPIOA, &GPIO_InitStructure);              // ���������� ������������
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // ������ ������������ �� SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3); // ���������� EXTI � �����
  
  // ��������� EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;             // ����� EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    // ����� ����������
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // ������� �� ���������� ������
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;              // ��������
  EXTI_Init(&EXTI_InitStructure);                        // ���������� ������������
  
  // ��������� ����� ����������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;           // �����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

// =======================================================
// ������������� ���������� �� ������� ������ 1
void EXTI4_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  EXTI_InitTypeDef   EXTI_InitStructure;

	GPIO_StructInit(&GPIO_InitStructure);
	EXTI_StructInit(&EXTI_InitStructure);

  
  // ��������� �����
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); // ������ ������������ �� ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;        // ����� ����� "����"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        // �������� � +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;           // ����� ����� � �����
  GPIO_Init(GPIOA, &GPIO_InitStructure);              // ���������� ������������
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // ������ ������������ �� SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4); // ���������� EXTI � �����
  
  // ��������� EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;             // ����� EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    // ����� ����������
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // ������� �� ���������� ������
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;              // ��������
  EXTI_Init(&EXTI_InitStructure);                        // ���������� ������������
  
  // ��������� ����� ����������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;           // �����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


// =======================================================
// ������������� ���������� �� ������� ������ 2
void EXTI6_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  EXTI_InitTypeDef   EXTI_InitStructure;

	GPIO_StructInit(&GPIO_InitStructure);
	EXTI_StructInit(&EXTI_InitStructure);

  
  // ��������� �����
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); // ������ ������������ �� ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;        // ����� ����� "����"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        // �������� � +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           // ����� ����� � �����
  GPIO_Init(GPIOA, &GPIO_InitStructure);              // ���������� ������������
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // ������ ������������ �� SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6); // ���������� EXTI � �����
  
  // ��������� EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line6;             // ����� EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    // ����� ����������
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // ������� �� ���������� ������
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;              // ��������
  EXTI_Init(&EXTI_InitStructure);                        // ���������� ������������
  
  // ��������� ����� ����������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;           // �����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}