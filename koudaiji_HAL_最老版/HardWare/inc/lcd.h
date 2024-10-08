#ifndef __LCD_H__
#define __LCD_H__

#include "gpio.h"
#include "sys_font.h"

#define LCD_W_SIZE 320
#define LCD_H_SIZE 240  //宏定义口袋机lcd屏分辨率

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define GREEN         	 0x07E0
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40

extern uint16_t LCD_BACKGROUND; //背景色
extern uint16_t LCD_TYPEFACE;  //画笔色

void Lcd_Pin_Init(void);
void Lcd_Init(void);
void Lcd_Write_Cmd(uint8_t cmd);
void Lcd_Write_Data8(uint8_t data);
void Lcd_Write_Data16(uint16_t data);
void Lcd_Clear(uint16_t color);
void Lcd_Draw_Point(uint16_t x, uint16_t y, uint16_t color);
void Lcd_ShowChar(uint16_t x, uint16_t y, uint8_t num, Show_Size_Enum size, uint16_t Color);
void Lcd_ShowString(uint16_t x, uint16_t y, char *p, Show_Size_Enum size, uint16_t Color);
void Lcd_printf(char *fmt, ...);

void Lcd_Clear_Osci(uint16_t color);
void Lcd_Osci_printf(char *fmt, ...);

#endif


