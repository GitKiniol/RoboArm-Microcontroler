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
	uint16_t MaximumPosition;								/* maksymalna wartoœæ pozycji												*/
	int16_t MinimumPosition;								/* minimalna wartoœæ pozycji												*/
	uint8_t Direction;										/* kierunek ruchu															*/
	TC1_t *DriverTimer;										/* timer sterownika															*/
	PORT_t *DriverPort;										/* port pinów sterownika													*/
	uint8_t EnablePin;										/* numer pinu dla sygna³u enable											*/
	uint8_t DirectionPin;									/* numer pinu dla sygna³u dir												*/
	uint8_t PulsePin;										/* numer pinu dla sygna³u pul												*/
	uint8_t IsRunning:1;									/* flaga informuj¹ca o pracy/zatrzymaniu sterownika							*/
	uint16_t MotorSteps;									/* Liczba kroków silnika na jeden obrót										*/
	uint8_t ElectricalRatio;								/* wartoœæ prze³o¿enia elektrycznego(iloœæ impulsów na krok, ustawienie pinów na sterowniku)				*/
	float MechanicalRatio;									/* wartoœæ prze³o¿enia mechanicznego (obroty przek³adni na obrót silnika)	*/
	uint8_t Speed;											/* prêdkoœæ zadana dla silnika	[obr/min]									*/
	
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