/*
 * menu.h
 *
 * Created: 23.10.2022 08:46:37
 *  Author: rybka
 */ 


#ifndef MENU_H_
#define MENU_H_



/*----------------------------------------------------definicje struktur i typ�w danych-----------------------------------------------------*/
																																
typedef struct BOOL_STRUCT										/*struktura opisuj�ca typ danych "bool"										*/
{
	uint8_t State :1;											/*jedno bitowa zmienna okre�laj�ca stany 0-False i 1-True					*/
}boot_t;

typedef struct LABEL_STRUCT										/*struktura opisuj�ca labelk�												*/
{
	char *Text;													/*wska�nik na adres w pami�ci pod kt�rym zapisany jest tekst				*/
	uint8_t X;													/*pozycja w osi poziomej wy�wietlacza (0-127)								*/
	uint8_t Y;													/*pozycja w osi pionowej wy�wietlacza (0-7)									*/
	void(*Show)(uint8_t, uint8_t, char *);						/*wska�nik na funkcj� kt�ra wy�wietli tekst na ekranie						*/
	/*          X        Y        text																										*/
}label_t;	

typedef struct ICON_STRUCT										/*struktura opisuj�ca ikonk�												*/
{
	__memx const uint8_t *Image;								/*wska�nik na adres w pami�ci flash pod kt�rym zapisany jest obrazek		*/
	uint8_t X;													/*pozycja w osi poziomej wy�wietlacza (0-127)								*/
	uint8_t Y;													/*pozycja w osi pionowej wy�wietlacza (0-7)									*/
	void(*Show)(uint8_t, uint8_t, __memx const uint8_t *);		/*wska�nik na funkcj� kt�ra wy�wietli obraz na ekranie						*/
	/*          X        Y        image																										*/
}icon_t;																														

typedef struct MENU_ITEM_STRUCT									/*struktura opisuje element menu											*/
{
	label_t *Name;												/*nazwa parametru menu														*/
	label_t *Value;												/*warto�� parametru															*/
	uint8_t X;													/*pozycja w osi poziomej wy�wietlacza (0-127)								*/
	uint8_t Y;													/*pozycja w osi pionowej wy�wietlacza (0-7)									*/
	boot_t IsSelected;											/*zmienna okre�la stan pod�wietlenia warto�ci								*/																					
}menu_item_t;

typedef struct LOOP_LIST_ITEM_STRUCT							/*struktura opisuje element listy typu 'loop'								*/
{
	void *Next;													/*wska�nik na kolejny element listy											*/
	void *Prev;													/*wska�nik na poprzedni element listy										*/
	void *Data;													/*wska�nik na dane b\ed\ace zawarto�ci� tego elementu						*/	
}loop_item_t;

typedef struct LOOP_LIST_STRUCT									/*struktura opisuje list� typu 'loop'										*/
{
	loop_item_t *Head;											/*wska�nik na pocz�tek listy(pierwszy wstawiony element)					*/
	loop_item_t *Tail;											/*wska�nik na koniec listy(ostatni wstawiony element)						*/
	loop_item_t *Current;										/*aktualny element listy													*/
	uint8_t	Count;												/*licznik element�w listy													*/
}loop_list_t;

typedef struct STATUS_BAR_STRUCT								/*struktura opisuje pasek statusu											*/
{
	label_t *Message;											/*wiadomo�� wy�wietlana na pasku											*/
	loop_list_t *Icons;											/*lista ikon do wy�wietlenia na pasku										*/
	void(*Show)();												/*wska�nik na funkcj� kt�ra wy�wietli wszystkie elementy paska				*/
	void(*Refresh)();											/*wska�nik na funkcj� kt�ra od�wie�y pasek									*/
	void(*Clear)();												/*wska�nik na funkcj� kt�ra usunie wszystko z paska							*/
}status_bar_t;

typedef struct MENU_SCREEN_STRUCT								/*struktura opisuje menu													*/
{
	loop_list_t *Parameters;									/*lista zawiera parametry danego menu										*/
	void(*Show)();												/*wska�nik na funkcj� kt�ra wy�wietli wszystkie elementy menu				*/
	void(*Refresh)();											/*wska�nik na funkcj� kt�ra od�wie�y menu									*/
	void(*Clear)();												/*wska�nik na funkcj� kt�ra usunie wszystko z menu							*/
	boot_t IsReadOnly;											/*zmienna informuje czy menu jest tylko do odczytu							*/
}menu_screen_t;
#endif /* MENU_H_ */