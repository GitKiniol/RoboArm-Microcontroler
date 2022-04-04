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
#include "BLUETOOTH/DATA/data.h"
#include "CONTROL/WORK/work.h"


list_t Job;

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
					break;
				case 3:
					Data_InsertMoveToJob(&Job, ReceivingFrame);
					break;
				default:
					break;
			}
		}
    }
}

