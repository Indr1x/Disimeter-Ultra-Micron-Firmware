#ifndef __ext2760_H
#define __ext2760_H

#include "stm32l1xx.h"

//***********************************************************
//��������� ����������� ������� � ���������� ��� ������ � ���
//***********************************************************


// ����� RST
#define LCD_RST_H   GPIOB->BSRRL = GPIO_Pin_3;
#define LCD_RST_L   GPIOB->BSRRH = GPIO_Pin_3;

// ����� DATA
#define LCD_DATA_H  GPIOB->BSRRL = GPIO_Pin_5;
#define LCD_DATA_L  GPIOB->BSRRH = GPIO_Pin_5;

// ����� CLK
#define LCD_CLK_H   GPIOB->BSRRL = GPIO_Pin_6;
#define LCD_CLK_L   GPIOB->BSRRH = GPIO_Pin_6;

// ����� CS
#define LCD_CS_H    GPIOB->BSRRL = GPIO_Pin_8;
#define LCD_CS_L    GPIOB->BSRRH = GPIO_Pin_8;



#define PIXEL_OFF	0       // ������ ����������� ������� - ������������ � ����������� ��������
#define PIXEL_ON	1
#define PIXEL_XOR	2

#define LCD_X_RES               96      // ���������� ������
#define LCD_Y_RES               72
#define LCD_CACHSIZE          LCD_X_RES*LCD_Y_RES>>3
//#define LCD_CACHSIZE          LCD_X_RES*LCD_Y_RES/8  

#define Cntr_X_RES              96      // ���������� �����������
#define Cntr_Y_RES              72
//#define Cntr_buf_size           Cntr_X_RES*Cntr_Y_RES/8
#define Cntr_buf_size           Cntr_X_RES*Cntr_Y_RE>>3

#define lcd_CMD 1
#define lcd_DATA 2

extern char lcd_buf[];


//***************************************************
//****************��������� �������******************
//***************************************************
void init_lcd_port(void);       // ������������� ����� LCD �������
void LcdInit(void);
void LcdClear(void);            //Clears the display
void LcdPixel(unsigned char x, unsigned char y, unsigned char mode);    //Displays a pixel at given absolute (x, y) location, mode -> Off, On or Xor
void LcdStringBold(unsigned char x, unsigned char y);   //Displays a string at current cursor location


//void LcdSend (unsigned char data, unsigned char cmd);                         //Sends data to display controller
void LcdUpdate(void);           //Copies the LCD cache into the device RAM
void LcdClear(void);            //Clears the display
void LcdInit(void);             //��������� SPI � �������
//void LcdContrast (unsigned char contrast);                                    //contrast -> Contrast value from 0x00 to 0x7F
//void LcdMode (unsigned char mode);                                            //������ �������: 0 - blank, 1 - all on, 2 - normal, 3 - inverse
//void LcdPwrMode (void);                                                               //����������� ��������� ���/���� �������
//void LcdPwrOff (void);                                                                //���� �������
void LcdPwrOn(void);            //��� �������
void LcdPixel(unsigned char x, unsigned char y, unsigned char mode);    //Displays a pixel at given absolute (x, y) location, mode -> Off, On or Xor
void LcdLine(int x1, int y1, int x2, int y2, unsigned char mode);       //Draws a line between two points on the display
//void LcdCircle(char x, char y, char radius, unsigned char mode);              //������ ���� � ������������ ������ � ��������
//void LcdBatt(int x1, int y1, int x2, int y2, unsigned char persent);          //������ ��������� � ��������� �� �� %
void LcdGotoXYFont(unsigned char x, unsigned char y);   //Sets cursor location to xy location. Range: 1,1 .. 14,6
void clean_lcd_buf(void);       //������� ���������� ������
void LcdChr(int ch);            //Displays a character at current cursor location and increment cursor location
void LcdString(unsigned char x, unsigned char y);       //Displays a string at current cursor location
void LcdChrBold(int ch);        //�������� ������ �� ������� �����, ������� � ������)
void LcdStringBold(unsigned char x, unsigned char y);   //�������� ������� � ������ ������
void LcdChrBig(int ch);         //�������� ������ �� ������� �����, �������
void LcdStringBig(unsigned char x, unsigned char y);    //�������� ������� ������
//***************************************************
// UPDATE ##1
void LcdBar(int x1, int y1, int x2, int y2, unsigned char persent);     // ������ ��������-��� � ��������� ��� �� "�������"
void LcdBarLine(unsigned char line, unsigned char persent);     // ������ ��������-��� � ��������� ������
void LcdStringInv(unsigned char x, unsigned char y);    // �������� ������ � ��������� ������ (������ ��� ��������)



void Draw_fon_graph(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end);
void Draw_AMODUL_graph(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end);
void Draw_AMODUL_graph_spectr(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end, uint8_t page);
void Draw_speedup(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end);
void Draw_fon_digit(uint8_t line, uint8_t start_char, uint8_t seconds);
void Draw_AB_digit(uint8_t line, uint8_t start_char, uint8_t seconds);
void Draw_AMODUL_digit(uint8_t line, uint8_t start_char, uint8_t seconds);
void LcdBatt(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t persent);     //������ ��������� � ����������� � %
void LcdClear_massive(void);
void display_on(void);
void display_off(void);
#endif
