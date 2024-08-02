#include "common.h"

//#include "ALL_Variables.h"


void Init_All(void)
{
    gpio_init(KEY_Down, GPI, GPIO_HIGH, GPI_PULL_UP);//�ĸ�������ʼ��
    gpio_init(KEY_Left, GPI, GPIO_HIGH, GPI_PULL_UP);
    gpio_init(KEY_Right, GPI, GPIO_HIGH, GPI_PULL_UP);
    gpio_init(KEY_Enter, GPI, GPIO_HIGH, GPI_PULL_UP);

    gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);//�ĸ�LED��
    gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(LED3, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(LED4, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    gpio_init(DIR_X_Left, GPO, GPIO_HIGH, GPO_PUSH_PULL);//�ĸ�������������ʼ��
    gpio_init(DIR_X_Right,GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(DIR_Y, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(DIR_Z, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    gpio_init(PWM_X_Left, GPO, GPIO_HIGH, GPO_PUSH_PULL);//�����������PWM�����IO�ڳ�ʼ��
    gpio_init(PWM_X_Right,GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(PWM_Y, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(PWM_Z, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    gpio_init(Chess_Gripper, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    ips200_init(IPS200_TYPE_PARALLEL8);//˫��

//    gpio_init(P21_2, GPO, GPIO_LOW, GPO_PUSH_PULL);
//    gpio_init(P21_4, GPO, GPIO_LOW, GPO_PUSH_PULL);
//    gpio_init(P21_3, GPO, GPIO_LOW, GPO_PUSH_PULL);
//    gpio_init(P21_5, GPO, GPIO_LOW, GPO_PUSH_PULL);
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ����״̬ɨ��
// ʹ��ʾ��     Key_Scan();
// ��ע��Ϣ     �������������ѭ������ PIT �ж���
// ��ע��Ϣ     ��������key_press_time��ʼ������������Ϊ����������С��Ϊ�̰���û��
// ��ע��Ϣ     �˺����ڶ�ʱ��3�е��ã�ִ��ʱ����������״̬���洢��Key_State[]��
//-------------------------------------------------------------------------------------------------------------------
void Key_Scan(void)
{
    uint8 i=0;
    for(i = 0;i<5; i ++)
    {
        if( !gpio_get_level(Key_index[i]))//�������¿�ʼ������������Ϊ����������С��Ϊ�̰���û��
        {
            key_press_time[i]++;
            if(key_press_time[i]>=KEY_LongPress_Period)//��ʱ�䰴��
            {
                Key_State[i]=KEY_LongPress;
            }
        }
        else
        {
            if((Key_State[i]!=KEY_LongPress) && (key_press_time[i]>=KEY_ShortPress_Period))
            {
                Key_State[i]=KEY_ShortPress;
            }
            else
            {
                Key_State[i]=KEY_Release;
            }
            key_press_time[i]=0;
         }
    }
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ����״̬��ȡ
// ʹ��ʾ��     if(Key_Get(Key_Up)==KEY_Release);//�԰���״̬�����ж�
// ��ע��Ϣ     �˺���������Ļ������
//-------------------------------------------------------------------------------------------------------------------
KEY_State Key_Get(Key_index_enum pin)
{
    return Key_State[pin];
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ����״̬���
// ʹ��ʾ��     Key_clear_state(Key_Up);
// ��ע��Ϣ     �˺������ڰ���״̬��ȡ�Ľ�β;ʵ�����ֹ��󣬰���ɨ��ɨ���˰���ʱ���Ѿ��������״̬���㣬�˺�������˫�ر���
//-------------------------------------------------------------------------------------------------------------------
void Key_clear_state (Key_index_enum key_n)
{
    Key_State[key_n] = KEY_Release;
}


