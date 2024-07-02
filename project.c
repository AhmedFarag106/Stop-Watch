#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* 	Definitions 		*/
#define DELAY  3

/* 	Global Variables 	*/
unsigned char tick=0,seconds=0,minutes=0,hours=0;

/* 	Functions Declaration 	*/
void enable_seg(unsigned char no);  
void TIMER1_COMP_init(void);
void INT0_init(void);
void INT1_init(void);
void INT2_init(void);



int main ()
{
	/*
	* Defining the first four pins in port C as outputs to connect the decoder
	* Initializing the output 
	*/
	DDRC |= (0x0F);
	PORTC &= ~(0x0F);
	
	/*
	* Defining the pins for the enable for each 7-segments
	* Initializing the output 
	*/
	DDRA |= (0x3F);
	PORTA &= ~(0x3F);

	SREG |= (1<<7); /*	Enabling the global interrupts 	*/
			
	/*	initializing the interrupts 		*/
	INT0_init();
	INT1_init();
	INT2_init();
	
	/* 	initializing the timer		*/
	TIMER1_COMP_init();

	while(1)
	{
		/* 	resetting the seconds every minute and increasing the minutes		*/
		if (seconds>59)
		{
			seconds =0;
			minutes ++;
		}
		
		/* 	resetting the minutes every hour and increasing the hours		*/
		if (minutes>59)
		{
			minutes =0;
			hours ++;
		}
		
		/* 	resetting the stop watch						*/
		if (hours>12)
		{
			seconds=0;
			minutes =0;
			hours =0;
		}

		/*
		* enabling each 7-segment one after another by writing one in for the specified pin
		* we send the first digit of the number (الاحاد) by making modulus 10 for example 35 % 10
		* gives 5 which is the first digit
		* we send the second digit (العشرات) by dividing by 10 for example 35 / 10 gives 3.5
		* but it is an integer division so it will be 3
		*/

		enable_seg(0);
		PORTC = (PORTC & 0xF0 ) | ((seconds%10) & 0x0F);
		_delay_ms(DELAY);

		enable_seg(1);
		PORTC = (PORTC & 0xF0 ) | ((seconds/10) & 0x0F);
		_delay_ms(DELAY);


		enable_seg(2);
		PORTC = (PORTC & 0xF0 ) | ((minutes%10) & 0x0F);
		_delay_ms(DELAY);

		enable_seg(3);
		PORTC = (PORTC & 0xF0 ) | ((minutes/10) & 0x0F);
		_delay_ms(DELAY);

		enable_seg(4);
		PORTC = (PORTC & 0xF0 ) | ((hours%10) & 0x0F);
		_delay_ms(DELAY);

		enable_seg(5);
		PORTC = (PORTC & 0xF0 ) | ((hours/10) & 0x0F);
		_delay_ms(DELAY);

	}

	return 0;
}



ISR (INT2_vect)
{
	TCCR1B |= (1 << CS11); // clock gating for the timer1 (turning it ON)
}

void INT2_init(void)
{
	DDRB &= ~(1<<PB2); // input pin
	PORTB |= (1<<PB2);  // enabling internal pull up
	MCUCSR &= (1<<ISC2);  // falling edge
	GICR  |= (1<<INT2);  // External Interrupt Request 2 Enable

}



ISR (INT1_vect)
{
	TCCR1B &= ~(1 << CS11);  // stop the clock gating for timer1 (timer if OFF)
}

void INT1_init(void)
{
	DDRD &= ~(1<<PD3); // input pin
	MCUCR |= (1<<ISC10); // rising edge
	MCUCR |= (1<<ISC11); // rising edge also
	GICR  |= (1<<INT1);  // External Interrupt Request 1 Enable

}




ISR (INT0_vect)
{
	seconds=0;		// resetting all variables
	minutes =0;
	hours =0;
}

void INT0_init(void)
{
	DDRD &= ~(1<<PD2); // input pin
	PORTD |= (1<<PD2); // internal pull up
	MCUCR |= (1<<ISC01); // falling edge
	MCUCR &= ~(1<<ISC00); // falling edge
	GICR |= (1<<INT0); // External Interrupt Request 0 Enable

}




ISR (TIMER1_COMPA_vect)
{
	tick ++;

	if(tick==2) // checking for two interrupts as the interrupt time is 0.5 second
	{
		seconds++;
		tick=0;
	}

}

void TIMER1_COMP_init(void)
{
	/*
	 * Fcpu = 1 MHZ
	 * N = 8
	 * Ttimer = 8 *10^-6 seconds
	 * For OCR1A = 62536 , the time of overflow is 0.500 sharp
	 *
	 * */

	TCCR1A =(1<<FOC1A); // disabling the PWM
	TCCR1B = (1<<WGM12) | (1<<CS11); // prescalar = 8 and enabling the timer CTC mood
	TCNT1=0; // initial value
	OCR1A=62536;
	TIMSK |= (1<<OCIE1A); // interrupt enable
}


void enable_seg(unsigned char no)
{
	/*
	 * taking input to enable only one bit in the first 6 bits of portA to
	 * enable only one 7-segment at a time
	 * */
	PORTA = (PORTA & 0xc0) | ( (1<<no) & 0x3F );
}
