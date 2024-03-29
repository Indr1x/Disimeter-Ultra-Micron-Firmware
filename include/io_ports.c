#include "main.h"

void io_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  ////////////////////////////////////////////////////  
  // ���� A
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // ????? ????? "????"
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin =
      GPIO_Pin_All & ~GPIO_Pin_1 & ~GPIO_Pin_5 & ~GPIO_Pin_7 & ~GPIO_Pin_13 &
      ~GPIO_Pin_14 & ~GPIO_Pin_11 & ~GPIO_Pin_12 & ~GPIO_Pin_3 & ~GPIO_Pin_4 & ~GPIO_Pin_8 & ~GPIO_Pin_6;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA, GPIO_InitStructure.GPIO_Pin);   // ��������� ����������

  // ���� B
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // ????? ????? "????"
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All & ~GPIO_Pin_12 & ~GPIO_Pin_13 & ~GPIO_Pin_14 & ~GPIO_Pin_4;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOB, GPIO_InitStructure.GPIO_Pin);   // ��������� ����������

  // ���� B
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // ????? ????? "????"
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOB, GPIO_InitStructure.GPIO_Pin);   // ��������� ����������

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // ===============================================================================================  
  // ����� ������������ ������� 1.8�-3.1�
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_7);      // ����������� � ����� 3 ������
  //GPIO_ResetBits(GPIOA,GPIO_Pin_7);// ����������� � ����� 3 ������

  // ===============================================================================================  
  // key Down
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ????? ????? "????"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // ???????? ? +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;     // ????? ????? ? ?????
  GPIO_Init(GPIOA, &GPIO_InitStructure);        // ?????????? ????????????

  // ===============================================================================================  
  // key Menu
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ????? ????? "????"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // ???????? ? +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;     // ????? ????? ? ?????
  GPIO_Init(GPIOA, &GPIO_InitStructure);        // ?????????? ????????????

  // ===============================================================================================  
  // key UP
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ????? ????? "????"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // ???????? ? +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;     // ????? ????? ? ?????
  GPIO_Init(GPIOA, &GPIO_InitStructure);        // ?????????? ????????????


// ===============================================================================================  
  //������������� ����� ��� ��������� ��
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;  // GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;         // ���������� �����
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

// ===============================================================================================  
  //������������� ����� ��� ��������� Geiger pulse
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;  // GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;         // ���������� �����
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

// ===============================================================================================  
  //������������� ����� ��� ��������� USB
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;  // GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;         // ���������� �����
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // ===============================================================================================  
  // ����� �������
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA, GPIO_Pin_15);   // ����������� � ����� 3 ������


// ===============================================================================================  
  // ����� ��������� ���������� ���
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;      // �����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // ��������� ������������
  GPIO_SetBits(GPIOB, GPIO_InitStructure.GPIO_Pin);     // ��������� ����������

// ===============================================================================================  
  // ����� LCDLED
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;    // �����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);        // ��������� ������������
  GPIO_SetBits(GPIOC, GPIO_InitStructure.GPIO_Pin);     // ��������� ����������

// ===============================================================================================  
  // ����� LCDLED
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;     // �����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // ��������� ������������
  GPIO_SetBits(GPIOB, GPIO_InitStructure.GPIO_Pin);     // ��������� ����������

// ===============================================================================================  
  // ����� ������ �������� �������
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;    // �����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // ��������� ������������
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_TIM9);

// ===============================================================================================  
  // ����� DAC ����� 2
/*  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;     // �����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);        // ��������� ������������
  */
// ===============================================================================================  
  // ����� ���� ������������

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
