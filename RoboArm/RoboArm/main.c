/*
 * RoboArm.c
 *
 * Created: 05.02.2022 08:34:34
 * Author : rybka
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include "SYS_CLOCK/sysclock.h"
//#include "HMI/TWI_BUS/twi.h"
//#include "HMI/DISPLAY/oled_SSD1306.h"
//#include "BLUETOOTH/USART/usart.h"
//#include "BLUETOOTH/FRAMES/frame.h"
//#include "BLUETOOTH/HC05/hc05.h"
//#include "BLUETOOTH/DATA/data.h"
//#include "CONTROL/WORK/work.h"
//#include "CONTROL/DRIVERS/drivers.h"

#include "HMI/MENU/menu.h"

//TWI_t *lcdBus = &TWIE;

char *parvalues[] = {"val1", "val2", "val3"};
char *v1;
char *v2;
char *v3;
par_values_t *vvalues;

int main(void)
{
	ClkSys32MHz();							
	//twiMasterInit(lcdBus, TWI_BAUDRATE);
	//ssd1306Init(lcdBus);
	//ssd1306ClrScr(lcdBus, 0xAA);
	//Driver_AxisInit();
	//Job = Data_CreateList();
	//Bluetooth = HC05_Init(Bluetooth);
	v1 = *parvalues;
	vvalues = Menu_CreateParameterValues(parvalues, 3, 3, 3, &Menu_ShowParameterValue);
	
	sei();
    while (1) 
    {
		//Bluetooth->Read();						/* cykliczne odbieranie ramek danych z telefonu	*/
    }
}


