#ifndef __TRIPOD_H__
#define __TRIPOD_H__

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"

#define X_STEP_ANGLE 59.5f  //云台X轴运行一度需要的步数
#define Y_STEP_ANGLE 60.0f  //云台Y轴运行一度需要的步数
#define DIS_X   1337			// 屏幕分辨率是1366  768  屏幕到云台的距离是70cm  屏幕的水平也是70cm  1366个像素   屏幕上的格子是 19像素
//将云台和屏幕直线距离控制在70CM，这样就不用换算距离和像素坐标了，直接使用1366 像素
#define DIS_Y 768

extern uint16_t Y_OFFSET;

typedef struct Tripod_Str  //云台相关结构体
{
    volatile uint32_t step_num;  //需要运行的步数
    volatile uint32_t step_code;
    uint16_t coord;  //当前坐标
    float angle;  //当前角度
    volatile bool is_limit;  //是否到达限位
    volatile bool is_running;  //是否正在运行 （volatile标记这是一个不能优化的变量）
}Tripod_Struct; 

extern GPIO_Struct Tripod_X_DIR, Tripod_X_EN, Tripod_X_STEP, Tripod_X_LIMIT, Tripod_Y_DIR, Tripod_Y_EN, Tripod_Y_STEP, Tripod_Y_LIMIT;
extern Tripod_Struct Tripod_X, Tripod_Y;

void Tripod_Init(void);
void Tripod_X_Dir(uint8_t dir);
void Tripod_X_Step(uint16_t num);

void Tripod_Y_Dir(uint8_t dir);
void Tripod_Y_Step(uint16_t num);
void Tripod_Key_Scan(void);
void Tripod_X_Go_Mechzero(void);
void Tripod_Y_Go_Mechzero(void);
void Tripod_X_Angle(float x_dat);
void Tripod_Y_Angle(float y_dat);
void Tripod_X_Coord(int x_dat);
void Tripod_Y_Coord(int y_dat);

#endif



