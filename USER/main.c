
/******************** 鑫盛电子工作室 ********************
 * 文件名  ：main.c
 * 描述    ：通过串口调试软件，向板子发送数据，板子接收到数据后，立即回传给电脑。         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.0.0  																										  
 * 淘宝店：http://shop66177872.taobao.com
*********************************************************/

#include "stm32f10x.h"
#include "usart1.h"
#include "misc.h"
#include "exti.h"

int main(void)
{       
  	SystemInit();	//配置系统时钟为 72M 
	USART1_Config(); //USART1 配置 		  
	USART3_int(); //USART3 配置	
	NVIC_Configuration();//中断配置	
	EXTI_uart1_config();//串口1中断配置
	DelayNuS(10000000);
	UART1SendByte('O') ; //激光测距开机
	UART1SendByte('C') ; //激光测距连续测距命令
  	while (1)
  	{	
	 	DelayNuS(2000000);

  	}
}




