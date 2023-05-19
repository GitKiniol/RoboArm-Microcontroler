/*
 * menu.h
 *
 * Created: 23.10.2022 08:46:37
 *  Author: rybka
 */ 


#ifndef MENU_H_
#define MENU_H_



/*----------------------------------------------------definicje struktur i typ�w danych---------------------------------------------------------------------*/
																																
typedef struct BOOL_STRUCT										/*struktura opisuj�ca typ danych "bool"														*/
{
	uint8_t State :1;											/*jedno bitowa zmienna okre�laj�ca stany 0-False i 1-True									*/
}bool_t;

typedef struct LABEL_STRUCT										/*struktura opisuj�ca labelk�																*/
{
	char *Text;													/*wska�nik na adres w pami�ci pod kt�rym zapisany jest tekst								*/
	uint8_t X;													/*pozycja w osi poziomej wy�wietlacza (0-127)												*/
	uint8_t Y;													/*pozycja w osi pionowej wy�wietlacza (0-7)													*/
	void(*Show)(uint8_t, uint8_t, char *, uint8_t);				/*wska�nik na funkcj� kt�ra wy�wietli tekst na ekranie										*/
	/*          X        Y        text	  zaznaczenie																										*/
}label_t;	

typedef struct ICON_STRUCT										/*struktura opisuj�ca ikonk�																*/
{
	__memx const uint8_t *Image;								/*wska�nik na adres w pami�ci flash pod kt�rym zapisany jest obrazek						*/
	uint8_t X;													/*pozycja w osi poziomej wy�wietlacza (0-127)												*/
	uint8_t Y;													/*pozycja w osi pionowej wy�wietlacza (0-7)													*/
	void(*Show)(uint8_t, uint8_t, __memx const uint8_t *);		/*wska�nik na funkcj� kt�ra wy�wietli obraz na ekranie										*/
	/*          X        Y        image																														*/
}icon_t;																														

typedef struct LOOP_LIST_ITEM_STRUCT							/*struktura opisuje element listy typu 'loop'												*/
{
	void *Next;													/*wska�nik na kolejny element listy															*/
	void *Prev;													/*wska�nik na poprzedni element listy														*/
	void *Data;													/*wska�nik na dane b\ed\ace zawarto�ci� tego elementu										*/	
}loop_item_t;

typedef struct LOOP_LIST_STRUCT									/*struktura opisuje list� typu 'loop'														*/
{
	loop_item_t *Head;											/*wska�nik na pocz�tek listy(pierwszy wstawiony element)									*/
	loop_item_t *Tail;											/*wska�nik na koniec listy(ostatni wstawiony element)										*/
	loop_item_t *Current;										/*aktualny element listy																	*/
	uint8_t	Count;												/*licznik element�w listy																	*/
}loop_list_t;

typedef struct STATUS_BAR_STRUCT								/*struktura opisuje pasek statusu															*/
{
	label_t *Message;											/*wiadomo�� wy�wietlana na pasku															*/
	loop_list_t *Icons;											/*lista ikon do wy�wietlenia na pasku														*/
	void(*Show)(void *);										/*wska�nik na funkcj� kt�ra wy�wietli wszystkie elementy paska								*/
	void(*Refresh)(void *);										/*wska�nik na funkcj� kt�ra od�wie�y pasek													*/
	void(*Clear)();												/*wska�nik na funkcj� kt�ra usunie wszystko z paska											*/
}status_bar_t;

typedef struct MENU_SCREEN_STRUCT								/*struktura opisuje menu																	*/
{
	loop_list_t *Parameters;									/*lista zawiera parametry danego menu														*/
	void(*Show)(void *);										/*wska�nik na funkcj� kt�ra wy�wietli wszystkie elementy menu								*/
	void(*Refresh)(void *);										/*wska�nik na funkcj� kt�ra od�wie�y menu													*/
	void(*Clear)();												/*wska�nik na funkcj� kt�ra usunie wszystko z menu											*/
	bool_t IsReadOnly;											/*zmienna informuje czy menu jest tylko do odczytu											*/
}menu_screen_t;

typedef struct PARAM_VALUE_STRUCT								/*struktura opisuj�ca parametr																*/
{
	loop_list_t *Values;										/*lista warto�ci parametru																	*/
	uint8_t X;													/*pozycja w osi poziomej wy�wietlacza (0-127)												*/
	uint8_t Y;													/*pozycja w osi pionowej wy�wietlacza (0-7)													*/
	void(*Show)(void *, uint8_t);								/*wska�nik na funkcj� kt�ra wy�wietli warto�� na ekranie									*/
	/*          parameter	  zaznaczenie																													*/
}par_values_t;

typedef struct MENU_ITEM_STRUCT									/*struktura opisuje element menu															*/
{
	label_t *Name;												/*nazwa parametru menu																		*/
	par_values_t *Value;										/*warto�ci parametru																		*/
	uint8_t X;													/*pozycja w osi poziomej wy�wietlacza (0-127)												*/
	uint8_t Y;													/*pozycja w osi pionowej wy�wietlacza (0-7)													*/
	bool_t IsSelected;											/*zmienna okre�la stan pod�wietlenia warto�ci												*/
}menu_item_t;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------deklaracja funkcji---------------------------------------------------------------------------*/

/* Obs�uga listy danych:	*/

loop_list_t *Menu_ListInit(void);																/* inicjalizacja listy										*/

loop_item_t *Menu_ListItemInit(void *data);														/* inicjalizacje elementu listy								*/

menu_item_t *Menu_MenuItemInit(label_t *name, par_values_t *value, uint8_t x, uint8_t y);		/* inicjalizacja elementu menu	(wiersz menu)				*/

void Menu_AddToList(loop_list_t *list, loop_item_t *item);										/* wstawienie elementu do listy								*/

loop_item_t *Menu_GetFromList(loop_list_t *list);												/* pobranie aktualnego elementu listy						*/

void Menu_ListScrollUp(loop_list_t *list);														/* przewijanie listy w g�r�									*/

void Menu_ListScrollDown(loop_list_t *list);													/* przewijanie listy w d�									*/

void Menu_ListScrollDown(loop_list_t *list);													/* przewijanie listy w d�									*/

void Menu_ListScrollUp(loop_list_t *list);														/* przewijanie listy w g�r�									*/

/* Obs�uga menu */

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
							
void Menu_ShowLabel(uint8_t x, uint8_t y,char *txt, uint8_t select);							/* wy�wietlenie labelki										*/

void Menu_ShowParameterValue(void *parameter, uint8_t select);									/* wy�wietla warto�� parametru								*/

void Menu_NextParameterValue(menu_item_t *menuitem);											/* prze��czenie na kolejn� warto�� parametru				*/

void Menu_PrevParameterValue(menu_item_t *menuitem);											/* prze��czenie na poprzedni� warto�� parametru				*/

void Menu_ShowIcon(uint8_t x, uint8_t y, __memx const uint8_t *img);							/* wy�wietlenie ikony										*/

void Menu_ShowStatusBar(void *statusbar);														/* wy�wietlenie paska statusu								*/

void Menu_ShowMenu(void *menuscreen);															/* wy�wietlenie menu										*/

void Menu_ClearStatusBar(void);																	/* czyszczenie obszaru paska statusu						*/

void Menu_ClearMenu(void);																		/* czyszczenie obszaru menu									*/

void Menu_RefreshStatusBar(void *statusbar);													/* od�wie�anie paska statusu								*/

void Menu_RefreshMenu(void *menuscreen);														/* od�wie�anie menu											*/

loop_list_t *Menu_CreateScreens(void);															/* funkcja generuje list� ekran�w							*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/
#endif /* MENU_H_ */