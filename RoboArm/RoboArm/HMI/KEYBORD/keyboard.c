/*
 * keyboard.c
 *
 * Created: 23.10.2022 08:40:19
 *  Author: rybka
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "keyboard.h"
#include "../MENU/menu.h"

/*---------------------------------------------------------Deklaracje zmiennych---------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------Definicje funkcji------------------------------------------------------------*/

keyboard_t *Keyboard_Init(void)
{
	keyboard_t *tempkeyboard = (keyboard_t *)malloc(sizeof(keyboard_t));				/*alokacja pamiêci dla klawiatury				*/
	key_t *up = (key_t*)malloc(sizeof(key_t));											/*alokacja pamiêci dla przycisku "up"			*/
	up->Pin = 3;																		/*przyporz¹dkowanie numeru pinu					*/
	up->Port = &PORTB;																	/*przyporz¹dkowanie portu						*/
	up->Port->DIR &= ~(1<<up->Pin);														/*ustawienie kierunku							*/
	up->Port->OUT |= (1<<up->Pin);														/*ustawienie stanu pocz¹tkowego					*/
	up->KeyPress = &Keyboard_UpKeyEvent;												/*przypisanie zdarzenia							*/
	key_t *down = (key_t*)malloc(sizeof(key_t));										/*alokacja pamiêci dla przycisku "down"			*/
	down->Pin = 0;																		/*przyporz¹dkowanie numeru pinu					*/
	down->Port = &PORTB;																/*przyporz¹dkowanie portu						*/
	down->Port->DIR &= ~(1<<down->Pin);													/*ustawienie kierunku							*/
	down->Port->OUT |= (1<<down->Pin);													/*ustawienie stanu pocz¹tkowego					*/
	down->KeyPress = &Keyboard_DownKeyEvent;											/*przypisanie zdarzenia							*/
	key_t *right = (key_t*)malloc(sizeof(key_t));										/*alokacja pamiêci dla przycisku "right"		*/
	right->Pin = 4;																		/*przyporz¹dkowanie numeru pinu					*/
	right->Port = &PORTB;																/*przyporz¹dkowanie portu						*/
	right->Port->DIR &= ~(1<<right->Pin);												/*ustawienie kierunku							*/
	right->Port->OUT |= (1<<right->Pin);												/*ustawienie stanu pocz¹tkowego					*/
	right->KeyPress = &Keyboard_RightKeyEvent;											/*przypisanie zdarzenia							*/
	key_t *left = (key_t*)malloc(sizeof(key_t));										/*alokacja pamiêci dla przycisku "left"			*/
	left->Pin = 1;																		/*przyporz¹dkowanie numeru pinu					*/
	left->Port = &PORTB;																/*przyporz¹dkowanie portu						*/
	left->Port->DIR &= ~(1<<left->Pin);													/*ustawienie kierunku							*/
	left->Port->OUT |= (1<<left->Pin);													/*ustawienie stanu pocz¹tkowego					*/
	left->KeyPress = &Keyboard_LeftKeyEvent;											/*przypisanie zdarzenia							*/
	key_t *enter = (key_t*)malloc(sizeof(key_t));										/*alokacja pamiêci dla przycisku "enter"		*/
	enter->Pin = 2;																		/*przyporz¹dkowanie numeru pinu					*/
	enter->Port = &PORTB;																/*przyporz¹dkowanie portu						*/
	enter->Port->DIR &= ~(1<<enter->Pin);												/*ustawienie kierunku							*/
	enter->Port->OUT |= (1<<enter->Pin);												/*ustawienie stanu pocz¹tkowego					*/
	enter->KeyPress = &Keyboard_EnterKeyEvent;											/*przypisanie zdarzenia							*/
	
	tempkeyboard->KeyUp = up;															/*dodanie klawisza do klawiatury				*/
	tempkeyboard->KeyDown = down;														/*dodanie klawisza do klawiatury				*/
	tempkeyboard->KeyRight = right;														/*dodanie klawisza do klawiatury				*/
	tempkeyboard->KeyLeft = left;														/*dodanie klawisza do klawiatury				*/
	tempkeyboard->KeyEnter = enter;														/*dodanie klawisza do klawiatury				*/
	tempkeyboard->Listner = &Keyboard_Listner;											/*przypisanie funkcji nas³uchuj¹cej				*/
	
	return tempkeyboard;																/*zwrócenie utworzonej klawiatury				*/
}

uint8_t Keyboard_IsKeyPressed(key_t *key)
{
	if (!(key->Port->IN & (1<<key->Pin)))
	{
		_delay_ms(25);
		if (!(key->Port->IN & (1<<key->Pin)) && key->LastState == 0)
		{
			key->LastState = 1;
			return 1;
		} 
		else
		{
			return 0;
		}
	} 
	else
	{
		key->LastState = 0;
		return 0;
	}
}

void Keyboard_Listner(void *keyboard, loop_list_t *scr)
{
	keyboard_t *kb = (keyboard_t *)keyboard;									/*rzutowanie parametru na typ klawiatury	*/
	if (Keyboard_IsKeyPressed(kb->KeyUp)) kb->KeyUp->KeyPress(scr);				/*wywo³anie zdarzenia klawisza "UP"			*/
	
	if (Keyboard_IsKeyPressed(kb->KeyDown))	kb->KeyDown->KeyPress(scr);			/*wywo³anie zdarzenia klawisza "DOWN"		*/
	
	if (Keyboard_IsKeyPressed(kb->KeyRight)) kb->KeyRight->KeyPress(scr);		/*wywo³anie zdarzenia klawisza "RIGHT"		*/
	
	if (Keyboard_IsKeyPressed(kb->KeyLeft))	kb->KeyLeft->KeyPress(scr);			/*wywo³anie zdarzenia klawisza "LEFT"		*/
	
	if (Keyboard_IsKeyPressed(kb->KeyEnter)) kb->KeyEnter->KeyPress(scr);		/*wywo³anie zdarzenia klawisza "ENTER"		*/
	
}

void Keyboard_UpKeyEvent(loop_list_t *scr)
{
	menu_screen_t *current;											/*aktualny ekran											*/
	current = (menu_screen_t *)scr->Current->Data;					/*pobranie adresu aktualnego ekranu							*/
	if (current->IsReadOnly.State == 0)
	{
		Screen_ParameterScrollDown(current->Parameters, current);	/*przesuniêcie wskaŸnika na kolejny parametr				*/
		current->Refresh(current);									/*odœwie¿anie aktualnego ekranu								*/
	}
}

void Keyboard_DownKeyEvent(loop_list_t *scr)
{
	menu_screen_t *current;											/*aktualny ekran											*/
	current = (menu_screen_t *)scr->Current->Data;					/*pobranie adresu aktualnego ekranu							*/
	if (current->IsReadOnly.State == 0)
	{
		Screen_ParameterScrollUp(current->Parameters, current);		/*przesuniêcie wskaŸnika na poprzedni parametr				*/
		current->Refresh(current);									/*odœwie¿anie aktualnego ekranu								*/
	}
}

void Keyboard_RightKeyEvent(loop_list_t *scr)
{
	menu_screen_t *currentscreen;													/*aktualny ekran							*/
	currentscreen = (menu_screen_t *)scr->Current->Data;							/*pobranie adresu aktualnego ekranu			*/	
	menu_item_t *menuitem;															/*aktualny element menu						*/
	menuitem = (menu_item_t *)currentscreen->Parameters->Current->Data;				/*pobranie adresu aktualnego elementu		*/
	
	if (menuitem->IsSelected.State == 0)											/*jeœli zaznaczono parametr, to :			*/
	{
		Menu_ListScrollUp(menuitem->Value->Values);									/*zmiana wartoœci aktualnego parametru		*/
		menuitem->Value->Show(menuitem->Value, 1);									/*odœwie¿enie ekranu						*/
	}
	else
	{
		Menu_ListScrollUp(scr);														/*przesuniêcie wskaŸnika aktualnego ekranu	*/
		currentscreen = (menu_screen_t *)scr->Current->Data;						/*pobranie adresu aktualnego ekranu			*/
		currentscreen->Refresh(currentscreen);										/*odœwie¿enie ekranu						*/
	}
}

void Keyboard_LeftKeyEvent(loop_list_t *scr)
{
	menu_screen_t *currentscreen;													/*aktualny ekran							*/
	currentscreen = (menu_screen_t *)scr->Current->Data;							/*pobranie adresu aktualnego ekranu			*/
	menu_item_t *menuitem;															/*aktualny element menu						*/
	menuitem = (menu_item_t *)currentscreen->Parameters->Current->Data;				/*pobranie adresu aktualnego elementu		*/
	
	if (menuitem->IsSelected.State == 0)
	{
		Menu_ListScrollDown(menuitem->Value->Values);								/*zmiana wartoœci aktualnego parametru		*/
		menuitem->Value->Show(menuitem->Value, 1);									/*odœwie¿enie ekranu						*/
	}
	else
	{
		Menu_ListScrollDown(scr);													/*przesuniêcie wskaŸnika aktualnego ekranu	*/
		currentscreen = (menu_screen_t *)scr->Current->Data;						/*pobranie adresu aktualnego ekranu			*/
		currentscreen->Refresh(currentscreen);										/*odœwie¿enie ekranu						*/
	}
}

void Keyboard_EnterKeyEvent(loop_list_t *scr)
{
	menu_screen_t *currentscreen;													/*aktualny ekran							*/
	currentscreen = (menu_screen_t *)scr->Current->Data;							/*pobranie adresu aktualnego ekranu			*/
	menu_item_t *menuitem;															/*aktualny element menu						*/
	menuitem = (menu_item_t *)currentscreen->Parameters->Current->Data;				/*pobranie adresu aktualnego elementu		*/
	
	if (menuitem->IsSelected.State == 0)											/*jeœli jakiœ parametr jest zaznaczony, to:	*/
	{
		menuitem->IsSelected.State = 1;												/*odznacz parametr							*/
		currentscreen->Refresh(currentscreen);										/*odœwie¿enie ekranu						*/
	}
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/