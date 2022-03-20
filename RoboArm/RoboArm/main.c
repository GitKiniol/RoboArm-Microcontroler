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

	sei();
    while (1) 
    {
		if(Bluetooth->Read() == 1)									// jeœli odczyt zakoñczony poprawnie, to:
		{
			Bluetooth->SendStatus(DATA_OK);							// wyœlij informacje ¿e status OK
		}
    }
}

