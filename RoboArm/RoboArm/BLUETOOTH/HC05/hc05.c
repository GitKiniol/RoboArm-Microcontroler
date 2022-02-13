/*
 * hc05.c
 *
 * Created: 10.02.2022 17:41:30
 *  Author: rybka
 */ 


#include <avr/io.h>
#include <stdlib.h>
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
	Usart_Init(&USARTE1, &PORTE, PIN7_bp, PIN6_bp);						/* inicjalizacja sprzêtowego uart'u						*/	
	ReceivingFrame = Frame_Init(ReceivingFrame);						/* inicjalizacja obs³ugi ramek danych					*/
	module->Read = &HC05_Read;											/* ustawienie wskaŸnika na funkcjê odbiorcz¹			*/
	module->SendString = &HC05_SendString;								/* ustawienie wskaŸnika na funkcjê nadawcz¹				*/
	
	return module;														/* zwrócenie wskaŸnika na zainicjowany modu³			*/
}

void HC05_SendString(char *txt)
{
	Usart_SendString(txt);
}

uint8_t HC05_Read(void)
{
	if (ReceivingBuffer->IsFull == TRUE)
	{
		Frame_Fill(ReceivingBuffer);
	}
	return 0;
}

/*----------------------------------------------------------------------------------------------------------------------*/