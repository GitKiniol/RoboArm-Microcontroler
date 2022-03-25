/*
 * work.c
 *
 * Created: 19.03.2022 19:29:04
 *  Author: rybka
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include "work.h"

/*-------------------------------------------Deklaracje zmiennych-------------------------------------------------------------------------------------------*/
/* EXTERN: */


/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------Definicje funkcji----------------------------------------------------------------------------------------------*/

move_t *Work_CreateMove(void)
{
	move_t *ptrMove;																/* deklaracja wskaŸnika na ruch											*/
	ptrMove = (move_t *)malloc(sizeof(move_t));										/* alokacja pamiêci dla wskaŸnika na ruch								*/
	return ptrMove;																	/* zwrócenie adresu na alokowan¹ pamiêæ									*/
}

void Work_DeleteMove(move_t *move)
{
	if (move != NULL)																/* jeœli wskaŸnik nie jest pusty, to:									*/
	{
		free(move);																	/* zwolnij wskazywan¹ przez niego pamiêæ								*/
	}
}

list_element_t *Work_CreateListElement(void *data, void *next)
{
	list_element_t *ptrElement;														/* deklaracja wskaŸnika na element listy								*/
	ptrElement = (list_element_t *)malloc(sizeof(list_element_t));					/* alokacja pamiêci dla elementu listy									*/
	ptrElement->Data = data;														/* ustawienie wskaŸnika na dane elementu listy							*/
	ptrElement->Next = next;														/* ustawienie wskaŸnika na nastêpny element listy						*/
	return ptrElement;																/* zwrócenie wskaŸnika na alokowan¹ pamiêæ								*/
}

void Work_DeleteListElement(list_element_t *element)
{
	if (element != NULL)															/* jeœli wskaŸnik nie jest pusty, to:									*/
	{
		free(element);																/* zwolnij wskazywan¹ przez niego pamiêæ								*/
	}
}

list_t *Work_CreateList(void)
{
	list_t *ptrList;																/* deklaracja wskaŸnika na listê										*/
	ptrList = (list_t *)malloc(sizeof(list_t));										/* alokacja pamiêci dla listy											*/
	ptrList->Count = 0;																/* ustawienie licznika listy na 0										*/
	ptrList->Current = NULL;														/* ustawienie wskaŸnika na aktualny element listy						*/
	ptrList->Head = NULL;															/* ustawienie wskaŸnika na pierwszy element listy						*/
	ptrList->Tail = NULL;															/* ustawienie wskaŸnika na ostatni element listy						*/
	return ptrList;																	/* zwrócenie wskaŸnika na alokowan¹ pamiêæ								*/
}

void Work_DeleteList(list_t *list)
{
	if (list != NULL)																/* jeœli wskaŸnik nie jest pusty, to:									*/
	{
		free(list);																	/* zwolnij wskazywan¹ przez niego pamiêæ								*/
	}
}

void Work_InsertToList(list_t *list, list_element_t *element)
{
	if (list->Tail == NULL)															/* jeœli lista jest pusta, to:  (umieszczanie pierwszego elementu)		*/
	{
		list->Tail = element;														/* wstaw element na koniec listy										*/
		list->Tail->Next = NULL;													/* element na koñcu listy nie mo¿e ju¿ na nic wskazywaæ wiêc ma NULL	*/
		list->Head = list->Tail;													/* w liœcie jest jeden element wiêc pierwszy i ostatni s¹ tym samym		*/
	}
	else
	{
		element->Next = list->Head;													/* ustaw wstawianemu do listy elementowi wskaŸnik na poprzedni			*/
		list->Head = element;														/* ustaw wstawiany element na pocz¹tku listy							*/
	}
	list->Current = list->Head;														/* ustaw pierwszy element listy jako bie¿¹cy element					*/
	list->Count++;																	/* inkrementacja licznika elementów listy								*/
}

list_t *Work_GetTaskFromList(list_t *list)
{
	list_t *ptrTask = list->Current->Data;											/* odczyt wskaŸnika na listê ruchów	(lista ruchów = Task)				*/
	list_element_t *ptrNext = list->Current->Next;									/* odczyt wskaŸnika na poprzedni element								*/
	list->Current = ptrNext;														/* przesuniêcie wskaŸnika Current na poprzedni element					*/
	return ptrTask;																	/* zwrócenie wskaŸnika na listê ruchów									*/
}

move_t *Work_GetMoveFromList(list_t *list)
{
	move_t *ptrMove = list->Current->Data;											/* odczyt wskaŸnika na dane ruchu										*/
	list_element_t *ptrNext = list->Current->Next;									/* odczyt wskaŸnika na poprzedni element								*/
	list->Current = ptrNext;														/* przesuniêcie wskaŸnika Current na poprzedni element					*/
	return ptrMove;																	/* zwrócenie wskaŸnika na dane ruchu									*/
}

void Work_ClearList(list_t *list)
{
	list_element_t *ptrNext;
	while(list->Head)
	{
		ptrNext = list->Head->Next;
		if (sizeof(*list->Head->Data) == sizeof(list_t))
		{
			list_t *ptrSubList = list->Head->Data;
			while(ptrSubList->Head)
			{
				ptrNext = ptrSubList->Head->Next;
				free(ptrSubList->Head->Data);
				free(ptrSubList->Head);
				ptrSubList->Head = ptrNext;
			}
		}
		else
		{
			free(list->Head->Data);
			free(list->Head);
			list->Head = ptrNext;
		}
	}
	list->Head = NULL;
	list->Current = NULL;
	list->Tail = NULL;
	list->Count = 0;
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/