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

char ***parsvals;
char *par1values[] = {"p1v1", "p1v2", "p1v3"};
char *par2values[] = {"p2v1", "p2v2", "p2v3"};
char *par3values[] = {"p3v1", "p3v2", "p3v3"};
char *parnames[] = {"par1", "par2", "par3"};
	
par_values_t *pv;						/*wartoœci parametru						*/
label_t *pn;							/*nazwa parametru							*/
loop_item_t *li;						/*element listy	(kontener)					*/
menu_item_t *mi;						/*element menu								*/
menu_screen_t *scr;						/*menu										*/

void MenuTest(void);
char *s;

int main(void)
{
	
	ClkSys32MHz();							
	//twiMasterInit(lcdBus, TWI_BAUDRATE);
	//ssd1306Init(lcdBus);
	//ssd1306ClrScr(lcdBus, 0xAA);
	//Driver_AxisInit();
	//Job = Data_CreateList();
	//Bluetooth = HC05_Init(Bluetooth);
	parsvals = (char ***)malloc(sizeof(char **) * 4);
	parsvals[0] = parnames;
	parsvals[1] = par1values;
	parsvals[2] = par2values;
	parsvals[3] = par3values;
	MenuTest();
	sei();
    while (1) 
    {
		//Bluetooth->Read();						/* cykliczne odbieranie ramek danych z telefonu	*/
    }
}


void MenuTest(void)
{
	
	static uint8_t i = 0;
	
	do 
	{
		pn = Menu_CreateLabel(parsvals[0][i], 1, i, &Menu_ShowLabel);
		i++;
		pv = Menu_CreateParameterValues(parsvals[i], 3, 1, i - 1, &Menu_ShowParameterValue);
		mi = Menu_MenuItemInit(pn, pv, 1, i - 1);
		li = Menu_ListItemInit(mi);
		if (scr == NULL)
		{
			scr = Menu_CreateMenu(0, &Menu_ShowMenu, &Menu_RefreshMenu, &Menu_ClearMenu);
		}
		Menu_AddToList(scr->Parameters, li);
	} while (/*scr->Parameters->Count*/i < 3);
	
	i = 0;
}


