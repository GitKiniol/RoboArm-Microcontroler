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

stepper_driver_t test_stepperDriver;
servo_driver_t test_servoDriver1;
servo_driver_t test_servoDriver2;
to_run_list_t *test_driverList;

int main(void)
{
	ClkSys32MHz();
	twiMasterInit(lcdBus, TWI_BAUDRATE);
	ssd1306Init(lcdBus);
	ssd1306ClrScr(lcdBus, 0xAA);
	
	Job = Data_CreateList();
	
	test_driverList = Driver_ToRunListInit();
	Driver_ToRunListAdd(test_driverList, &test_stepperDriver, STEPPER);
	Driver_ToRunListAdd(test_driverList, &test_servoDriver1, STEPPER);
	Driver_ToRunListAdd(test_driverList, &test_servoDriver2, STEPPER);
	
	Bluetooth = HC05_Init(Bluetooth);
	
	sei();
    while (1) 
    {
		Bluetooth->Read();						/* cykliczne odbieranie ramek danych z telefonu	*/
    }
}


