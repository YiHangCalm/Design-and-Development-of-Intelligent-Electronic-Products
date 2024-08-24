#ifndef __RUN_FAST_H__
#define __RUN_FAST_H__

#include "vision.h"

typedef struct Run_Fast_Str //快速模式运行相关的结构体
{
    uint8_t step; //运行的步数标记
    Res_Coord_Struct res_coord[10];  //AI模组识别到的物体坐标
    uint8_t res_num;  //AI模组识别到的物体的数量
    bool first_flag;  //是否是首次检测标志
    Res_Coord_Struct last_res;  //记录当前页面最后一个物体的坐标
    uint16_t res_sum; //当前模式下识别物体总数
    uint8_t need_point_num;

    uint16_t user_num1;
    uint16_t user_num2;
    uint8_t i;
    bool new_flag;
} Run_Fast_Struct;

extern Run_Fast_Struct Run_Fast;

void Run_Mode_Fast_Init(void);
void Run_Mode_Fast_Enter(void);
void Run_Mode_Fast_Exit(void);
void Run_Mode_Fast_Run(void);

#endif



