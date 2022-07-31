/*
 * drivers.c
 *
 * Created: 19.03.2022 19:28:12
 *  Author: rybka
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "drivers.h"
#include "../../BLUETOOTH/DATA/data.h"

/*-------------------------------------------Deklaracje zmiennych---------------------------------------------------------------*/
/* EXTERN: */

/* LOCAL:  */
stepper_driver_t *axisA, *axisB, *axisC, *axisZ;		/* osie nap�dzane silnikami krokowymi									*/
servo_driver_t *axisG, *axisT;							/* osie nap�dzane silnikami serwo										*/

/*------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------Definicje funkcji------------------------------------------------------------------*/

stepper_driver_t *Driver_Init(stepper_driver_t *driver, TC1_t *timer, PORT_t *port, uint16_t motor_steps, uint8_t electrical_ratio, float mechanical_ratio)
{
	driver = (stepper_driver_t *)malloc(sizeof(stepper_driver_t));
	driver->CurrentPosition = 0;
	driver->SetpointPosition = 85;
	driver->MaximumPosition = 90;
	driver->MinimumPosition = -90;
	driver->Direction = 0;
	driver->EnablePin = 6;
	driver->DirectionPin = 5;
	driver->PulsePin = 4;
	driver->IsRunning = 0;
	driver->DriverTimer = timer;
	driver->DriverPort = port;
	driver->MotorSteps = motor_steps;
	driver->ElectricalRatio = electrical_ratio;
	driver->MechanicalRatio = mechanical_ratio;
	driver->Speed = 150;
	/* ustawienie portu pin�w wyj�ciowych sterownika */
	driver->DriverPort->DIRSET = (1<<driver->DirectionPin);
	driver->DriverPort->DIRSET = (1<<driver->EnablePin);
	driver->DriverPort->DIRSET = (1<<driver->PulsePin);
	/* parametryzacja timera */
	driver->DriverTimer->CTRLA = TC_CLKSEL_OFF_gc;							/* preskaler= 0												*/
	driver->DriverTimer->CTRLB = TC_WGMODE_FRQ_gc;							/* tryb FRQ													*/
	driver->DriverTimer->CTRLB |= (1<<TC1_CCAEN_bp);						/* za��czenie generowania impuls�w na pinie wyj�ciowym		*/
	driver->DriverTimer->INTCTRLA = TC1_OVFINTLVL0_bm;						/* odblokowanie przerwania od przepe�nienia timera			*/
	
	
	return driver;
}

servo_driver_t *Driver_ServoDriverInit(servo_driver_t *driver, TC0_t *timer, PORT_t *port, uint8_t pwmpin)
{
	driver = (servo_driver_t *)malloc(sizeof(servo_driver_t));
	driver->DriverPort = port;
	driver->DriverTimer = timer;
	driver->IsRunning = 0;
	driver->MaximumPosition = 90;
	driver->MinimumPosition = 0;
	driver->SetpointPosition = 0;
	driver->PwmPin = pwmpin;
	driver->DriverPort->DIRSET = (1 << driver->PwmPin);
	driver->DriverTimer->CTRLB |= TC_WGMODE_DS_T_gc;
	driver->DriverTimer->CTRLB |= (1<<(7 - pwmpin));									/* przekazanie sterowania pinem do timer sprz�towego		*/
	driver->DriverTimer->INTCTRLB |= (1<<(1 + pwmpin));
	PMIC.CTRL |= PMIC_MEDLVLEN_bm;
	
	return driver;
}

uint16_t Driver_ConvertAngleToStep(uint8_t angle, void *driver)
{
	//Ir = Sr * Er * Mr				=> Liczba impuls�w drivera programowego na obr�t
	//Fo = So / 60 * Ir				=> Obliczenie cz�stotoliwo�ci wyj�ciowej na podstawie pr�dko�ci i liczby impuls�w
	//CCA = (Fi / 2 * N * Fo) - 1	=> Obliczenie rejestru CCA na podstawie cz�stotliwo�ci wyj�ciowej
	//Sr - liczba krok�w silnika
	//Er - podzia� krok�w na driverze (switche)
	//Mr - prze�o�enie przek�adni
	
	float ir = 0.0;
	float fo = 0.0;
	uint16_t cca = 0;
	stepper_driver_t *drv = (stepper_driver_t *)driver;						/*rzutowanie void do stepper_driver_t									*/
	ir = drv->MotorSteps * drv->ElectricalRatio * drv->MechanicalRatio;		/*ustalenie liczby impuls�w sterownika programowego na obr�t silnika	*/
	fo = (drv->Speed / 60) * ir;											/*obliczenie cz�stotliwo�ci wyj�ciowej sterownika programowego			*/
	cca = (uint16_t)((F_CPU / (2.0 * 8.0 * fo)) - 1);						/*obliczenie warto�ci rejestru timera									*/
	return cca;
}

uint16_t Driver_ConvertAngleToPwm(uint8_t angle)
{
	return (uint16_t)((angle * 18.88) + 2300);
}

void Drivers_SetParameters(move_t *move)
{
	static uint16_t x = 2333;
	if (x > 5)
	{
		x = move->Angle;
	}
}


/*------------------------------------------------------------------------------------------------------------------------------*/


/*---------------------------------Przerwania driver�w--------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------*/