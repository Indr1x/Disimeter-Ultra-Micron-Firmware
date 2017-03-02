#ifndef __menu_user_H
#define __menu_user_H
#include <STM32L1xx.h>

#define max_string_len 16       // максимальная длинна строки
#define max_string_count 8      // максимальное количество строк
#define max_public_string_count 11      // максимальное количество строк публичного меню
#define max_struct_index 22     // максимальное количество пунктов меню
#define start_offset 2          // на сколько строк сместить вниз меню

#define modul_max_struct_index 19       // максимальное количество пунктов меню


#define NORMAL_menu_mode 0
#define AMODUL_menu_mode 1

typedef struct
{
  int8_t Hide;
  uint16_t EEPROM_address;
  char Text[17];
  char Param_is_0[10];
  char Param_is_1[10];
  char Param_is_N[10];
  uint32_t *Parameter_value;
  uint32_t Min_limit;
  uint32_t Max_limit;
  uint32_t Value_default;
  void (*Plus_reaction) (uint32_t *);
  void (*Minus_reaction) (uint32_t *);

} MenuItem;

void main_screen(void);
void menu_screen(uint32_t);
void stat_screen(void);
void amodul_screen(void);

extern MenuItem Menu_list[];
extern MenuItem Modul_Menu_list[];

#endif
