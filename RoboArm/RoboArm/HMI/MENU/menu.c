/*
 * menu.c
 *
 * Created: 23.10.2022 08:46:51
 *  Author: rybka
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include "avr/pgmspace.h"
#include "menu.h"
#include "../DISPLAY/oled_SSD1306.h"
#include "../DISPLAY/fonts.h"
#include "../DISPLAY/graphics.h"
#include "../DISPLAY/displaytypes.h"

/*---------------------------------------------------------Deklaracje zmiennych---------------------------------------------------------*/

/*LOCAL:	*/
TWI_t *TwiBus = &TWIE;

/*--------------------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------Definicje funkcji------------------------------------------------------------*/
/* Obs³uga listy danych:	*/

loop_list_t *Menu_ListInit(void)
{
	loop_list_t *templist;													/*lista tymczasowa											*/
	templist = (loop_list_t *)malloc(sizeof(loop_list_t));					/*alokacja pamiêci dla listy								*/
	templist->Head = NULL;													/*zerowanie wskaŸnika na pocz¹tek listy						*/
	templist->Tail = NULL;													/*zerowanie wskaŸnika na koniec listy						*/
	templist->Current = NULL;												/*zerowanie wskaŸnika na element aktualny					*/
	templist->Count = 0;													/*zerowanie licznika elementów								*/
	return templist;														/*zwrócenie wskaŸnika do listy								*/
}

loop_item_t *Menu_ListItemInit(void *data)
{
	loop_item_t *tempitem;													/*element tymczasowy										*/
	tempitem = (loop_item_t *)malloc(sizeof(loop_item_t));					/*alokacja pamiêci dal elementu								*/
	tempitem->Next = NULL;													/*zerowanie wskaŸnika na element nastêpny					*/
	tempitem->Prev = NULL;													/*zerowanie wskaŸnika na element poprzedni					*/
	tempitem->Data = data;													/*kopiowanie wskaŸnika na dane								*/
	return tempitem;														/*zwrócenie wskaŸnika do elementu							*/
}

menu_item_t *Menu_MenuItemInit(label_t *name, par_values_t *value, uint8_t x, uint8_t y)
{
	menu_item_t *tempitem;													/*element tymczasowy										*/
	tempitem = (menu_item_t *)malloc(sizeof(menu_item_t));					/*alokacja pamiêci dla elementu								*/
	tempitem->Name = name;													/*wskaŸnik na nazwê parametru								*/
	tempitem->Value = value;												/*wskaŸnik na wartoœæ parametru								*/
	tempitem->X = x;														/*pozycja w poziomie										*/
	tempitem->Y = y;														/*pozycja w pionie											*/
	name->X = tempitem->X;													/*ustawienie pozycji x labelki z nazw¹						*/	
	name->Y = tempitem->Y;													/*ustawienie pozycji y labelki z nazw¹						*/
	value->X = tempitem->X + 64;											/*ustawienie pozycji x labelki z wartoœci¹					*/
	value->Y = tempitem->Y;													/*ustawienie pozycji x labelki z wartoœci¹					*/	
	tempitem->IsSelected.State = 1;											/*element domyœlnie nie jest zaznaczony						*/
	return tempitem;														/*zwrócenie wskaŸnika na element							*/	
}

void Menu_AddToList(loop_list_t *list, loop_item_t *item)
{
	if (list->Tail == NULL && list->Head == NULL)							/*sprawdzenie czy lista jest pusta, jeœli tak to:										*/
	{
		list->Current = item;												/*ustaw wskaŸnik aktualnego elementu													*/
		list->Head = item;													/*ustaw wskaŸnik na pocz¹tek listy														*/
		list->Tail = item;													/*ustaw wskaŸnik na koniec listy														*/
		list->Head->Next = list->Tail;										/*ustawienie pierwszemu elementowi listy wskaŸnika na nastêpny element					*/
		list->Head->Prev = list->Tail;										/*ustawienie pierwszemu elementowi listy wskaŸnika na poprzedni element					*/
		list->Tail->Next = list->Head;										/*ustawienie ostatniemu elementowi listy wskaŸnika na nastêpny element					*/
		list->Tail->Prev = list->Head;										/*ustawienie ostatniemu elementowi listy wskaŸnika na poprzedni element					*/
	}
	else																	/*jeœli lista nie jest pusta to:														*/
	{
		list->Head->Next = item;											/*ustawienie wskaŸnika na nastêpny element elementowi który aktualnie jest pierwszy		*/
		item->Prev = list->Head;											/*ustawienie nowemu elementowi wskaŸnika na element poprzedzaj¹cy go					*/
		item->Next = list->Tail;											/*ustawienie nowemu elementowi wskaŸnika na element nastêpny							*/
		list->Tail->Prev = item;											/*ustawienie ostatniemu elementowi listy wskaŸnika na element poprzedzaj¹cy go			*/
		list->Head = item;													/*wstawienie elementu na pocz¹tek listy													*/
		list->Current = list->Head;											/*ustawienie wskaŸnika na element aktualny listy										*/
	}
	list->Count++;															/*inkrementacja licznika elementów														*/
}

loop_item_t *Menu_GetFromList(loop_list_t *list)
{
	if (list->Tail == NULL && list->Head == NULL)							/*sprawdzenie czy lista jest pusta, jeœli tak to:			*/
	{
		return NULL;														/*zwrócenie pustego wskaŸnika								*/
	}
	loop_item_t *tempitem;													/*utworzenie elementu tymczasowego							*/
	tempitem = list->Current;												/*wykonanie kopi aktualnego elementu listy					*/
	return tempitem;														/*zwrócenie wskaŸnika na pobrany element z listy			*/
}

menu_item_t *Menu_ListScrollDown(loop_list_t *list, menu_screen_t* menu)
{
	if (!menu->IsReadOnly.State)											/*czy aktualne menu jest tylko do odczytu?, jeœli tak to:	*/
	{
		loop_item_t *templistitem;											/*tymczasowy element listy									*/
		menu_item_t *tempmenuitem;											/*tymczasowy element menu									*/
		templistitem = Menu_GetFromList(list);								/*pobranie elementu z listy									*/
		tempmenuitem = templistitem->Data;									/*pobranie elementu menu z elementu listy					*/
		if (tempmenuitem->IsSelected.State)
		{
			tempmenuitem->IsSelected.State = 0;								/*wy³¹czenie zaznaczenia elementu							*/
			list->Current = templistitem->Prev;								/*przesuniêcie aktualnego elementu listy w dó³				*/
			templistitem = Menu_GetFromList(list);							/*pobranie elementu z listy									*/
			tempmenuitem = templistitem->Data;								/*pobranie elementu menu z elementu listy					*/
		}
		tempmenuitem->IsSelected.State = 1;									/*zaznacz element											*/	
		return tempmenuitem;												/*zwrócenie aktualnego elementu menu						*/						
	}
	return NULL;															/*jeœli menu tylko do odczytu to zwróæ pusty element		*/
}

menu_item_t *Menu_ListScrollUp(loop_list_t *list, menu_screen_t* menu)
{
	if (!menu->IsReadOnly.State)											/*czy aktualne menu jest tylko do odczytu?, jeœli tak to:	*/
	{
		loop_item_t *templistitem;											/*tymczasowy element listy									*/
		menu_item_t *tempmenuitem;											/*tymczasowy element menu									*/
		templistitem = Menu_GetFromList(list);								/*pobranie elementu z listy									*/
		tempmenuitem = templistitem->Data;									/*pobranie elementu menu z elementu listy					*/
		if (tempmenuitem->IsSelected.State)
		{
			tempmenuitem->IsSelected.State = 0;								/*wy³¹czenie zaznaczenia elementu							*/
			list->Current = templistitem->Next;								/*przesuniêcie aktualnego elementu listy w górê				*/
			templistitem = Menu_GetFromList(list);							/*pobranie elementu z listy									*/
			tempmenuitem = templistitem->Data;								/*pobranie elementu menu z elementu listy					*/
		}
		tempmenuitem->IsSelected.State = 1;									/*zaznacz element											*/
		return tempmenuitem;												/*zwrócenie aktualnego elementu menu						*/	
	}
	return NULL;															/*jeœli menu tylko do odczytu to zwróæ pusty element		*/
}

/* Obs³uga menu */

label_t *Menu_CreateLabel(char *txt, uint8_t x, uint8_t y, void (*show)(uint8_t, uint8_t, char*, uint8_t))
{
	label_t *templabel;														/*deklaracja labelki										*/
	templabel = (label_t *)malloc(sizeof(label_t));							/*alokacja pamiêci dla labelki								*/
	templabel->X = x;														/*ustawienie pozycji poziomej								*/
	templabel->Y = y;														/*ustawienie pozycji pionowej								*/
	templabel->Text = txt;													/*przyporz¹dkowanie tekstu									*/
	templabel->Show = show;													/*ustawienie wskaŸnika na funkcjê wyœwietlaj¹c¹ labelkê		*/
	return templabel;														/*zwrócenie wskaŸnika na labelkê							*/
}

par_values_t *Menu_CreateParameterValues(char **vtxt, uint8_t vcount, uint8_t x, uint8_t y, void (*show)(void*, uint8_t))
{
	par_values_t *parametervalues;											/*deklaracja wartoœci dla parametru							*/
	parametervalues = (par_values_t *)malloc(sizeof(par_values_t));			/*alokacja pamiêci dla wartoœci parametru					*/
	loop_list_t *values;													/*deklaracja listy wartoœci									*/
	values = Menu_ListInit();												/*inicjalizacja listy wartoœci								*/
	loop_item_t *value;														/*deklaracja pojedynczej wartoœci							*/
	for (uint8_t i = 0; i < vcount; i++)
	{
		value = Menu_ListItemInit((void *)*vtxt++);							/*przypisz tekst do wartoœci								*/
		Menu_AddToList(values, value);										/*dodaj wartoœæ do listy wartoœci							*/
	}
	parametervalues->Values = values;										/*przypisanie listy wartoœci								*/
	parametervalues->Show = show;											/*przypisanie funkcji wyœwietlaj¹cej wartoœæ				*/
	parametervalues->X = x;													/*przypisanie pozycji X										*/
	parametervalues->Y = y;													/*przypisanie pozycji Y										*/
	return parametervalues;													/*zwrócenie wskaŸnika na parametr							*/
}

icon_t *Menu_CreateIcon(__memx const uint8_t *img, uint8_t x, uint8_t y, void (*show)(uint8_t, uint8_t, __memx const uint8_t *))
{
	icon_t *tempicon;														/*deklaracja ikony											*/
	tempicon = (icon_t *)malloc(sizeof(icon_t));							/*alokacja pamiêci dla ikony								*/
	tempicon->X = x;														/*ustawienie pozycji poziomej								*/
	tempicon->Y = y;														/*ustawienie pozycji pionowej								*/
	tempicon->Image = img;													/*przyporz¹dkowanie obrazka ikony							*/
	tempicon->Show = show;													/*ustawienie wskaŸnika na funkcjê wyœwietlaj¹c¹ ikonê		*/
	return tempicon;														/*zwrócenie wskaŸnika na ikonê								*/
}

status_bar_t *Menu_CreateStatusBar(label_t *message, void (*show)(void *), void (*refresh)(void *), void (*clear)())
{
	status_bar_t *tempbar;													/*deklaracja paska statusu									*/
	tempbar = (status_bar_t *)malloc(sizeof(status_bar_t));					/*alokacja pamiêci dla paska statusu						*/
	tempbar->Icons = Menu_ListInit();										/*utworzenie listy ikon										*/
	tempbar->Message = message;												/*ustawienie wskaŸnika na labelkê z wiadomoœci¹				*/
	tempbar->Clear = clear;													/*ustawienie wskaŸnika na funkcjê czyszcz¹c¹ pasek statusu	*/
	tempbar->Refresh = refresh;												/*ustawienie wskaŸnika na funkcjê odœwie¿aj¹c¹ pasek statusu*/
	tempbar->Show = show;													/*ustawienie wskaŸnika na funkcjê wyœwietlaj¹c¹ pasek		*/
	return tempbar;															/*zwrócenie wskaŸnika na pasek statusu						*/									
}

menu_screen_t *Menu_CreateMenu(uint8_t isreadonly, void (*show)(void *), void (*refresh)(void *), void (*clear)())
{
	menu_screen_t *tempmenu;												/*deklaracja menu											*/
	tempmenu = (menu_screen_t *)malloc(sizeof(menu_screen_t));				/*alokacja pamiêci dla menu									*/
	tempmenu->Parameters = Menu_ListInit();									/*utworzenie listy parametrów								*/
	tempmenu->IsReadOnly.State = isreadonly;								/*okreœlenie czy menu jest tylko do odczytu					*/
	tempmenu->Clear = clear;												/*ustawienie wskaŸnika na funkcjê czyszcz¹c¹ menu			*/
	tempmenu->Refresh = refresh;											/*ustawienie wskaŸnika na funkcjê odœwie¿aj¹c¹ menu			*/
	tempmenu->Show = show;													/*ustawienie wskaŸnika na funkcjê wyœwietlaj¹c¹ menu		*/
	return tempmenu;														/*zwrócenie wskaŸnika na menu								*/
}

void Menu_NextParameterValue(menu_item_t *menuitem)
{
	if (menuitem == NULL) return;											/*jeœli menuitem jest pusty to zakoñcz funkcjê				*/
	loop_list_t *vals;														/*tymczasowa lista wartoœci parametru						*/
	vals = menuitem->Value->Values;											/*ustawienie wskaŸnika na listê w elemencie menu			*/
	vals->Current = (loop_item_t *)vals->Current->Next;						/*przesuniêcie wskaŸnika na kolejn¹ wartoœæ					*/
}

void Menu_PrevParameterValue(menu_item_t *menuitem)
{
	if (menuitem == NULL) return;											/*jeœli menuitem jest pusty to zakoñcz funkcjê				*/
	loop_list_t *vals;														/*tymczasowa lista wartoœci parametru						*/
	vals = menuitem->Value->Values;											/*ustawienie wskaŸnika na listê w elemencie menu			*/
	vals->Current = (loop_item_t *)vals->Current->Prev;						/*przesuniêcie wskaŸnika na kolejn¹ wartoœæ					*/
}

void Menu_ShowParameterValue(void *parameter, uint8_t select)
{
	char emptystring[] = {32,32,32,32,32,32,0};								/*pusty ³añcuch 6 x "space"									*/
	par_values_t *param;													/*parametr tymczasowy										*/
	param = (par_values_t *)parameter;										/*rzutowanie parametru wejœciowego na odpowiedni typ		*/
	char *txt;																/*tekst bêd¹cy wartoœci¹ aktualn¹ parametru					*/
	loop_item_t *item;														/*element zawieraj¹cy aktualn¹ wartoœæ parametru			*/
	item = Menu_GetFromList(param->Values);									/*pobranie elementu z listy wartoœci						*/
	txt = (char *)item->Data;												/*pobranie wartoœci aktualnej								*/
	t_point_t position;														/*zmienna okreœla pozycjê parametru na ekranie				*/
	position.X = param->X;													/*ustalenie pozycji poziomej								*/
	position.Y = param->Y;													/*ustalenie pozycji pionowej								*/
	ssd1306WriteTxt(TwiBus, position, font7x5, emptystring, 1);				/*czyszczenie ekranu w miejscu na wartoœæ parametru			*/
	ssd1306WriteTxt(TwiBus, position, font7x5, txt, select);				/*wyœwietlenie aktualnej wartoœci parametru					*/
}

void Menu_ShowLabel(uint8_t x, uint8_t y, char *txt, uint8_t select)
{
	char emptystring[] = {32,32,32,32,32,32,32,32,32,0};					/*pusty ³añcuch 10 x "space"								*/
	t_point_t labelpos;														/*zmienna okreœla pozycjê labelki na ekranie				*/
	labelpos.X = x;															/*ustawienie pozycji X										*/
	labelpos.Y = y;															/*ustawienie pozycji Y										*/
	ssd1306WriteTxt(TwiBus, labelpos, font7x5, emptystring, 1);				/*czyszczenie miejsca pod napis z labelki					*/
	ssd1306WriteTxt(TwiBus, labelpos, font7x5, txt, select);				/*wyœwietlenie napisu z labelki								*/			
}

void Menu_ShowIcon(uint8_t x, uint8_t y, __memx const uint8_t *img)
{															
	t_point_t iconpos;														/*zmienna okreœlaj¹ca pozycjê ikony							*/
	iconpos.X = x;															/*ustawienie pozycji x										*/
	iconpos.Y = y;															/*ustawienie pozycji y										*/
	g_size_t iconsize;														/*zmienna okreœla rozmiar ikonki							*/
	iconsize.height = EmptyIcon[1];											/*pobranie z obrazka informacji o jego wysokoœci			*/
	iconsize.width = EmptyIcon[0];											/*pobranie z obrazka informacji o jego szerokoœci			*/
	ssd1306FillAreaFromFlash(TwiBus, iconpos, iconsize, &EmptyIcon[2]);		/*czyszczenie miejsca pod ikonkê							*/
	ssd1306FillAreaFromFlash(TwiBus, iconpos, iconsize, &img[2]);			/*wyœwietlenie ikonki										*/
}

void Menu_ShowStatusBar(void *statusbar)
{
	status_bar_t *status = (status_bar_t *)statusbar;						/*rzutowanie parametru typu void do typu status_bar_t		*/
	if (status->Message->Text != NULL)										/*jeœli wiadomoœæ paska statusu nie jest pusta, to:			*/
	{
		label_t *label = status->Message;									/*pobierz wiadomoœæ z paska									*/
		status->Message->Show(label->X, label->Y, label->Text, 1);			/*wyœwietl treœæ wiadomoœci									*/
	}
	if (status->Icons->Count != 0)											/*czy lista ikon zawiera elementy ? Jeœli tak, to:			*/
	{
		uint8_t i = 0;														/*deklaracja zmiennej iteracyjnej							*/
		for (; i < status->Icons->Count; i++)								/*iteracja po liœcie ikon									*/
		{
			loop_item_t *item = Menu_GetFromList(status->Icons);			/*pobierz element z listy									*/
			icon_t *icon = item->Data;										/*pobierz ikonê z elementu listy							*/
			status->Icons->Current = item->Prev;							/*przesuwanie wskaŸnika na poprzedni element				*/
			icon->Show(icon->X, icon->Y, icon->Image);						/*wyœwietlenie ikony na pasku statusu						*/
		}
		status->Icons->Current = status->Icons->Head;						/*przesuñ wskaŸnik bie¿¹cego elementu na wartoœæ domyœl¹	*/
	}
}

void Menu_ShowMenu(void *menuscreen)
{
	menu_screen_t *menu = (menu_screen_t*)menuscreen;						/*rzutowanie parametru na typ menu_screen_t					*/
	if (menu->Parameters->Count > 0)										/*czy lista parametrów zawiera elementy? jeœli tak, to:		*/
	{
		uint8_t i = 0;														/*deklaracja zmiennej iteracyjnej							*/
		for (; i < menu->Parameters->Count; i++)							/*iteracja po liœcie parametrów								*/
		{
			loop_item_t *litem = Menu_GetFromList(menu->Parameters);		/*pobranie elementu listy									*/
			menu_item_t *mitem = litem->Data;								/*pobranie elementu menu z elementu listy					*/
			menu->Parameters->Current = litem->Prev;						/*przesuniêcie wskaŸnika na poprzedni element listy			*/
			label_t *nlabel = mitem->Name;									/*pobranie labelki z nazw¹ parametru						*/
			par_values_t *vlabel = mitem->Value;							/*pobranie labelki z wartoœci¹ parametru					*/
			nlabel->Show(nlabel->X, nlabel->Y, nlabel->Text, mitem->IsSelected.State);			/*wyœwietlenie labelki z nazw¹			*/
			vlabel->Show(vlabel, 1);										/*wyœwietlenie wartoœci parametru							*/
		}
		menu->Parameters->Current = menu->Parameters->Head;					/*przesuñ wskaŸnik bie¿¹cego elementu na wartoœæ domyœl¹	*/		
	}
}

void Menu_ClearStatusBar(void)
{
	t_point_t clrpos;														/*pozycja pocz¹tku czyszczenia paska statusu				*/
	clrpos.X = 0;															/*okreœlenie pozycji x										*/
	clrpos.Y = 0;															/*okreœlenie pozycji y										*/
	g_size_t clrsize;														/*zmienna okreœla obszar czyszczenia						*/
	clrsize.height = EmptyStatus[1];										/*wysokoœæ czyszczenia (2 wiersze)							*/
	clrsize.width = EmptyStatus[0];											/*szerokoœæ czyszczenia (128 pixeli	)						*/
	ssd1306FillAreaFromFlash(TwiBus, clrpos, clrsize, &EmptyStatus[2]);		/*czyszczenie paska statusu									*/
}

void Menu_ClearMenu(void)
{
	t_point_t clrpos;														/*pozycja pocz¹tku czyszczenia pola menu					*/
	clrpos.X = 0;															/*okreœlenie pozycji x										*/
	clrpos.Y = 2;															/*okreœlenie pozycji y										*/
	g_size_t clrsize;														/*zmienna okreœla obszar czyszczenia						*/
	clrsize.height = EmptyMenu[1];											/*wysokoœæ czyszczenia (2 wiersze)							*/
	clrsize.width = EmptyMenu[0];											/*szerokoœæ czyszczenia (128 pixeli	)						*/
	ssd1306FillAreaFromFlash(TwiBus, clrpos, clrsize, &EmptyMenu[2]);		/*czyszczenie pola menu										*/
}

void Menu_RefreshStatusBar(void *statusbar)
{
	status_bar_t *status = (status_bar_t *) statusbar;
	status->Clear();
	status->Show(status);
}

void Menu_RefreshMenu(void *menuscreen)
{
	status_bar_t *menu = (status_bar_t *) menuscreen;
	menu->Clear();
	menu->Show(menu);
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/