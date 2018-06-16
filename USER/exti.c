#include "exti.h"
#include "usart1.h"
/*����Ƕ�������жϿ�����NVIC */

unsigned char USART_RX_BUF[64];     //���ջ���,���64���ֽ�.
unsigned int BUFLEN=0;
unsigned char   clc=0;
//����״̬
//bit7��00
//bit6�����յ�FF
//bit5~0�����յ�����Ч�ֽ���Ŀ
unsigned int USART_RX_STA=0;       //����״̬���

void NVIC_Configuration(void)
{

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);// �������ȼ�����
  
}

void EXTI_uart1_config(void)
{    
  NVIC_InitTypeDef NVIC_InitStructure; 
  
  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}



void USART1_IRQHandler(void)                	//����1�жϷ������
{
	unsigned char Res;
	unsigned int  j;
	unsigned char data;
	unsigned int  sum;
	unsigned char  sum_l;
	unsigned char  sum_h;
	unsigned char  cc[100];
	unsigned char  ERR[100]={"$STSDI,90000,2,2,2,2,2,2,2*52"};
	unsigned int num=0;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)   //�����ж�
	{

		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		if(Res==0xff)
		{
			BUFLEN=0;
		}
		USART_RX_BUF[BUFLEN]=Res;
		BUFLEN++;
		USART_RX_STA = BUFLEN;
		if(BUFLEN ==6)//���յ�6���ֽ���������ʱ
		{
			if(USART_RX_BUF[0]==0xff)
			{
				if((USART_RX_BUF[2]==0x0A)&&(USART_RX_BUF[3]==0x0A)&&(USART_RX_BUF[4]==0x0A))
				{
					j=0;
					while(ERR[j]!='\0')
					{  
						RS485_SendByte(ERR[j]);	 
						j++;
					}					
					 RS485_SendByte(0x0D);
					 RS485_SendByte(0x0A);
				}
				else
				{
//					RS485_SendByte('$');
//					RS485_SendByte('S');
//					RS485_SendByte('T');
//					RS485_SendByte('S');
//					RS485_SendByte('D');
//					RS485_SendByte('I');
//					RS485_SendByte(',');
					sum='S'^'T'^'S'^'D'^'I';
					for(j=1;j<6;j++)
					{
						

						if(USART_RX_BUF[j]!=0)	//�ҵ����λ
						{
							data=j;
							for(j=data;j<6;j++)
							{
						//		RS485_SendByte(USART_RX_BUF[j]+48);	
								sum=sum^(USART_RX_BUF[j]+48);
							}
							num=USART_RX_BUF[1]*10000+USART_RX_BUF[2]*1000+USART_RX_BUF[3]*100+USART_RX_BUF[4]*10+USART_RX_BUF[5];
							break;
							
						}
					}

//					RS485_SendByte(',');
//					RS485_SendByte('2');
// 					RS485_SendByte(',');
//					RS485_SendByte('2');
// 					RS485_SendByte(',');
//					RS485_SendByte('2');
//					RS485_SendByte(',');
//					RS485_SendByte('2');
// 					RS485_SendByte(',');
//					RS485_SendByte('2');
//					RS485_SendByte(',');
//					RS485_SendByte('2');
//					RS485_SendByte(',');
//					RS485_SendByte('2');
//					RS485_SendByte('*');
					sum=sum^'2';

					sum=0;
					sprintf(cc,"$STSDI,%d,2,2,2,2,2,2,2,2",num);

					    j=1;
						while(cc[j]!='\0')
						{  
							sum=sum^cc[j];	 
							j++;
						}
						j=0;
						while(cc[j]!='\0')
						{  
							RS485_SendByte(cc[j]);	 
							j++;
						}
	
	
	
	
	
						RS485_SendByte('*');
				   		
						sum_l=sum&0x0f;
						sum_h=(sum>>4)&0x0f;
						if(sum_h>=10)
						{
							RS485_SendByte(sum_h+55);	
						}
						else
						{
							RS485_SendByte(sum_h+48);
						}
	
						if(sum_l>=10)
						{
							RS485_SendByte(sum_l+55);	
						}
						else
						{
							RS485_SendByte(sum_l+48);
						}
	
						RS485_SendByte(0X0D);
						RS485_SendByte(0X0A);
					

				}

			}
			USART_RX_STA=0;
			BUFLEN=0;		
		}

	



	}	  
} 



