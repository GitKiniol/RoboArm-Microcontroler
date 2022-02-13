/*
 * displaytypes.h
 *
 * Created: 05.02.2022 17:58:26
 *  Author: rybka
 */ 


#ifndef DISPLAYTYPES_H_
#define DISPLAYTYPES_H_

/*-------------------------------------DEFINICJE TYPÓW DANYCH-----------------------------------------------------------------------------------*/

typedef struct GPoint								/* struktura opisuje punkt graficzny														*/
{
	uint8_t X : 7;									/* zmienna siedmio-bitowa okreœlaj¹ca kolumnê wyœwietlacza, zakres wartoœci 0-127			*/
	uint8_t Y : 6;									/* zmienna szeœcio-bitowa okreœlaj¹ca wiersz wyœwietlacza, zakres wartoœci 0-63				*/
}g_point_t;

typedef struct TPoint								/* struktura opisuje punkt tekstowy															*/
{
	uint8_t X : 7;									/* zmienna siedmio-bitowa okreœlaj¹ca kolumnê wyœwietlacza, zakres wartoœci 0-127			*/
	uint8_t Y : 3;									/* zmienna trzy-bitowa okreœlaj¹ca stronê(8 wierszy) wyœwietlacza, zakres wartoœci 0-7		*/
}t_point_t;

typedef struct GItem								/* struktura opisuje element graficzny														*/
{
	uint8_t ID;										/* numer identyfikacyjny elementu graficznego												*/
	t_point_t beginPoint;							/* pocz¹tek pola zajmowanego przez element													*/
	t_point_t endPoit;								/* koniec pola zajmowanego przez element													*/
	uint8_t *gData;									/* wskaŸnik na dane tworz¹ce element														*/
	void *next;										/* wskaŸnik na nastêpny element																*/
}g_item_t;

typedef struct GitemsList							/* struktura opisuje listê elementów graficznych											*/
{
	g_item_t *current;								/* wskaŸnik na aktualny element graficzny													*/
	g_item_t *head;									/* wskaŸnik na pierwszy element graficzny													*/
	g_item_t *tail;									/* wskaŸnik na ostatni element graficzny													*/
}g_itemsList_t;

typedef struct TItem								/* struktura opisuje element tekstowy														*/
{
	uint8_t ID;										/* numer identyfikacyjny elementu tekstowego												*/
	uint8_t negateTxt;								/* zmienna okreœla czy tekst bêdzie normalny czy podœwietlony								*/
	t_point_t beginPoint;							/* pocz¹tek tekstu																			*/
	char *tData;									/* wskaŸnik na tekst																		*/
	void *next;										/* wskaŸnik na nastêpny element																*/
}t_item_t;

typedef struct TitemsList							/* struktura opisuje listê elementów tekstowych												*/
{
	t_item_t *current;								/* wskaŸnik na aktualny element tekstowy													*/
	t_item_t *head;									/* wskaŸnik na pierwszy element tekstowy													*/
	t_item_t *tail;									/* wskaŸnik na ostatni element tekstowy														*/
}t_itemsList_t;

typedef struct Screen								/* struktura opisuje ekran wyœwietlacza														*/
{
	uint8_t ID;										/* numer identyfikacyjny ekranu																*/
	g_itemsList_t *gItems;							/* wskaŸnik na listê elementów graficznych do wyœwietlenia na ekranie						*/
	t_itemsList_t *tItems;							/* wskaŸnik na listê elementów tekstowych do wyœwietlenia na ekranie						*/
	void *next;										/* wskaŸnik na nastêpny ekran																*/
	void *previous;									/* wskaŸnik na poprzedni ekran																*/
}screen_t;

typedef struct ScreensList							/* struktura opisuje listê ekranów															*/
{
	screen_t *current;								/* wskaŸnik na aktualny ekran																*/
	screen_t *head;									/* wskaŸnik na pierwszy ekran																*/
	screen_t *tail;									/* wskaŸnik na ostatni ekran																*/
}screensList_t;


typedef struct List									/* struktura opisuje listê powi¹zan¹ w postaci ogólnej										*/
{
	void *current;									/* wskaŸnik na aktualny ekran																*/
	void *head;										/* wskaŸnik na pierwszy ekran																*/
	void *tail;										/* wskaŸnik na ostatni ekran																*/
}list_t;

typedef struct GddramScreen							/* struktura opisuje GDDRAM wyœwietlacza													*/
{
	uint8_t memoryMap[128][8];						/* zmienna okreœla strukturê pamiêci GDDRAM													*/
}gddram_t;

typedef struct GraphicSize							/* struktura opisuje rozmiar elementu graficznego (obrazka, litery, itp.)					*/
{
	uint8_t width;									/* szerokoœæ elementu																		*/
	uint8_t height;									/* wysokoœæ elementu																		*/
}g_size_t;

/*----------------------------------------------------------------------------------------------------------------------------------------------*/




#endif /* DISPLAYTYPES_H_ */