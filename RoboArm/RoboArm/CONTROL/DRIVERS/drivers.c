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
to_run_list_t *drvToRunList;							/* lista driver�w przydzielona do zadania								*/

/*------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------Definicje funkcji------------------------------------------------------------------*/

stepper_driver_t *Driver_StepperDriverInit(stepper_driver_t *driver, TC1_t *timer, PORT_t *port, uint16_t motor_steps, uint8_t electrical_ratio, float mechanical_ratio)
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
	driver->DriverTimer->CTRLA = TC_CLKSEL_OFF_gc;						/* preskaler= 0												*/
	driver->DriverTimer->CTRLB = TC_WGMODE_FRQ_gc;						/* tryb FRQ													*/
	driver->DriverTimer->CTRLB |= (1<<TC1_CCAEN_bp);					/* za��czenie generowania impuls�w na pinie wyj�ciowym		*/
	driver->DriverTimer->INTCTRLA = TC1_OVFINTLVL0_bm;					/* odblokowanie przerwania od przepe�nienia timera			*/
	/* ustawienie wska�nik�w na funkcje */
	driver->Start = &Driver_StartStepperDriver;							/* ustawienie wska�nika na funkcj� start					*/
	driver->Stop = &Driver_StopStepperDriver;							/* ustawienie wska�nika na funkcj� stop						*/
	driver->Convert = &Driver_ConvertAngleToStep;						/* ustawienie wska�nika na funkcj� convert					*/
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
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
	driver->DriverPort->DIRCLR = (1 << driver->PwmPin);
	driver->DriverTimer->CTRLB |= TC_WGMODE_DS_T_gc;
	driver->DriverTimer->CTRLB |= (1<<(7 - pwmpin));					/* przekazanie sterowania pinem do timer sprz�towego		*/
	driver->DriverTimer->INTCTRLB |= (1<<(1 + pwmpin));
	driver->DriverTimer->PER = 40000;									/* ustawienie cz�stotliwo�ci pwm na 50Hz					*/
	driver->Start = &Driver_StartServoDriver;							/* ustawienie wska�nika na funkcj� start					*/
	driver->Stop = &Driver_StopServoDriver;								/* ustawienie wska�nika na funkcj� stop						*/
	driver->Convert = &Driver_ConvertAngleToPwm;						/* ustawienie wska�nika na funkcj� convert					*/
	PMIC.CTRL |= PMIC_MEDLVLEN_bm;
	
	return driver;
}

uint16_t Driver_ConvertAngleToStep(uint8_t angle, void *driver)
{
	/* ca�kowita ilo�� impuls�w na obr�t									*/
	float pulsesPerRev = 0.0;	
	/*rzutowanie void do stepper_driver_t									*/													
	stepper_driver_t *drv = (stepper_driver_t *)driver;		
	/*ustalenie liczby impuls�w sterownika programowego na obr�t silnika	*/				
	pulsesPerRev = drv->MotorSteps * drv->ElectricalRatio * drv->MechanicalRatio;		
	return (uint16_t)((pulsesPerRev / 360) * angle);
}

void Driver_SetStepperSpeed(stepper_driver_t *driver, float speed)
{
	//Ir = Sr * Er * Mr				=> Liczba impuls�w drivera programowego na obr�t
	//Fo = So / 60 * Ir				=> Obliczenie cz�stotoliwo�ci wyj�ciowej na podstawie pr�dko�ci i liczby impuls�w
	//CCA = (Fi / 2 * N * Fo) - 1	=> Obliczenie rejestru CCA na podstawie cz�stotliwo�ci wyj�ciowej
	//Sr - liczba krok�w silnika
	//Er - przek�adnia elektryczna(podzia� kroku, ustawiany switchami)
	//Mr - prze�o�enie mechaniczne wynikaj�ce ze �rednic k� z�batych
	
	float ir = 0.0;
	float fo = 0.0;
	ir = driver->MotorSteps * driver->ElectricalRatio * driver->MechanicalRatio;	/*ustalenie liczby impuls�w sterownika programowego na obr�t silnika	*/
	fo = (speed / 60) * ir;															/*obliczenie cz�stotliwo�ci wyj�ciowej sterownika programowego			*/
	driver->DriverTimer->CCA = (uint16_t)((F_CPU / (2.0 * 8.0 * fo)) - 1);			/*obliczenie warto�ci rejestru timera									*/
	
}

void Driver_StartStepperDriver(void *driver, uint8_t preskaler)
{
	stepper_driver_t *drv = (stepper_driver_t*)driver;				/* konwersja typu parametru	*/
	drv->IsRunning = 1;												/* sterownik uruchomiony	*/
	drv->DriverPort->OUTSET = (1<<drv->EnablePin);					/* odblokowanie silnika		*/
	drv->DriverTimer->CTRLA = preskaler;							/* uruchomienie timera		*/
}

void Driver_StartServoDriver(void *driver, uint8_t preskaler)
{
	servo_driver_t *drv = (servo_driver_t*)driver;					/* konwersja typu parametru						*/
	drv->DriverTimer->CTRLA = preskaler;							/* uruchomienie timera							*/
	drv->IsRunning = 1;												/* driver uruchomiony							*/
	drv->DriverPort->DIRSET = (1 << drv->PwmPin);					/* odblokowanie pinu pwm						*/
}

void Driver_StopStepperDriver(void *driver)
{
	stepper_driver_t *drv = (stepper_driver_t *)driver;				/* konwersja typu parametru	*/
	drv->IsRunning = 0;												/* sterownik zatrzymany		*/
	drv->DriverPort->OUTCLR = (1<<drv->EnablePin);					/* zablokowanie silnika		*/
	drv->DriverTimer->CTRLA = TC_CLKSEL_OFF_gc;						/* zatrzymanie timera		*/
}

void Driver_StopServoDriver(void *driver)
{
	servo_driver_t *drv = (servo_driver_t*)driver;					/* konwersja typu parametru						*/
	drv->IsRunning = 0;												/* driver zatrzymany							*/
	drv->DriverPort->DIRCLR = (1<<drv->PwmPin);						/* zablokowanie pinu pwm						*/
	if(axisT->IsRunning == 0 && axisG->IsRunning == 0)				/* je�li servosterowniki zako�czy�y prac�, to:	*/
	{
		drv->DriverTimer->CTRLA = TC_CLKSEL_OFF_gc;					/* zatrzymanie timera							*/
	}
}

uint16_t Driver_ConvertAngleToPwm(uint8_t angle)
{
	return (uint16_t)((angle * 18.88) + 2300);
}

void Driver_SetParameters(move_t *move)
{
	static uint16_t x = 2333;
	if (x > 5)
	{
		x = move->Angle;
	}
}

to_run_list_t *Driver_ToRunListInit(void)
{
	to_run_list_t *ptrToRunList = (to_run_list_t*)malloc(sizeof(to_run_list_t));		/* alokacja pami�ci dla listy			*/
	ptrToRunList->Head = NULL;															/* wyzerowanie wska�nika pocz�tku listy	*/
	ptrToRunList->Tail = NULL;															/* wyzerowanie wska�nika ko�ca listy	*/
	return ptrToRunList;
}

/*------------------------------------------------------------------------------------------------------------------------------*/


/*---------------------------------Przerwania driver�w--------------------------------------------------------------------------*/
ISR(TCC1_OVF_vect)
{
	
}
/*------------------------------------------------------------------------------------------------------------------------------*/