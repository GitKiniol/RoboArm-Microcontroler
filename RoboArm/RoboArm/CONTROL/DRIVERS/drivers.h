/*
 * drivers.h
 *
 * Created: 19.03.2022 19:28:30
 *  Author: rybka
 */ 


#ifndef DRIVERS_H_
#define DRIVERS_H_

#include "../../BLUETOOTH/DATA/data.h"


/*-----------------------------------------------Deklaracje makroinstrukcji-------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------Definicje struktur danych--------------------------------------------------*/

typedef struct DRIVER_STRUCT
{
	int16_t SetpointPosition;								/* pozycja zadana															*/
	int16_t CurrentPosition;								/* aktualna pozycja															*/
	uint16_t MaximumPosition;								/* maksymalna warto�� pozycji												*/
	int16_t MinimumPosition;								/* minimalna warto�� pozycji												*/
	uint8_t Direction;										/* kierunek ruchu															*/
	TC1_t *DriverTimer;										/* timer sterownika															*/
	PORT_t *DriverPort;										/* port pin�w sterownika													*/
	uint8_t EnablePin;										/* numer pinu dla sygna�u enable											*/
	uint8_t DirectionPin;									/* numer pinu dla sygna�u dir												*/
	uint8_t PulsePin;										/* numer pinu dla sygna�u pul												*/
	uint8_t IsRunning:1;									/* flaga informuj�ca o pracy/zatrzymaniu sterownika							*/
	uint16_t MotorSteps;									/* Liczba krok�w silnika na jeden obr�t										*/
	uint8_t ElectricalRatio;								/* warto�� prze�o�enia elektrycznego(ilo�� impuls�w na krok, ustawienie pin�w na sterowniku)				*/
	float MechanicalRatio;									/* warto�� prze�o�enia mechanicznego (obroty przek�adni na obr�t silnika)	*/
	uint8_t Speed;											/* pr�dko�� zadana dla silnika	[obr/min]									*/
	
}driver_t;

/*--------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------Deklaracje zmiennych-----------------------------------------------------*/
/* EXTERN:	*/

/* LOCAL:	*/

/*--------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------Deklaracje funkcji-----------------------------------------------------*/

void Driver_AxesInit(void);

void Drivers_SetParameters(move_t *move);

/*--------------------------------------------------------------------------------------------------------------------------*/


#endif /* DRIVERS_H_ */