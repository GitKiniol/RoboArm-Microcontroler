/*
 * work.c
 *
 * Created: 19.03.2022 19:29:04
 *  Author: rybka
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "work.h"
#include "../../BLUETOOTH/DATA/data.h"

/*-------------------------------------------Deklaracje zmiennych-------------------------------------------------------------------------------------------*/
/* EXTERN: */


/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------Definicje funkcji----------------------------------------------------------------------------------------------*/

void Work_TimerInit(TC1_t *timer)
{
	timer->PER = 2;																/* ustawienie wartoúci TOP dla timera										*/
	timer->CNT = 0;																/* zerowanie aktualnej wartoúci timera										*/
	Work_TimerStop(timer);														/* zatrzymanie timera														*/
	timer->INTCTRLA = TC_OVFINTLVL_LO_gc;										/* odblokowanie przerwania przepe≥nienia timera								*/
	PMIC.CTRL = PMIC_LOLVLEN_bm;												/* odblokowanie przerwaÒ o niskim priorytecie								*/
}

void Work_TimerStart(TC1_t *timer)
{
	timer->CTRLA = TC_CLKSEL_DIV1024_gc;										/* preskaler = 1024, timer uruchomiony										*/
}

void Work_TimerStop(TC1_t *timer)
{
	timer->CTRLA = TC_CLKSEL_OFF_gc;											/* preskaler = 0, timer zatrzymany											*/
}

uint8_t Work_GetParameters(list_t *list)
{
	static move_t m;
	if (list->Count > 0)														/* jeúli lista nie jest pusta, to:											*/						
	{
		list_t *task;															/* deklaracja wskaünika na listÍ ruchÛw pobranπ z listy Job					*/
		task = Data_GetTaskFromList(list);										/* pobranie listy ruchÛw													*/
		while (task->Current != NULL)											/* do czasu gdy wskaünik na ruch nie jest pusty, to:						*/
		{
			move_t *move;														/* deklaracja wskaünika na ruch												*/
			move = Data_GetMoveFromList(task);									/* pobranie ruchu															*/
			m = *move;
			m.Angle++;
			//Driver_SetParameters(move);
		}
		return 1;
	}
	else
	{
		return 0;
	}
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------przerwania---------------------------------------------------------------------------------*/

ISR(TCC1_OVF_vect)
{
	static uint8_t counts = 0;
	counts++;
	if (counts == 1)
	{
		counts = 0;
	}
}