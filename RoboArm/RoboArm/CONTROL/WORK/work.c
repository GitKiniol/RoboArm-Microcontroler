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

/*-------------------------------------------Deklaracje zmiennych-------------------------------------------------------------------------------------------*/
/* EXTERN: */


/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------Definicje funkcji----------------------------------------------------------------------------------------------*/

void Work_TimerInit(TC1_t *timer)
{
	timer->PER = 2;										/* ustawienie wartoœci TOP dla timera																*/
	timer->CNT = 0;										/* zerowanie aktualnej wartoœci timera																*/
	Work_TimerStop(timer);								/* zatrzymanie timera																				*/
	timer->INTCTRLA = TC_OVFINTLVL_LO_gc;				/* odblokowanie przerwania przepe³nienia timera														*/
	PMIC.CTRL |= PMIC_LOLVLEN_bm;						/* odblokowanie przerwañ o niskim priorytecie														*/
}

void Work_TimerStart(TC1_t *timer)
{
	timer->CTRLA = TC_CLKSEL_DIV1024_gc;				/* preskaler = 1024, timer uruchomiony																*/
}

void Work_TimerStop(TC1_t *timer)
{
	timer->CTRLA = TC_CLKSEL_OFF_gc;					/* preskaler = 0, timer zatrzymany																	*/
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
		Work_TimerStop(&TCC1);
	}
}