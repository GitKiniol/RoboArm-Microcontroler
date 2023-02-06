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

menu_screen_t *Screen_CreateScreen(char *names[], char *parset1[], char *parset2[], char *parset3[], char *parset4[], char *parset5[])
{
	menu_screen_t *tempscreen;												/*ekran tymczasowy														*/
	label_t *parametername;													/*labelka z nazw¹ parametru												*/
	par_values_t *parameter;												/*obiekt reprezentuje parametr posiadaj¹cy listê wartoœci				*/
	menu_item_t *menuitem;													/*element menu (labelka z nazw¹ oraz obiekt parametru)					*/
	loop_item_t *paramlistitem;												/*element listy parametrów, nie wartoœci!	(kontener na menuitem)		*/
	char ***screentexts;													/*wskaŸnik na teksty zawarte na ekranie									*/
	screentexts = (char ***)malloc(sizeof(char **) * 6);					/*alokacja pamiêci dla napisów											*/
	screentexts[0] = names;
	screentexts[1] = parset1;
	screentexts[2] = parset2;
	screentexts[3] = parset3;
	screentexts[4] = parset4;
	screentexts[5] = parset5;
	
	/*utworzenie ekranu																																*/
	tempscreen = Menu_CreateMenu(0, &Menu_ShowMenu, &Menu_RefreshMenu, &Menu_ClearMenu);
	
	/*dodawanie parametrów do ekranu																												*/
	for (uint8_t i = 0; i < 5; i++)
	{
		parametername = Menu_CreateLabel(screentexts[0][i], 1, i + 3, &Menu_ShowLabel);
		parameter = Menu_CreateParameterValues(screentexts[1], 2, 64, i + 3, &Menu_ShowParameterValue);
		menuitem = Menu_MenuItemInit(parametername, parameter, 1, i + 3);
		paramlistitem = Menu_ListItemInit(menuitem);
		Menu_AddToList(tempscreen->Parameters, paramlistitem);
	}
	
	free(screentexts);
	return tempscreen;														/*zwrócenie obiektu ekranu												*/
}
