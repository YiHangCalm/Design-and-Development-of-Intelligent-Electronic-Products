#include "LcdDriver.h"

LcdDriver::LcdDriver::LcdDriver() {
    LCD_BACKGROUND = BLACK;  // 在构造函数体内部初始化成员变量
    LCD_TYPEFACE = WHITE;
//    memset(&mUserLcdData, 0, sizeof(mUserLcdData));  // 手动初始化结构体
//    PinInit();  // 初始化引脚
//    Init();     // 初始化LCD
}
LcdDriver::~LcdDriver() {
    // 可以在这里添加一些必要的清理代码，如果需要的话
}

uint16_t LcdDriver::GetFontColor() const {
	
    return LCD_TYPEFACE;
}
uint16_t LcdDriver::GetBackColor() const {
	
    return LCD_BACKGROUND;
}
void LcdDriver::PinInit() {
    Lcd_Pin_Init(); // 直接调用C函数进行引脚初始化
}

void LcdDriver::WriteCmd(uint8_t cmd) {
    Lcd_Write_Cmd(cmd); // 直接调用C函数
}

void LcdDriver::WriteData8(uint8_t data) {
    Lcd_Write_Data8(data); // 直接调用C函数
}

void LcdDriver::WriteData16(uint16_t data) {
    Lcd_Write_Data16(data); // 直接调用C函数
}



void LcdDriver::Init() {
    Lcd_Init(); // 直接调用C函数
}

void LcdDriver::Clear(uint16_t color) {
    Lcd_Clear(color); // 直接调用C函数
}

void LcdDriver::ClearOsci(uint16_t color) {
    Lcd_Clear_Osci(color); // 直接调用C函数
}

void LcdDriver::ClearPrint(uint16_t color) {
    Lcd_Clear_Print(color); // 直接调用C函数
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
    char buffer[12];  // 使用字符数组
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
    char buffer[12];  // 使用字符数组
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
