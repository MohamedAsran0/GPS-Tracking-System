#include "tm4c123gh6pm.h"

void portF_init()
{
	SYSCTL_RCGCGPIO_R |= 0x20;
	while((SYSCTL_PRGPIO_R & 0x20) == 0);
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x02;
	GPIO_PORTF_AFSEL_R = 0;
	GPIO_PORTF_AMSEL_R = 0;
	GPIO_PORTF_PCTL_R = 0;
	GPIO_PORTF_DIR_R = 0x02;
	GPIO_PORTF_DEN_R = 0x02;
	GPIO_PORTF_PUR_R = 0;
	
	
}

void portA_init()
{
	SYSCTL_RCGCGPIO_R |= 0x01;
	while((SYSCTL_PRGPIO_R & 0x01) == 0);
	GPIO_PORTA_CR_R = 0x70;
	GPIO_PORTA_AFSEL_R = 0;
	GPIO_PORTA_AMSEL_R = 0;
	GPIO_PORTA_PCTL_R = 0;
	GPIO_PORTA_DIR_R = 0x7F;
	GPIO_PORTA_DEN_R = 0x7F;
	GPIO_PORTA_PUR_R = 0;
	
	
}

void portB_init()
{
	SYSCTL_RCGCGPIO_R |= 0x02;
	while((SYSCTL_PRGPIO_R & 0x02) == 0);
	GPIO_PORTB_CR_R = 0x7F;
	GPIO_PORTB_AFSEL_R = 0;
	GPIO_PORTB_AMSEL_R = 0;
	GPIO_PORTB_PCTL_R = 0;
	GPIO_PORTB_DIR_R = 0x7F;
	GPIO_PORTB_DEN_R = 0x7F;
	GPIO_PORTB_PUR_R = 0;
	
	
}

// Delay for Seven Segmant Display
int i;
void delay()
{
	for(i=0;i<300;i++);
}


// Seven Segmant Display Function
int number;
void sevenSegment(int input)
{
	for(i=0; i<1000;i++)
	{
		GPIO_PORTA_DATA_R = 0x60;
		number = input % 10;
		digit(number);
		delay();
		GPIO_PORTA_DATA_R = 0x50;
		number = (input / 10) % 10;
		digit(number);
		delay();
		GPIO_PORTA_DATA_R = 0x30;
		number = (input / 100) % 10;
		digit(number);
		delay();
	}
}

int main()
{
	portF_init();
	portA_init();
	portB_init();

}
