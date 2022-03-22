/*
 * RoboArm.c
 *
 * Created: 05.02.2022 08:34:34
 * Author : rybka
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SYS_CLOCK/sysclock.h"
#include "HMI/TWI_BUS/twi.h"
#include "HMI/DISPLAY/oled_SSD1306.h"
#include "BLUETOOTH/USART/usart.h"
#include "BLUETOOTH/FRAMES/frame.h"
#include "BLUETOOTH/HC05/hc05.h"
#include "CONTROL/WORK/work.h"

TWI_t *lcdBus = &TWIC;

//pe7 - tx  pe6-rx, pb7-key, pb6-state
int main(void)
{
	ClkSys32MHz();
    twiMasterInit(lcdBus, TWI_BAUDRATE);
	ssd1306Init(lcdBus);
	ssd1306ClrScr(lcdBus, 0xAA);
	
	Bluetooth = HC05_Init(Bluetooth);
	
	list_t lista1;
	list_t lista2;
	
	list_element_t element1;
	list_element_t element2;
	
	move_t move1;
	
	element1.Data = &move1;
	element2.Data = &lista2;
	
	Work_InsertToList(&lista1, &element1);
	Work_InsertToList(&lista1, &element2);
	
	Work_GetDataFromListElement(&element1);
	Work_GetDataFromListElement(&element1);

	sei();
    while (1) 
    {
		if(Bluetooth->Read() == 1)									// jeœli odczyt zakoñczony poprawnie, to:
		{
			Bluetooth->SendStatus(DATA_OK);							// wyœlij informacje ¿e status OK
		}
    }
}

