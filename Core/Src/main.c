/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "OpenMV.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t usart1_rxbuff;
uint8_t uart4_rxbuff;
uint8_t timer_count;
uint8_t cross2 = 0;
uint8_t cross3 = 0;
uint8_t cross4 = 0;
uint8_t cross5 = 0;
uint8_t startit = 0;
uint8_t start_move = 0;
uint8_t number_get_remind = 0;
extern uint8_t  Cx;
extern uint8_t  Cy;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define Get_Redline_L (HAL_GPIO_ReadPin(SCAN_L_GPIO_Port,SCAN_L_Pin) == 1) 
#define Get_Redline_R (HAL_GPIO_ReadPin(SCAN_R_GPIO_Port,SCAN_R_Pin) == 1) 
#define Get_line_0 (HAL_GPIO_ReadPin(XU_0_GPIO_Port,XU_0_Pin) == 1) 
#define Get_line_1 (HAL_GPIO_ReadPin(XU_1_GPIO_Port,XU_1_Pin) == 1) 
#define Get_line_2 (HAL_GPIO_ReadPin(XU_2_GPIO_Port,XU_2_Pin) == 1) 
#define Get_yao (HAL_GPIO_ReadPin(XU_3_GPIO_Port,XU_3_Pin) == 1) 
#define relse_yao (HAL_GPIO_ReadPin(XU_3_GPIO_Port,XU_3_Pin) == 0) 



#define Red_LED_ON		HAL_GPIO_WritePin (Red_GPIO_Port,Red_Pin,GPIO_PIN_SET);
#define Red_LED_OFF		HAL_GPIO_WritePin (Red_GPIO_Port,Red_Pin,GPIO_PIN_RESET);
#define Green_LED_ON		HAL_GPIO_WritePin (Green_GPIO_Port,Green_Pin,GPIO_PIN_SET);
#define Green_LED_OFF		HAL_GPIO_WritePin (Green_GPIO_Port,Green_Pin,GPIO_PIN_RESET);
#define Yellow_LED_ON		HAL_GPIO_WritePin (Yellow_GPIO_Port,Yellow_Pin,GPIO_PIN_SET);
#define Yellow_LED_OFF		HAL_GPIO_WritePin (Yellow_GPIO_Port,Yellow_Pin,GPIO_PIN_RESET);
#define Buzzer_ON		HAL_GPIO_WritePin (Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_RESET);
#define Buzzer_OFF		HAL_GPIO_WritePin (Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_SET);

#define arrive HAL_GPIO_WritePin (arrive_GPIO_Port,arrive_Pin,GPIO_PIN_SET);
#define car2right HAL_GPIO_WritePin (pos_GPIO_Port,pos_Pin,GPIO_PIN_SET);
#define carleft HAL_GPIO_WritePin (pos_GPIO_Port,pos_Pin,GPIO_PIN_RESET);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void TIM_SetTIM2Compare3 (uint32_t compare)  
{
  TIM2->CCR3=compare;
}

void TIM_SetTIM2Compare2 (uint32_t compare)  
{
  TIM2->CCR2=compare;
}




void go_straight(uint16_t speed){
	TIM_SetTIM2Compare2(speed);
	TIM_SetTIM2Compare3(speed);
	HAL_GPIO_WritePin (AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
	
	HAL_GPIO_WritePin (BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);
}
void go_back(uint16_t speed){
	TIM_SetTIM2Compare2(speed);
	TIM_SetTIM2Compare3(speed);
	HAL_GPIO_WritePin (AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin (BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
}


void stop(){

	HAL_GPIO_WritePin (AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin (BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
}

void turn_right(){
		TIM_SetTIM2Compare2(120);
		TIM_SetTIM2Compare3(120);
		HAL_GPIO_WritePin (AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin (AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
		
		HAL_GPIO_WritePin (BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin (BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
}

void turn_back(uint16_t h,uint16_t l){
		TIM_SetTIM2Compare2(h);
		TIM_SetTIM2Compare3(l);
		HAL_GPIO_WritePin (AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin (AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin (BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin (BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);
}

void turn_left(){
	TIM_SetTIM2Compare2(120);
	TIM_SetTIM2Compare3(120);
	HAL_GPIO_WritePin (AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin (AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin (BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin (BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);
}


void scan_right(uint16_t h,uint16_t l){
		TIM_SetTIM2Compare2(l);
		TIM_SetTIM2Compare3(h);
		HAL_GPIO_WritePin (AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin (AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
		
		HAL_GPIO_WritePin (BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin (BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);
}

void scan_left(uint16_t h,uint16_t l){
		TIM_SetTIM2Compare2(h);
		TIM_SetTIM2Compare3(l);
		HAL_GPIO_WritePin (AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin (AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
		
		HAL_GPIO_WritePin (BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin (BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	timer_count++;
	if(timer_count == 100){
		cross2 = 1;
		timer_count = 0;
		HAL_TIM_Base_Stop_IT(&htim3);
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_UART4_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart4,(void *)&uart4_rxbuff,1);
	HAL_UART_Receive_IT(&huart1,(void *)&usart1_rxbuff,1);
	uint8_t turn_count = 0;
	uint8_t back = 0;
	uint8_t back_ok = 0;
	uint8_t cross = 0;
	uint8_t cross2_turn_ok = 0;
	uint8_t back2_ok = 0;
	uint8_t turn_ok = 0;
	uint8_t turn1_ok = 0;
	uint8_t turn2_ok = 0;
	Buzzer_OFF;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		/*************************************************************			number2     *********************************************/		 
		if(Cx == 2){
			while(number_get_remind == 0){
				Buzzer_ON;
				HAL_Delay(500);
				Buzzer_OFF;
				number_get_remind = 1;
			}
		if(Cx == 2 && Get_yao && back == 0){
		 while(start_move == 0){
				go_straight(70);
				HAL_Delay(800);
				start_move = 1;
			}
			go_straight(70);
			if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
			if(Get_Redline_L && Get_Redline_R){
				HAL_Delay(100);
				turn_right();
				HAL_Delay(600);
			}
			if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
		  	Red_LED_ON;
				HAL_Delay(1000);
				back = 1;
			}
		}
		
		 if(relse_yao && back == 1 && back_ok == 0){
			  Red_LED_OFF;
			  HAL_Delay(500);
			  turn_back(128,128);
				HAL_Delay(1200);
			  back_ok = 1;
	  	}
     if (back_ok == 1 && back2_ok == 0){
				go_straight(70);
			if(Get_Redline_L && Get_Redline_R){
				turn_left();
				HAL_Delay(600);
				back2_ok = 1;
			}
			if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
			}
		 	if(back2_ok == 1){
				go_straight(70);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
				if(Get_line_0 || Get_line_1 || Get_line_2 ){
					stop();
					Green_LED_ON;
					HAL_Delay(9000);
				}
		}
		}
/******************************************************************************************************************************/
		
/*************************************************************			number1     *********************************************/		 
		
		if(Cx == 1){
			while(number_get_remind == 0){
				Buzzer_ON;
				HAL_Delay(500);
				Buzzer_OFF;
				number_get_remind = 1;
			}
		if(Cx == 1 && Get_yao && back == 0  ){
			while(start_move == 0){
				go_straight(70);
				HAL_Delay(800);
				start_move = 1;
			}
			go_straight(70);
			if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
			if(Get_Redline_L && Get_Redline_R){
				HAL_Delay(50);
				turn_left();
				HAL_Delay(700);
			}
			if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
		
		 if(relse_yao && back == 1 && back_ok == 0){
			 	Red_LED_OFF;
			  HAL_Delay(500);
				turn_back(128,128);
				HAL_Delay(1200);
			  back_ok = 1;
	  	}
		 
     if (back_ok == 1 && back2_ok == 0){
				go_straight(70);
			if(Get_Redline_L && Get_Redline_R){
			  HAL_Delay(80);
        turn_right();
				HAL_Delay(600);
				back2_ok = 1;
			}
			if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
			}
		 
			if(back2_ok == 1){
				go_straight(70);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
				if(Get_line_0 || Get_line_1 || Get_line_2 ){
					stop();
					Green_LED_ON;
					HAL_Delay(9000);
				}
		}
		}
/*********************************************************************************************************/

/******************************************************number3************************************************/
	/*	if(Cx == 3){
			while(number_get_remind == 0){
				Buzzer_ON;
				HAL_Delay(500);
				Buzzer_OFF;
				number_get_remind = 1;
			}			
			if(Cx == 3 && Get_yao && cross == 0  && cross2 == 0 && cross3 == 0 && cross4 == 0 && cross5 == 0 ){
			 while(start_move == 0){
				go_straight(70);
				HAL_Delay(800);
				start_move = 1;
			}			
			go_straight(110);
			if(Get_Redline_L){
				scan_right(130,50);
			}
			if(Get_Redline_R){
				scan_left(130,50);
			}
			
			if(Cy == 0 && Get_Redline_L && Get_Redline_R){
				cross = 1;
		  	go_straight(110);
				HAL_Delay(1620); 
				stop();
			}
		}
			if(cross == 1 && Cy == 0 && cross2 == 0 && cross2 == 0 && cross3 == 0 && cross4 == 0 && cross5 == 0 ){
        while(startit == 0){
					HAL_TIM_Base_Start_IT(&htim3);
					startit = 1;
				}
				for(uint8_t i=0;i<80;i++){
					go_back(i);
					HAL_Delay(12);
				}		
				for(uint8_t i=0;i<80;i++){
			    go_straight(i);
					HAL_Delay(12);
				}
			}
			
			
//misson 2	

			if(Cy == 1 && cross == 1 && turn_ok == 0  && back == 0 && cross2 == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_left();
					HAL_Delay(1000);
				  turn_ok = 1;
			 }
			}
			
			if(Cy == 1 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0 && cross2 == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
			
		
		
		
		
		
			if(Cy == 2 && cross == 1 && turn_ok == 0  && back == 0 && cross2 == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_right();
					HAL_Delay(800);
				  turn_ok = 1;
			 }
			}
		if(Cy == 2 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0 && cross2 == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
		 if(relse_yao && back == 1 && back_ok == 0 && cross2 == 0){
			 	Red_LED_OFF;
			  back_ok = 1;
				turn_back(128,128);
				HAL_Delay(1300);
	  	}
		 
		 if (Cy == 2 && back_ok == 1 && turn1_ok == 0 && cross2 == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R) {
        turn_left();
				HAL_Delay(720);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
		 
			if (Cy == 1 && back_ok == 1 && turn1_ok == 0 && cross2 == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_right();
				HAL_Delay(800);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
		
		
		 if (back2_ok == 1 && turn2_ok == 0 && turn1_ok == 1 && cross2 == 0 && cross3 == 0 && cross4 == 0 && cross5 == 0  && Cy != 0 ){
			 go_straight(140);
			if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
			if(Get_Redline_L && Get_Redline_R){
					turn2_ok = 1;
			}
		}	
			
			
		 if (back2_ok == 1 && turn2_ok == 1 && turn1_ok == 1 && cross2 == 0 && cross3 == 0 && cross4 == 0 && cross5 == 0 && Cy != 0 ){
		   go_straight(80);
			 if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
		 	if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Green_LED_ON;
				HAL_Delay(9000);
			}
		 }
		 
//misson 3
		 if (Cy == 0 && cross2 == 1 && cross2_turn_ok == 0 &&	cross4 == 0 && cross5 == 0){
			 while (cross3 == 0){
				 	go_straight(110);
				 HAL_Delay(1000);
				 cross3 = 1;
			 }
				go_straight(110);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
			if(Get_Redline_L && Get_Redline_R){
				cross4 = 1;
				turn_left();
				HAL_Delay(1100);
			}
		 }
		 if (Cy == 0 && cross2 == 1 && cross2_turn_ok == 0 && cross3 == 1 && cross4 == 1 && cross5 == 0){
			 	go_straight(110);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
			if(Get_Redline_L && Get_Redline_R){
				cross5 = 1;
				turn_left();
				HAL_Delay(900);
			}
		}
		 
	  if (Cy == 0 && cross2 == 1 && cross2_turn_ok == 0 && cross3 == 1 && cross4 == 1 && cross5 == 1){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
			if(Get_Redline_L && Get_Redline_R){
				HAL_Delay(50);
				turn_left();
				HAL_Delay(900);
			}
		 	if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Green_LED_ON;
				HAL_Delay(9000);
			}
		}
	}*/
	  if(Cx == 3){
			while(number_get_remind == 0){
				Buzzer_ON;
				HAL_Delay(500);
				Buzzer_OFF;
				number_get_remind = 1;
			}				
			if(Cx == 3 && Get_yao && cross == 0 ){
		 while(start_move == 0){
				go_straight(70);
				HAL_Delay(800);
				start_move = 1;
			}				
			go_straight(110);
			if(Get_Redline_L){
				scan_right(130,50);
			}
			if(Get_Redline_R){
				scan_left(130,50);
			}
			
			if(Cy == 0 && Get_Redline_L && Get_Redline_R){
				cross = 1;
		  	go_straight(110);
				HAL_Delay(1620); 
				stop();
			}
		}
			if(cross == 1 && Cy == 0){
				for(uint8_t i=0;i<80;i++){
					go_back(i);
					HAL_Delay(12);
				}		
				for(uint8_t i=0;i<80;i++){
			    go_straight(i);
					HAL_Delay(12);
				}
			}
			
			
			

			if(Cy == 1 && cross == 1 && turn_ok == 0  && back == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_left();
					HAL_Delay(1000);
				  turn_ok = 1;
			 }
			}
			
			if(Cy == 1 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
			
			
			if(Cy == 2 && cross == 1 && turn_ok == 0  && back == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_right();
					HAL_Delay(750);
				  turn_ok = 1;
			 }
			}
		if(Cy == 2 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
		 if(relse_yao && back == 1 && back_ok == 0){
			 	Red_LED_OFF;
			 	HAL_Delay(500);
			  back_ok = 1;
				turn_back(128,128);
				HAL_Delay(1200);
	  	}
		 
		 if (Cy == 2 && back_ok == 1 && turn1_ok == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_left();
				HAL_Delay(850);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
		 
		if (Cy == 1 && back_ok == 1 && turn1_ok == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_right();
				HAL_Delay(800);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
		
		
		
		 if (back2_ok == 1 && turn2_ok == 0 && turn1_ok == 1){
			 go_straight(110);
			if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
			if(Get_Redline_L && Get_Redline_R){
					turn2_ok = 1;
			}
		}	
			
			
		 if (back2_ok == 1 && turn2_ok == 1 && turn1_ok == 1){
		   go_straight(90);
			 if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
		 	if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Green_LED_ON;
				HAL_Delay(9000);
			}
		 }
		 
	}
/*******************************************************************************************************************************************/

	/***************************************************************number4********************************************************************/
			if(Cx == 4){
			while(number_get_remind == 0){
				Buzzer_ON;
				HAL_Delay(500);
				Buzzer_OFF;
				number_get_remind = 1;
			}				
			if(Cx == 4 && Get_yao && cross == 0 ){
		 while(start_move == 0){
				go_straight(70);
				HAL_Delay(800);
				start_move = 1;
			}				
			go_straight(110);
			if(Get_Redline_L){
				scan_right(130,50);
			}
			if(Get_Redline_R){
				scan_left(130,50);
			}
			
			if(Cy == 0 && Get_Redline_L && Get_Redline_R){
				cross = 1;
		  	go_straight(110);
				HAL_Delay(1620); 
				stop();
			}
		}
			if(cross == 1 && Cy == 0){
				for(uint8_t i=0;i<80;i++){
					go_back(i);
					HAL_Delay(12);
				}		
				for(uint8_t i=0;i<80;i++){
			    go_straight(i);
					HAL_Delay(12);
				}
			}
			
			
			

			if(Cy == 1 && cross == 1 && turn_ok == 0  && back == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_left();
					HAL_Delay(1000);
				  turn_ok = 1;
			 }
			}
			
			if(Cy == 1 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
			
			
			if(Cy == 2 && cross == 1 && turn_ok == 0  && back == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_right();
					HAL_Delay(750);
				  turn_ok = 1;
			 }
			}
		if(Cy == 2 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
		 if(relse_yao && back == 1 && back_ok == 0){
			 	Red_LED_OFF;
			 	HAL_Delay(500);
			  back_ok = 1;
				turn_back(128,128);
				HAL_Delay(1300);
	  	}
		 
		 if (Cy == 2 && back_ok == 1 && turn1_ok == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_left();
				HAL_Delay(900);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
		 
		if (Cy == 1 && back_ok == 1 && turn1_ok == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_right();
				HAL_Delay(750);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
		
		
		
		 if (back2_ok == 1 && turn2_ok == 0 && turn1_ok == 1){
			 go_straight(110);
			if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
			if(Get_Redline_L && Get_Redline_R){
					turn2_ok = 1;
			}
		}	
			
			
		 if (back2_ok == 1 && turn2_ok == 1 && turn1_ok == 1){
		   go_straight(90);
			 if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
		 	if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Green_LED_ON;
				HAL_Delay(9000);
			}
		 }
		 
	}
/************************************************************************************************************/

/*******************************************************number5***********************************************/	
			if(Cx == 5){
			while(number_get_remind == 0){
				Buzzer_ON;
				HAL_Delay(500);
				Buzzer_OFF;
				number_get_remind = 1;
			}				
			if(Cx == 5 && Get_yao && cross == 0 ){
		 while(start_move == 0){
				go_straight(70);
				HAL_Delay(800);
				start_move = 1;
			}				
			go_straight(110);
			if(Get_Redline_L){
				scan_right(130,50);
			}
			if(Get_Redline_R){
				scan_left(130,50);
			}
			
			if(Cy == 0 && Get_Redline_L && Get_Redline_R){
				cross = 1;
		  	go_straight(110);
				HAL_Delay(1620); 
				stop();
			}
		}
			if(cross == 1 && Cy == 0){
				for(uint8_t i=0;i<80;i++){
					go_back(i);
					HAL_Delay(12);
				}		
				for(uint8_t i=0;i<80;i++){
			    go_straight(i);
					HAL_Delay(12);
				}
			}
			
			
			

			if(Cy == 1 && cross == 1 && turn_ok == 0  && back == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_left();
					HAL_Delay(1000);
				  turn_ok = 1;
			 }
			}
			
			if(Cy == 1 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
			
			
			if(Cy == 2 && cross == 1 && turn_ok == 0  && back == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_right();
					HAL_Delay(750);
				  turn_ok = 1;
			 }
			}
		if(Cy == 2 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
		 if(relse_yao && back == 1 && back_ok == 0){
			 	Red_LED_OFF;
			  back_ok = 1;
				turn_back(128,128);
				HAL_Delay(1500);
	  	}
		 
		 if (Cy == 2 && back_ok == 1 && turn1_ok == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_left();
				HAL_Delay(850);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
		 
			if (Cy == 1 && back_ok == 1 && turn1_ok == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_right();
				HAL_Delay(850);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
				
		
		
		 if (back2_ok == 1 && turn2_ok == 0 && turn1_ok == 1){
			 go_straight(110);
			if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
			if(Get_Redline_L && Get_Redline_R){
					turn2_ok = 1;
			}
		}	
			
			
		 if (back2_ok == 1 && turn2_ok == 1 && turn1_ok == 1){
		   go_straight(90);
			 if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
		 	if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Green_LED_ON;
				HAL_Delay(9000);
			}
		 }
		 
	}
/********************************************************************************************************************/
	
/*******************************************************number6*******************************************************/
			if(Cx == 6){
			while(number_get_remind == 0){
				Buzzer_ON;
				HAL_Delay(500);
				Buzzer_OFF;
				number_get_remind = 1;
			}				
			if(Cx == 6 && Get_yao && cross == 0 ){
		 while(start_move == 0){
				go_straight(70);
				HAL_Delay(800);
				start_move = 1;
			}				
			go_straight(110);
			if(Get_Redline_L){
				scan_right(130,50);
			}
			if(Get_Redline_R){
				scan_left(130,50);
			}
			
			if(Cy == 0 && Get_Redline_L && Get_Redline_R){
				cross = 1;
		  	go_straight(110);
				HAL_Delay(1620); 
				stop();
			}
		}
			if(cross == 1 && Cy == 0){
				for(uint8_t i=0;i<80;i++){
					go_back(i);
					HAL_Delay(12);
				}		
				for(uint8_t i=0;i<80;i++){
			    go_straight(i);
					HAL_Delay(12);
				}
			}
			
			
			
			if(Cy == 1 && cross == 1 && turn_ok == 0  && back == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_left();
					HAL_Delay(1000);
				  turn_ok = 1;
			 }
			}
			
			if(Cy == 1 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
			
			
			if(Cy == 2 && cross == 1 && turn_ok == 0  && back == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_right();
					HAL_Delay(800);
				  turn_ok = 1;
			 }
			}
		if(Cy == 2 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
		 if(relse_yao && back == 1 && back_ok == 0){
			 	Red_LED_OFF;
			  back_ok = 1;
				turn_back(128,128);
				HAL_Delay(1500);
	  	}
		 
		 if (Cy == 2 && back_ok == 1 && turn1_ok == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_left();
				HAL_Delay(900);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
		 
			if (Cy == 1 && back_ok == 1 && turn1_ok == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_right();
				HAL_Delay(900);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
				
		
		
		 if (back2_ok == 1 && turn2_ok == 0 && turn1_ok == 1){
			 go_straight(140);
			if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
			if(Get_Redline_L && Get_Redline_R){
					turn2_ok = 1;
			}
		}	
			
			
		 if (back2_ok == 1 && turn2_ok == 1 && turn1_ok == 1){
		   go_straight(90);
			 if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
		 	if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Green_LED_ON;
				HAL_Delay(9000);
			}
		 }
		 
	}
/***************************************************************************************************************************/

/*********************************************************number7*************************************************************/
		if(Cx == 7){
			while(number_get_remind == 0){
				Buzzer_ON;
				HAL_Delay(500);
				Buzzer_OFF;
				number_get_remind = 1;
			}			
			if(Cx == 7 && Get_yao && cross == 0 ){
		 while(start_move == 0){
				go_straight(70);
				HAL_Delay(800);
				start_move = 1;
			}				
			go_straight(110);
			if(Get_Redline_L){
				scan_right(130,50);
			}
			if(Get_Redline_R){
				scan_left(130,50);
			}
			
			if(Cy == 0 && Get_Redline_L && Get_Redline_R){
				cross = 1;
		  	go_straight(110);
				HAL_Delay(1620); 
				stop();
			}
		}
			if(cross == 1 && Cy == 0){
				for(uint8_t i=0;i<80;i++){
					go_back(i);
					HAL_Delay(12);
				}		
				for(uint8_t i=0;i<80;i++){
			    go_straight(i);
					HAL_Delay(12);
				}
			}
			
			
			

			if(Cy == 1 && cross == 1 && turn_ok == 0  && back == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_left();
					HAL_Delay(1000);
				  turn_ok = 1;
			 }
			}
			
			if(Cy == 1 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
			
			
			if(Cy == 2 && cross == 1 && turn_ok == 0  && back == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_right();
					HAL_Delay(800);
				  turn_ok = 1;
			 }
			}
		if(Cy == 2 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
		 if(relse_yao && back == 1 && back_ok == 0){
			 	Red_LED_OFF;
			  back_ok = 1;
				turn_back(128,128);
				HAL_Delay(1500);
	  	}
		 
		 if (Cy == 2 && back_ok == 1 && turn1_ok == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_left();
				HAL_Delay(900);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
		 
			if (Cy == 1 && back_ok == 1 && turn1_ok == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_right();
				HAL_Delay(900);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
				
		
		
		 if (back2_ok == 1 && turn2_ok == 0 && turn1_ok == 1){
			 go_straight(140);
			if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
			if(Get_Redline_L && Get_Redline_R){
					turn2_ok = 1;
			}
		}	
			
			
		 if (back2_ok == 1 && turn2_ok == 1 && turn1_ok == 1){
		   go_straight(90);
			 if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
		 	if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Green_LED_ON;
				HAL_Delay(9000);
			}
		 }
		 
	}	
/********************************************************************************************************************/

/***************************************************number8****************************************************************/
		if(Cx == 8){
			while(number_get_remind == 0){
				Buzzer_ON;
				HAL_Delay(500);
				Buzzer_OFF;
				number_get_remind = 1;
			}			
			if(Cx == 8 && Get_yao && cross == 0 ){
		 while(start_move == 0){
				go_straight(70);
				HAL_Delay(800);
				start_move = 1;
			}				
			go_straight(110);
			if(Get_Redline_L){
				scan_right(130,50);
			}
			if(Get_Redline_R){
				scan_left(130,50);
			}
			
			if(Cy == 0 && Get_Redline_L && Get_Redline_R){
				cross = 1;
		  	go_straight(110);
				HAL_Delay(1620); 
				stop();
			}
		}
			if(cross == 1 && Cy == 0){
				for(uint8_t i=0;i<80;i++){
					go_back(i);
					HAL_Delay(12);
				}		
				for(uint8_t i=0;i<80;i++){
			    go_straight(i);
					HAL_Delay(12);
				}
			}
			
			
			

			if(Cy == 1 && cross == 1 && turn_ok == 0  && back == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_left();
					HAL_Delay(1000);
				  turn_ok = 1;
			 }
			}
			
			if(Cy == 1 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
			
			
			if(Cy == 2 && cross == 1 && turn_ok == 0  && back == 0){
				go_straight(110);
				if(Get_Redline_L){
					scan_right(200,0);
				}
				if(Get_Redline_R){
					scan_left(200,0);
				}
	     if(Get_Redline_L && Get_Redline_R){
					HAL_Delay(60);
					turn_right();
					HAL_Delay(800);
				  turn_ok = 1;
			 }
			}
		if(Cy == 2 && cross == 1 && turn_ok == 1 && back == 0 && turn1_ok == 0){
				go_straight(80);
				if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}
		 if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Red_LED_ON;
				back = 1;
				HAL_Delay(1000);
			}
		}
			
		 if(relse_yao && back == 1 && back_ok == 0){
			 	Red_LED_OFF;
			  back_ok = 1;
				turn_back(128,128);
				HAL_Delay(1500);
	  	}
		 
		 if (Cy == 2 && back_ok == 1 && turn1_ok == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_left();
				HAL_Delay(900);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
		 
			if (Cy == 1 && back_ok == 1 && turn1_ok == 0){
				go_straight(110);
			if(Get_Redline_L){
					scan_right(210,0);
				}
				if(Get_Redline_R){
					scan_left(210,0);
				}	 
			if(Get_Redline_L && Get_Redline_R){
        turn_right();
				HAL_Delay(900);
				back2_ok = 1;
				turn1_ok = 1;
			}
		}
				
		
		
		 if (back2_ok == 1 && turn2_ok == 0 && turn1_ok == 1){
			 go_straight(140);
			if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
			if(Get_Redline_L && Get_Redline_R){
					turn2_ok = 1;
			}
		}	
			
			
		 if (back2_ok == 1 && turn2_ok == 1 && turn1_ok == 1){
		   go_straight(90);
			 if(Get_Redline_L){
				scan_right(210,0);
			}
			if(Get_Redline_R){
				scan_left(210,0);
			}
		 	if(Get_line_0 || Get_line_1 || Get_line_2 ){
				stop();
				Green_LED_ON;
				HAL_Delay(9000);
			}
		 }
		 
	}	
	
	/*******************************************************************************************************************************************************************/
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  uint16_t tem;
  if(huart->Instance==UART4)
  {
    tem=uart4_rxbuff;
    Openmv_Receive_Data(tem);
  }	
HAL_UART_Receive_IT(&huart4,(void *)&uart4_rxbuff,1);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
