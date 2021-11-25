#include "OpenMV.h"
#include "stdio.h"
#include "usart.h"


 uint8_t  Cx=0,Cy=0,Cw=0,Ch=0;

void   Openmv_Receive_Data(int16_t com_data)
{
  
    uint8_t i;
		static uint8_t RxCounter1=0;//����
		static uint16_t RxBuffer1[10]={0};
		static uint8_t RxState = 0;	
		static uint8_t RxFlag1 = 0;

  if(RxState==0&&com_data==0x2C)  //0x2c֡ͷ
				{
          
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
          HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
				}

				else if(RxState==1&&com_data==0x12)  //0x12֡ͷ
				{
          HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
				}
				else if(RxState==2)
				{
           
					RxBuffer1[RxCounter1++]=com_data;
					if(RxCounter1>=10||com_data == 0x5B)       //RxBuffer1��������,�������ݽ���
					{
						RxState=3;
						RxFlag1=1;
            
						Cx=RxBuffer1[RxCounter1-5];
						Cy=RxBuffer1[RxCounter1-4];
						Cw=RxBuffer1[RxCounter1-3];
						Ch=RxBuffer1[RxCounter1-2];
            printf("%d\r   ",Cx);
            printf("%d\r   ",Cy);
            printf("%d\r   ",Cw);
            printf("%d\r\n",Ch); 
//               if(RxState==1)
//          {
//            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
//          }
//          else if(RxState!=1&&RxState!=0)
//          {
//            HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
//          }
					}
			}
		
				else if(RxState==3)		//����Ƿ���ܵ�������־
				{
						if(RxBuffer1[RxCounter1-1] == 0x5B)
						{
									
									RxFlag1 = 0;
									RxCounter1 = 0;
									RxState = 0;
								
						}
						else   //���մ���
						{
									RxState = 0;
									RxCounter1=0;
									for(i=0;i<10;i++)
									{
											RxBuffer1[i]=0x00;      //�����������������
									}
						}
				} 
	
				else   //�����쳣
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //�����������������
						}
				}
      }

/**
  * ��������: �ض���c�⺯��printf��DEBUG_USARTx
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}
 
/**
  * ��������: �ض���c�⺯��getchar,scanf��DEBUG_USARTx
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
  return ch;
}
