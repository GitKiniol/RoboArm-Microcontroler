/*
 * menu.c
 *
 * Created: 23.10.2022 08:46:51
 *  Author: rybka
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include "menu.h"

/*---------------------------------------------------------Deklaracje zmiennych---------------------------------------------------------*/

/*LOCAL:	*/


/*--------------------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------Definicje funkcji------------------------------------------------------------*/

loop_list_t *Menu_ListInit(void)
{
	loop_list_t *templist;													/*lista tymczasowa											*/
	templist = (loop_list_t *)malloc(sizeof(loop_list_t));					/*alokacja pami�ci dla listy								*/
	templist->Head = NULL;													/*zerowanie wska�nika na pocz�tek listy						*/
	templist->Tail = NULL;													/*zerowanie wska�nika na koniec listy						*/
	templist->Current = NULL;												/*zerowanie wska�nika na element aktualny					*/
	templist->Count = 0;													/*zerowanie licznika element�w								*/
	return templist;														/*zwr�cenie wska�nika do listy								*/
}

loop_item_t *Menu_ListItemInit(void *data)
{
	loop_item_t *tempitem;													/*element tymczasowy										*/
	tempitem = (loop_item_t *)malloc(sizeof(loop_item_t));					/*alokacja pami�ci dal elementu								*/
	tempitem->Next = NULL;													/*zerowanie wska�nika na element nast�pny					*/
	tempitem->Prev = NULL;													/*zerowanie wska�nika na element poprzedni					*/
	tempitem->Data = data;													/*kopiowanie wska�nika na dane								*/
	return tempitem;														/*zwr�cenie wska�nika do elementu							*/
}

menu_item_t *Menu_MenuItemInit(label_t *name, label_t *value, uint8_t x, uint8_t y)
{
	menu_item_t *tempitem;													/*element tymczasowy										*/
	tempitem = (menu_item_t *)malloc(sizeof(menu_item_t));					/*alokacja pami�ci dla elementu								*/
	tempitem->Name = name;													/*wska�nik na nazw� parametru								*/
	tempitem->Value = value;												/*wska�nik na warto�� parametru								*/
	tempitem->X = x;														/*pozycja w poziomie										*/
	tempitem->Y = y;														/*pozycja w pionie											*/
	name->X = tempitem->X;													/*ustawienie pozycji x labelki z nazw�						*/	
	name->Y = tempitem->Y;													/*ustawienie pozycji y labelki z nazw�						*/
	value->X = tempitem->X + 50;											/*ustawienie pozycji x labelki z warto�ci�					*/
	value->Y = tempitem->Y;													/*ustawienie pozycji x labelki z warto�ci�					*/		
	return tempitem;														/*zwr�cenie wska�nika na element							*/	
}

void Menu_AddToList(loop_list_t *list, loop_item_t *item)
{
	if (list->Tail == NULL && list->Head == NULL)							/*sprawdzenie czy lista jest pusta, je�li tak to:			*/
	{
		list->Current = item;												/*ustaw wska�nik aktualnego elementu						*/
		list->Head = item;													/*ustaw wska�nik na pocz�tek listy							*/
		list->Tail = item;													/*ustaw wska�nik na koniec listy							*/
	} 
	else
	{
	}
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/