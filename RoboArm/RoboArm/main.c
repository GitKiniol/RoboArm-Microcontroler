/*
 * RoboArm.c
 *
 * Created: 05.02.2022 08:34:34
 * Author : rybka
 */ 

#include <stdlib.h>
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
#include "HMI/KEYBORD/keyboard.h"
#include "HMI/MENU/screen.h"
#include "HMI/MENU/menu.h"

TWI_t *lcdBus = &TWIE;

keyboard_t *Keyboard;
loop_list_t *Screens;
menu_screen_t *Screen;

int main(void)
{
	
	ClkSys32MHz();							
	twiMasterInit(lcdBus, TWI_BAUDRATE);
	ssd1306Init(lcdBus);
	ssd1306ClrScr(lcdBus, 0x00);
	Driver_AxisInit();
	Job = Data_CreateList();
	Bluetooth = HC05_Init(Bluetooth);

	Keyboard = Keyboard_Init();
	
	Screen = Screen_CreateScreen(Scr1Names, ScrValuesSet1, ScrValuesSet1, ScrValuesSet1, ScrValuesSet1, ScrValuesSet1);
	
	sei();
    while (1) 
    {
		Bluetooth->Read();									/* cykliczne odbieranie ramek danych z telefonu	*/
		Keyboard->Listner(Keyboard, Screens);				/* nas³uch klawiatury							*/
    }
}





