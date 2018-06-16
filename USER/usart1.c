/******************** ��ʢ���ӹ����� ********************
 * �ļ���  ��usart1.c
 * ����    ������USART1         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ�------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * ��汾  ��ST3.0.0  
 * �Ա��꣺http://shop66177872.taobao.com
**********************************************************************************/

#include "usart1.h"
#include <stdarg.h>

/*RE��GPIOB1�ܽ�����*/   
#define Set_RE  GPIO_SetBits(GPIOB,GPIO_Pin_1);			 
#define Clr_RE  GPIO_ResetBits(GPIOB,GPIO_Pin_1);
/*DE��GPIOB0�ܽ�����*/
#define Set_DE  GPIO_SetBits(GPIOB,GPIO_Pin_0);
#define Clr_DE  GPIO_ResetBits(GPIOB,GPIO_Pin_0);

void DelayNuS(unsigned int i)
{
	unsigned char t = 0;
    for(;i>0;i--)
    {
       for(t=0;t<2;t++)
       {
       }
    }
} 
/*���� USART3*/

void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� USART3 ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//ʹ������ʱ��	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* USART3 ʹ��IO�˿����� */    
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);    
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);   //��ʼ��GPIOA
	  
	/* USART3 ����ģʽ���� */
	USART_InitStructure.USART_BaudRate = 115200;	//���������ã�9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�����뷢�Ͷ�ʹ��
	USART_Init(USART3, &USART_InitStructure);  //��ʼ��USART3
	
    /*ʹ�ܴ���3�ķ��ͺͽ����ж�*/
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    

	USART_Cmd(USART3, ENABLE);// USART3ʹ��
}

 /*����һ���ֽ�����*/
 void RS485_SendByte(unsigned char SendData)
{	   
        Set_DE;
	    Set_RE;
		DelayNuS(5000);
        USART_SendData(USART3,SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		DelayNuS(5000);
	    Clr_DE;
	    Clr_RE; 	    
}  
/*��ʼ��USART3*/
void USART3_int(void)
{ 
  USART3_Config();
}

void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� USART1 ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO, ENABLE); 

	/* USART1 ʹ��IO�˿����� */    
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
  	GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOA
	  
	/* USART1 ����ģʽ���� */
	USART_InitStructure.USART_BaudRate = 9600;	//���������ã�115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�����뷢�Ͷ�ʹ��
	USART_Init(USART1, &USART_InitStructure);  //��ʼ��USART1
	USART_Cmd(USART1, ENABLE);// USART1ʹ��
}

 /*����һ���ֽ�����*/
 void UART1SendByte(unsigned char SendData)
{	   
    USART_SendData(USART1,SendData);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	    
}  

/*����һ���ֽ�����*/
unsigned char UART1GetByte(unsigned char* GetData)
{   	   
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) == RESET)
    {  return 0;//û���յ����� 
	}
    *GetData = USART_ReceiveData(USART1); 
    return 1;//�յ�����
}




