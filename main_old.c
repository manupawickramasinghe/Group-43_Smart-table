#ifndef F_CPU

#define F_CPU 16000000UL // clock speed is 16MHz

#endif

#include <avr/io.h>     // AVR header
#include <util/delay.h> // delay header
#include "lcd.h"
#include "keypad header.h"
#define KEY_PRT PORTA
#define KEY_DDR DDRA
#define KEY_PIN PINA
#define Fan_ON() PORTD |= (1<<0)
#define Fan_OFF() PORTD &= ~(1<<0)
#define Heater_ON() PORTD |= (1 << 1)
#define Heater_OFF() PORTD &= ~(1 << 1)
#define Fan_ON() PORTD |= (1<<0)
#define Fan_OFF() PORTD &= ~(1<<0)
#define Heater_ON() PORTD |= (1 << 1)
#define Heater_OFF() PORTD &= ~(1 << 1)
int i = 0, j = 0, no = 0;
int timer_r;
int password = 1122;
char selecNum();
char personNum();
int selecnumber = 0, personnumber = 0;
void LCD_String(char *str);
void Hincrease();
void Hdecrease();
void LCD_Display_INT_TO_STRING(int value);
int adc_read(char channel)
{
	unsigned int result, x;
	ADMUX = channel;
	ADCSRA = 0x80;
	ADCH = 0x00;
	ADCL = 0x00;
	ADCSRA |= (1 << 6);  //start the conversion
	// wait till conversion is finished
	while ( (ADCSRA & 0x40) != 0 );
	x = ADCL;
	result = ADCH;
	result = result << 8;
	result = result | x;
	return result;
}
int main(void)
{
	unsigned int volt;
	unsigned int temp;
	DDRD |= (1<<0) ;
	DDRD |= (1<<1);
	
 while(1){   
	DDRC = 0xFF;
	volt = adc_read(0);
	volt = volt * 4.88;  //convert into mV
	temp = volt/10;
	LCD_Set();

	LCD_Write_String("  FSS Table 1.0   ");
	_delay_ms(1000);
	//...............................................................................................................................................................................
	do
	{
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("    TIME(FUNK)");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("MENU PRESS");

		selecNum();
		selecnumber = no;
		_delay_ms(1000);
		LCD_cmd(0x01); // clear screen
		LCD_Write_String(" CONFIRM CHOICE ");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("   ");
		_delay_ms(1000);
		do
		{
			LCD_cmd(0x01); // clear screen
			LCD_Write_String("ENTER + RESELECT");
			LCD_cmd(0xC0); // move cursor to the start of 2nd line
			LCD_Write_String("ENTER x CONFIRM");
			char accept = keyfind();
			switch (accept)
			{
				case ('*'):
				i = 1;
				j = 1;
				//...............................................................................................................................................................................
				do
				{
					LCD_cmd(0x01); // clear screen
					LCD_Write_String("   ENTER DATA");
					LCD_cmd(0xC0); // move cursor to the start of 2nd line
					LCD_Write_String("   TYPE");

//					personNum();
					personnumber = no;
					_delay_ms(1000);
					LCD_cmd(0x01); // clear screen 
					LCD_Write_String(" CONFIRM DATA");
					LCD_cmd(0xC0); // move cursor to the start of 2nd line
					LCD_Write_String("   ENTERED");
					_delay_ms(1000);
					do
					{
						LCD_cmd(0x01); // clear screen
						LCD_Write_String("ENTER + RESELECT");
						LCD_cmd(0xC0); // move cursor to the start of 2nd line
						LCD_Write_String("ENTER x CONFIRM");
						char accept = keyfind();
						switch (accept)
						{
							case ('*'):
							i = 1;
							j = 1;
							LCD_cmd(0x01); // clear screen
							LCD_Write_String("SETTING........");
							LCD_cmd(0xC0); // move cursor to the start of 2nd line
							_delay_ms(1000);
							LCD_Write_String("ALL SET");
							break;
							case ('+'):
							i = 1;
							j = 0;
							break;
							default:
							i = 0;
						}

					} while (i == 0);

				} while (j == 0);
				//...........................................................................................................................................................................
				break;
				case ('+'):
				i = 1;
				j = 0;
				break;
				default:
				i = 0;
			}

		} while (i == 0);

	} while (j == 0);

	switch (selecnumber)
	{
		case 1:
		DDRC |= 0x08;
		
		if(password == 1122){
		PORTC = 0x08;
		_delay_ms(2000);}
		break;
		
		case 2:
		DDRC |= 0x08;
		PORTC &= ~(1<<3);
		_delay_ms(2000);
		break;
		case 3:
		if (temp>=30)
		{
			Fan_ON();
			_delay_ms(1000);
		}else if (temp<=25)
		{
			Heater_ON();
			_delay_ms(1000);
		break;
		case 4:
		Fan_OFF();
		Heater_OFF();
		_delay_ms(1000);
		break;
		case 5:
		Hincrease();
		break;
		case 6:
		Hdecrease();
		break;
		case 7:
		DDRD |= 0x08;
		PORTD = 0x08;
		_delay_ms(2000);
		break;
		case 8:
		DDRD |= 0x08;
		PORTD &= ~(1<<3);
		_delay_ms(2000);
		break;
		
	}

	//Countdown coding --------------------------------------------------------

	_delay_ms(1000);
	LCD_cmd(0xC0); // move cursor to the start of 2nd line
	LCD_Write_String("THANK YOU!");
	_delay_ms(1000);
	LCD_cmd(0x01); // clear screen

/*int Time[9][9]={{10,11,12,13,14,15,16,17,18},{10,14,12,13,14,15,16,17,18},{10,11,12,13,14,15,16,17,18},{10,11,12,13,14,15,16,17,18},{10,11,12,13,14,15,16,17,18},{10,11,12,13,14,15,16,17,18},{10,11,12,13,14,15,16,17,18},{10,11,12,13,14,15,16,17,18},
{10,11,12,13,14,15,16,17,18},};
*/
	//timer_r=Time[personnumber-1][selecnumber-1];

	/*LCD_Write_String("PREPARE MEAL IN:");
	_delay_ms(1000);

	for (i = timer_r; i >= 0; i--)
	{
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		char time[5];
		itoa(i, time, 10);
		LCD_Write_String(time);
		LCD_Write_String("\n MIN");
		_delay_ms(24000);
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
	}
	
	LCD_cmd(0x01); // clear screen
	LCD_Write_String("YOUR MEAL IS");
	LCD_cmd(0x01); // clear screen
	LCD_Write_String("   READY  ");
	_delay_ms(1000);*/
	LCD_cmd(0x01); // clear screen
	LCD_cmd(0xC0); // move cursor to the start of 2nd line
	LCD_Write_String("   THANK YOU !");
	_delay_ms(1000);
}
}
		}
char selecNum()
{
	char test = keyfind();
	switch (test)
	{
		case ('1'):
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("UNLOCK SOLENOID");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("     LOCK");
		no = 1;
		break;
		case ('2'):
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("LOCK SOLENOID");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("     LOCK");
		no = 2;
		break;
		case ('3'):
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("     TURN UP ");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("     HEAT");
		no = 3;
		break;
		case ('4'):
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("      TURN DOWN");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("     HEAT");
		no = 9;
		break;
		case ('5'):
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("     INCREASE");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("     ELEVATION");
		no = 5;
		break;
		case ('6'):
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("	DECREASE");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("     ELEVATION");
		no = 6;
		break;
		case ('7'):
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("	TURN ON");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("     LIGHT");
		no = 7;
		break;
		case ('8'):
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("   TURN OFF");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("     LIGHT");
		no = 8;
		break;
		default:
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("   PLEASE ADD");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("     NUMBER");
		_delay_ms(1000);
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("   ADD SELECTION");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("     NUMBER ");
		selecNum();
	}
}
/*char PASS(){
	char test = keyfind();
			LCD_cmd(0x01); // clear screen
			LCD_Write_String("   PLEASE Enter");
			LCD_cmd(0xC0); // move cursor to the start of 2nd line
			LCD_Write_String("PASSWORD");
			_delay_ms(1000);
			PASS();
}*/
/*char TEMP(){
	char test = keyfind();
}*/
/*char personNum()
{
	char test = keyfind();
	switch (test)
	{
		case ('1'):
		no = 1;
		break;
		case ('2'):
		no = 2;
		break;
		case ('3'):
		no = 3;
		break;
		case ('9'):
		no = 9;
		break;
		case ('4'):
		no = 4;
		break;
		case ('5'):
		no = 5;
		break;
		case ('6'):
		no = 6;
		break;
		case ('7'):
		no = 7;
		break;
		case ('8'):
		no = 8;
		break;
		default:
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("   PLEASE ADD");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("     NUMBER");
		_delay_ms(1000);
		LCD_cmd(0x01); // clear screen
		LCD_Write_String("   ADD NUMBER");
		LCD_cmd(0xC0); // move cursor to the start of 2nd line
		LCD_Write_String("   OF PERSONS");

		personNum();
	}
}
*/

// Speaker coding ----------------------------------------------------------
/*void Time()
{
	switch (personnumber)
	{
		
	case 1:
	timer_r = 10;
	break;
	case 2:
	LCD_cmd(0x01); // clear screen
	timer_r = 11;
	break;
	case 3:
	LCD_cmd(0x01); // clear screen
	timer_r = 12;
	break;
	case 4:
	LCD_cmd(0x01); // clear screen
	timer_r = 13;
	break;
	case 5:
	LCD_cmd(0x01); // clear screen
	timer_r = 14;
	break;
	case 6:
	LCD_cmd(0x01); // clear screen
	timer_r = 15;
	break;
	case 7:
	LCD_cmd(0x01); // clear screen
	timer_r = 16;
	break;
	case 8:
	LCD_cmd(0x01); // clear screen
	timer_r = 17;
	break;
	case 9:
	LCD_cmd(0x01); // clear screen
	timer_r = 18;
	break;}
}*/
void Hincrease(){
	PORTC |= (1<<PORTC2);
	_delay_ms(100000);
	PORTC &= ~ (1<<PORTC2);
	//_delay_ms(1000);
}

void Hdecrease(){
	PORTC |= (1<<PORTC2);
	_delay_ms(100000);
	PORTC &= ~ (1<<PORTC2);
	//_delay_ms(1000);
}
