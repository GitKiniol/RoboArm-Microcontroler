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
/* Pozycja zadana odebrana z telefonu jest z zakresu 0-90, mimo �e na ekranie telefonu zakres wynosi -90 do 90,
sterownik warto�ci ujemne interpretuje jako warto�ci dodatnie ale z ustawion� flag� kierunku w lewo. Warto��
pozycji przeliczana jest na ilo�� impuls�w jakie trzeba wygenerowa� do wykonania obrotu o zadany k�t, i ta 
w�a�nie liczba jest parametrem "SetpointPosition" w poni�szej strukturze sterownika. Wszystkie inne  
parametry w strukturze sterownika odnosz�ce si� do pozycji wyra�one s� w impulsach a nie w stopniach */
typedef struct STEPPER_DRIVER_STRUCT
{
	int16_t SetpointPosition;					/* pozycja zadana																				*/
	int16_t CurrentPosition;					/* aktualna pozycja																				*/
	uint16_t MaximumPosition;					/* maksymalna warto�� pozycji																	*/
	int16_t MinimumPosition;					/* minimalna warto�� pozycji																	*/
	uint8_t Direction;							/* kierunek ruchu																				*/
	TC1_t *DriverTimer;							/* timer sterownika																				*/
	PORT_t *DriverPort;							/* port pin�w sterownika																		*/
	uint8_t EnablePin;							/* numer pinu dla sygna�u enable																*/
	uint8_t DirectionPin;						/* numer pinu dla sygna�u dir																	*/
	uint8_t PulsePin;							/* numer pinu dla sygna�u pul																	*/
	uint8_t IsRunning:1;						/* flaga informuj�ca o pracy/zatrzymaniu sterownika												*/
	uint16_t MotorSteps;						/* Liczba krok�w silnika na jeden obr�t															*/
	uint8_t ElectricalRatio;					/* warto�� prze�o�enia elektrycznego(ilo�� impuls�w na krok, ustawienie pin�w na sterowniku)	*/
	float MechanicalRatio;						/* warto�� prze�o�enia mechanicznego (obroty przek�adni na obr�t silnika)						*/
	uint8_t Speed;								/* pr�dko�� zadana dla silnika	[obr/min]														*/
	
}stepper_driver_t;

/* Pozycja zadana oraz pozycja max i minimum odbierane z telefonu s� w zakresie 0 - 90, mikrokontroler przelicza je na 
warto�ci odpowiednie dla rejestru timera i w takiej formie wstawiane s� do parametr�w w poni�szej strukturze*/
typedef struct SERVO_DRIVER_STRUCT
{
	uint16_t SetpointPosition;					/* pozycja zadana																				*/
	uint16_t MaximumPosition;					/* maksymalna warto�� pozycji																	*/
	uint16_t MinimumPosition;					/* minimalna warto�� pozycji																	*/
	TC0_t *DriverTimer;							/* timer sterownika																				*/
	PORT_t *DriverPort;							/* port pin�w sterownika																		*/
	uint8_t PwmPin;								/* numer pinu steruj�cego serwem																*/
	uint8_t IsRunning:1;						/* flaga informuj�ca o pracy/zatrzymaniu sterownika												*/

}servo_driver_t;

/*--------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------Deklaracje zmiennych-----------------------------------------------------*/
/* EXTERN:	*/

/* LOCAL:	*/

/*--------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------Deklaracje funkcji-----------------------------------------------------*/

stepper_driver_t *Driver_StepperDriverInit(stepper_driver_t *driver, TC1_t *timer, PORT_t *port, uint16_t motor_steps, uint8_t electrical_ratio, float mechanical_ratio);

servo_driver_t *Driver_ServoDriverInit(servo_driver_t *driver, TC0_t *timer, PORT_t *port, uint8_t pwmpin);

void Driver_AxesInit(void);

void Drivers_SetParameters(move_t *move);

/*--------------------------------------------------------------------------------------------------------------------------*/


#endif /* DRIVERS_H_ */