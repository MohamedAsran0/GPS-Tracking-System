#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"


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


#include <math.h>
#define pi 3.14159265358979323846


// initalize_bluetooth_uart //bonus 
void UART_bluetooth_init() //UART2_INIT OF D6 "RX" & D7 "TX"
{
	SYSCTL_RCGCUART_R |= 0x80;                          // UART7 CLOCK
	SYSCTL_RCGCGPIO_R |= 0x10;                          // portE CLOCK 
	while((SYSCTL_PRGPIO_R & 0x10) == 0){};
	UART7_CTL_R &= ~0x0001;                //DISABLE UART
	UART7_IBRD_R = 104;                   // IBDR = INT(16MHZ / (16*9600)) 
	UART7_FBRD_R = 11;   
	UART7_LCRH_R = 0x0070;              // 8-BITS , NO PARITY , ONE STOP ,FIFO
	UART7_CTL_R = 0x0301;           	// ENABLE TX , ENABLE RX & UART
	     /// UART7 ====>   ~TX[E0],RX[E1]~ ///
	GPIO_PORTE_AFSEL_R |= 0x03;  // ENABLE ALT. FUNCTION ON E0&E1
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFFFFFF00)+0x00000011;   
	GPIO_PORTE_DEN_R |= 0x03;     //DIGITAL ENABLE 
	GPIO_PORTE_AMSEL_R &= ~0x03;   // NOT ANALOG
}
/////////////////////////////////////////////////////////////////////////////////////////////

// bluetooth_reading_function
char Bluetooth_data;
char Bluetooth_Read(void)  
{
    while((UART7_FR_R & 0x0010) != 0);       // wait until Rx buffer is not full "check RXFE flag"  before giving it another byte 
    Bluetooth_data= UART7_DR_R;     	      // take recived value in a variable    
    return (Bluetooth_data & 0xFF);  //RETURN Bluetooth_Read
}
//////////////////////////////////////////////////////////////////////////////////////
// bluetooth_writing_function
void Bluetooth_Write ( char bluetooth_data)  
{
   while((UART7_FR_R & 0x0020) != 0); // wait until Tx buffer is not full "check TXFF flag"  before giving it another byte 
    UART7_DR_R = bluetooth_data;                  //OUTPUT = VARIABLE
}
///////////////////////////////////////////////////////////////////////////////
// bluetooth_writing_string_function
void Bluetooth_Write_String(char *str)
{
  while(*str)
	{
		Bluetooth_Write(*(str++));
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////


void UART2_init() //UART2_INIT OF D6 "RX" & D7 "TX"
{
	SYSCTL_RCGCUART_R |= 0x04;
	SYSCTL_RCGCGPIO_R |= 0x08;
	while((SYSCTL_PRGPIO_R & 0x08) == 0);
	UART2_CTL_R &= ~0x0001;
	UART2_IBRD_R = 104;   // IBDR = INT(16,000,000 / (16*9600)) //104 
	UART2_FBRD_R = 11;   //11  
	UART2_LCRH_R = 0x0070;   // 8-BITS , NO PARITY , ONE STOP ,FIFO
	UART2_CTL_R = 0x0201;   // DISABLE TX , ENABLE RX & UART
	GPIO_PORTD_AFSEL_R |= 0x40;  // ENABLE ALT. FUNCTION ON D6
	GPIO_PORTD_DEN_R |= 0x40;
	GPIO_PORTD_AMSEL_R &= ~0x40;
	GPIO_PORTD_PCTL_R &= ~0x01000000;
	GPIO_PORTD_PCTL_R |= 0x01000000;

}

// Checking Reciever for UART2 
char UART2_receiver()
{
    while((UART2_FR_R & 0x0010) != 0);    // WAIT UNTIL RXFE IS 0 
    return(UART2_DR_R & 0xFF);

}

//intialization of UART0 
void UART0_init(){
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

    UART0_CTL_R &= ~UART_CTL_UARTEN;
    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;
    UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
    UART0_CTL_R |= (UART_CTL_RXE|UART_CTL_TXE|UART_CTL_UARTEN);

    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R &= ~0XFF) | (GPIO_PCTL_PA0_U0RX|GPIO_PCTL_PA1_U0TX);
    GPIO_PORTA_AMSEL_R &= ~0x03;
        GPIO_PORTA_DEN_R |= 0x03; 
}

//Writing Data on putty
void Write_data(char data) {
	while ((UART0_FR_R & UART_FR_TXFF) == UART_FR_TXFF);
	UART0_DR_R = ((char)data);
}

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



// Reading Data from GPS 
 void readGps(){
	int degrees = 0;
	double minutes = 0.0;
	double seconds = 0.0;
	double tempLatitude;
	double tempLongitude;
  char array[12][20];
	char *buf;
  for(i=0;i<500;i++)
	{
		 buf[i] = UART2_receiver();
	}	
	
        if(strstr(buf, "$GPRMC"))
        {
            int count = 0;
            char *token;
            token = strtok(buf, ",");
            while(token != NULL)
            {
                strcpy(array[count], token);
                token = strtok(NULL, ",");
								count++;
						}
				}
		



							if(firstTime){
										tempLatitude=atof(array[3]);
										tempLongitude=atof(array[5]);
	
										degrees = tempLatitude / 100;
										minutes = tempLatitude - (double)(degrees * 100);
										seconds = minutes / 60.00;
										latitude1 = degrees + seconds;
										
										degrees = tempLongitude / 100;
										minutes = tempLongitude - (double)(degrees * 100);
										seconds = minutes / 60.00;
										longitude1 = degrees + seconds;
										
								
									firstTime=false;
								  delay_milli(100);
								
							}
							else
			        {
									tempLatitude = atof(array[3]);
									tempLongitude = atof(array[5]);

									degrees = tempLatitude / 100;
									minutes = tempLatitude - (double)(degrees * 100);
									seconds = minutes / 60.00;
									latitude2 = degrees + seconds;

									degrees = tempLongitude / 100;
									minutes = tempLongitude - (double)(degrees * 100);
									seconds = minutes / 60.00;
									longitude2 = degrees + seconds;
								
								totaldistance(latitude2,longitude2);
								sevenSegment((int)totaldis);
								delay_milli(100);
							}
						
							
	  }


//float arr[13][2];

char x ;

int main()
{
    portF_init();
    portA_init();
    portB_init();
    UART2_init();
    UART0_init();


    while (1)
    {

            x = UART2_receiver();
            Write_data(x);
						//readGps(); 
        }

}

	/********************** Test Code For distance Calculation *********************/

	/*arr[0][0] = 30.0641830;
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
	}*/

	/*************************** Seven Segment Display *********************/

	//sevenSegment(totaldis);

}
