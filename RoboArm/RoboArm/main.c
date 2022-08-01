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
#include "HMI/TWI_BUS/twi.h"
#include "HMI/DISPLAY/oled_SSD1306.h"
#include "BLUETOOTH/USART/usart.h"
#include "BLUETOOTH/FRAMES/frame.h"
#include "BLUETOOTH/HC05/hc05.h"
#include "BLUETOOTH/DATA/data.h"
#include "CONTROL/WORK/work.h"
#include "CONTROL/DRIVERS/drivers.h"

TWI_t *lcdBus = &TWIC;

volatile uint8_t z = 0;
stepper_driver_t *tempAxis;
int main(void)
{
	ClkSys32MHz();
	
	twiMasterInit(lcdBus, TWI_BAUDRATE);
	ssd1306Init(lcdBus);
	ssd1306ClrScr(lcdBus, 0xAA);
	
	Job = Data_CreateList();
	
	Bluetooth = HC05_Init(Bluetooth);
	
	tempAxis = Driver_StepperDriverInit(tempAxis, &TCC1, &PORTC, 200, 4, 3);
	Driver_SetStepperSpeed(tempAxis, 235.0);
	tempAxis->Start(tempAxis, TC_CLKSEL_DIV8_gc);
	_delay_ms(5000);
	tempAxis->Stop(tempAxis);
	
	sei();
    while (1) 
    {
		Bluetooth->Read();						/* cykliczne odbieranie ramek danych z telefonu	*/
    }
}


