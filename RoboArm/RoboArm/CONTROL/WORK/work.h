/*
 * work.h
 *
 * Created: 19.03.2022 19:28:49
 *  Author: rybka
 */ 


#ifndef WORK_H_
#define WORK_H_


/*-----------------------------------------------Deklaracje makroinstrukcji--------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------Definicje struktur danych----------------------------------------------------------------------*/

typedef struct MOVE_STRUCT										/* struktura zawiera parametry ruchu pojedynczej osi							*/
{
	char AxisName;												/* literka oznaczaj¹ca oœ: Z,A,B,C,G lub T										*/					
	uint8_t Angle;												/* k¹t obrotu osi 0° - 180°														*/
	uint8_t Speed;												/* prêdkoœæ obrotowa osi 0% - 100%												*/
	uint8_t Direction : 1;										/* kierunek obrotów osi 1 - prawo, 0 - lewo										*/
}move_t;

typedef struct LIST_ELEMENT_STRUCT								/* lista powi¹zana ruchów tworz¹ca multiruch									*/
{
	void *Next;													/* wskaŸnik na kolejny element													*/
	void *Data;													/* wskaŸnik na dane elementu													*/
}list_element_t;

typedef struct LIST_STRUCT										/* lista powi¹zana ruchów i mutiruchów											*/
{
	list_element_t *Head;										/* pierwszy element na liœcie													*/
	list_element_t *Tail;										/* ostatni element na liœcie													*/
	list_element_t *Current;									/* aktualny element																*/
	uint8_t Count;												/* licznik elementów															*/
}list_t;

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------Deklaracje zmiennych-------------------------------------------------------------------------*/
/* EXTERN:	*/

/* LOCAL:	*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------Deklaracje funkcji-------------------------------------------------------------------------*/

move_t *Work_CreateMove(void);													/* funkcja alokuje pamiêæ dla struktury typu Move				*/

void Work_DeleteMove(move_t *move);												/* funkcja zwalnia pomiêæ zajêt¹ przez strukturê Move			*/

list_element_t *Work_CreateListElement(void *data, void *next);					/* funkcja alokuje pamiêæ dla elementu listy					*/

void Work_DeleteListElement(list_element_t *element);							/* funkcja zwalnia pamiêæ zajmowan¹ przez element				*/

list_t *Work_CreateList(void);													/* funkcja alokuje pamiêæ dla listy								*/

void Work_DeleteList(list_t *list);												/* funkcja zwalnia pamiêæ zajmowan¹ przez listê					*/

void Work_InsertToList(list_t *list, list_element_t *element);					/* funkcja umieszcza element na liœcie							*/

list_element_t *Work_GetElementFromList(list_t *list);							/* funkcja pobiera bie¿¹cy element z listy						*/

void *Work_GetDataFromListElement(list_element_t *element);						/* funkcja pobiera dane z elementu listy						*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/


#endif /* WORK_H_ */