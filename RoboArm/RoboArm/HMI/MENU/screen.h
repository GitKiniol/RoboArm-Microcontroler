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

menu_screen_t *Screen_CreateScreen(char *names[], char *parset1[], char *parset2[],
									char *parset3[], char *parset4[], char *parset5[]);						/*funkcja generuje ekran					*/

loop_list_t *Screen_CreateScreens(void);						/*funkcja tworzy listê ekranów															*/



#endif /* SCREEN_H_ */