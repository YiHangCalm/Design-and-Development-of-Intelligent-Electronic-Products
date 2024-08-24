/*
*����ģʽʵ���߼���������ģʽ��ͬ
*/
#include "run_fast.h"
#include "run_mode.h"
#include "lcd.h"
#include "voice.h"
#include "infared.h"
#include "tripod.h"
#include "relay.h"
#include "diwen_lcd.h"
#include <math.h>

Run_Fast_Struct Run_Fast; //�������ģʽ�ṹ�����

/*����ģʽ��ʼ��*/
void Run_Mode_Fast_Init(void)
{
    Run_Mode_Fast.mode_enter = Run_Mode_Fast_Enter;
    Run_Mode_Fast.mode_exit = Run_Mode_Fast_Exit;
    Run_Mode_Fast.mode_run = Run_Mode_Fast_Run;  //������ģʽ���롢�˳�����������������ʵ��ע�ᵽ����ָ��

    Run_Fast.res_num = 0;
    Run_Fast.step = 0;
    Run_Fast.first_flag = true;
    Run_Fast.last_res.x = 0;
    Run_Fast.last_res.y = 0;
    Run_Fast.res_sum = 0;  //�����ر���
    Run_Fast.need_point_num = 0;

    Run_Fast.user_num1 = 0;
    Run_Fast.user_num2 = 0;
    Run_Fast.i = 0;
    Run_Fast.new_flag = false;
}

/*����ģʽ����*/
void Run_Mode_Fast_Enter(void)
{
    Run_Fast.res_num = 0;
    Run_Fast.step = 0;
    Run_Fast.first_flag = true;
    Run_Fast.last_res.x = 0;
    Run_Fast.last_res.y = 0;  //�����ر���
    Run_Fast.need_point_num = 0;
    Run_Fast.user_num1 = 0;
    Run_Fast.user_num2 = 0;
    Run_Fast.i = 0;
    Run_Fast.new_flag = false;

    Infared.Infared_Is_Pause = false;

    DiWenLcd_Show_RunState(129, "����ģʽ");  //��������ʾ��ص�״̬��Ϣ

    if(enter_voice_flag == true) //�������������
    {
        Voice_Play((uint8_t)FAST_START); //���Ž������ģʽ������
    }
    else //����˴β�����������
    {
        enter_voice_flag = true; //��ոñ�־λ
    }
}

/*����ģʽ�˳�*/
void Run_Mode_Fast_Exit(void)
{
    Relay_Control(RELAY_OFF); //�رռ����
}

/*����ģʽ���к���*/
void Run_Mode_Fast_Run(void)
{
    if(Run_Fast.first_flag == true) //�ж��Ƿ����״μ�⣨�״μ��ʱ��Ҫָʾ��Ļ�����м�⵽�����壬�Ժ���ֻ��Ҫָʾ���һ���Ϳ��ԣ�
    {
        if(Run_Fast.step == 0)
        {
            if(Vision_Dat_Explan() != 0)
            {
                Run_Fast.user_num1++;
                if(Run_Fast.user_num1 >= 5)
                {
                    Infared_Send_OK();
                    Run_Fast.step = 1; 
                    Run_Fast.user_num1 = 0;
                }
            }
        }
        if(Run_Fast.step == 1)
        {
            if(Vision_Dat_Explan() != 0)
            {
                Run_Fast.user_num1++;
                if(Run_Fast.user_num1 >= 20)
                {
                    Run_Fast.user_num1 = 0;
                    Run_Fast.user_num2 = 0;
                    Run_Fast.step = 2;
                }
            }
            Run_Fast.user_num2++;
            if(Run_Fast.user_num2 >= 3000)
            {
                Run_Fast.user_num2 = 0;
                Run_Fast.user_num1 = 0;
                Run_Fast.step = 0;
                Infared_Send_OK();
            }
        }
        if(Run_Fast.step == 2)
        {
            for(Run_Fast.i=0; Run_Fast.i<Vision_Coord.Res_Num; Run_Fast.i++)
            {
                Run_Fast.res_coord[Run_Fast.i].x = Vision_Coord.Res_Coord[Run_Fast.i].x;
                Run_Fast.res_coord[Run_Fast.i].y = Vision_Coord.Res_Coord[Run_Fast.i].y;
            }
            Run_Fast.i = 0;
            Run_Fast.res_num = Vision_Coord.Res_Num;
            Run_Fast.step = 3;       
        }

        if(Run_Fast.step == 3)
        {
            if((Run_Fast.user_num1 % 5000 == 0) && (Run_Fast.i < Run_Fast.res_num))
            {
                Relay_Control(RELAY_OFF);
                Tripod_X_Coord(Run_Fast.res_coord[Run_Fast.i].x);
                Tripod_Y_Coord(Run_Fast.res_coord[Run_Fast.i].y);
                while(Tripod_Y.is_running);
                while(Tripod_X.is_running);
                Voice_Play((select_shape-1)*4 + select_color);
                Relay_Control(RELAY_ON);
                Lcd_printf("Detected %s %s:x=%d,y=%d", ColorStr[select_color-1], ShapeStr[select_shape-1],  Run_Fast.res_coord[Run_Fast.i].x, Run_Fast.res_coord[Run_Fast.i].y);
                DiWenLcd_Printf("��⵽%s%s: X=%d,Y=%d", ColorStrZh[select_color-1], ShapeStrZh[select_shape-1], Run_Fast.res_coord[Run_Fast.i].x, Run_Fast.res_coord[Run_Fast.i].y);
                Run_Fast.res_sum++;
				DiWenLcd_Cmd_Data(0x6006, Run_Fast.res_sum);
                Run_Fast.i++;
                Run_Fast.user_num1 = 0;
            }

            Run_Fast.user_num1++;

            if(Run_Fast.user_num1 == 5001)
            {
                Relay_Control(RELAY_OFF);
            }

            if(Run_Fast.user_num1 == 5500)
            {
                Run_Fast.last_res.x = Run_Fast.res_coord[Run_Fast.res_num-1].x;
                Run_Fast.last_res.y = Run_Fast.res_coord[Run_Fast.res_num-1].y;
                Infared_Send_OK();
            }

            if(Run_Fast.user_num1 == 6000)
            {
                Run_Fast.step = 0;
                Run_Fast.user_num1 = 0;
                Run_Fast.i = 0;
                Run_Fast.first_flag = false;
            }
        }
    }
    /*���ǵ�һ�ν���ʱ*/
    else
    {
        if(Run_Fast.step == 0)
        {
            if(Vision_Dat_Explan() != 0)
            {
                if(Run_Fast.new_flag == false)
                {
                    if(Vision_Coord.Res_Coord[Vision_Coord.Res_Num-1].x > (Run_Fast.last_res.x+5))
                    {
                        Run_Fast.new_flag = true;
                    }
                    else
                    {
                        Run_Fast.last_res.x = Vision_Coord.Res_Coord[Vision_Coord.Res_Num-1].x;
                        Run_Fast.last_res.y = Vision_Coord.Res_Coord[Vision_Coord.Res_Num-1].y;
                    }
                }
                else
                {
                    for(Run_Fast.i=0; Run_Fast.i<Vision_Coord.Res_Num; Run_Fast.i++)
                    {
                        if(Vision_Coord.Res_Coord[Run_Fast.i].x >= (Run_Fast.last_res.x + 5))
                        {
                            if(Run_Fast.i > 0)
                            {
                               Run_Fast.last_res.x = Vision_Coord.Res_Coord[Run_Fast.i-1].x; 
                               Run_Fast.last_res.y = Vision_Coord.Res_Coord[Run_Fast.i-1].y;
                            }
                            else
                            {
                                Run_Fast.last_res.x = 0;
                                Run_Fast.last_res.y = 0;
                            }
                            break;
                        }
                    }
                }
            }
            if(Run_Fast.new_flag == true)
            {
                Run_Fast.user_num1 ++;
                if(Run_Fast.user_num1 >= 1000)
                {
                    Run_Fast.user_num1 = 0;
                    Run_Fast.new_flag = false;
                    Infared_Send_OK();
                    Run_Fast.step = 1;
                }
            }
        }
        if(Run_Fast.step == 1)
        {
            if(Vision_Dat_Explan() != 0)
            {
                Run_Fast.user_num1++;
                for(Run_Fast.i=0; Run_Fast.i<Vision_Coord.Res_Num; Run_Fast.i++)
                {
                    if(Vision_Coord.Res_Coord[Run_Fast.i].x > (Run_Fast.last_res.x + 5))
                    {
                        if(Run_Fast.i > 0)
                        {
                            Run_Fast.last_res.x = Vision_Coord.Res_Coord[Run_Fast.i-1].x; 
                            Run_Fast.last_res.y = Vision_Coord.Res_Coord[Run_Fast.i-1].y; 
                        }
                        else
                        {
                            Run_Fast.last_res.x = 0;
                            Run_Fast.last_res.y = 0;
                        }
                        break;
                    }
                }
                if(Run_Fast.user_num1 >= 30)
                {
                    for(Run_Fast.i=0; Run_Fast.i<Vision_Coord.Res_Num; Run_Fast.i++)
                    {
                        Run_Fast.res_coord[Run_Fast.i].x = Vision_Coord.Res_Coord[Run_Fast.i].x;
                        Run_Fast.res_coord[Run_Fast.i].y = Vision_Coord.Res_Coord[Run_Fast.i].y;
                    }
                    Run_Fast.res_num = Vision_Coord.Res_Num;

                    for(Run_Fast.i=0; Run_Fast.i<Run_Fast.res_num; Run_Fast.i++)
                    {
                        if(Run_Fast.res_coord[Run_Fast.i].x > Run_Fast.last_res.x)
                        {
                            Run_Fast.need_point_num++;
                        }
                    }
                    Run_Fast.i = 0;
                    Run_Fast.step = 2;
                    Run_Fast.user_num1 = 0;
                    Run_Fast.user_num2 = 0;
                }
            }
            Run_Fast.user_num2++;
            if(Run_Fast.user_num2 >= 3000)
            {
                Run_Fast.user_num1 = 0;
                Run_Fast.user_num2 = 0;
                Infared_Send_OK();
                Run_Fast.step = 0;
            }
        }
        if(Run_Fast.step == 2)
        {
            if((Run_Fast.user_num1 % 5000 == 0) && (Run_Fast.i < Run_Fast.need_point_num))
            {
                Relay_Control(RELAY_OFF);
                Lcd_printf("Detected %s %s:x=%d,y=%d", ColorStr[select_color-1], ShapeStr[select_shape-1], Run_Fast.res_coord[Run_Fast.res_num-Run_Fast.need_point_num+Run_Fast.i].x, Run_Fast.res_coord[Run_Fast.res_num-Run_Fast.need_point_num+Run_Fast.i].y);
                DiWenLcd_Printf("��⵽%s%s: X=%d,Y=%d", ColorStrZh[select_color-1], ShapeStrZh[select_shape-1], Run_Fast.res_coord[Run_Fast.res_num-Run_Fast.need_point_num+Run_Fast.i].x, Run_Fast.res_coord[Run_Fast.res_num-Run_Fast.need_point_num+Run_Fast.i].y);
                Run_Fast.res_sum++;
				DiWenLcd_Cmd_Data(0x6006, Run_Fast.res_sum);
                Tripod_X_Coord(Run_Fast.res_coord[Run_Fast.res_num-Run_Fast.need_point_num+Run_Fast.i].x);
                Tripod_Y_Coord(Run_Fast.res_coord[Run_Fast.res_num-Run_Fast.need_point_num+Run_Fast.i].y);
                Voice_Play((select_shape-1)*4 + select_color);
                while(Tripod_Y.is_running);
                while(Tripod_X.is_running);
                Relay_Control(RELAY_ON);
                Run_Fast.i++;
                Run_Fast.user_num1 = 0;
            }

            Run_Fast.user_num1++;

            if(Run_Fast.user_num1 == 5001)
            {
                Relay_Control(RELAY_OFF);
            }

            if(Run_Fast.user_num1 == 5500)
            {
                Run_Fast.last_res.x = Run_Fast.res_coord[Run_Fast.res_num-1].x;
                Run_Fast.last_res.y = Run_Fast.res_coord[Run_Fast.res_num-1].y;
                Infared_Send_OK();
            }

            if(Run_Fast.user_num1 == 6000)
            {
                Run_Fast.user_num1 = 0;
                Run_Fast.step = 0;
                Run_Fast.i = 0;
                Run_Fast.need_point_num = 0;
            }
        }
    }
}



