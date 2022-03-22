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
    //twiMasterInit(lcdBus, TWI_BAUDRATE);
	//ssd1306Init(lcdBus);
	//ssd1306ClrScr(lcdBus, 0xAA);
	
	Bluetooth = HC05_Init(Bluetooth);
	
	list_t lista;
	list_t lista2;
	list_t lista3;
	list_element_t element1;
	list_element_t element2;
	list_element_t element3;
	list_element_t element4;
	list_element_t element5;
	list_element_t element6;
	list_element_t element7;
	list_element_t element8;
	
	Work_InsertToList(&lista,&element1);
	Work_InsertToList(&lista,&element2);
	Work_InsertToList(&lista,&element3);
	Work_InsertToList(&lista,&element4);
	
	element5.Data = &lista;
	element7.Data = &lista3;
	
	Work_InsertToList(&lista2,&element5);
	Work_InsertToList(&lista2,&element6);
	Work_InsertToList(&lista2,&element7);
	Work_InsertToList(&lista2,&element8);
	
	
	
	Work_InsertToList(&lista3,&element6);
	Work_InsertToList(&lista3,&element1);
	Work_InsertToList(&lista3,&element8);
	Work_InsertToList(&lista3,&element4);

	sei();
    while (1) 
    {
		if(Bluetooth->Read() == 1)									// jeœli odczyt zakoñczony poprawnie, to:
		{
			Bluetooth->SendStatus(DATA_OK);							// wyœlij informacje ¿e status OK
		}
    }
}

