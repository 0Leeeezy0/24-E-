#include "common.h"

void int16_2_uint8(int16 int16data)
{
    int16TOuint8_result.low_byte = (uint8)(int16data & 0xFF);
    int16TOuint8_result.high_byte = (uint8)((int16data >> 8) & 0xFF);
}

int16 uint8_2_int16(uint8 low_byte, uint8 high_byte)
{
    int16 High_Data=((int16)high_byte)<<8;
    // С������ϣ��ȷŵ�λ�ֽڣ��ٷŸ�λ�ֽڣ�����8λ��
    return (int16)(High_Data | low_byte);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��int32���͵����ݲ�ֳ��ĸ�uint8����
// ʹ��ʾ��
//-------------------------------------------------------------------------------------------------------------------
void int32_2_uint8(int32 int32data)
{
    Int32ToBytes[0] = (uint8)( int32data & 0xFF);        // ���λ�ֽ�
    Int32ToBytes[1] = (uint8)((int32data >> 8) & 0xFF);  // �ڶ���λ�ֽ�
    Int32ToBytes[2] = (uint8)((int32data >> 16) & 0xFF); // �ڶ���λ�ֽ�
    Int32ToBytes[3] = (uint8)((int32data >> 24) & 0xFF); // ���λ�ֽ�
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���ĸ�uint8���ݺϲ���һ��int32����
// ʹ��ʾ��
//-------------------------------------------------------------------------------------------------------------------
int32 uint8_2_int32(uint8 Byte_A, uint8 Byte_B, uint8 Byte_C, uint8 Byte_D)
{
    return ((int32)Byte_D << 24) | ((int32)Byte_C << 16) | ((int32)Byte_B << 8)  | (int32)Byte_A;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��int16�͵�����ת��Ϊuint8�����ͳ�ȥ
// ʹ��ʾ��
//-------------------------------------------------------------------------------------------------------------------
void uart3_send_int16(int16 INT16DATA)
{
    uint8 uart_send_buff[2]={0x00};//����Ҫͨ��UART3���͵�����
    int16_2_uint8(INT16DATA);//����������ݽ���ת��,ת���������int16TOuint8_result�ṹ����
    //д�뷢������
    uart_send_buff[0]=int16TOuint8_result.low_byte;
    uart_send_buff[1]=int16TOuint8_result.high_byte;

    uart_write_buffer(UART_3,uart_send_buff,2);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ��int16�͵�����ת��Ϊuint8�����ͳ�ȥ
// ʹ��ʾ��
//-------------------------------------------------------------------------------------------------------------------
void uart3_send_int32(int32 INT32DATA)
{
    uint8 uart_send_buff[4]={0x00};//����Ҫͨ��UART3���͵�����
    int32_2_uint8(INT32DATA);//����������ݽ���ת����ת���������Int32ToBytes[4]���������
    //д�뷢������
    uart_send_buff[0]=Int32ToBytes[0];
    uart_send_buff[1]=Int32ToBytes[1];
    uart_send_buff[2]=Int32ToBytes[2];
    uart_send_buff[3]=Int32ToBytes[3];

    uart_write_buffer(UART_3,uart_send_buff,4);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ����һ������ѡ����λ���·�������ģʽ
// ���ݸ�ʽ     A0 A1 ģʽ A2
//-------------------------------------------------------------------------------------------------------------------
void uart3_send_Mode(uint8 mode,uint8 color)
{
    uint8 uart_send_buff[5]={0x00};//����Ҫͨ��UART3���͵�����
    uart_send_buff[0]=0xA0;
    uart_send_buff[1]=0xA1;
    uart_send_buff[2]=mode;
    uart_send_buff[3]=color;
    uart_send_buff[4]=0xA2;

    uart_write_buffer(UART_3,uart_send_buff,5);
}
