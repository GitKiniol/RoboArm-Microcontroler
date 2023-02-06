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

/*----------------------------------------------------definicje struktur i typ�w danych---------------------------------------------------------------------*/

typedef struct KEY_STRUCT
{
	PORT_t *Port;												/*port do kt�rego pod��czony jest klawisz													*/
	uint8_t Pin;												/*numer pinu do kt�rego podpi�ty jest klawisz												*/
	uint8_t LastState:1;										/*stan pinu podczas poprzedniego sprawdzania												*/
	void (*KeyPress)(loop_list_t *);							/*funkcja obs�ugi zdarzenia wci�ni�cia przycisku											*/
}key_t;
typedef struct KEYBOARD_STRUCT
{
	key_t *KeyUp;												/*przycisk "W G�R�"																			*/
	key_t *KeyDown;												/*przycisk "W Dӣ"																			*/
	key_t *KeyRight;											/*przycisk "W PRAWO"																		*/
	key_t *KeyLeft;												/*przycisk "W LEWO"																			*/
	key_t *KeyEnter;											/*przycisk "OK"																				*/
	void (*Listner)(void *, loop_list_t *);						/*funkcja nas�uchuj�ca klawiatur�															*/
}keyboard_t;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------deklaracja funkcji---------------------------------------------------------------------------------------*/

keyboard_t *Keyboard_Init(void);								/*inicjalizacja klawiatury																	*/

void Keyboard_Listner(void *keyboard, loop_list_t *scr);		/*nas�uch klawiatury, jako parametr poda� zmienn� reprezentuj�c� klawiatur�					*/

uint8_t Keyboard_IsKeyPressed(key_t *key);						/*sprawdzenie stanu klawisza																*/

void Keyboard_UpKeyEvent(loop_list_t *scr);						/*zdarzenie wci�ni�cia klawisza "UP"														*/

void Keyboard_DownKeyEvent(loop_list_t *scr);					/*zdarzenie wci�ni�cia klawisza "DOWN"														*/

void Keyboard_RightKeyEvent(loop_list_t *scr);					/*zdarzenie wci�ni�cia klawisza "RIGHT"														*/

void Keyboard_LeftKeyEvent(loop_list_t *scr);					/*zdarzenie wci�ni�cia klawisza "LEFT"														*/

void Keyboard_EnterKeyEvent(loop_list_t *scr);					/*zdarzenie wci�ni�cia klawisza "ENTER"														*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif /* KEYBOARD_H_ */