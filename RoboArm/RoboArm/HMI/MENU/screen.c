/*
 * screen.c
 *
 * Created: 05.02.2023 16:52:14
 *  Author: rybka
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "screen.h"


/*---------------------------------------------------------Definicje funkcji------------------------------------------------------------------------*/

menu_screen_t *Screen_CreateScreen1(uint8_t isreadonly)
{
	menu_screen_t *tempscreen;												/*ekran tymczasowy														*/
	label_t *parametername;													/*labelka z nazw¹ parametru												*/
	par_values_t *parameter;												/*obiekt reprezentuje parametr posiadaj¹cy listê wartoœci				*/
	menu_item_t *menuitem;													/*element menu (labelka z nazw¹ oraz obiekt parametru)					*/
	loop_item_t *paramlistitem;												/*element listy parametrów, nie wartoœci!	(kontener na menuitem)		*/
	
	
	/*utworzenie ekranu																																*/
	tempscreen = Menu_CreateMenu(isreadonly, &Menu_ShowMenu, &Menu_RefreshMenu, &Menu_ClearMenu);
	
	/*dodawanie parametru nr.1																												*/
	parametername = Menu_CreateLabel(Scr1Names[0], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet1, 2, 64, 3, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 3);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.2																												*/
	parametername = Menu_CreateLabel(Scr1Names[1], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet2, 3, 64, 4, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 4);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.3																												*/
	parametername = Menu_CreateLabel(Scr1Names[2], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet3, 4, 64, 5, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 5);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.4																												*/
	parametername = Menu_CreateLabel(Scr1Names[3], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet4, 5, 64, 6, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 6);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.5																												*/
	parametername = Menu_CreateLabel(Scr1Names[4], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet2, 3, 64, 7, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 7);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	tempscreen->Parameters->Current = tempscreen->Parameters->Tail;
	
	return tempscreen;														/*zwrócenie obiektu ekranu												*/
}

menu_screen_t *Screen_CreateScreen2(uint8_t isreadonly)
{
	menu_screen_t *tempscreen;												/*ekran tymczasowy														*/
	label_t *parametername;													/*labelka z nazw¹ parametru												*/
	par_values_t *parameter;												/*obiekt reprezentuje parametr posiadaj¹cy listê wartoœci				*/
	menu_item_t *menuitem;													/*element menu (labelka z nazw¹ oraz obiekt parametru)					*/
	loop_item_t *paramlistitem;												/*element listy parametrów, nie wartoœci!	(kontener na menuitem)		*/
	
	
	/*utworzenie ekranu																																*/
	tempscreen = Menu_CreateMenu(isreadonly, &Menu_ShowMenu, &Menu_RefreshMenu, &Menu_ClearMenu);
	
	/*dodawanie parametru nr.1																												*/
	parametername = Menu_CreateLabel(Scr2Names[0], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet1, 2, 64, 3, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 3);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.2																												*/
	parametername = Menu_CreateLabel(Scr2Names[1], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet2, 3, 64, 4, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 4);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.3																												*/
	parametername = Menu_CreateLabel(Scr2Names[2], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet3, 4, 64, 5, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 5);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.4																												*/
	parametername = Menu_CreateLabel(Scr2Names[3], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet4, 5, 64, 6, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 6);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.5																												*/
	parametername = Menu_CreateLabel(Scr2Names[4], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet2, 3, 64, 7, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 7);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	tempscreen->Parameters->Current = tempscreen->Parameters->Tail;
	
	return tempscreen;														/*zwrócenie obiektu ekranu												*/
}

menu_screen_t *Screen_CreateScreen3(uint8_t isreadonly)
{
	menu_screen_t *tempscreen;												/*ekran tymczasowy														*/
	label_t *parametername;													/*labelka z nazw¹ parametru												*/
	par_values_t *parameter;												/*obiekt reprezentuje parametr posiadaj¹cy listê wartoœci				*/
	menu_item_t *menuitem;													/*element menu (labelka z nazw¹ oraz obiekt parametru)					*/
	loop_item_t *paramlistitem;												/*element listy parametrów, nie wartoœci!	(kontener na menuitem)		*/
	
	
	/*utworzenie ekranu																																*/
	tempscreen = Menu_CreateMenu(isreadonly, &Menu_ShowMenu, &Menu_RefreshMenu, &Menu_ClearMenu);
	
	/*dodawanie parametru nr.1																												*/
	parametername = Menu_CreateLabel(Scr3Names[0], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet1, 2, 64, 3, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 3);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.2																												*/
	parametername = Menu_CreateLabel(Scr3Names[1], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet2, 3, 64, 4, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 4);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.3																												*/
	parametername = Menu_CreateLabel(Scr3Names[2], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet3, 4, 64, 5, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 5);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.4																												*/
	parametername = Menu_CreateLabel(Scr3Names[3], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet4, 5, 64, 6, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 6);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.5																												*/
	parametername = Menu_CreateLabel(Scr3Names[4], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet2, 3, 64, 7, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 7);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	tempscreen->Parameters->Current = tempscreen->Parameters->Tail;
	
	return tempscreen;														/*zwrócenie obiektu ekranu												*/
}

menu_screen_t *Screen_CreateScreen4(uint8_t isreadonly)
{
	menu_screen_t *tempscreen;												/*ekran tymczasowy														*/
	label_t *parametername;													/*labelka z nazw¹ parametru												*/
	par_values_t *parameter;												/*obiekt reprezentuje parametr posiadaj¹cy listê wartoœci				*/
	menu_item_t *menuitem;													/*element menu (labelka z nazw¹ oraz obiekt parametru)					*/
	loop_item_t *paramlistitem;												/*element listy parametrów, nie wartoœci!	(kontener na menuitem)		*/
	
	
	/*utworzenie ekranu																																*/
	tempscreen = Menu_CreateMenu(isreadonly, &Menu_ShowMenu, &Menu_RefreshMenu, &Menu_ClearMenu);
	
	/*dodawanie parametru nr.1																												*/
	parametername = Menu_CreateLabel(Scr4Names[0], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet1, 2, 64, 3, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 3);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.2																												*/
	parametername = Menu_CreateLabel(Scr4Names[1], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet2, 3, 64, 4, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 4);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.3																												*/
	parametername = Menu_CreateLabel(Scr4Names[2], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet3, 4, 64, 5, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 5);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.4																												*/
	parametername = Menu_CreateLabel(Scr4Names[3], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet4, 5, 64, 6, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 6);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	/*dodawanie parametru nr.5																												*/
	parametername = Menu_CreateLabel(Scr4Names[4], 1, 3, &Menu_ShowLabel);
	parameter = Menu_CreateParameterValues(ScrValuesSet2, 3, 64, 7, &Menu_ShowParameterValue);
	menuitem = Menu_MenuItemInit(parametername, parameter, 1, 7);
	paramlistitem = Menu_ListItemInit(menuitem);
	Menu_AddToList(tempscreen->Parameters, paramlistitem);
	
	tempscreen->Parameters->Current = tempscreen->Parameters->Tail;
	
	return tempscreen;														/*zwrócenie obiektu ekranu												*/
}

loop_list_t *Screen_CreateScreens(void)
{
	menu_screen_t *tempscreen;												/*ekran tymczasowy														*/
	loop_item_t *screen;													/*element listy pojedynczy ekran	(kontener na ekran)					*/
	loop_list_t *screens;													/*lista ekranów															*/
	
	screens = Menu_ListInit();												/*inicjalizacja listy ekranów											*/
	
	tempscreen = Screen_CreateScreen1(0);									/*inicjalizacja ekranu nr.1												*/
	screen = Menu_ListItemInit(tempscreen);									/*utworzenie kontenera na ekran											*/
	Menu_AddToList(screens, screen);										/*dodanie ekranu do listy												*/
	
	tempscreen = Screen_CreateScreen2(0);									/*inicjalizacja ekranu nr.1												*/
	screen = Menu_ListItemInit(tempscreen);									/*utworzenie kontenera na ekran											*/
	Menu_AddToList(screens, screen);										/*dodanie ekranu do listy												*/
	
	tempscreen = Screen_CreateScreen3(0);									/*inicjalizacja ekranu nr.1												*/
	screen = Menu_ListItemInit(tempscreen);									/*utworzenie kontenera na ekran											*/
	Menu_AddToList(screens, screen);										/*dodanie ekranu do listy												*/
	
	tempscreen = Screen_CreateScreen4(0);									/*inicjalizacja ekranu nr.1												*/
	screen = Menu_ListItemInit(tempscreen);									/*utworzenie kontenera na ekran											*/
	Menu_AddToList(screens, screen);										/*dodanie ekranu do listy												*/
	
	return screens;
}

menu_item_t *Screen_ParameterScrollDown(loop_list_t *list, menu_screen_t* menu)
{
	if (!menu->IsReadOnly.State)											/*czy aktualne menu jest tylko do odczytu?, jeœli tak to:	*/
	{
		loop_item_t *templistitem;											/*tymczasowy element listy									*/
		menu_item_t *tempmenuitem;											/*tymczasowy element menu									*/
		templistitem = Menu_GetFromList(list);								/*pobranie elementu z listy									*/
		tempmenuitem = templistitem->Data;									/*pobranie elementu menu z elementu listy					*/
		if (!tempmenuitem->IsSelected.State)
		{
			tempmenuitem->IsSelected.State = 1;								/*wy³¹czenie zaznaczenia elementu							*/
			list->Current = templistitem->Prev;								/*przesuniêcie aktualnego elementu listy w dó³				*/
			templistitem = Menu_GetFromList(list);							/*pobranie elementu z listy									*/
			tempmenuitem = templistitem->Data;								/*pobranie elementu menu z elementu listy					*/
		}
		tempmenuitem->IsSelected.State = 0;									/*zaznacz element											*/
		return tempmenuitem;												/*zwrócenie aktualnego elementu menu						*/
	}
	return NULL;															/*jeœli menu tylko do odczytu to zwróæ pusty element		*/
}

menu_item_t *Screen_ParameterScrollUp(loop_list_t *list, menu_screen_t* menu)
{
	if (!menu->IsReadOnly.State)											/*czy aktualne menu jest tylko do odczytu?, jeœli tak to:	*/
	{
		loop_item_t *templistitem;											/*tymczasowy element listy									*/
		menu_item_t *tempmenuitem;											/*tymczasowy element menu									*/
		templistitem = Menu_GetFromList(list);								/*pobranie elementu z listy									*/
		tempmenuitem = templistitem->Data;									/*pobranie elementu menu z elementu listy					*/
		if (!tempmenuitem->IsSelected.State)
		{
			tempmenuitem->IsSelected.State = 1;								/*wy³¹czenie zaznaczenia elementu							*/
			list->Current = templistitem->Next;								/*przesuniêcie aktualnego elementu listy w górê				*/
			templistitem = Menu_GetFromList(list);							/*pobranie elementu z listy									*/
			tempmenuitem = templistitem->Data;								/*pobranie elementu menu z elementu listy					*/
		}
		tempmenuitem->IsSelected.State = 0;									/*zaznacz element											*/
		return tempmenuitem;												/*zwrócenie aktualnego elementu menu						*/
	}
	return NULL;															/*jeœli menu tylko do odczytu to zwróæ pusty element		*/
}
