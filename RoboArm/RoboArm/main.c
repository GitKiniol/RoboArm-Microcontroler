/*
 * RoboArm.c
 *
 * Created: 05.02.2022 08:34:34
 * Author : rybka
 */ 

#include <avr/io.h>
#include <stdlib.h>
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

size_t l, m;
list_t *Job;
list_t *Temp;

int main(void)
{
	ClkSys32MHz();
	
	Bluetooth = HC05_Init(Bluetooth);
	
	/* --------  TESTY -------------*/
	
	Job = Work_CreateList();
	Work_InsertToList(Job, Work_CreateListElement(Work_CreateList(), NULL));
	
	Temp = Job->Head->Data;
	Work_InsertToList(Temp, Work_CreateListElement(Work_CreateMove(), NULL));
	Work_InsertToList(Temp, Work_CreateListElement(Work_CreateMove(), Temp->Head));
	Work_InsertToList(Temp, Work_CreateListElement(Work_CreateMove(), Temp->Head));
	Work_InsertToList(Temp, Work_CreateListElement(Work_CreateMove(), Temp->Head));
	
	Work_InsertToList(Job, Work_CreateListElement(Work_CreateList(), Job->Head));
	Temp = Job->Head->Data;
	Work_InsertToList(Temp, Work_CreateListElement(Work_CreateMove(), NULL));
	Work_InsertToList(Temp, Work_CreateListElement(Work_CreateMove(), Temp->Head));
	Work_InsertToList(Temp, Work_CreateListElement(Work_CreateMove(), Temp->Head));
	Work_InsertToList(Temp, Work_CreateListElement(Work_CreateMove(), Temp->Head));
	
	Work_InsertToList(Job, Work_CreateListElement(Work_CreateList(), Job->Head));
	Temp = Job->Head->Data;
	Work_InsertToList(Temp, Work_CreateListElement(Work_CreateMove(), NULL));
	Work_InsertToList(Temp, Work_CreateListElement(Work_CreateMove(), Temp->Head));
	Work_InsertToList(Temp, Work_CreateListElement(Work_CreateMove(), Temp->Head));
	Work_InsertToList(Temp, Work_CreateListElement(Work_CreateMove(), Temp->Head));
	
	l = sizeof(Job->Head->Data);
	Work_ClearList(Temp);
	Temp = NULL;
	
	/*------------------------------*/

	sei();
    while (1) 
    {
		if(Bluetooth->Read() == 1)									// jeœli odczyt zakoñczony poprawnie, to:
		{
			Bluetooth->SendStatus(DATA_OK);							// wyœlij informacje ¿e status OK
		}
    }
}

