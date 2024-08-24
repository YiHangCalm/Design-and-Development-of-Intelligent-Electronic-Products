#include "LcdDriver.h"

LcdDriver::LcdDriver::LcdDriver() {
    LCD_BACKGROUND = BLACK;  // �ڹ��캯�����ڲ���ʼ����Ա����
    LCD_TYPEFACE = WHITE;
//    memset(&mUserLcdData, 0, sizeof(mUserLcdData));  // �ֶ���ʼ���ṹ��
//    PinInit();  // ��ʼ������
//    Init();     // ��ʼ��LCD
}
LcdDriver::~LcdDriver() {
    // �������������һЩ��Ҫ��������룬�����Ҫ�Ļ�
}

uint16_t LcdDriver::GetFontColor() const {
	
    return LCD_TYPEFACE;
}
uint16_t LcdDriver::GetBackColor() const {
	
    return LCD_BACKGROUND;
}
void LcdDriver::PinInit() {
    Lcd_Pin_Init(); // ֱ�ӵ���C�����������ų�ʼ��
}

void LcdDriver::WriteCmd(uint8_t cmd) {
    Lcd_Write_Cmd(cmd); // ֱ�ӵ���C����
}

void LcdDriver::WriteData8(uint8_t data) {
    Lcd_Write_Data8(data); // ֱ�ӵ���C����
}

void LcdDriver::WriteData16(uint16_t data) {
    Lcd_Write_Data16(data); // ֱ�ӵ���C����
}



void LcdDriver::Init() {
    Lcd_Init(); // ֱ�ӵ���C����
}

void LcdDriver::Clear(uint16_t color) {
    Lcd_Clear(color); // ֱ�ӵ���C����
}

void LcdDriver::ClearOsci(uint16_t color) {
    Lcd_Clear_Osci(color); // ֱ�ӵ���C����
}

void LcdDriver::ClearPrint(uint16_t color) {
    Lcd_Clear_Print(color); // ֱ�ӵ���C����
}

void LcdDriver::Show(int x, int y, char c, Show_Size_Enum size, uint16_t color) {
    y*=size;
	Lcd_ShowChar(x, y, static_cast<uint8_t>(c), size, color);
}

void LcdDriver::Show(int x, int y, const char* str, Show_Size_Enum size, uint16_t color) {
    y*=size;
	Lcd_ShowString(x, y, reinterpret_cast<char*>(const_cast<char*>(str)), size, color);
}

void LcdDriver::Show(int x, int y, int num, Show_Size_Enum size, uint16_t color) {
    char buffer[12];  // ʹ���ַ�����
    snprintf(buffer, sizeof(buffer), "%d", num);
    y*=size;
	Lcd_ShowString(x, y, reinterpret_cast<char*>(buffer), size, color);
}
void LcdDriver::Show(int x, int y, float num, Show_Size_Enum size, uint16_t color) {
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%.2f", num);
    y*=size;
	Lcd_ShowString(x, y, buffer, size, color);
}


void LcdDriver::Show(int x, int y, char c, Show_Size_Enum size) {
    y*=size;
	Lcd_ShowChar(x, y, static_cast<uint8_t>(c), size, this->GetBackColor());
}

void LcdDriver::Show(int x, int y, const char* str, Show_Size_Enum size) {
    y*=size;
	Lcd_ShowString(x, y, reinterpret_cast<char*>(const_cast<char*>(str)), size, this->GetBackColor());
}

void LcdDriver::Show(int x, int y, int num, Show_Size_Enum size) {
    char buffer[12];  // ʹ���ַ�����
    snprintf(buffer, sizeof(buffer), "%d", num); 
    y*=size;
	Lcd_ShowString(x, y, reinterpret_cast<char*>(buffer), size, this->GetBackColor());
}
void LcdDriver::Show(int x, int y, float num, Show_Size_Enum size) {
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%.2f", num);
    y*=size;
	Lcd_ShowString(x, y, buffer, size, this->GetBackColor());
}



void LcdDriver::SetBackgroundColor(uint16_t color) {
    LCD_BACKGROUND = color;
}

void LcdDriver::SetFontColor(uint16_t color) {
    LCD_TYPEFACE = color;
}
