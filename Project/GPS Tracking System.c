#include "tm4c123gh6pm.h"
#include <math.h>
#define pi 3.14159265358979323846

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


// incialization of port F
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
// incialization of port A
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
// incialization of port B
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
// Digits intialization
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


double totaldis=0; //GlobalVariable for the total distance

double latitude1 = 0;   // initial latitiude 
double longitude1 = 0;   //initial longitude  

double lat2;
double lon2;

//Function turning on the red LED on exceeding 100m
void ledon(double totaldistance) {
	if (totaldistance > 100)
		GPIO_PORTF_DATA_R |= 0x02;
}

//Functions converting from degree to radian and vice versa
double degtorad(double deg) {
	return (deg * pi / 180);
}
double radtodeg(double rad) {
	return (rad * 180 / pi);
}


//Function calculating the shortest distance between two points
//Input parameters are in degree
double shortdistance(double lat1, double lon1, double lat2, double lon2) {
	double theta, dis;
	if ((lat1 == lat2) && (lon1 == lon2)) {
		return 0;
	}
	else {
		theta = lon1 - lon2;
		dis = sin(degtorad(lat1)) * sin(degtorad(lat2)) + cos(degtorad(lat1)) * cos(degtorad(lat2)) * cos(degtorad(theta));
		dis = acos(dis);
		dis = radtodeg(dis);
		dis = dis * 60 * 1.1515;
		dis = dis * 1.609344 * 1000;
		return (dis); //distance between two points in meter
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


float arr[13][2];





int main()
{
 	portF_init();
	portA_init();
	portB_init();

	/********************** Test Code For distance Calculation *********************/

	arr[0][0] = 30.0641830;
	arr[0][1] = 31.2778710;

	arr[1][0] = 30.0641320;
	arr[1][1] = 31.2778920;

	arr[2][0] = 30.0641030;
	arr[2][1] = 31.2779130;

	arr[3][0] = 30.0640770;
	arr[3][1] = 31.2779140;

	arr[4][0] = 30.0640540;
	arr[4][1] = 31.2779240;

	arr[5][0] = 30.0640380;
	arr[5][1] = 31.2779230;

	arr[6][0] = 30.0640330;
	arr[6][1] = 31.2779460;

	arr[7][0] = 30.0640420;
	arr[7][1] = 31.2779650;

	arr[8][0] = 30.0640570;
	arr[8][1] = 31.2780050;

	arr[9][0] = 30.0640750;
	arr[9][1] = 31.2780490;

	arr[10][0] = 30.0640850;
	arr[10][1] = 31.2780870;

	arr[11][0] = 30.0640840;
	arr[11][1] = 31.2781390;

	arr[12][0] = 30.0643120;
	arr[12][1] = 31.2787740;


	latitude1 = arr[0][0];
	longitude1 = arr[0][1];

	for(i=0;i<12;i++)
	{
		totaldistance(arr[i+1][0],arr[i+1][1]);
	}

	/*************************** Seven Segment Display *********************/

	sevenSegment(totaldis);

}
