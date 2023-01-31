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
/* Obs�uga listy danych:	*/

loop_list_t *Menu_ListInit(void)
{
	loop_list_t *templist;													/*lista tymczasowa											*/
	templist = (loop_list_t *)malloc(sizeof(loop_list_t));					/*alokacja pami�ci dla listy								*/
	templist->Head = NULL;													/*zerowanie wska�nika na pocz�tek listy						*/
	templist->Tail = NULL;													/*zerowanie wska�nika na koniec listy						*/
	templist->Current = NULL;												/*zerowanie wska�nika na element aktualny					*/
	templist->Count = 0;													/*zerowanie licznika element�w								*/
	return templist;														/*zwr�cenie wska�nika do listy								*/
}

loop_item_t *Menu_ListItemInit(void *data)
{
	loop_item_t *tempitem;													/*element tymczasowy										*/
	tempitem = (loop_item_t *)malloc(sizeof(loop_item_t));					/*alokacja pami�ci dal elementu								*/
	tempitem->Next = NULL;													/*zerowanie wska�nika na element nast�pny					*/
	tempitem->Prev = NULL;													/*zerowanie wska�nika na element poprzedni					*/
	tempitem->Data = data;													/*kopiowanie wska�nika na dane								*/
	return tempitem;														/*zwr�cenie wska�nika do elementu							*/
}

menu_item_t *Menu_MenuItemInit(label_t *name, par_values_t *value, uint8_t x, uint8_t y)
{
	menu_item_t *tempitem;													/*element tymczasowy										*/
	tempitem = (menu_item_t *)malloc(sizeof(menu_item_t));					/*alokacja pami�ci dla elementu								*/
	tempitem->Name = name;													/*wska�nik na nazw� parametru								*/
	tempitem->Value = value;												/*wska�nik na warto�� parametru								*/
	tempitem->X = x;														/*pozycja w poziomie										*/
	tempitem->Y = y;														/*pozycja w pionie											*/
	name->X = tempitem->X;													/*ustawienie pozycji x labelki z nazw�						*/	
	name->Y = tempitem->Y;													/*ustawienie pozycji y labelki z nazw�						*/
	value->X = tempitem->X + 64;											/*ustawienie pozycji x labelki z warto�ci�					*/
	value->Y = tempitem->Y;													/*ustawienie pozycji x labelki z warto�ci�					*/	
	tempitem->IsSelected.State = 1;											/*element domy�lnie nie jest zaznaczony						*/
	return tempitem;														/*zwr�cenie wska�nika na element							*/	
}

void Menu_AddToList(loop_list_t *list, loop_item_t *item)
{
	if (list->Tail == NULL && list->Head == NULL)							/*sprawdzenie czy lista jest pusta, je�li tak to:										*/
	{
		list->Current = item;												/*ustaw wska�nik aktualnego elementu													*/
		list->Head = item;													/*ustaw wska�nik na pocz�tek listy														*/
		list->Tail = item;													/*ustaw wska�nik na koniec listy														*/
		list->Head->Next = list->Tail;										/*ustawienie pierwszemu elementowi listy wska�nika na nast�pny element					*/
		list->Head->Prev = list->Tail;										/*ustawienie pierwszemu elementowi listy wska�nika na poprzedni element					*/
		list->Tail->Next = list->Head;										/*ustawienie ostatniemu elementowi listy wska�nika na nast�pny element					*/
		list->Tail->Prev = list->Head;										/*ustawienie ostatniemu elementowi listy wska�nika na poprzedni element					*/
	}
	else																	/*je�li lista nie jest pusta to:														*/
	{
		list->Head->Next = item;											/*ustawienie wska�nika na nast�pny element elementowi kt�ry aktualnie jest pierwszy		*/
		item->Prev = list->Head;											/*ustawienie nowemu elementowi wska�nika na element poprzedzaj�cy go					*/
		item->Next = list->Tail;											/*ustawienie nowemu elementowi wska�nika na element nast�pny							*/
		list->Tail->Prev = item;											/*ustawienie ostatniemu elementowi listy wska�nika na element poprzedzaj�cy go			*/
		list->Head = item;													/*wstawienie elementu na pocz�tek listy													*/
		list->Current = list->Head;											/*ustawienie wska�nika na element aktualny listy										*/
	}
	list->Count++;															/*inkrementacja licznika element�w														*/
}

loop_item_t *Menu_GetFromList(loop_list_t *list)
{
	if (list->Tail == NULL && list->Head == NULL)							/*sprawdzenie czy lista jest pusta, je�li tak to:			*/
	{
		return NULL;														/*zwr�cenie pustego wska�nika								*/
	}
	loop_item_t *tempitem;													/*utworzenie elementu tymczasowego							*/
	tempitem = list->Current;												/*wykonanie kopi aktualnego elementu listy					*/
	return tempitem;														/*zwr�cenie wska�nika na pobrany element z listy			*/
}

menu_item_t *Menu_ListScrollDown(loop_list_t *list, menu_screen_t* menu)
{
	if (!menu->IsReadOnly.State)											/*czy aktualne menu jest tylko do odczytu?, je�li tak to:	*/
	{
		loop_item_t *templistitem;											/*tymczasowy element listy									*/
		menu_item_t *tempmenuitem;											/*tymczasowy element menu									*/
		templistitem = Menu_GetFromList(list);								/*pobranie elementu z listy									*/
		tempmenuitem = templistitem->Data;									/*pobranie elementu menu z elementu listy					*/
		if (tempmenuitem->IsSelected.State)
		{
			tempmenuitem->IsSelected.State = 0;								/*wy��czenie zaznaczenia elementu							*/
			list->Current = templistitem->Prev;								/*przesuni�cie aktualnego elementu listy w d�				*/
			templistitem = Menu_GetFromList(list);							/*pobranie elementu z listy									*/
			tempmenuitem = templistitem->Data;								/*pobranie elementu menu z elementu listy					*/
		}
		tempmenuitem->IsSelected.State = 1;									/*zaznacz element											*/	
		return tempmenuitem;												/*zwr�cenie aktualnego elementu menu						*/						
	}
	return NULL;															/*je�li menu tylko do odczytu to zwr�� pusty element		*/
}

menu_item_t *Menu_ListScrollUp(loop_list_t *list, menu_screen_t* menu)
{
	if (!menu->IsReadOnly.State)											/*czy aktualne menu jest tylko do odczytu?, je�li tak to:	*/
	{
		loop_item_t *templistitem;											/*tymczasowy element listy									*/
		menu_item_t *tempmenuitem;											/*tymczasowy element menu									*/
		templistitem = Menu_GetFromList(list);								/*pobranie elementu z listy									*/
		tempmenuitem = templistitem->Data;									/*pobranie elementu menu z elementu listy					*/
		if (tempmenuitem->IsSelected.State)
		{
			tempmenuitem->IsSelected.State = 0;								/*wy��czenie zaznaczenia elementu							*/
			list->Current = templistitem->Next;								/*przesuni�cie aktualnego elementu listy w g�r�				*/
			templistitem = Menu_GetFromList(list);							/*pobranie elementu z listy									*/
			tempmenuitem = templistitem->Data;								/*pobranie elementu menu z elementu listy					*/
		}
		tempmenuitem->IsSelected.State = 1;									/*zaznacz element											*/
		return tempmenuitem;												/*zwr�cenie aktualnego elementu menu						*/	
	}
	return NULL;															/*je�li menu tylko do odczytu to zwr�� pusty element		*/
}

/* Obs�uga menu */

label_t *Menu_CreateLabel(char *txt, uint8_t x, uint8_t y, void (*show)(uint8_t, uint8_t, char*, uint8_t))
{
	label_t *templabel;														/*deklaracja labelki										*/
	templabel = (label_t *)malloc(sizeof(label_t));							/*alokacja pami�ci dla labelki								*/
	templabel->X = x;														/*ustawienie pozycji poziomej								*/
	templabel->Y = y;														/*ustawienie pozycji pionowej								*/
	templabel->Text = txt;													/*przyporz�dkowanie tekstu									*/
	templabel->Show = show;													/*ustawienie wska�nika na funkcj� wy�wietlaj�c� labelk�		*/
	return templabel;														/*zwr�cenie wska�nika na labelk�							*/
}

par_values_t *Menu_CreateParameterValues(char **vtxt, uint8_t vcount, uint8_t x, uint8_t y, void (*show)(void*, uint8_t))
{
	par_values_t *parametervalues;											/*deklaracja warto�ci dla parametru							*/
	parametervalues = (par_values_t *)malloc(sizeof(par_values_t));			/*alokacja pami�ci dla warto�ci parametru					*/
	loop_list_t *values;													/*deklaracja listy warto�ci									*/
	values = Menu_ListInit();												/*inicjalizacja listy warto�ci								*/
	loop_item_t *value;														/*deklaracja pojedynczej warto�ci							*/
	for (uint8_t i = 0; i < vcount; i++)
	{
		value = Menu_ListItemInit((void *)*vtxt++);							/*przypisz tekst do warto�ci								*/
		Menu_AddToList(values, value);										/*dodaj warto�� do listy warto�ci							*/
	}
	parametervalues->Values = values;										/*przypisanie listy warto�ci								*/
	parametervalues->Show = show;											/*przypisanie funkcji wy�wietlaj�cej warto��				*/
	parametervalues->X = x;													/*przypisanie pozycji X										*/
	parametervalues->Y = y;													/*przypisanie pozycji Y										*/
	return parametervalues;													/*zwr�cenie wska�nika na parametr							*/
}

icon_t *Menu_CreateIcon(__memx const uint8_t *img, uint8_t x, uint8_t y, void (*show)(uint8_t, uint8_t, __memx const uint8_t *))
{
	icon_t *tempicon;														/*deklaracja ikony											*/
	tempicon = (icon_t *)malloc(sizeof(icon_t));							/*alokacja pami�ci dla ikony								*/
	tempicon->X = x;														/*ustawienie pozycji poziomej								*/
	tempicon->Y = y;														/*ustawienie pozycji pionowej								*/
	tempicon->Image = img;													/*przyporz�dkowanie obrazka ikony							*/
	tempicon->Show = show;													/*ustawienie wska�nika na funkcj� wy�wietlaj�c� ikon�		*/
	return tempicon;														/*zwr�cenie wska�nika na ikon�								*/
}

status_bar_t *Menu_CreateStatusBar(label_t *message, void (*show)(void *), void (*refresh)(void *), void (*clear)())
{
	status_bar_t *tempbar;													/*deklaracja paska statusu									*/
	tempbar = (status_bar_t *)malloc(sizeof(status_bar_t));					/*alokacja pami�ci dla paska statusu						*/
	tempbar->Icons = Menu_ListInit();										/*utworzenie listy ikon										*/
	tempbar->Message = message;												/*ustawienie wska�nika na labelk� z wiadomo�ci�				*/
	tempbar->Clear = clear;													/*ustawienie wska�nika na funkcj� czyszcz�c� pasek statusu	*/
	tempbar->Refresh = refresh;												/*ustawienie wska�nika na funkcj� od�wie�aj�c� pasek statusu*/
	tempbar->Show = show;													/*ustawienie wska�nika na funkcj� wy�wietlaj�c� pasek		*/
	return tempbar;															/*zwr�cenie wska�nika na pasek statusu						*/									
}

menu_screen_t *Menu_CreateMenu(uint8_t isreadonly, void (*show)(void *), void (*refresh)(void *), void (*clear)())
{
	menu_screen_t *tempmenu;												/*deklaracja menu											*/
	tempmenu = (menu_screen_t *)malloc(sizeof(menu_screen_t));				/*alokacja pami�ci dla menu									*/
	tempmenu->Parameters = Menu_ListInit();									/*utworzenie listy parametr�w								*/
	tempmenu->IsReadOnly.State = isreadonly;								/*okre�lenie czy menu jest tylko do odczytu					*/
	tempmenu->Clear = clear;												/*ustawienie wska�nika na funkcj� czyszcz�c� menu			*/
	tempmenu->Refresh = refresh;											/*ustawienie wska�nika na funkcj� od�wie�aj�c� menu			*/
	tempmenu->Show = show;													/*ustawienie wska�nika na funkcj� wy�wietlaj�c� menu		*/
	return tempmenu;														/*zwr�cenie wska�nika na menu								*/
}

void Menu_NextParameterValue(menu_item_t *menuitem)
{
	if (menuitem == NULL) return;											/*je�li menuitem jest pusty to zako�cz funkcj�				*/
	loop_list_t *vals;														/*tymczasowa lista warto�ci parametru						*/
	vals = menuitem->Value->Values;											/*ustawienie wska�nika na list� w elemencie menu			*/
	vals->Current = (loop_item_t *)vals->Current->Next;						/*przesuni�cie wska�nika na kolejn� warto��					*/
}

void Menu_PrevParameterValue(menu_item_t *menuitem)
{
	if (menuitem == NULL) return;											/*je�li menuitem jest pusty to zako�cz funkcj�				*/
	loop_list_t *vals;														/*tymczasowa lista warto�ci parametru						*/
	vals = menuitem->Value->Values;											/*ustawienie wska�nika na list� w elemencie menu			*/
	vals->Current = (loop_item_t *)vals->Current->Prev;						/*przesuni�cie wska�nika na kolejn� warto��					*/
}

void Menu_ShowParameterValue(void *parameter, uint8_t select)
{
	char emptystring[] = {32,32,32,32,32,32,0};								/*pusty �a�cuch 6 x "space"									*/
	par_values_t *param;													/*parametr tymczasowy										*/
	param = (par_values_t *)parameter;										/*rzutowanie parametru wej�ciowego na odpowiedni typ		*/
	char *txt;																/*tekst b�d�cy warto�ci� aktualn� parametru					*/
	loop_item_t *item;														/*element zawieraj�cy aktualn� warto�� parametru			*/
	item = Menu_GetFromList(param->Values);									/*pobranie elementu z listy warto�ci						*/
	txt = (char *)item->Data;												/*pobranie warto�ci aktualnej								*/
	t_point_t position;														/*zmienna okre�la pozycj� parametru na ekranie				*/
	position.X = param->X;													/*ustalenie pozycji poziomej								*/
	position.Y = param->Y;													/*ustalenie pozycji pionowej								*/
	ssd1306WriteTxt(TwiBus, position, font7x5, emptystring, 1);				/*czyszczenie ekranu w miejscu na warto�� parametru			*/
	ssd1306WriteTxt(TwiBus, position, font7x5, txt, select);				/*wy�wietlenie aktualnej warto�ci parametru					*/
}

void Menu_ShowLabel(uint8_t x, uint8_t y, char *txt, uint8_t select)
{
	char emptystring[] = {32,32,32,32,32,32,32,32,32,0};					/*pusty �a�cuch 10 x "space"								*/
	t_point_t labelpos;														/*zmienna okre�la pozycj� labelki na ekranie				*/
	labelpos.X = x;															/*ustawienie pozycji X										*/
	labelpos.Y = y;															/*ustawienie pozycji Y										*/
	ssd1306WriteTxt(TwiBus, labelpos, font7x5, emptystring, 1);				/*czyszczenie miejsca pod napis z labelki					*/
	ssd1306WriteTxt(TwiBus, labelpos, font7x5, txt, select);				/*wy�wietlenie napisu z labelki								*/			
}

void Menu_ShowIcon(uint8_t x, uint8_t y, __memx const uint8_t *img)
{															
	t_point_t iconpos;														/*zmienna okre�laj�ca pozycj� ikony							*/
	iconpos.X = x;															/*ustawienie pozycji x										*/
	iconpos.Y = y;															/*ustawienie pozycji y										*/
	g_size_t iconsize;														/*zmienna okre�la rozmiar ikonki							*/
	iconsize.height = EmptyIcon[1];											/*pobranie z obrazka informacji o jego wysoko�ci			*/
	iconsize.width = EmptyIcon[0];											/*pobranie z obrazka informacji o jego szeroko�ci			*/
	ssd1306FillAreaFromFlash(TwiBus, iconpos, iconsize, &EmptyIcon[2]);		/*czyszczenie miejsca pod ikonk�							*/
	ssd1306FillAreaFromFlash(TwiBus, iconpos, iconsize, &img[2]);			/*wy�wietlenie ikonki										*/
}

void Menu_ShowStatusBar(void *statusbar)
{
	status_bar_t *status = (status_bar_t *)statusbar;						/*rzutowanie parametru typu void do typu status_bar_t		*/
	if (status->Message->Text != NULL)										/*je�li wiadomo�� paska statusu nie jest pusta, to:			*/
	{
		label_t *label = status->Message;									/*pobierz wiadomo�� z paska									*/
		status->Message->Show(label->X, label->Y, label->Text, 1);			/*wy�wietl tre�� wiadomo�ci									*/
	}
	if (status->Icons->Count != 0)											/*czy lista ikon zawiera elementy ? Je�li tak, to:			*/
	{
		uint8_t i = 0;														/*deklaracja zmiennej iteracyjnej							*/
		for (; i < status->Icons->Count; i++)								/*iteracja po li�cie ikon									*/
		{
			loop_item_t *item = Menu_GetFromList(status->Icons);			/*pobierz element z listy									*/
			icon_t *icon = item->Data;										/*pobierz ikon� z elementu listy							*/
			status->Icons->Current = item->Prev;							/*przesuwanie wska�nika na poprzedni element				*/
			icon->Show(icon->X, icon->Y, icon->Image);						/*wy�wietlenie ikony na pasku statusu						*/
		}
		status->Icons->Current = status->Icons->Head;						/*przesu� wska�nik bie��cego elementu na warto�� domy�l�	*/
	}
}

void Menu_ShowMenu(void *menuscreen)
{
	menu_screen_t *menu = (menu_screen_t*)menuscreen;						/*rzutowanie parametru na typ menu_screen_t					*/
	if (menu->Parameters->Count > 0)										/*czy lista parametr�w zawiera elementy? je�li tak, to:		*/
	{
		uint8_t i = 0;														/*deklaracja zmiennej iteracyjnej							*/
		for (; i < menu->Parameters->Count; i++)							/*iteracja po li�cie parametr�w								*/
		{
			loop_item_t *litem = Menu_GetFromList(menu->Parameters);		/*pobranie elementu listy									*/
			menu_item_t *mitem = litem->Data;								/*pobranie elementu menu z elementu listy					*/
			menu->Parameters->Current = litem->Prev;						/*przesuni�cie wska�nika na poprzedni element listy			*/
			label_t *nlabel = mitem->Name;									/*pobranie labelki z nazw� parametru						*/
			par_values_t *vlabel = mitem->Value;							/*pobranie labelki z warto�ci� parametru					*/
			nlabel->Show(nlabel->X, nlabel->Y, nlabel->Text, mitem->IsSelected.State);			/*wy�wietlenie labelki z nazw�			*/
			vlabel->Show(vlabel, 1);										/*wy�wietlenie warto�ci parametru							*/
		}
		menu->Parameters->Current = menu->Parameters->Head;					/*przesu� wska�nik bie��cego elementu na warto�� domy�l�	*/		
	}
}

void Menu_ClearStatusBar(void)
{
	t_point_t clrpos;														/*pozycja pocz�tku czyszczenia paska statusu				*/
	clrpos.X = 0;															/*okre�lenie pozycji x										*/
	clrpos.Y = 0;															/*okre�lenie pozycji y										*/
	g_size_t clrsize;														/*zmienna okre�la obszar czyszczenia						*/
	clrsize.height = EmptyStatus[1];										/*wysoko�� czyszczenia (2 wiersze)							*/
	clrsize.width = EmptyStatus[0];											/*szeroko�� czyszczenia (128 pixeli	)						*/
	ssd1306FillAreaFromFlash(TwiBus, clrpos, clrsize, &EmptyStatus[2]);		/*czyszczenie paska statusu									*/
}

void Menu_ClearMenu(void)
{
	t_point_t clrpos;														/*pozycja pocz�tku czyszczenia pola menu					*/
	clrpos.X = 0;															/*okre�lenie pozycji x										*/
	clrpos.Y = 2;															/*okre�lenie pozycji y										*/
	g_size_t clrsize;														/*zmienna okre�la obszar czyszczenia						*/
	clrsize.height = EmptyMenu[1];											/*wysoko�� czyszczenia (2 wiersze)							*/
	clrsize.width = EmptyMenu[0];											/*szeroko�� czyszczenia (128 pixeli	)						*/
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