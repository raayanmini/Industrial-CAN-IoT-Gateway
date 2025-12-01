/*
 * 16x2_LCD.c
 * Created on: Dec 29, 2024
 * Author: MSR3
 *
 */

#include "main.h"
#include "16x2_LCD.h"
#include "stm32f4xx_hal.h"

void KM_LCD_Init(void) {
    HAL_Delay(20);
    KM_LCD_Write_Cmd(0x33);
    HAL_Delay(5);
    KM_LCD_Write_Cmd(0x32);
    KM_LCD_Write_Cmd(0x0C);
    KM_LCD_Write_Cmd(0x01);
}

void KM_Write_High_Nibble(unsigned char data) {
    data >>= 4;  // Extract high nibble

    HAL_GPIO_WritePin(DATA4_GPIO_Port, DATA4_Pin, (data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DATA5_GPIO_Port, DATA5_Pin, (data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DATA6_GPIO_Port, DATA6_Pin, (data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DATA7_GPIO_Port, DATA7_Pin, (data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
}

void KM_Write_Low_Nibble(unsigned char data) {
    data &= 0x0F;  // Extract low nibble

    HAL_GPIO_WritePin(DATA4_GPIO_Port, DATA4_Pin, (data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DATA5_GPIO_Port, DATA5_Pin, (data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DATA6_GPIO_Port, DATA6_Pin, (data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DATA7_GPIO_Port, DATA7_Pin, (data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
}


void KM_LCD_Write_Cmd(unsigned char data)
{
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
	KM_Write_High_Nibble(data);
	KM_Write_Low_Nibble(data);
}

void KM_LCD_Write_Data(unsigned char data)
{
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
	KM_Write_High_Nibble(data);
	KM_Write_Low_Nibble(data);
}

void KM_LCD_Write_Str(char *data)
{
	while(*data)
	{
		KM_LCD_Write_Data(*data++);
	}
}

void custom_degree(void)
{
	char arr[] = {0X0E,0X0A,0X0E,0x00,0X00,0X00,0X00,0x00};
	KM_LCD_Write_Cmd(0x40);
	for(int i=0;i<8;i++)
	{
		KM_LCD_Write_Data(arr[i]);
	}
	KM_LCD_Write_Data(0);

}
void itoa(int num,char str[])
{
	int i=0,j=0,k=0,arr[20];
	while(num)
	{
		int r = num%10;
		arr[i] = r;
		i++;
		num = num/10;
	}
	for(j=i-1,k=0;j>=0;j--,k++)
	{
		str[k]=arr[j]+48;
	}
}
