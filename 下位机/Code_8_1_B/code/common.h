/*
 * common.h
 *
 *  Created on: 2024��7��30��
 *      Author: 86152
 */

#ifndef CODE_COMMON_H_
#define CODE_COMMON_H_

//���ܵ�����λ��
//��ע��1.�޸����ݳ���;2.�޸�uart3_receive()����������ݽ���switch���;
#define length_uart_receive_info 12

#define LED1                    (P20_9)
#define LED2                    (P20_8)
#define LED3                    (P21_5)
#define LED4                    (P21_4)

#define KEY_Down                (P20_6)
#define KEY_Left                (P20_7)
#define KEY_Right               (P11_2)
#define KEY_Enter               (P11_3)

//�ұߵ�������
#define DIR_X_Left               (P33_6)
#define DIR_X_Right              (P02_5)
#define DIR_Y                    (P02_6)
#define DIR_Z                    (P02_4)

//#define PWM_X_Left               (P02_4)
//#define PWM_X_Right              (P10_1)
//#define PWM_Y                    (P02_5)
//#define PWM_Z                    (P10_3)

#define PWM_X_Left               (P33_7)
#define PWM_X_Right              (P02_4)
#define PWM_Y                    (P02_7)
#define PWM_Z                    (P02_5)

#define Chess_Gripper            (P21_3)

typedef enum
{
    KEY_Release,                                                                // �����ͷ�״̬
    KEY_ShortPress,                                                            // �����̰�״̬
    KEY_LongPress,                                                             // ��������״̬
}KEY_State;
typedef enum
{
    Key_Down,
    Key_Left,
    Key_Right,
    Key_Enter,
}Key_index_enum;



#include "zf_common_headfile.h"
#include "All_Variables.h"
#include "Motor.h"
#include "My_Device.h"
#include "Page.h"
#include "Data.h"
#include "UART_Analysis.h"

#endif /* CODE_COMMON_H_ */
