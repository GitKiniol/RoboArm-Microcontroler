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
		item->Next = list->Tail;											/*ustawienie wska�nika na nast�pny element					*/
		item->Prev = list->Head;											/*ustawienie wska�nika na poprzedni element					*/
	} 
	else																	/*je�li lista nie jest pusta to:							*/
	{
		list->Head->Next = item;											/*ustawienie wska�nika na nast�pny element elementowi kt�ry aktualnie jest pierwszy*/
		list->Head = item;													/*wstawienie elementu na pocz�tek listy						*/
		list->Current = list->Head;											/*ustawienie wska�nika na element aktualny listy			*/
	}
	list->Count++;															/*inkrementacja licznika element�w							*/
}

loop_item_t *Menu_GetFromList(loop_list_t *list)
{
	if (list->Tail == NULL && list->Head == NULL)							/*sprawdzenie czy lista jest pusta, je�li tak to:			*/
	{
		return NULL;														/*zwr�cenie pustego wska�nika								*/
	}
	loop_item_t *tempitem;													/*utworzenie elementu tymczasowego							*/
	tempitem = (loop_item_t *)malloc(sizeof(loop_item_t));					/*alokacja pami�ci dla elementu tymczasowego				*/
	tempitem = list->Current;												/*wykonanie kopi aktualnego elementu listy					*/
	return tempitem;														/*zwr�cenie wska�nika na pobrany element z listy			*/
}

void Menu_ListScrollDown(loop_list_t *list, menu_screen_t* menu)
{
	if (!menu->IsReadOnly.State)											/*czy aktualne menu jest tylko do odczytu?, je�li tak to:	*/
	{
		loop_item_t *templistitem;											/*tymczasowy element listy									*/
		templistitem = (loop_item_t *)malloc(sizeof(loop_item_t));			/*alokacja pami�ci dla elementu tymczasowego				*/
		menu_item_t *tempmenuitem;											/*tymczasowy element menu									*/
		tempmenuitem = (menu_item_t *)malloc(sizeof(menu_item_t));			/*alokacja pami�ci dla tymczasowego elementu menu			*/
		templistitem = Menu_GetFromList(list);								/*pobranie elementu z listy									*/
		tempmenuitem = templistitem->Data;									/*pobranie elementu menu z elementu listy					*/
		if (tempmenuitem->IsSelected.State)
		{
			tempmenuitem->IsSelected.State = 0;								/*wy��czenie zaznaczenia elementu							*/
			list->Current = templistitem->Prev;								/*przesuni�cie aktualnego elementu listy w d�				*/
			templistitem = Menu_GetFromList(list);							/*pobranie elementu z listy									*/
			tempmenuitem = templistitem->Data;								/*pobranie elementu menu z elementu listy					*/
		}
		tempmenuitem->IsSelected.State = 1;									/*zaznacz element											*/							
	}
}

void Menu_ListScrollUp(loop_list_t *list, menu_screen_t* menu)
{
	if (!menu->IsReadOnly.State)											/*czy aktualne menu jest tylko do odczytu?, je�li tak to:	*/
	{
		loop_item_t *templistitem;											/*tymczasowy element listy									*/
		templistitem = (loop_item_t *)malloc(sizeof(loop_item_t));			/*alokacja pami�ci dla elementu tymczasowego				*/
		menu_item_t *tempmenuitem;											/*tymczasowy element menu									*/
		tempmenuitem = (menu_item_t *)malloc(sizeof(menu_item_t));			/*alokacja pami�ci dla tymczasowego elementu menu			*/
		templistitem = Menu_GetFromList(list);								/*pobranie elementu z listy									*/
		tempmenuitem = templistitem->Data;									/*pobranie elementu menu z elementu listy					*/
		if (tempmenuitem->IsSelected.State)
		{
			tempmenuitem->IsSelected.State = 0;								/*wy��czenie zaznaczenia elementu							*/
			list->Current = templistitem->Next;								/*przesuni�cie aktualnego elementu listy w g�r�				*/
			templistitem = Menu_GetFromList(list);							/*pobranie elementu z listy									*/
			tempmenuitem = templistitem->Data;								/*pobranie elementu menu z elementu listy					*/
		}
		tempmenuitem->IsSelected.State = 1;									/*zaznacz element											*/
	}
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/