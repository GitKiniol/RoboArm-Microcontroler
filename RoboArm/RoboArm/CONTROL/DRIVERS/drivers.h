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
/* Pozycja zadana odebrana z telefonu jest z zakresu 0-90, mimo ¿e na ekranie telefonu zakres wynosi -90 do 90,
sterownik wartoœci ujemne interpretuje jako wartoœci dodatnie ale z ustawion¹ flag¹ kierunku w lewo. Wartoœæ
pozycji przeliczana jest na iloœæ impulsów jakie trzeba wygenerowaæ do wykonania obrotu o zadany k¹t, i ta 
w³aœnie liczba jest parametrem "SetpointPosition" w poni¿szej strukturze sterownika. Wszystkie inne  
parametry w strukturze sterownika odnosz¹ce siê do pozycji wyra¿one s¹ w impulsach a nie w stopniach */
typedef struct STEPPER_DRIVER_STRUCT
{
	int16_t SetpointPosition;					/* pozycja zadana																				*/
	int16_t CurrentPosition;					/* aktualna pozycja																				*/
	uint16_t MaximumPosition;					/* maksymalna wartoœæ pozycji																	*/
	int16_t MinimumPosition;					/* minimalna wartoœæ pozycji																	*/
	uint8_t Direction;							/* kierunek ruchu																				*/
	TC1_t *DriverTimer;							/* timer sterownika																				*/
	PORT_t *DriverPort;							/* port pinów sterownika																		*/
	uint8_t EnablePin;							/* numer pinu dla sygna³u enable																*/
	uint8_t DirectionPin;						/* numer pinu dla sygna³u dir																	*/
	uint8_t PulsePin;							/* numer pinu dla sygna³u pul																	*/
	uint8_t IsRunning:1;						/* flaga informuj¹ca o pracy/zatrzymaniu sterownika												*/
	uint16_t MotorSteps;						/* Liczba kroków silnika na jeden obrót															*/
	uint8_t ElectricalRatio;					/* wartoœæ prze³o¿enia elektrycznego(iloœæ impulsów na krok, ustawienie pinów na sterowniku)	*/
	float MechanicalRatio;						/* wartoœæ prze³o¿enia mechanicznego (obroty przek³adni na obrót silnika)						*/
	uint8_t Speed;								/* prêdkoœæ zadana dla silnika	[obr/min]														*/
	
}stepper_driver_t;

/* Pozycja zadana oraz pozycja max i minimum odbierane z telefonu s¹ w zakresie 0 - 90, mikrokontroler przelicza je na 
wartoœci odpowiednie dla rejestru timera i w takiej formie wstawiane s¹ do parametrów w poni¿szej strukturze*/
typedef struct SERVO_DRIVER_STRUCT
{
	uint16_t SetpointPosition;					/* pozycja zadana																				*/
	uint16_t MaximumPosition;					/* maksymalna wartoœæ pozycji																	*/
	uint16_t MinimumPosition;					/* minimalna wartoœæ pozycji																	*/
	TC0_t *DriverTimer;							/* timer sterownika																				*/
	PORT_t *DriverPort;							/* port pinów sterownika																		*/
	uint8_t PwmPin;								/* numer pinu steruj¹cego serwem																*/
	uint8_t IsRunning:1;						/* flaga informuj¹ca o pracy/zatrzymaniu sterownika												*/

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