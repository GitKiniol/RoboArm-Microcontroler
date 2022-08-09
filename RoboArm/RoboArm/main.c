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
to_run_list_t *test_lista;
to_run_drv_t *test_toRunDrv;
servo_driver_t test_servo1, test_servo2;
stepper_driver_t test_stepper1, test_stepper2;

int main(void)
{
	ClkSys32MHz();
	twiMasterInit(lcdBus, TWI_BAUDRATE);
	ssd1306Init(lcdBus);
	ssd1306ClrScr(lcdBus, 0xAA);
	Job = Data_CreateList();
	Bluetooth = HC05_Init(Bluetooth);
	
	/*test block 1*/
	test_lista = Driver_ToRunListInit();
	/*end test block 1*/
	
	sei();
    while (1) 
    {
		Bluetooth->Read();						/* cykliczne odbieranie ramek danych z telefonu	*/
		/*test block 2*/
		Driver_ToRunListAdd(test_lista, &test_servo1, SERVO);
		Driver_ToRunListAdd(test_lista, &test_stepper1, STEPPER);
		Driver_ToRunListAdd(test_lista, &test_servo2, SERVO);
		Driver_ToRunListAdd(test_lista, &test_stepper1, STEPPER);
		test_toRunDrv = Driver_ToRunListGet(test_lista);
		test_toRunDrv = Driver_ToRunListGet(test_lista);
		test_toRunDrv = Driver_ToRunListGet(test_lista);
		test_toRunDrv = Driver_ToRunListGet(test_lista);
		/*end test block 2*/
    }
}


