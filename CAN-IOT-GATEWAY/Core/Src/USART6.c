/*
 * USART6.c
 *
 *  Created on: Dec 30, 2024
 *      Author: MSR3
 */

#include "main.h"


extern UART_HandleTypeDef huart6;
extern uint8_t temperature,nodeID;

char link[100];
char Rx_buff[500];
void Wifi_Init(void)
{
	AT_Cmd();
}

void AT_Cmd(void)
{
	HAL_UART_Transmit(&huart6, (uint8_t *)"AT\r\n", 6, 100);
	while(Check_Wifi_Response() != 0)
	{
		HAL_UART_Transmit(&huart6, (uint8_t *)"AT\r\n", 6, 100);
	}
//	KM_LCD_Write_Cmd(0x01);
//	KM_LCD_Write_Str("AT OK");
	//Rst_Cmd();
	Set_Wifi_Mode_Cmd();
}

void Rst_Cmd(void)
{
	HAL_UART_Transmit(&huart6, (uint8_t *)"AT+RST\r\n", 10, 1000);
	while(Check_Wifi_Response() != 0)
	{
		HAL_UART_Transmit(&huart6, (uint8_t *)"AT+RST\r\n", 10, 1000);
	}
//	KM_LCD_Write_Cmd(0x01);
//	KM_LCD_Write_Str("AT+RST OK");
	Set_Wifi_Mode_Cmd();
}

void Set_Wifi_Mode_Cmd(void)
{
	HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CWMODE=3\r\n", 15, 100);
	while(Check_Wifi_Response() != 0)
	{
		HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CWMODE=3\r\n", 15, 100);
	}
//	KM_LCD_Write_Cmd(0x01);
//	KM_LCD_Write_Str("AT+CWMODE=3 OK");
	Connect_Wifi_Cmd();
}

void Connect_Wifi_Cmd(void)
{
	HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CWJAP_DEF=\"KM-2.4G\",\"9963111084\"\r\n", 50, 900);
	while(Check_Wifi_Response() != 0)
	{
		HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CWJAP_DEF=\"KM-2.4G\",\"9963111084\"\r\n", 50, 900);
	}
//	KM_LCD_Write_Cmd(0x01);
//	KM_LCD_Write_Str("AT+CWJAP OK");
	Mux_Mode_Cmd();
}

void Mux_Mode_Cmd(void)
{
	HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CIPMUX=0\r\n", 15, 100);
	while(Check_Wifi_Response() != 0)
	{
		HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CIPMUX=0\r\n", 15, 100);
	}
//	KM_LCD_Write_Cmd(0x01);
//	KM_LCD_Write_Str("AT+CIPMUX OK");
	Mode_Selection_Cmd();
}

void Mode_Selection_Cmd(void)
{
	HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CIPMODE=0\r\n", 16, 100);
	while(Check_Wifi_Response() != 0)
	{
		HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CIPMODE=0\r\n", 16, 100);
	}
//	KM_LCD_Write_Cmd(0x01);
//	KM_LCD_Write_Str("AT+CIPMODE=0 OK");
}


void Wifi_Transmit(void)
{
	HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CIPSTATUS\r\n", 16, 1000);
	HAL_Delay(100);
	HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n", 44, 1000);
	HAL_Delay(100);
	sprintf(link,"GET /page.php?temp=%d&hum=29&dev=%d\r\n\r\n",temperature,nodeID);
	HAL_Delay(50);
	HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CIPSEND=45\r\n", 17, 1000);
	HAL_Delay(50);
	HAL_UART_Transmit(&huart6, (uint8_t *)link, 45, 1000);
	//HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CIPSTATUS\r\n", 16, 1000);
}

int Check_Wifi_Response(void)
{
	volatile int i=0;
	memset((uint8_t *)Rx_buff, 0, sizeof(Rx_buff));
	HAL_UART_Receive(&huart6,(uint8_t *)Rx_buff, 200, 100);
	for(i-0;i<400;i++)
	{
		if(Rx_buff[i] == 'K' && Rx_buff[i-1] == 'O')
			return 0;
	}
	return 1;
}

