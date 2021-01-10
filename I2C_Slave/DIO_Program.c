#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_PRIVATE.h"




void DIO_VidSetPin_Direction(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8State)
{
	if (1==Copy_u8State)
	{
		switch (Copy_u8Port)
			{case 0:
			SET_BIT( DDRA,Copy_u8Pin); break;
			case 1:
			SET_BIT( DDRB,Copy_u8Pin); break;
			case 2:
			SET_BIT( DDRC,Copy_u8Pin); break;
			case 3:
			SET_BIT( DDRD,Copy_u8Pin); break;
	}}
	else if (0==Copy_u8State)
	{	switch(Copy_u8Port)
			{case 0:
			CLR_BIT( DDRA,Copy_u8Pin); break;
			case 1:
			CLR_BIT( DDRB,Copy_u8Pin); break;
			case 2:
			CLR_BIT( DDRC,Copy_u8Pin); break;
			case 3:
			CLR_BIT( DDRD,Copy_u8Pin); break;
	}}

	}
	
	
void DIO_VidSetPin_Value(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value)
{
	if(0==Copy_u8Value)
	
	{switch(Copy_u8Port)
		{case 0:
		CLR_BIT( PORTA,Copy_u8Pin) ;break;
		case 1:
		CLR_BIT( PORTB,Copy_u8Pin) ;break;
		case 2:
		CLR_BIT( PORTC,Copy_u8Pin) ;break;
		case 3:
		CLR_BIT( PORTD,Copy_u8Pin) ;break;
	}}
	else if (1==Copy_u8Value)
	{switch(Copy_u8Port)
		{case 0:
		SET_BIT( PORTA,Copy_u8Pin) ;break;
		case 1:
		SET_BIT( PORTB,Copy_u8Pin) ;break;
		case 2:
		SET_BIT( PORTC,Copy_u8Pin) ;break;
		case 3:
		SET_BIT( PORTD,Copy_u8Pin) ;break;
	}}
		
		
}
	
	u8 DIO_VidGetPin(u8 Copy_u8Port,u8 Copy_u8Pin)
	{	u8 bit=0;
		switch(Copy_u8Port)
		{case 0:
		bit=GET_BIT( PINA,Copy_u8Pin) ;break;
		case 1:
		bit=GET_BIT( PINB,Copy_u8Pin) ;break;
		case 2:
		bit=GET_BIT( PINC,Copy_u8Pin) ;break;
		case 3:
		bit=GET_BIT( PIND,Copy_u8Pin) ;break;
		}
		return bit;
				
		
	}

	
	
	void DIO_VidToggelPin(u8 Copy_u8Port,u8 Copy_u8Pin)
	{
		
		switch(Copy_u8Port)
		{
			case 0:   TOGGLE_BIT( PORTA,Copy_u8Pin); break;
			case 1:   TOGGLE_BIT( PORTB,Copy_u8Pin); break;
			case 2:   TOGGLE_BIT( PORTC,Copy_u8Pin); break;
			case 3:   TOGGLE_BIT( PORTD,Copy_u8Pin); break;
		}
			
		
	}
	
	void DIO_VidSetPort_Direction(u8 Copy_u8Port,u8 Copy_u8State)
	{
		
		if (1==Copy_u8State)
		{
			switch(Copy_u8Port)
			{
				case 0: SET_PORT(DDRA);   break;
				case 1: SET_PORT(DDRB);   break;
				case 2: SET_PORT(DDRC);   break;
				case 3: SET_PORT(DDRD);   break;
			}
			
		}
		else if(0==Copy_u8State)
		
		{
			switch(Copy_u8Port)
			{
				case 0: CLR_PORT(DDRA);   break;
				case 1: CLR_PORT(DDRB);   break;
				case 2: CLR_PORT(DDRC);   break;
				case 3: CLR_PORT(DDRD);   break;
			}	
		}
		
	}

	void DIO_VidWriteOnPort(u8 Copy_u8Port,u8 Copy_u8Value)
	{
		
		switch(Copy_u8Port)
		{
			case 0: WRITEON_PORT(PORTA,Copy_u8Value); break;
			case 1: WRITEON_PORT(PORTB,Copy_u8Value); break;
			case 2: WRITEON_PORT(PORTC,Copy_u8Value); break;
			case 3: WRITEON_PORT(PORTD,Copy_u8Value); break;
		}
		
	}


	
	void DIO_VidPullUp_Pin(u8 Copy_u8Port,u8 Copy_u8Pin)
	{
		
		switch(Copy_u8Port)
		{
			case 0: SET_BIT(PORTA,Copy_u8Pin); break;
			case 1: SET_BIT(PORTB,Copy_u8Pin); break;
			case 2: SET_BIT(PORTC,Copy_u8Pin); break;
			case 3: SET_BIT(PORTD,Copy_u8Pin); break;
			
		}
		
	}
	
	void DIO_VidPullDown_Pin(u8 Copy_u8Port,u8 Copy_u8Pin)
	{
		
		switch(Copy_u8Port)
		{
			case 0: CLR_BIT(PORTA,Copy_u8Pin); break;
			case 1: CLR_BIT(PORTB,Copy_u8Pin); break;
			case 2: CLR_BIT(PORTC,Copy_u8Pin); break;
			case 3: CLR_BIT(PORTD,Copy_u8Pin); break;
			
		}
	}

	void DIO_VidSetPort_Value(u8 Copy_u8Port,u8 Copy_u8Value)

	{if (Copy_u8Value==1)
		{switch(Copy_u8Port)
				{
					case 0: SET_PORT(PORTA); break;
					case 1: SET_PORT(PORTB); break;
					case 2: SET_PORT(PORTC); break;
					case 3: SET_PORT(PORTD); break;

				}
		}
	else if(Copy_u8Value==0)
	{

		switch(Copy_u8Port)
						{
							case 0: CLR_PORT(PORTA); break;
							case 1: CLR_PORT(PORTB); break;
							case 2: CLR_PORT(PORTC); break;
							case 3: CLR_PORT(PORTD); break;

						}
	}
	}
