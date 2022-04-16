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

/* LOCAL:  */
uint8_t IsJobInProgress = 0;												/* czy trwa wykonywanie pracy (sekwencji zadañ) ?								*/
uint8_t IsTaskInProgress = 0;												/* czy trwa wykonywanie zadania ?												*/


/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------Definicje funkcji----------------------------------------------------------------------------------------------*/

void Work_TimerInit(TC1_t *timer)
{
	timer->PER = 2;																/* ustawienie wartoœci TOP dla timera										*/
	timer->CNT = 0;																/* zerowanie aktualnej wartoœci timera										*/
	Work_TimerStop(timer);														/* zatrzymanie timera														*/
	timer->INTCTRLA = TC_OVFINTLVL_LO_gc;										/* odblokowanie przerwania przepe³nienia timera								*/
	PMIC.CTRL = PMIC_LOLVLEN_bm;												/* odblokowanie przerwañ o niskim priorytecie								*/
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
	if (list->Count > 0)														/* jeœli lista nie jest pusta, to:											*/						
	{
		list_t *task;															/* deklaracja wskaŸnika na listê ruchów pobran¹ z listy Job					*/
		task = Data_GetTaskFromList(list);										/* pobranie listy ruchów													*/
		while (task->Current != NULL)											/* do czasu gdy wskaŸnik na ruch nie jest pusty, to:						*/
		{
			move_t *move;														/* deklaracja wskaŸnika na ruch												*/
			move = Data_GetMoveFromList(task);									/* pobranie ruchu															*/
			//Drivers_SetParameters(move);
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

void Work_RunRobot(void)
{
	Work_TimerInit(&TCC1);														/* inicjalizacje timera														*/
	Work_TimerStart(&TCC1);														/* uruchomienie timera														*/
}

void Work_StopRobot(void)
{
	Work_TimerStop(&TCC1);														/* zatrzymanie timera														*/
	//Drivers_StopDrivers();
}

void Work_RunTask(list_t *joblist, void(*sendstatus)(char *))
{
	uint8_t IsParametersOk = 0;													/* zmienna do przechowywania rezultatu pobrania parametrów					*/
	if (!IsTaskInProgress)														/* jeœli zadanie nie zosta³o uruchomione, to:								*/
	{
		IsParametersOk = Work_GetParameters(joblist);							/* pobierz parametry i zapisz je w sterownikach								*/
	} 
	if (IsTaskInProgress || IsParametersOk)										/* jeœli zadanie jest ju¿ uruchomione lub pobranie parametrów ok, to:		*/								
	{
		//Drivers_RunDrivers();													/* uruchomienie driveów														*/
	}
	else if (!IsParametersOk)													/* jeœli pobieranie parametrów zakoñczy³o siê niepowodzeniem, to:			*/								
	{
		if (IsJobInProgress)													/* jeœli za³¹czone zosta³o wykonywanie pracy, to:							*/
		{
			IsJobInProgress = 0;												/* wyzeruj flagê informuj¹c¹ o wykonywaniu pracy							*/
			Data_ClearJob();													/* wyczyœæ listê job														*/
			sendstatus("6\n");													/* wyœlij informacjê ¿e robot zakoñczy³ pracê								*/
		} 
		else
		{
			sendstatus("99\n");													/* b³¹d wykonywania pracy													*/
		}
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