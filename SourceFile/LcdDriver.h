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
	 LcdDriver();       // ���캯��
    ~LcdDriver();                   // ��������

    void Init();                    // ��ʼ��LCD
    void Clear(uint16_t color);     // ����
    void ClearOsci(uint16_t color); // ���ʾ��������
    void ClearPrint(uint16_t color);// �����ӡ����

	uint16_t GetFontColor() const ;
	uint16_t GetBackColor() const ;
    // ���ñ���ɫ��������ɫ
    void SetBackgroundColor(uint16_t color);
    void SetFontColor(uint16_t color);

    // �������أ�ʵ�ֶ�̬��ʾ
    void Show(int x, int y, char c, Show_Size_Enum size, uint16_t color);
    void Show(int x, int y, const char* str, Show_Size_Enum size, uint16_t color);
    void Show(int x, int y, int num, Show_Size_Enum size, uint16_t color);
    void Show(int x, int y, float num, Show_Size_Enum size, uint16_t color);
    //Ĭ�ϱ���
	void Show(int x, int y, char c, Show_Size_Enum size);
    void Show(int x, int y, const char* str, Show_Size_Enum size);
    void Show(int x, int y, int num, Show_Size_Enum size);
    void Show(int x, int y, float num, Show_Size_Enum size);
    

	void Show(uint16_t x, uint16_t y, float num);

 
    



private:
    GPIO_Struct LCD_DC_Pin, LCD_CS_Pin, LCD_RST_Pin; // LCD��������
    uint16_t LCD_BACKGROUND; // ����ɫ
    uint16_t LCD_TYPEFACE;   // ������ɫ
    LcdData mUserLcdData;    // ��ʾ���ݽṹ��

    void PinInit();          // ��ʼ��LCD��������
    void WriteCmd(uint8_t cmd);        // ��������
    void WriteData8(uint8_t data);     // ����8λ����
    void WriteData16(uint16_t data);   // ����16λ����
    
   
};

#endif // LCDDRIVER_H
