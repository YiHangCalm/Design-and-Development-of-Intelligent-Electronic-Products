#ifndef LCDDRIVER_H
#define LCDDRIVER_H

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h >
#include "lcd.h"

class LcdDriver {
public:
	 LcdDriver();       // 构造函数
    ~LcdDriver();                   // 析构函数

    void Init();                    // 初始化LCD
    void Clear(uint16_t color);     // 清屏
    void ClearOsci(uint16_t color); // 清除示波器区域
    void ClearPrint(uint16_t color);// 清除打印区域

	uint16_t GetFontColor() const ;
	uint16_t GetBackColor() const ;
    // 设置背景色和字体颜色
    void SetBackgroundColor(uint16_t color);
    void SetFontColor(uint16_t color);

    // 函数重载，实现多态显示
    void Show(int x, int y, char c, Show_Size_Enum size, uint16_t color);
    void Show(int x, int y, const char* str, Show_Size_Enum size, uint16_t color);
    void Show(int x, int y, int num, Show_Size_Enum size, uint16_t color);
    void Show(int x, int y, float num, Show_Size_Enum size, uint16_t color);
    //默认背景
	void Show(int x, int y, char c, Show_Size_Enum size);
    void Show(int x, int y, const char* str, Show_Size_Enum size);
    void Show(int x, int y, int num, Show_Size_Enum size);
    void Show(int x, int y, float num, Show_Size_Enum size);
    

	void Show(uint16_t x, uint16_t y, float num);

 
    



private:
    GPIO_Struct LCD_DC_Pin, LCD_CS_Pin, LCD_RST_Pin; // LCD控制引脚
    uint16_t LCD_BACKGROUND; // 背景色
    uint16_t LCD_TYPEFACE;   // 字体颜色
    LcdData mUserLcdData;    // 显示数据结构体

    void PinInit();          // 初始化LCD控制引脚
    void WriteCmd(uint8_t cmd);        // 发送命令
    void WriteData8(uint8_t data);     // 发送8位数据
    void WriteData16(uint16_t data);   // 发送16位数据
    
   
};

#endif // LCDDRIVER_H
