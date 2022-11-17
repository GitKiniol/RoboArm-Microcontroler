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
	templist = (loop_list_t *)malloc(sizeof(loop_list_t));					/*alokacja pamiêci dla listy								*/
	templist->Head = NULL;													/*zerowanie wskaŸnika na pocz¹tek listy						*/
	templist->Tail = NULL;													/*zerowanie wskaŸnika na koniec listy						*/
	templist->Current = NULL;												/*zerowanie wskaŸnika na element aktualny					*/
	templist->Count = 0;													/*zerowanie licznika elementów								*/
	return templist;														/*zwrócenie wskaŸnika do listy								*/
}

loop_item_t *Menu_ListItemInit(void *data)
{
	loop_item_t *tempitem;													/*element tymczasowy										*/
	tempitem = (loop_item_t *)malloc(sizeof(loop_item_t));					/*alokacja pamiêci dal elementu								*/
	tempitem->Next = NULL;													/*zerowanie wskaŸnika na element nastêpny					*/
	tempitem->Prev = NULL;													/*zerowanie wskaŸnika na element poprzedni					*/
	tempitem->Data = data;													/*kopiowanie wskaŸnika na dane								*/
	return tempitem;														/*zwrócenie wskaŸnika do elementu							*/
}

menu_item_t *Menu_MenuItemInit(label_t *name, label_t *value, uint8_t x, uint8_t y)
{
	menu_item_t *tempitem;													/*element tymczasowy										*/
	tempitem = (menu_item_t *)malloc(sizeof(menu_item_t));					/*alokacja pamiêci dla elementu								*/
	tempitem->Name = name;													/*wskaŸnik na nazwê parametru								*/
	tempitem->Value = value;												/*wskaŸnik na wartoœæ parametru								*/
	tempitem->X = x;														/*pozycja w poziomie										*/
	tempitem->Y = y;														/*pozycja w pionie											*/
	name->X = tempitem->X;													/*ustawienie pozycji x labelki z nazw¹						*/	
	name->Y = tempitem->Y;													/*ustawienie pozycji y labelki z nazw¹						*/
	value->X = tempitem->X + 50;											/*ustawienie pozycji x labelki z wartoœci¹					*/
	value->Y = tempitem->Y;													/*ustawienie pozycji x labelki z wartoœci¹					*/		
	return tempitem;														/*zwrócenie wskaŸnika na element							*/	
}

void Menu_AddToList(loop_list_t *list, loop_item_t *item)
{
	if (list->Tail == NULL && list->Head == NULL)							/*sprawdzenie czy lista jest pusta, jeœli tak to:			*/
	{
		list->Current = item;												/*ustaw wskaŸnik aktualnego elementu						*/
		list->Head = item;													/*ustaw wskaŸnik na pocz¹tek listy							*/
		list->Tail = item;													/*ustaw wskaŸnik na koniec listy							*/
		item->Next = list->Tail;											/*ustawienie wskaŸnika na nastêpny element					*/
		item->Prev = list->Head;											/*ustawienie wskaŸnika na poprzedni element					*/
	} 
	else																	/*jeœli lista nie jest pusta to:							*/
	{
		list->Head->Next = item;											/*ustawienie wskaŸnika na nastêpny element elementowi który aktualnie jest pierwszy*/
		list->Head = item;													/*wstawienie elementu na pocz¹tek listy						*/
		list->Current = list->Head;											/*ustawienie wskaŸnika na element aktualny listy			*/
	}
	list->Count++;															/*inkrementacja licznika elementów							*/
}

loop_item_t *Menu_GetFromList(loop_list_t *list)
{
	if (list->Tail == NULL && list->Head == NULL)							/*sprawdzenie czy lista jest pusta, jeœli tak to:			*/
	{
		return NULL;														/*zwrócenie pustego wskaŸnika								*/
	}
	loop_item_t *tempitem;													/*utworzenie elementu tymczasowego							*/
	tempitem = (loop_item_t *)malloc(sizeof(loop_item_t));					/*alokacja pamiêci dla elementu tymczasowego				*/
	tempitem = list->Current;												/*wykonanie kopi aktualnego elementu listy					*/
	return tempitem;														/*zwrócenie wskaŸnika na pobrany element z listy			*/
}

void Menu_ListScrollDown(loop_list_t *list, menu_screen_t* menu)
{
	if (!menu->IsReadOnly.State)											/*czy aktualne menu jest tylko do odczytu?, jeœli tak to:	*/
	{
		loop_item_t *templistitem;											/*tymczasowy element listy									*/
		templistitem = (loop_item_t *)malloc(sizeof(loop_item_t));			/*alokacja pamiêci dla elementu tymczasowego				*/
		menu_item_t *tempmenuitem;											/*tymczasowy element menu									*/
		tempmenuitem = (menu_item_t *)malloc(sizeof(menu_item_t));			/*alokacja pamiêci dla tymczasowego elementu menu			*/
		templistitem = Menu_GetFromList(list);								/*pobranie elementu z listy									*/
		tempmenuitem = templistitem->Data;									/*pobranie elementu menu z elementu listy					*/
		if (tempmenuitem->IsSelected.State)
		{
			tempmenuitem->IsSelected.State = 0;								/*wy³¹czenie zaznaczenia elementu							*/
			list->Current = templistitem->Prev;								/*przesuniêcie aktualnego elementu listy w dó³				*/
			templistitem = Menu_GetFromList(list);							/*pobranie elementu z listy									*/
			tempmenuitem = templistitem->Data;								/*pobranie elementu menu z elementu listy					*/
		}
		tempmenuitem->IsSelected.State = 1;									/*zaznacz element											*/							
	}
}

void Menu_ListScrollUp(loop_list_t *list, menu_screen_t* menu)
{
	if (!menu->IsReadOnly.State)											/*czy aktualne menu jest tylko do odczytu?, jeœli tak to:	*/
	{
		loop_item_t *templistitem;											/*tymczasowy element listy									*/
		templistitem = (loop_item_t *)malloc(sizeof(loop_item_t));			/*alokacja pamiêci dla elementu tymczasowego				*/
		menu_item_t *tempmenuitem;											/*tymczasowy element menu									*/
		tempmenuitem = (menu_item_t *)malloc(sizeof(menu_item_t));			/*alokacja pamiêci dla tymczasowego elementu menu			*/
		templistitem = Menu_GetFromList(list);								/*pobranie elementu z listy									*/
		tempmenuitem = templistitem->Data;									/*pobranie elementu menu z elementu listy					*/
		if (tempmenuitem->IsSelected.State)
		{
			tempmenuitem->IsSelected.State = 0;								/*wy³¹czenie zaznaczenia elementu							*/
			list->Current = templistitem->Next;								/*przesuniêcie aktualnego elementu listy w górê				*/
			templistitem = Menu_GetFromList(list);							/*pobranie elementu z listy									*/
			tempmenuitem = templistitem->Data;								/*pobranie elementu menu z elementu listy					*/
		}
		tempmenuitem->IsSelected.State = 1;									/*zaznacz element											*/
	}
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/