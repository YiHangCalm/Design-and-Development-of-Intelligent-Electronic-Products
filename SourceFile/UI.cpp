#include "UI.h"

LcdDriver Lcd;
void Show(){
	Lcd.Show(1,1,"asdas",SHOW_SIZE_32,Lcd.GetFontColor());

}