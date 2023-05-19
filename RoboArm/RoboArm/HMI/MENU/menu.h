/*
 * menu.h
 *
 * Created: 23.10.2022 08:46:37
 *  Author: rybka
 */ 


#ifndef MENU_H_
#define MENU_H_



/*----------------------------------------------------definicje struktur i typów danych---------------------------------------------------------------------*/
																																
typedef struct BOOL_STRUCT										/*struktura opisuj¹ca typ danych "bool"														*/
{
	uint8_t State :1;											/*jedno bitowa zmienna okreœlaj¹ca stany 0-False i 1-True									*/
}bool_t;

typedef struct LABEL_STRUCT										/*struktura opisuj¹ca labelkê																*/
{
	char *Text;													/*wskaŸnik na adres w pamiêci pod którym zapisany jest tekst								*/
	uint8_t X;													/*pozycja w osi poziomej wyœwietlacza (0-127)												*/
	uint8_t Y;													/*pozycja w osi pionowej wyœwietlacza (0-7)													*/
	void(*Show)(uint8_t, uint8_t, char *, uint8_t);				/*wskaŸnik na funkcjê która wyœwietli tekst na ekranie										*/
	/*          X        Y        text	  zaznaczenie																										*/
}label_t;	

typedef struct ICON_STRUCT										/*struktura opisuj¹ca ikonkê																*/
{
	__memx const uint8_t *Image;								/*wskaŸnik na adres w pamiêci flash pod którym zapisany jest obrazek						*/
	uint8_t X;													/*pozycja w osi poziomej wyœwietlacza (0-127)												*/
	uint8_t Y;													/*pozycja w osi pionowej wyœwietlacza (0-7)													*/
	void(*Show)(uint8_t, uint8_t, __memx const uint8_t *);		/*wskaŸnik na funkcjê która wyœwietli obraz na ekranie										*/
	/*          X        Y        image																														*/
}icon_t;																														

typedef struct LOOP_LIST_ITEM_STRUCT							/*struktura opisuje element listy typu 'loop'												*/
{
	void *Next;													/*wskaŸnik na kolejny element listy															*/
	void *Prev;													/*wskaŸnik na poprzedni element listy														*/
	void *Data;													/*wskaŸnik na dane b\ed\ace zawartoœci¹ tego elementu										*/	
}loop_item_t;

typedef struct LOOP_LIST_STRUCT									/*struktura opisuje listê typu 'loop'														*/
{
	loop_item_t *Head;											/*wskaŸnik na pocz¹tek listy(pierwszy wstawiony element)									*/
	loop_item_t *Tail;											/*wskaŸnik na koniec listy(ostatni wstawiony element)										*/
	loop_item_t *Current;										/*aktualny element listy																	*/
	uint8_t	Count;												/*licznik elementów listy																	*/
}loop_list_t;

typedef struct STATUS_BAR_STRUCT								/*struktura opisuje pasek statusu															*/
{
	label_t *Message;											/*wiadomoœæ wyœwietlana na pasku															*/
	loop_list_t *Icons;											/*lista ikon do wyœwietlenia na pasku														*/
	void(*Show)(void *);										/*wskaŸnik na funkcjê która wyœwietli wszystkie elementy paska								*/
	void(*Refresh)(void *);										/*wskaŸnik na funkcjê która odœwie¿y pasek													*/
	void(*Clear)();												/*wskaŸnik na funkcjê która usunie wszystko z paska											*/
}status_bar_t;

typedef struct MENU_SCREEN_STRUCT								/*struktura opisuje menu																	*/
{
	loop_list_t *Parameters;									/*lista zawiera parametry danego menu														*/
	void(*Show)(void *);										/*wskaŸnik na funkcjê która wyœwietli wszystkie elementy menu								*/
	void(*Refresh)(void *);										/*wskaŸnik na funkcjê która odœwie¿y menu													*/
	void(*Clear)();												/*wskaŸnik na funkcjê która usunie wszystko z menu											*/
	bool_t IsReadOnly;											/*zmienna informuje czy menu jest tylko do odczytu											*/
}menu_screen_t;

typedef struct PARAM_VALUE_STRUCT								/*struktura opisuj¹ca parametr																*/
{
	loop_list_t *Values;										/*lista wartoœci parametru																	*/
	uint8_t X;													/*pozycja w osi poziomej wyœwietlacza (0-127)												*/
	uint8_t Y;													/*pozycja w osi pionowej wyœwietlacza (0-7)													*/
	void(*Show)(void *, uint8_t);								/*wskaŸnik na funkcjê która wyœwietli wartoœæ na ekranie									*/
	/*          parameter	  zaznaczenie																													*/
}par_values_t;

typedef struct MENU_ITEM_STRUCT									/*struktura opisuje element menu															*/
{
	label_t *Name;												/*nazwa parametru menu																		*/
	par_values_t *Value;										/*wartoœci parametru																		*/
	uint8_t X;													/*pozycja w osi poziomej wyœwietlacza (0-127)												*/
	uint8_t Y;													/*pozycja w osi pionowej wyœwietlacza (0-7)													*/
	bool_t IsSelected;											/*zmienna okreœla stan podœwietlenia wartoœci												*/
}menu_item_t;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------deklaracja funkcji---------------------------------------------------------------------------*/

/* Obs³uga listy danych:	*/

loop_list_t *Menu_ListInit(void);																/* inicjalizacja listy										*/

loop_item_t *Menu_ListItemInit(void *data);														/* inicjalizacje elementu listy								*/

menu_item_t *Menu_MenuItemInit(label_t *name, par_values_t *value, uint8_t x, uint8_t y);		/* inicjalizacja elementu menu	(wiersz menu)				*/

void Menu_AddToList(loop_list_t *list, loop_item_t *item);										/* wstawienie elementu do listy								*/

loop_item_t *Menu_GetFromList(loop_list_t *list);												/* pobranie aktualnego elementu listy						*/

void Menu_ListScrollUp(loop_list_t *list);														/* przewijanie listy w górê									*/

void Menu_ListScrollDown(loop_list_t *list);													/* przewijanie listy w dó³									*/

void Menu_ListScrollDown(loop_list_t *list);													/* przewijanie listy w dó³									*/

void Menu_ListScrollUp(loop_list_t *list);														/* przewijanie listy w górê									*/

/* Obs³uga menu */

label_t *Menu_CreateLabel(char *txt, uint8_t x, uint8_t y, 
							void (*show)(uint8_t, uint8_t, char*, uint8_t));					/* utworzenie labelki										*/
							
par_values_t *Menu_CreateParameterValues(char **vtxt, uint8_t vcount, uint8_t x, uint8_t y,
							void (*show)(void*, uint8_t));

icon_t *Menu_CreateIcon(__memx const uint8_t *img, uint8_t x, uint8_t y,
							void (*show)(uint8_t, uint8_t, __memx const uint8_t *));			/* utworzenie ikony											*/
							
status_bar_t *Menu_CreateStatusBar(label_t *message, void (*show)(void *), 
							void (*refresh)(void *), void (*clear)());							/* utworzenie paska statusu									*/
							
menu_screen_t *Menu_CreateMenu(uint8_t isreadonly, void (*show)(void *),
							void (*refresh)(void *), void (*clear)());							/* utworzenie menu											*/
							
void Menu_ShowLabel(uint8_t x, uint8_t y,char *txt, uint8_t select);							/* wyœwietlenie labelki										*/

void Menu_ShowParameterValue(void *parameter, uint8_t select);									/* wyœwietla wartoœæ parametru								*/

void Menu_NextParameterValue(menu_item_t *menuitem);											/* prze³¹czenie na kolejn¹ wartoœæ parametru				*/

void Menu_PrevParameterValue(menu_item_t *menuitem);											/* prze³¹czenie na poprzedni¹ wartoœæ parametru				*/

void Menu_ShowIcon(uint8_t x, uint8_t y, __memx const uint8_t *img);							/* wyœwietlenie ikony										*/

void Menu_ShowStatusBar(void *statusbar);														/* wyœwietlenie paska statusu								*/

void Menu_ShowMenu(void *menuscreen);															/* wyœwietlenie menu										*/

void Menu_ClearStatusBar(void);																	/* czyszczenie obszaru paska statusu						*/

void Menu_ClearMenu(void);																		/* czyszczenie obszaru menu									*/

void Menu_RefreshStatusBar(void *statusbar);													/* odœwie¿anie paska statusu								*/

void Menu_RefreshMenu(void *menuscreen);														/* odœwie¿anie menu											*/

loop_list_t *Menu_CreateScreens(void);															/* funkcja generuje listê ekranów							*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/
#endif /* MENU_H_ */