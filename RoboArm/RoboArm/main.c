/*
 * RoboArm.c
 *
 * Created: 05.02.2022 08:34:34
 * Author : rybka
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "SYS_CLOCK/sysclock.h"
#include "HMI/TWI_BUS/twi.h"
#include "HMI/DISPLAY/oled_SSD1306.h"
#include "BLUETOOTH/USART/usart.h"
#include "BLUETOOTH/FRAMES/frame.h"
#include "BLUETOOTH/HC05/hc05.h"
#include "CONTROL/WORK/work.h"

TWI_t *lcdBus = &TWIC;

list_t *Job;	
list_element_t *JobElement_1;
list_element_t *JobElement_2;
list_t *Task_1;
list_element_t *Task1Element_1;
list_t *Task_2;
list_element_t *Task2Element_1;
list_element_t *Task2Element_2;
list_element_t *Task2Element_3;

move_t *Move_1;
move_t *Move_2;
move_t *Move_3;
move_t *Move_4;

list_t *TaskToDo;
move_t *MoveToDo;


//pe7 - tx  pe6-rx, pb7-key, pb6-state
int main(void)
{
	ClkSys32MHz();
    //twiMasterInit(lcdBus, TWI_BAUDRATE);
	//ssd1306Init(lcdBus);
	//ssd1306ClrScr(lcdBus, 0xAA);
	
	Bluetooth = HC05_Init(Bluetooth);
	
	Move_1 = Work_CreateMove('Z', 45, 95, 0);
	Move_2 = Work_CreateMove('A', 67, 5, 1);
	Move_3 = Work_CreateMove('B', 92, 52, 1);
	Move_4 = Work_CreateMove('C', 13, 91, 0);
	
	Job = Work_CreateList();
	Task_1 = Work_CreateList();
	Task_2 = Work_CreateList();
	
	Task1Element_1 = Work_CreateListElement(Move_1, NULL);
	Task2Element_1 = Work_CreateListElement(Move_2, NULL);
	Task2Element_2 = Work_CreateListElement(Move_3, NULL);
	Task2Element_3 = Work_CreateListElement(Move_4, NULL);
	
	Work_InsertToList(Task_1, Task1Element_1);
	Work_InsertToList(Task_2, Task2Element_1);
	Work_InsertToList(Task_2, Task2Element_2);
	Work_InsertToList(Task_2, Task2Element_3);
	
	JobElement_1 = Work_CreateListElement(Task_1, NULL);
	JobElement_2 = Work_CreateListElement(Task_2, NULL); 
	
	Work_InsertToList(Job, JobElement_1);
	Work_InsertToList(Job, JobElement_2);
	
	while(Job->Current)
	{
		TaskToDo = Work_GetTaskFromList(Job);
		while(TaskToDo->Current)
		{
			MoveToDo = Work_GetMoveFromList(TaskToDo);
		}
	}
		
	sei();
    while (1) 
    {
		if(Bluetooth->Read() == 1)									// jeœli odczyt zakoñczony poprawnie, to:
		{
			Bluetooth->SendStatus(DATA_OK);							// wyœlij informacje ¿e status OK
		}
    }
}

