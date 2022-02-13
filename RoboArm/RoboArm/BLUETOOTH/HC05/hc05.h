/*
 * hc05.h
 *
 * Created: 09.02.2022 14:55:52
 *  Author: rybka
 */ 


#ifndef HC05_H_
#define HC05_H_

#include "../USART/usart.h"
#include "../FRAMES/frame.h"

/*-----------------------------------------------struktura modu³u HC-05-----------------------------------------------------*/

typedef struct HC_05_S
{
	void (*SendString)(char *txt);						/* funkcja do wysy³ania pojedynczego ³añcucha znaków				*/
	uint8_t (*Read)(void);								/* funkcja odczytu danych											*/
}bluetooth_t;

/*--------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------Deklaracje zmiennych-------------------------------------------------------*/
/* EXTERN:	*/
extern bluetooth_t *Bluetooth;							/* modu³ komunikacyjny												*/

/* LOCAL:	*/

/*--------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------deklaracje funkcji---------------------------------------------------------*/

bluetooth_t *HC05_Init(bluetooth_t *module);			/* inicjalizacja modu³u komunikacyjnego								*/

void HC05_SendString(char *txt);						/* funkcja wysy³aj¹ca ³añcuch znaków								*/

uint8_t HC05_Read(void);								/* funkcja odbiorcza												*/

/*--------------------------------------------------------------------------------------------------------------------------*/



#endif /* HC05_H_ */
