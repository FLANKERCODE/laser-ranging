/******************** 鑫盛电子工作室 ********************
 * 文件名  ：usart1.c
 * 描述    ：配置USART1         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * 库版本  ：ST3.0.0  
 * 淘宝店：http://shop66177872.taobao.com
**********************************************************************************/

#include "usart1.h"
#include <stdarg.h>

/*RE跟GPIOB1管脚相连*/   
#define Set_RE  GPIO_SetBits(GPIOB,GPIO_Pin_1);			 
#define Clr_RE  GPIO_ResetBits(GPIOB,GPIO_Pin_1);
/*DE跟GPIOB0管脚相连*/
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
/*配置 USART3*/

void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 使能 USART3 时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//使能外设时钟	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* USART3 使用IO端口配置 */    
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);    
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);   //初始化GPIOA
	  
	/* USART3 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 115200;	//波特率设置：9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收与发送都使能
	USART_Init(USART3, &USART_InitStructure);  //初始化USART3
	
    /*使能串口3的发送和接收中断*/
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    

	USART_Cmd(USART3, ENABLE);// USART3使能
}

 /*发送一个字节数据*/
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
/*初始化USART3*/
void USART3_int(void)
{ 
  USART3_Config();
}

void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 使能 USART1 时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO, ENABLE); 

	/* USART1 使用IO端口配置 */    
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
  	GPIO_Init(GPIOA, &GPIO_InitStructure);   //初始化GPIOA
	  
	/* USART1 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 9600;	//波特率设置：115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收与发送都使能
	USART_Init(USART1, &USART_InitStructure);  //初始化USART1
	USART_Cmd(USART1, ENABLE);// USART1使能
}

 /*发送一个字节数据*/
 void UART1SendByte(unsigned char SendData)
{	   
    USART_SendData(USART1,SendData);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	    
}  

/*接收一个字节数据*/
unsigned char UART1GetByte(unsigned char* GetData)
{   	   
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) == RESET)
    {  return 0;//没有收到数据 
	}
    *GetData = USART_ReceiveData(USART1); 
    return 1;//收到数据
}




