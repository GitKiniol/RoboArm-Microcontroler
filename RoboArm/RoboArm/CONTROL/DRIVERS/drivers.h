/*
 * drivers.h
 *
 * Created: 19.03.2022 19:28:30
 *  Author: rybka
 */ 


#ifndef DRIVERS_H_
#define DRIVERS_H_


/*-----------------------------------------------Deklaracje makroinstrukcji-------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------Definicje struktur danych--------------------------------------------------*/

typedef struct DRIVER_STRUCT
{
	uint16_t SetpointPosition;								/* pozycja zadana												*/
	uint16_t CurrentPosition;								/* aktualna pozycja												*/
	uint8_t Direction;										/* kierunek ruchu												*/
	TC1_t *DriverTimer;										/* timer sterownika												*/
	PORT_t *DriverPort;										/* port pinów sterownika										*/
	uint8_t EnablePin;										/* numer pinu dla sygna³u enable								*/
	uint8_t DirectionPin;									/* numer pinu dla sygna³u dir									*/
	uint8_t PulsePin;										/* numer pinu dla sygna³u pul									*/
	uint8_t IsRunning:1;									/* flaga informuj¹ca o pracy/zatrzymaniu sterownika				*/
	
}driver_t;

/*--------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------Deklaracje zmiennych-----------------------------------------------------*/
/* EXTERN:	*/

/* LOCAL:	*/

/*--------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------Deklaracje funkcji-----------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------------*/


#endif /* DRIVERS_H_ */