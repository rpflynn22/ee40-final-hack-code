#include <msp430.h> 

/* Define the pins that each device on the robot will use */
#define GREEN BIT1
#define YELLOW BIT3
#define RED BIT6
#define LOW_THRESH BIT7
#define HIGH_THRESH BIT4

//Auxiliary functions
void delay_ms(unsigned int ms);
void blink(unsigned int pin, unsigned int wait);

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer

	//Set the DCO (digitally controlled oscillator) used by the CPU to 1 MHz */
	BCSCTL1 = CALBC1_1MHZ;     					// Set range
	DCOCTL = CALDCO_1MHZ;      					// Set DCO step and modulation

	//Set the directions of each of the pins
	P1DIR |=  (GREEN + YELLOW + RED);		// set these bits to outputs
	P1DIR &= ~(LOW_THRESH + HIGH_THRESH); 				// set these bits to inputs
    P1REN |=  (LOW_THRESH + HIGH_THRESH);  				// enable input pull up resistors ??????

    P1OUT &= ~(GREEN + YELLOW + RED);

    /* Main robot program loop */
	for( ; ; )				   					// Loop ad infinitum
	{
		if (P1IN & HIGH_THRESH) {
			delay_ms(100);
			blink(RED, 200);
			delay_ms(100);
		} else if (P1IN & LOW_THRESH) {
			delay_ms(500);
			blink(YELLOW, 1000);
			delay_ms(500);
		} else {
			delay_ms(1000);
			blink(GREEN, 2000);
			delay_ms(1000);
		}
		P1OUT &= ~(GREEN + YELLOW + RED);
	}
}

void blink(unsigned int pin, unsigned int wait) {
	P1OUT &= ~(GREEN + YELLOW + RED);
	P1OUT |= pin;
	delay_ms(wait);
	P1OUT &= ~(GREEN + YELLOW + RED);
}

void delay_ms(unsigned int ms)
{
	unsigned int i;
	for (i = 0; i< ms; i++)
		__delay_cycles(1000);
}