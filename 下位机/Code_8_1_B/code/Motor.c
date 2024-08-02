#include "common.h"


//-------------------------------------------------------------------------------------------------------------------
//  �������      ����X�᷽��Ĳ�����ִ��һ��(������)
//  ����˵��
//-------------------------------------------------------------------------------------------------------------------
void Mortor_Move_X(int32 step_X)
{
    Step_OnceX_relative=step_X;//ÿ�ξ��Բ����ı仯����������Ĳ���
    if(step_X >= 0)
    {
        gpio_set_level(DIR_X_Left,1);
        gpio_set_level(DIR_X_Right,1);
        Step_X=step_X;
    }
    if(step_X < 0)
    {
        gpio_set_level(DIR_X_Left,0);
        gpio_set_level(DIR_X_Right,0);
        Step_X=-step_X;
    }

    MotorX_Flag=1;
}
//-------------------------------------------------------------------------------------------------------------------
//  �������      ����Y�᷽��Ĳ�����ִ��һ��(������)
//  ����˵��
//-------------------------------------------------------------------------------------------------------------------
void Mortor_Move_Y(int32 step_Y)
{
    Step_OnceY_relative=step_Y;
    if(step_Y >= 0)
    {
        gpio_set_level(DIR_Y,1);
        Step_Y=step_Y;
    }
    if(step_Y < 0)
    {
        gpio_set_level(DIR_Y,0);
        Step_Y=-step_Y;
    }

    MotorY_Flag=1;
}
//-------------------------------------------------------------------------------------------------------------------
//  �������      ����Y�᷽��Ĳ�����ִ��һ��(������)
//  ����˵��
//-------------------------------------------------------------------------------------------------------------------
void Mortor_Move_Z(int32 step_Z)
{
    Step_OnceZ_relative=step_Z;
    if(step_Z >= 0)
    {
        gpio_set_level(DIR_Z,0);
        Step_Z=step_Z;
    }
    if(step_Z < 0)
    {
        gpio_set_level(DIR_Z,1);
        Step_Z=-step_Z;
    }

    MotorZ_Flag=1;
}

//-------------------------------------------------------------------------------------------------------------------
//  �������      ������ĵ�������Լ�
//  ����˵��
//-------------------------------------------------------------------------------------------------------------------

void Motor_Move_Check(void)
{
    Mortor_Move_X(30);
    system_delay_ms(1000);
    Mortor_Move_X(-30);
    system_delay_ms(1000);
    Mortor_Move_Y(30);
    system_delay_ms(1000);
    Mortor_Move_Y(-30);
    system_delay_ms(1000);
    Mortor_Move_Z(5);
    system_delay_ms(1000);
    Mortor_Move_Z(-5);
}
//-------------------------------------------------------------------------------------------------------------------
//  �������      ����ץȡ
//  ����˵��      ���º�ץ��������
//              ����������;ƽʱ���͵�ƽ��ͨ�粻����
//-------------------------------------------------------------------------------------------------------------------
void Chess_Grab(void)
{
    gpio_set_level(P21_4,1);
    gpio_set_level(P21_2,1);

    Mortor_Move_Z(60);
    system_delay_ms(500);//�ȴ��ƶ����
    gpio_set_level(Chess_Gripper,0);
    gpio_set_level(LED3,0);
    system_delay_ms(300);
    Mortor_Move_Z(-60);
    system_delay_ms(500);
}
//-------------------------------------------------------------------------------------------------------------------
//  �������      ���ӷ���
//  ����˵��      ���º�������
//-------------------------------------------------------------------------------------------------------------------
void Chess_Put(void)
{
    gpio_set_level(P21_4,0);
    gpio_set_level(P21_2,0);

    Mortor_Move_Z(40);
    system_delay_ms(500);//�ȴ��ƶ����
    gpio_set_level(Chess_Gripper,1);
    gpio_set_level(LED3,1);
    system_delay_ms(500);
    Mortor_Move_Z(-40);
    system_delay_ms(500);
    gpio_set_level(Chess_Gripper,0);
    gpio_set_level(LED3,0);
}


//-------------------------------------------------------------------------------------------------------------------
//  �������      �ӵ�ǰ���ƶ���P��(P������Ϊ��������)
//  ����˵��
//  ����˵��
//-------------------------------------------------------------------------------------------------------------------
void Facility_TO_Point(int32 position_x, int32 position_y)
{
    int32 STEP_X=position_x-Step_X_absolute;
    int32 STEP_Y=position_y-Step_Y_absolute;
    Mortor_Move_X(STEP_X);
//    system_delay_ms(1000);
    Mortor_Move_Y(STEP_Y);
}


//-------------------------------------------------------------------------------------------------------------------
//  �������      ���ڵ�ǰλ�õ��豸�ƶ�
//  ����˵��      xmmΪˮƽ�ƶ�����
//  ����˵��      ymmΪ��ֱ�ƶ�����
//-------------------------------------------------------------------------------------------------------------------
void Facility_Move_MM(int32 xmm, int32 ymm)
{
    int32 x_step_temp=xmm*5;//ת��Ϊ������
    int32 y_step_temp=ymm*5;//ת��Ϊ������
    Mortor_Move_X(x_step_temp);
    Mortor_Move_Y(y_step_temp);
}

//-------------------------------------------------------------------------------------------------------------------
//  �������      ��A��Ų��B��(MM����)
//  ����˵��      A_XMM��A_YMMΪ��A������
//  ����˵��      B_XMM��B_YMMΪ��B������
//-------------------------------------------------------------------------------------------------------------------
void Facility_Move_From_ATOB_MM(int32 A_XMM, int32 A_YMM, int32 B_XMM, int32 B_YMM)
{
    uint32 X_Pulse=(B_XMM-A_XMM)*5;
    uint32 Y_Pulse=(B_YMM-A_YMM)*5;
    Mortor_Move_X(X_Pulse);
    Mortor_Move_Y(Y_Pulse);
}

//-------------------------------------------------------------------------------------------------------------------
//  �������      ��A��ץȡ����Ų����B�㲢����(MM����)
//  ����˵��      A_XMM��A_YMMΪ��A������
//  ����˵��      B_XMM��B_YMMΪ��B������
//-------------------------------------------------------------------------------------------------------------------
void Facility_Catch_From_ATOB_MM(int32 A_XMM, int32 A_YMM, int32 B_XMM, int32 B_YMM)
{
    uint32 X_Pulse=(B_XMM-A_XMM)*5;
    uint32 Y_Pulse=(B_YMM-A_YMM)*5;
    Chess_Grab();
    Mortor_Move_X(X_Pulse);
    Mortor_Move_Y(Y_Pulse);
    Chess_Put();
}

//-------------------------------------------------------------------------------------------------------------------
//  �������      ��A��Ų��B��(��������)
//  ����˵��      A_XPixel��A_YPixelΪ��A������
//  ����˵��      B_XPixel��B_YPixelΪ��B������
//-------------------------------------------------------------------------------------------------------------------
void Facility_Move_From_ATOB_Pixel(int32 A_XPixel, int32 A_YPixel, int32 B_XPixel, int32 B_YPixel)
{
    int32 X_Pulse=(B_XPixel-A_XPixel)*6.15;//ת��ϵ������
    int32 Y_Pulse=(B_YPixel-A_YPixel)*6.15;
    Mortor_Move_X(X_Pulse);
//    system_delay_ms(200);
    Mortor_Move_Y(Y_Pulse);
}

//-------------------------------------------------------------------------------------------------------------------
//  �������      ��A��ץȡ����Ų����B�㲢����(��������)
//  ����˵��      A_XPixel��A_YPixelΪ��A������
//  ����˵��      B_XPixel��B_YPixelΪ��B������
//-------------------------------------------------------------------------------------------------------------------
void Facility_Catch_From_ATOB_Pixel(int32 A_XPixel, int32 A_YPixel, int32 B_XPixel, int32 B_YPixel)
{
    Chess_Grab();
    Facility_Move_From_ATOB_Pixel(A_XPixel,A_YPixel,B_XPixel,B_YPixel);
    Chess_Put();
}

void Question2_3_Base(int32 NumChess,int32 NumNine)
{
    int NineSpace[2] = {0};
    int ChessPoint[2] = {0};

        ChessPoint[0] = AllChessPosition[NumChess-1][0];
        ChessPoint[1] = AllChessPosition[NumChess-1][1];

    NineSpace[0] = ChessPosition[NumNine-11][0];
    NineSpace[1] = ChessPosition[NumNine-11][1];

    Facility_TO_Point(Step_Origin_TO_Center_X,Step_Origin_TO_Center_Y);//�ȵ�����
    system_delay_ms(1000);
    Facility_Move_From_ATOB_Pixel(160,120,ChessPoint[0],ChessPoint[1]);
    system_delay_ms(1000);
    Chess_Grab();
    system_delay_ms(1000);
    Facility_Move_From_ATOB_Pixel(ChessPoint[0],ChessPoint[1],NineSpace[0],NineSpace[1]);
    system_delay_ms(1000);
    Chess_Put();
    system_delay_ms(1000);
    Facility_TO_Point(Step_Origin_TO_Center_X,Step_Origin_TO_Center_Y);//�ȵ�����
    system_delay_ms(1000);
}

void Question2_3(void)
{
    for(int i = 0;i < 4;i++)
    {
        Question2_3_Base(Point_Num_Select[i],Num_Select[i]);
    }
}

void Question4(void)
{
    if((Recive==true) && (Rigged==false))
    {
        static int BlackChessNum=0;//��ǰŲ�߼�������
        static int WhiteChessNum=0;
        Facility_TO_Point(Step_Origin_TO_Center_X,Step_Origin_TO_Center_Y);
        system_delay_ms(2000);
        if(COLOR==0)//��ɫ
        {
            Facility_Move_From_ATOB_Pixel(160,120,WhiteChessPosition[WhiteChessNum][0],WhiteChessPosition[WhiteChessNum][1]);
            system_delay_ms(2000);
            Chess_Grab();
            system_delay_ms(2000);
            Facility_Move_From_ATOB_Pixel(WhiteChessPosition[WhiteChessNum][0],WhiteChessPosition[WhiteChessNum][1],ChessPosition[checkerboard_PC1][0],ChessPosition[checkerboard_PC1][1]);
            system_delay_ms(2000);
            Chess_Put();
            Facility_TO_Point(position_P_X,position_P_Y);
            system_delay_ms(2000);
            WhiteChessNum++;//����һöŲ������
        }
        else if(COLOR==1)
        {
            Facility_Move_From_ATOB_Pixel(160,120,BlackChessPosition[BlackChessNum][0],BlackChessPosition[BlackChessNum][1]);
            system_delay_ms(2000);
            Chess_Grab();
            system_delay_ms(2000);
            Facility_Move_From_ATOB_Pixel(BlackChessPosition[BlackChessNum][0],BlackChessPosition[BlackChessNum][1],ChessPosition[checkerboard_PC1][0],ChessPosition[checkerboard_PC1][1]);
            system_delay_ms(2000);
            Chess_Put();
            Facility_TO_Point(position_P_X,position_P_Y);
            system_delay_ms(2000);
            BlackChessNum++;//����һöŲ������
        }
    }
    else if((Recive==true) && (Rigged==true))
    {
        Facility_TO_Point(Step_Origin_TO_Center_X,Step_Origin_TO_Center_Y);//������
        system_delay_ms(2000);
        Facility_Move_From_ATOB_Pixel(160,120,ChessPosition[checkerboard_PC2][0],ChessPosition[checkerboard_PC2][1]);//����������
        system_delay_ms(2000);
        Chess_Grab();
        system_delay_ms(2000);
        Facility_Move_From_ATOB_Pixel(ChessPosition[checkerboard_PC2][0],ChessPosition[checkerboard_PC2][1],ChessPosition[checkerboard_PC1][0],ChessPosition[checkerboard_PC1][1]);//�����굽������
        system_delay_ms(2000);
        Chess_Put();
        Facility_TO_Point(position_P_X,position_P_Y);
    }
    Recive=false;
}
