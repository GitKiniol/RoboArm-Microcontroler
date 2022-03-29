/*
 * hc05.c
 *
 * Created: 10.02.2022 17:41:30
 *  Author: rybka
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "hc05.h"
#include "../USART/BUFFER/buffer.h"

/*-------------------------------------------Deklaracje zmiennych---------------------------------------------------------------*/
/* EXTERN: */
bluetooth_t *Bluetooth = NULL;											/* modu³ komunikacyjny									*/

/*------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------Definicje funkcji------------------------------------------------------------------*/

bluetooth_t *HC05_Init(bluetooth_t *module)
{
	module = (bluetooth_t *)malloc(sizeof(bluetooth_t));				/* alokacja pamiêci dla modu³u bluetooth				*/
	ReceivingBuffer = Buffer_Init(ReceivingBuffer, RECEIVE_MAX_CHARS);	/*inicjalizacja bufora odbiorczego						*/
		//Usart_Init(&USARTD1, &PORTD, PIN7_bp, PIN6_bp);					/* inicjalizacja sprzêtowego uart'u						*/
		Usart_Init(&USARTE1, &PORTE, PIN7_bp, PIN6_bp);					/* inicjalizacja sprzêtowego uart'u						*/
		
	ReceivingFrame = Frame_Init(ReceivingFrame);						/* inicjalizacja obs³ugi ramek danych					*/
	module->Read = &HC05_Read;											/* ustawienie wskaŸnika na funkcjê odbiorcz¹			*/
	module->SendString = &HC05_SendString;								/* ustawienie wskaŸnika na funkcjê wysy³aj¹c¹ tekst		*/
	module->SendStatus = &HC05_SendStatus;								/* ustawienia wskaŸnika na funkcjê wysy³aj¹c¹ status	*/
	
	return module;														/* zwrócenie wskaŸnika na zainicjowany modu³			*/
}

void HC05_SendString(char *txt)
{
	Usart_SendString(txt);												/* wys³anie tekstu przez bluetooth						*/
}

uint8_t HC05_Read(void)
{
	if (ReceivingBuffer->IsFull == TRUE)								/* jeœli bufor odbiorczy pe³ny, to:						*/
	{
		return 1;														/* zwróæ 1												*/
	}
	else																/* w przeciwnym wypadku									*/
	{
		return 0;														/* zwróæ 0												*/
	}
}

uint8_t HC05_SendStatus(char *statusstate)
{
	Usart_SendString("SF\n");
	_delay_ms(7);
	Usart_SendString("STATUS\n");
	_delay_ms(17);
	Usart_SendString(statusstate);
	_delay_ms(7);
	Usart_SendString("0\n");
	_delay_ms(7);
	Usart_SendString("0\n");
	_delay_ms(7);
	Usart_SendString("0\n");
	_delay_ms(7);
	Usart_SendString("0\n");
	_delay_ms(7);
	Usart_SendString("EF\n");
	_delay_ms(7);
	return 1;
}

/*------------------------------------------------------------------------------------------------------------------------------*/