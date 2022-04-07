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
#include "HMI/TWI_BUS/twi.h"
#include "CONTROL/WORK/work.h"
#include "SYS_CLOCK/sysclock.h"
#include "BLUETOOTH/HC05/hc05.h"
#include "BLUETOOTH/DATA/data.h"
#include "BLUETOOTH/USART/usart.h"
#include "BLUETOOTH/FRAMES/frame.h"
#include "HMI/DISPLAY/oled_SSD1306.h"


list_t Job, Task;
move_t Move;

int main(void)
{
	ClkSys32MHz();
	
	Bluetooth = HC05_Init(Bluetooth);
	
	sei();
    while (1) 
    {
		if(Bluetooth->Read() == 1)											/* jeœli odczyt zakoñczony poprawnie, to:								*/
		{
			Frame_Fill(ReceivingBuffer, ReceivingFrame);
			switch(Frame_Check(ReceivingFrame))
			{
				case 1:
					HC05_SendStatus("1\n");
					break;
				case 2:
					Data_InsertMoveToJob(&Job, ReceivingFrame);
					HC05_SendStatus("1\n");
					break;
				case 3:
					Data_InsertTaskToJob(&Job, ReceivingFrame, 0);
					HC05_SendStatus("1\n");
					break;
				case 4:
					Data_InsertTaskToJob(&Job, ReceivingFrame, 1);
					Task = *Data_GetTaskFromList(&Job);
					Move = *Data_GetMoveFromList(&Task);
					Move = *Data_GetMoveFromList(&Task);
					Task = *Data_GetTaskFromList(&Job);
					Move = *Data_GetMoveFromList(&Task);
					HC05_SendStatus("1\n");
					Data_ClearList(Job.Head->Data);
					Job.Head = Job.Head->Next;
					Data_ClearList(Job.Head->Data);
					Data_ClearList(&Job);
					break;
				default:
					break;
			}
		}
    }
}

