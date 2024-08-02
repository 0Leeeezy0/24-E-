/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          cpu0_main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.4
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "common.h"
#pragma section all "cpu0_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��
// **************************** �������� ****************************
//#define IPS200_TYPE     (IPS200_TYPE_PARALLEL8)                                 // ˫������ ���������� ����궨����д IPS200_TYPE_PARALLEL8
//                                                                                // �������� SPI ������ ����궨����д IPS200_TYPE_SPI
int core0_main(void)
{
    clock_init();                   // ��ȡʱ��Ƶ��<��ر���>
    debug_init();                   // ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�û����� ���������ʼ�������

    Init_All();

    pit_us_init(CCU60_CH0,1000);//����ͨ���޸������ʱ����Ƶ��ʵ�ֲ�������ٶȵ���
    pit_ms_init(CCU60_CH1,1);//����ɨ�趨ʱ��

//    pwm_init(ATOM0_CH4_P02_4,Fre_A,5000);

    uart_init(UART_3,115200,UART3_TX_P15_6,UART3_RX_P15_7);//���ڶ�λģ���ͨ��
    uart_rx_interrupt(UART_3,1);

//    Motor_Move_Check();
    // �˴���д�û����� ���������ʼ�������
	cpu_wait_event_ready();         // �ȴ����к��ĳ�ʼ�����
	while (TRUE)
	{
	    Menu_Switch();

//        if(Key_Get(Key_Left)==KEY_ShortPress)
//        {
////            pwm_set_duty(ATOM0_CH4_P02_4,0);
//            gpio_set_level(P20_10,0);
//            gpio_toggle_level(LED2);
//            Key_clear_state(Key_Left);
//        }
//        if(Key_Get(Key_Right)==KEY_ShortPress)
//        {
////            pwm_set_duty(ATOM0_CH4_P02_4,5000);
//            gpio_set_level(P20_10,1);
//            gpio_toggle_level(LED3);
//            Key_clear_state(Key_Right);
//        }
//        if(Key_Get(Key_Enter)==KEY_ShortPress)
//        {
//            Key_clear_state(Key_Enter);
//        }
//	    if(!gpio_get_level(KEY_Down))
//	    {
//	        while(!gpio_get_level(KEY_Down));
//	        gpio_toggle_level(LED1);
//	    }
	}
}

#pragma section all restore
// **************************** �������� ****************************

// *************************** ���̳�������˵�� ***************************
// ��������ʱ�밴�������������б���
// ����1����Ļ����ʾ
//      ���ʹ��������ԣ��������Ҫ�õ�ع��� �����Ļ�������ŵ�ѹ
//      �����Ļ�ǲ��ǲ��λ���� ������Ŷ�Ӧ��ϵ
//      �����Ӧ���Ŷ���ȷ ���һ���Ƿ������Ų��β��� ��Ҫ��ʾ����
//      �޷���ɲ��β�������һ��GPIO���̽���Ļ����IO��ʼ��ΪGPIO��ת��ƽ �����Ƿ��ܿ�
