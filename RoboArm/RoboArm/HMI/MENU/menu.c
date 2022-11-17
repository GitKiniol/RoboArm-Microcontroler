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
	templist = (loop_list_t *)malloc(sizeof(loop_list_t));					/*alokacja pamiÍci dla listy								*/
	templist->Head = NULL;													/*zerowanie wskaünika na poczπtek listy						*/
	templist->Tail = NULL;													/*zerowanie wskaünika na koniec listy						*/
	templist->Current = NULL;												/*zerowanie wskaünika na element aktualny					*/
	templist->Count = 0;													/*zerowanie licznika elementÛw								*/
	return templist;														/*zwrÛcenie wskaünika do listy								*/
}

loop_item_t *Menu_ListItemInit(void *data)
{
	loop_item_t *tempitem;													/*element tymczasowy										*/
	tempitem = (loop_item_t *)malloc(sizeof(loop_item_t));					/*alokacja pamiÍci dal elementu								*/
	tempitem->Next = NULL;													/*zerowanie wskaünika na element nastÍpny					*/
	tempitem->Prev = NULL;													/*zerowanie wskaünika na element poprzedni					*/
	tempitem->Data = data;													/*kopiowanie wskaünika na dane								*/
	return tempitem;														/*zwrÛcenie wskaünika do elementu							*/
}

menu_item_t *Menu_MenuItemInit(label_t *name, label_t *value, uint8_t x, uint8_t y)
{
	menu_item_t *tempitem;													/*element tymczasowy										*/
	tempitem = (menu_item_t *)malloc(sizeof(menu_item_t));					/*alokacja pamiÍci dla elementu								*/
	tempitem->Name = name;													/*wskaünik na nazwÍ parametru								*/
	tempitem->Value = value;												/*wskaünik na wartoúÊ parametru								*/
	tempitem->X = x;														/*pozycja w poziomie										*/
	tempitem->Y = y;														/*pozycja w pionie											*/
	name->X = tempitem->X;													/*ustawienie pozycji x labelki z nazwπ						*/	
	name->Y = tempitem->Y;													/*ustawienie pozycji y labelki z nazwπ						*/
	value->X = tempitem->X + 50;											/*ustawienie pozycji x labelki z wartoúciπ					*/
	value->Y = tempitem->Y;													/*ustawienie pozycji x labelki z wartoúciπ					*/		
	return tempitem;														/*zwrÛcenie wskaünika na element							*/	
}

void Menu_AddToList(loop_list_t *list, loop_item_t *item)
{
	if (list->Tail == NULL && list->Head == NULL)							/*sprawdzenie czy lista jest pusta, jeúli tak to:			*/
	{
		list->Current = item;												/*ustaw wskaünik aktualnego elementu						*/
		list->Head = item;													/*ustaw wskaünik na poczπtek listy							*/
		list->Tail = item;													/*ustaw wskaünik na koniec listy							*/
	} 
	else
	{
	}
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/