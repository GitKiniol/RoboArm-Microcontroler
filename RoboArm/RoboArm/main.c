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
	
	twiMasterInit(lcdBus, TWI_BAUDRATE);
	ssd1306Init(lcdBus);
	ssd1306ClrScr(lcdBus, 0xAA);
	
	Bluetooth = HC05_Init(Bluetooth);
	list_t *ptrList;
	sei();
    while (1) 
    {
		if(Bluetooth->Read() == 1)											/* jeœli odczyt zakoñczony poprawnie, to:								*/
		{
			if (Frame_Fill(ReceivingBuffer, ReceivingFrame))				/* jeœli ramka zawiera prawid³owe dane, to:								*/
			{
				switch(Frame_Check(ReceivingFrame))							/* sprawdzenie tupu odebranych danych									*/					
				{
					case 1:
						/* Odebrano ramkê "STATUS"							*/
						break;
					case 2:
						/* Odebrano ramkê "MOVE"							*/
						
						ptrList = Work_CreateList();
						Work_InsertToList(ptrList, Work_CreateListElement(Work_CreateMove(), ptrList->Head));
						/* Dodanie do tej listy elementu "Move"				*/
						/* Wstawienie listy "Task" do listy "Job"			*/
						break;
					case 3:
						/* Odebrano ramkê "TASK"							*/
						/* Jeœli nie istnieje to utworzenie listy "Task"	*/
						/* Dodanie do tej listy elementu "Move"				*/
						break;
					case 4:
						/* Odebrano ramkê "ETASK"							*/
						/* Wstawienie listy "Task" do listy "Job"			*/
						break;
					case 5:
						/* Odebrano ramkê "JOB"								*/
						/* Start											*/
						break;
					case 6:
						/* Odebrano ramkê "EJOB"							*/
						/* Stop												*/
						break;
					default:
						/* Odebrano nieznan¹ ramkê							*/
						break;
				}
			}
		}
    }
}

