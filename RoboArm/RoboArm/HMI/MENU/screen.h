/*
 * screen.h
 *
 * Created: 05.02.2023 16:53:14
 *  Author: rybka
 */ 


#ifndef SCREEN_H_
#define SCREEN_H_

#include "menu.h"
#include "screendata.h"

/*------------------------------------------------------Deklaracje funkcji------------------------------------------------------------------------------*/

menu_screen_t *Screen_CreateScreen1(uint8_t isreadonly);											/*funkcja generuje ekran nr.1						*/

menu_screen_t *Screen_CreateScreen2(uint8_t isreadonly);											/*funkcja generuje ekran nr.1						*/

menu_screen_t *Screen_CreateScreen3(uint8_t isreadonly);											/*funkcja generuje ekran nr.1						*/

menu_screen_t *Screen_CreateScreen4(uint8_t isreadonly);											/*funkcja generuje ekran nr.1						*/

loop_list_t *Screen_CreateScreens(void);															/*funkcja tworzy listê ekranów						*/

menu_item_t *Screen_ParameterScrollUp(loop_list_t *list, menu_screen_t* menu);						/*przewijanie parametrów w górê 					*/			

menu_item_t *Screen_ParameterScrollDown(loop_list_t *list, menu_screen_t* menu);					/*przewijanie parametrów w dó³  					*/	

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif /* SCREEN_H_ */