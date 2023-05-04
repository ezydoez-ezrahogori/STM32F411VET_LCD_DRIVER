#include "stm32f4xx.h"                  // Device header

#define RS    0x20 
#define  RW    0x40
#define  EN     0x80
void delayMS(int delay);
void GPIO_Init(void);
void LCD_command(unsigned char command);
void LCD_data(char data);
void LCD_Init(void);
int main(void)
{
	LCD_Init();
	

while(1)
{
LCD_data('H');
LCD_data('e');
LCD_data('l');
LCD_data('l');
LCD_data('o');	

LCD_command(1);  //clear screen	
delayMS(500);
}
	
}

void LCD_Init(void)
{
	GPIO_Init();
	//Init sequence
	
	delayMS(30);
	LCD_command(0x30);
	delayMS(10);
	LCD_command(0x30);
	delayMS(10);
	LCD_command(0x30);
	
	LCD_command(0x38);    //set 8-bit data mode, 2-line, 5*7 font
	LCD_command(0x06);   //move cursor right
	LCD_command(0x01);    //clear screen, move cursor home
	LCD_command(0x0F);    //turn display, move cursor
	
	
}


void GPIO_Init(void)
{
	RCC->AHB1ENR |=0x06;
	GPIOB->MODER |=0x5400;
	
	GPIOB->BSRR = 0x00c;  //set EN and RW low
	
	//set PC0-PC7 as output
	GPIOC->MODER |= 0x00005555;
	
	
}

void LCD_command(unsigned char command)
{
	GPIOB->BSRR = (RW | RS )<<16;  //RS=0, r/w=0
	GPIOC->ODR =command;
	GPIOB->BSRR =EN;
	delayMs(10);
	GPIOB->BSRR =EN<<16;
	
	
}
void LCD_data(char data)
{
	GPIOB->BSRR = RS;  //RS=1
	GPIOB->BSRR = RW<<16;   //
	GPIOC->ODR =data;
	GPIOB->BSRR =EN;
	delayMS(0);
	GPIOB->BSRR =EN<<16; //clear EN
	
	
}
void delayMS(int delay)
{
	int i;
	for(; delay>0; delay--)
	{
		for(i=0; i<3195; i++)
		{}
		
	}
	
}




