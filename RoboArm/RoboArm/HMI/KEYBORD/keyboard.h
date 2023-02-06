/*
 * keyboard.h
 *
 * Created: 23.10.2022 08:40:32
 *  Author: rybka
 */ 

/*
key right = PB4
key left  = PB1
key up    = PB3
key down  = PB0
key enter = PB2

*/

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "../MENU/menu.h"

/*----------------------------------------------------definicje struktur i typów danych---------------------------------------------------------------------*/

typedef struct KEY_STRUCT
{
	PORT_t *Port;												/*port do którego pod³¹czony jest klawisz													*/
	uint8_t Pin;												/*numer pinu do którego podpiêty jest klawisz												*/
	uint8_t LastState:1;										/*stan pinu podczas poprzedniego sprawdzania												*/
	void (*KeyPress)(loop_list_t *);							/*funkcja obs³ugi zdarzenia wciœniêcia przycisku											*/
}key_t;
typedef struct KEYBOARD_STRUCT
{
	key_t *KeyUp;												/*przycisk "W GÓRÊ"																			*/
	key_t *KeyDown;												/*przycisk "W DÓ£"																			*/
	key_t *KeyRight;											/*przycisk "W PRAWO"																		*/
	key_t *KeyLeft;												/*przycisk "W LEWO"																			*/
	key_t *KeyEnter;											/*przycisk "OK"																				*/
	void (*Listner)(void *, loop_list_t *);						/*funkcja nas³uchuj¹ca klawiaturê															*/
}keyboard_t;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------deklaracja funkcji---------------------------------------------------------------------------------------*/

keyboard_t *Keyboard_Init(void);								/*inicjalizacja klawiatury																	*/

void Keyboard_Listner(void *keyboard, loop_list_t *scr);		/*nas³uch klawiatury, jako parametr podaæ zmienn¹ reprezentuj¹c¹ klawiaturê					*/

uint8_t Keyboard_IsKeyPressed(key_t *key);						/*sprawdzenie stanu klawisza																*/

void Keyboard_UpKeyEvent(loop_list_t *scr);						/*zdarzenie wciœniêcia klawisza "UP"														*/

void Keyboard_DownKeyEvent(loop_list_t *scr);					/*zdarzenie wciœniêcia klawisza "DOWN"														*/

void Keyboard_RightKeyEvent(loop_list_t *scr);					/*zdarzenie wciœniêcia klawisza "RIGHT"														*/

void Keyboard_LeftKeyEvent(loop_list_t *scr);					/*zdarzenie wciœniêcia klawisza "LEFT"														*/

void Keyboard_EnterKeyEvent(loop_list_t *scr);					/*zdarzenie wciœniêcia klawisza "ENTER"														*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif /* KEYBOARD_H_ */