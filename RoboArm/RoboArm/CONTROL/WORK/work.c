/*
 * work.c
 *
 * Created: 19.03.2022 19:29:04
 *  Author: rybka
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include "work.h"

/*-------------------------------------------Deklaracje zmiennych---------------------------------------------------------------*/
/* EXTERN: */


/*------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------Definicje funkcji------------------------------------------------------------------*/

move_t *Work_CreateMove(void)
{
	move_t *ptrMove;												/* deklaracja wskaŸnika na ruch								*/
	ptrMove = (move_t *)malloc(sizeof(move_t));						/* alokacja pamiêci dla wskaŸnika na ruch					*/
	ptrMove->Next = NULL;											/* przypisanie pustego wskaŸnika na ruch nastêpny			*/
	return ptrMove;													/* zwrócenie adresu na alokowan¹ pamiêæ						*/
}

void Work_DeleteMove(move_t *move)
{
	if (move != NULL)												/* jeœli wskaŸnik nie jest pusty, to:						*/
	{
		free(move);													/* zwolnij wskazywan¹ prze niego pamiêæ						*/
	}
}


/*------------------------------------------------------------------------------------------------------------------------------*/