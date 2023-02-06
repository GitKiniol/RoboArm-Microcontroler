/*
 * screendata.h
 *
 * Created: 05.02.2023 17:07:24
 *  Author: rybka
 */ 


#ifndef SCREENDATA_H_
#define SCREENDATA_H_

/*------------------------------------------------------Deklaracje zmiennych------------------------------------*/

extern char *Scr1Names[];							/*nazwy parametrów na ekranie nr.1						*/
extern char *Scr2Names[];							/*nazwy parametrów na ekranie nr.2						*/
extern char *Scr3Names[];							/*nazwy parametrów na ekranie nr.3						*/
extern char *Scr4Names[];							/*nazwy parametrów na ekranie nr.4						*/
//extern const char ***Scr1TextSet;						/*napisy dla ekranu nr.1								*/
//extern const char ***Scr2TextSet;						/*napisy dla ekranu nr.2								*/
//extern const char ***Scr3TextSet;						/*napisy dla ekranu nr.3								*/
//extern const char ***Scr4TextSet;						/*napisy dla ekranu nr.4								*/


/*------------------------------------------------------Wartoœci parametrów-------------------------------------*/

extern char *ScrValuesSet1[];						/*pierwszy zestaw wartoœci								*/
extern char *ScrValuesSet2[];						/*drugi zestaw wartoœci									*/
extern char *ScrValuesSet3[];						/*trzeci zestaw wartoœci								*/
extern char *ScrValuesSet4[];						/*czwarty zestaw wartoœci								*/

/*------------------------------------------------------Deklaracje funkcji--------------------------------------*/

void Screendata_DataInit(void);							/*inicjalizacja danych									*/

/*--------------------------------------------------------------------------------------------------------------*/

#endif /* SCREENDATA_H_ */