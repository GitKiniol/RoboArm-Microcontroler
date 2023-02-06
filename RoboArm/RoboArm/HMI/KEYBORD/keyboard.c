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
	keyboard_t *tempkeyboard = (keyboard_t *)malloc(sizeof(keyboard_t));				/*alokacja pamięci dla klawiatury				*/
	key_t *up = (key_t*)malloc(sizeof(key_t));											/*alokacja pamięci dla przycisku "up"			*/
	up->Pin = 3;																		/*przyporządkowanie numeru pinu					*/
	up->Port = &PORTB;																	/*przyporządkowanie portu						*/
	up->Port->DIR &= ~(1<<up->Pin);														/*ustawienie kierunku							*/
	up->Port->OUT |= (1<<up->Pin);														/*ustawienie stanu początkowego					*/
	up->KeyPress = &Keyboard_UpKeyEvent;												/*przypisanie zdarzenia							*/
	key_t *down = (key_t*)malloc(sizeof(key_t));										/*alokacja pamięci dla przycisku "down"			*/
	down->Pin = 0;																		/*przyporządkowanie numeru pinu					*/
	down->Port = &PORTB;																/*przyporządkowanie portu						*/
	down->Port->DIR &= ~(1<<down->Pin);													/*ustawienie kierunku							*/
	down->Port->OUT |= (1<<down->Pin);													/*ustawienie stanu początkowego					*/
	down->KeyPress = &Keyboard_DownKeyEvent;											/*przypisanie zdarzenia							*/
	key_t *right = (key_t*)malloc(sizeof(key_t));										/*alokacja pamięci dla przycisku "right"		*/
	right->Pin = 4;																		/*przyporządkowanie numeru pinu					*/
	right->Port = &PORTB;																/*przyporządkowanie portu						*/
	right->Port->DIR &= ~(1<<right->Pin);												/*ustawienie kierunku							*/
	right->Port->OUT |= (1<<right->Pin);												/*ustawienie stanu początkowego					*/
	right->KeyPress = &Keyboard_RightKeyEvent;											/*przypisanie zdarzenia							*/
	key_t *left = (key_t*)malloc(sizeof(key_t));										/*alokacja pamięci dla przycisku "left"			*/
	left->Pin = 1;																		/*przyporządkowanie numeru pinu					*/
	left->Port = &PORTB;																/*przyporządkowanie portu						*/
	left->Port->DIR &= ~(1<<left->Pin);													/*ustawienie kierunku							*/
	left->Port->OUT |= (1<<left->Pin);													/*ustawienie stanu początkowego					*/
	left->KeyPress = &Keyboard_LeftKeyEvent;											/*przypisanie zdarzenia							*/
	key_t *enter = (key_t*)malloc(sizeof(key_t));										/*alokacja pamięci dla przycisku "enter"		*/
	enter->Pin = 2;																		/*przyporządkowanie numeru pinu					*/
	enter->Port = &PORTB;																/*przyporządkowanie portu						*/
	enter->Port->DIR &= ~(1<<enter->Pin);												/*ustawienie kierunku							*/
	enter->Port->OUT |= (1<<enter->Pin);												/*ustawienie stanu początkowego					*/
	enter->KeyPress = &Keyboard_EnterKeyEvent;											/*przypisanie zdarzenia							*/
	
	tempkeyboard->KeyUp = up;															/*dodanie klawisza do klawiatury				*/
	tempkeyboard->KeyDown = down;														/*dodanie klawisza do klawiatury				*/
	tempkeyboard->KeyRight = right;														/*dodanie klawisza do klawiatury				*/
	tempkeyboard->KeyLeft = left;														/*dodanie klawisza do klawiatury				*/
	tempkeyboard->KeyEnter = enter;														/*dodanie klawisza do klawiatury				*/
	tempkeyboard->Listner = &Keyboard_Listner;											/*przypisanie funkcji nasłuchującej				*/
	
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
	if (Keyboard_IsKeyPressed(kb->KeyUp)) kb->KeyUp->KeyPress(scr);				/*wywołanie zdarzenia klawisza "UP"			*/
	
	if (Keyboard_IsKeyPressed(kb->KeyDown))	kb->KeyDown->KeyPress(scr);			/*wywołanie zdarzenia klawisza "DOWN"		*/
	
	if (Keyboard_IsKeyPressed(kb->KeyRight)) kb->KeyRight->KeyPress(scr);		/*wywołanie zdarzenia klawisza "RIGHT"		*/
	
	if (Keyboard_IsKeyPressed(kb->KeyLeft))	kb->KeyLeft->KeyPress(scr);			/*wywołanie zdarzenia klawisza "LEFT"		*/
	
	if (Keyboard_IsKeyPressed(kb->KeyEnter)) kb->KeyEnter->KeyPress(scr);		/*wywołanie zdarzenia klawisza "ENTER"		*/
	
}

void Keyboard_UpKeyEvent(loop_list_t *scr)
{
	
}

void Keyboard_DownKeyEvent(loop_list_t *scr)
{
	
}

void Keyboard_RightKeyEvent(loop_list_t *scr)
{
	
}

void Keyboard_LeftKeyEvent(loop_list_t *scr)
{
	
}

void Keyboard_EnterKeyEvent(loop_list_t *scr)
{
	
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/