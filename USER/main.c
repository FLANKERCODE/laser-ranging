
/******************** ��ʢ���ӹ����� ********************
 * �ļ���  ��main.c
 * ����    ��ͨ�����ڵ������������ӷ������ݣ����ӽ��յ����ݺ������ش������ԡ�         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * ��汾  ��ST3.0.0  																										  
 * �Ա��꣺http://shop66177872.taobao.com
*********************************************************/

#include "stm32f10x.h"
#include "usart1.h"
#include "misc.h"
#include "exti.h"

int main(void)
{       
  	SystemInit();	//����ϵͳʱ��Ϊ 72M 
	USART1_Config(); //USART1 ���� 		  
	USART3_int(); //USART3 ����	
	NVIC_Configuration();//�ж�����	
	EXTI_uart1_config();//����1�ж�����
	DelayNuS(10000000);
	UART1SendByte('O') ; //�����࿪��
	UART1SendByte('C') ; //�����������������
  	while (1)
  	{	
	 	DelayNuS(2000000);

  	}
}




