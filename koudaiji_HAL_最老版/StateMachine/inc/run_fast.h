#ifndef __RUN_FAST_H__
#define __RUN_FAST_H__

#include "vision.h"

typedef struct Run_Fast_Str //����ģʽ������صĽṹ��
{
    uint8_t step; //���еĲ������
    Res_Coord_Struct res_coord[10];  //AIģ��ʶ�𵽵���������
    uint8_t res_num;  //AIģ��ʶ�𵽵����������
    bool first_flag;  //�Ƿ����״μ���־
    Res_Coord_Struct last_res;  //��¼��ǰҳ�����һ�����������
    uint16_t res_sum; //��ǰģʽ��ʶ����������
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



