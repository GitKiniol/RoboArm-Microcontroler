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
	uint8_t State :1;											/*jedno bitowa zmienna okreœlaj¹ca stany 0-False i 1-True					*/
}bool_t;

typedef struct LABEL_STRUCT										/*struktura opisuj¹ca labelkê																*/
{
	char *Text;													/*wskaŸnik na adres w pamiêci pod którym zapisany jest tekst				*/
	uint8_t X;													/*pozycja w osi poziomej wyœwietlacza (0-127)								*/
	uint8_t Y;													/*pozycja w osi pionowej wyœwietlacza (0-7)									*/
	void(*Show)(uint8_t, uint8_t, char *);						/*wskaŸnik na funkcjê która wyœwietli tekst na ekranie						*/
	/*          X        Y        text																										*/
}label_t;	

typedef struct ICON_STRUCT										/*struktura opisuj¹ca ikonkê																*/
{
	__memx const uint8_t *Image;								/*wskaŸnik na adres w pamiêci flash pod którym zapisany jest obrazek		*/
	uint8_t X;													/*pozycja w osi poziomej wyœwietlacza (0-127)								*/
	uint8_t Y;													/*pozycja w osi pionowej wyœwietlacza (0-7)									*/
	void(*Show)(uint8_t, uint8_t, __memx const uint8_t *);		/*wskaŸnik na funkcjê która wyœwietli obraz na ekranie						*/
	/*          X        Y        image																										*/
}icon_t;																														

typedef struct MENU_ITEM_STRUCT									/*struktura opisuje element menu															*/
{
	label_t *Name;												/*nazwa parametru menu														*/
	label_t *Value;												/*wartoœæ parametru															*/
	uint8_t X;													/*pozycja w osi poziomej wyœwietlacza (0-127)								*/
	uint8_t Y;													/*pozycja w osi pionowej wyœwietlacza (0-7)									*/
	bool_t IsSelected;											/*zmienna okreœla stan podœwietlenia wartoœci								*/																					
}menu_item_t;

typedef struct LOOP_LIST_ITEM_STRUCT							/*struktura opisuje element listy typu 'loop'												*/
{
	void *Next;													/*wskaŸnik na kolejny element listy											*/
	void *Prev;													/*wskaŸnik na poprzedni element listy										*/
	void *Data;													/*wskaŸnik na dane b\ed\ace zawartoœci¹ tego elementu						*/	
}loop_item_t;

typedef struct LOOP_LIST_STRUCT									/*struktura opisuje listê typu 'loop'														*/
{
	loop_item_t *Head;											/*wskaŸnik na pocz¹tek listy(pierwszy wstawiony element)					*/
	loop_item_t *Tail;											/*wskaŸnik na koniec listy(ostatni wstawiony element)						*/
	loop_item_t *Current;										/*aktualny element listy													*/
	uint8_t	Count;												/*licznik elementów listy													*/
}loop_list_t;

typedef struct STATUS_BAR_STRUCT								/*struktura opisuje pasek statusu															*/
{
	label_t *Message;											/*wiadomoœæ wyœwietlana na pasku											*/
	loop_list_t *Icons;											/*lista ikon do wyœwietlenia na pasku										*/
	void(*Show)(void *);										/*wskaŸnik na funkcjê która wyœwietli wszystkie elementy paska				*/
	void(*Refresh)(void *);										/*wskaŸnik na funkcjê która odœwie¿y pasek									*/
	void(*Clear)();												/*wskaŸnik na funkcjê która usunie wszystko z paska							*/
}status_bar_t;

typedef struct MENU_SCREEN_STRUCT								/*struktura opisuje menu																	*/
{
	loop_list_t *Parameters;									/*lista zawiera parametry danego menu										*/
	void(*Show)(void *);										/*wskaŸnik na funkcjê która wyœwietli wszystkie elementy menu				*/
	void(*Refresh)(void *);										/*wskaŸnik na funkcjê która odœwie¿y menu									*/
	void(*Clear)();												/*wskaŸnik na funkcjê która usunie wszystko z menu							*/
	bool_t IsReadOnly;											/*zmienna informuje czy menu jest tylko do odczytu							*/
}menu_screen_t;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------deklaracja funkcji---------------------------------------------------------------------------------------*/

/* Obs³uga listy danych:	*/

loop_list_t *Menu_ListInit(void);																/* inicjalizacja listy										*/

loop_item_t *Menu_ListItemInit(void *data);														/* inicjalizacje elementu listy								*/

menu_item_t *Menu_MenuItemInit(label_t *name, label_t *value, uint8_t x, uint8_t y);			/* inicjalizacja elementu menu	(wiersz menu)				*/

void Menu_AddToList(loop_list_t *list, loop_item_t *item);										/* wstawienie elementu do listy								*/

loop_item_t *Menu_GetFromList(loop_list_t *list);												/* pobranie aktualnego elementu listy						*/

void Menu_ListScrollDown(loop_list_t *list, menu_screen_t* menu);								/* przewijanie listy w dó³									*/

void Menu_ListScrollUp(loop_list_t *list, menu_screen_t* menu);									/* przewijanie listy w górê									*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------*/
#endif /* MENU_H_ */