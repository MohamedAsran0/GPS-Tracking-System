#include "tm4c123gh6pm.h"

# define zero 0x3F
# define one 0x06
# define two 0x5B
# define three 0x4F
# define four 0x66
# define five 0x6D
# define six 0x7D
# define seven 0x07
# define eight 0x7F
# define nine 0x6F



double totaldis=0; //GlobalVariable for the total distance

double latitude1 = 0;   // initial latitiude 
double longitude1 = 0;   //initial longitude  



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
void digit(int digit)
{
		switch (digit){
			case 0:
				GPIO_PORTB_DATA_R = zero;
			  break;
			case 1:
				GPIO_PORTB_DATA_R = one;
			  break;
			case 2:
				GPIO_PORTB_DATA_R = two;
			  break;
			case 3:
				GPIO_PORTB_DATA_R = three;
			  break;
			case 4:
				GPIO_PORTB_DATA_R = four;
			  break;
			case 5:
				GPIO_PORTB_DATA_R = five;
			  break;
			case 6:
				GPIO_PORTB_DATA_R = six;
			  break;
			case 7:
				GPIO_PORTB_DATA_R = seven;
			  break;
			case 8:
				GPIO_PORTB_DATA_R = eight;
			  break;
			case 9:
				GPIO_PORTB_DATA_R = nine;
			  break;
		}
}

//Function calculating the total route distance based on a function that will calculate the shortest
// distance between two points that a team member will implement and it calls the function that turns the led on
//when exceeding 100m that a team member will implement
//Its inputs start from point 2,while the initial point is thrown to the global variables defined
void totaldistance(double lat2, double lon2) {
	totaldis += shortdistance(latitude1, longitude1, lat2, lon2);
		latitude1 = lat2;
		longitude1 = lon2;
		ledon(totaldis);
	}


int main()
{
	portF_init();
	portA_init();
	portB_init();

}
