#include<avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include<stdio.h>
unsigned char count = 0;
unsigned char count_2 = 0;
unsigned short int  count_3 = 0;
unsigned short int  count_4 = 0;
unsigned int  count_5 = 0;
unsigned char flag = 1;
unsigned char pressed_1 = 0;
unsigned char pressed_2 = 0;
char pin[6]={0,0,0,0,0,0};

int main(){
	DDRD&=~(1<<2);
	DDRD&=~(1<<3);
	DDRC  = 0x0F;
	DDRA  = 0xFF;
	PORTC = 0x01;
	PORTA = 0x00;
	SREG |= (1<<7);
	GICR|=(1<<INT0);
	GICR|=(1<<INT1);
	TCCR0 = (1<<FOC0)|(1<<CS02)|(1<<CS00);
	TIMSK|=(1<<TOIE0);
	TCNT0=6;
	GICR|=(1<<INT0);
	MCUCR = (1<<ISC01);
	MCUCR = (1<<ISC11);
	while(1){
		int i;
		for (i=0 ; i<6 ; i++)
		{
			PORTA = (1<<i);
			PORTC = pin[i];
			_delay_ms(2);
		}
		if(count == 4){
		pin[0]++;
		count = 0;
		}
		if(pin[0] > 9){
			pin[0] = 0;
			pin[1]++;
			count = 0;
		}
		if(count_2 == 240){
		pin[0] = 0;
		pin[1] = 0;
		pin[2]++;
		count = 0;
		count_2 = 0;
		}
		if(count_3 == 2400){
			pin[0] = 0;
			pin[1] = 0;
			pin[2] = 0;
			pin[3]++;
			count = 0;
			count_2 = 0;
			count_3 = 0;
		}
		if(count_4 == 14400){
			pin[0] = 0;
			pin[1] = 0;
			pin[2] = 0;
			pin[3] = 0;
			pin[4]++;
			count   = 0;
			count_2 = 0;
			count_3 = 0;
			count_4 = 0;
		}
		if(count_5 == 144000){
			pin[0]=0;
			pin[1]=0;
			pin[2]=0;
			pin[3]=0;
			pin[4]=0;
			pin[5]++;
			count = 0;
			count_2 = 0;
			count_3 = 0;
			count_4 = 0;
			count_5 = 0;

}

}
}






ISR(TIMER0_OVF_vect){

	count ++;
	count_2 ++;
	count_3 ++;
	count_4 ++;
	count_5 ++;

}
ISR(INT0_vect){
	if(pressed_2 == 1){
		int i;
		for (i=0 ; i<6 ; i++)
		{
			PORTA=(1<<i);
			PORTC = pin[i];
			_delay_ms(2);
		}
		pressed_2=0;
	}
	else {
		int i;

	count = 0;
	for (i=0 ; i<6 ; i++)
	{
		pin[i]=0;
		_delay_ms(2);
	}
	}
	}

ISR(INT1_vect){
	pressed_2 = 1;
	while((PIND&(1<<2))){

		if(!(PIND&(1<<3))){
			_delay_ms(320);
			if(!(PIND&(1<<3))){
				int i;
				count = 0;
				for (i=0 ; i<6 ; i++)
				{
					pin[i]=0;
					_delay_ms(2);
				}
				break;
			}


	}else{
	int i;
	for (i=0 ; i<6 ; i++)
		{
			PORTA=(1<<i);
			PORTC = pin[i];
			_delay_ms(2);
		}
		}

}
}





