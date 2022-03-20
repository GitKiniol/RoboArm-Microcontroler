/*
 * work.h
 *
 * Created: 19.03.2022 19:28:49
 *  Author: rybka
 */ 


#ifndef WORK_H_
#define WORK_H_


/*-----------------------------------------------Deklaracje makroinstrukcji-------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------Definicje struktur danych--------------------------------------------------*/

typedef struct MOVE_STRUCT					/* struktura zawiera parametry ruchu pojedynczej osi							*/
{
	char AxisName;							/* literka oznaczaj¹ca oœ: Z,A,B,C,G lub T										*/					
	uint8_t Angle;							/* k¹t obrotu osi 0° - 180°														*/
	uint8_t Speed;							/* prêdkoœæ obrotowa osi 0% - 100%												*/
	uint8_t Direction : 1;					/* kierunek obrotów osi 1 - prawo, 0 - lewo										*/
	uint8_t Blend : 1;						/* ³¹czenie ruchów 0 - ruch indywidualny, 1 - ruch jednoczesny z innymi osiami	*/
	uint8_t Index;							/* indeks aktualnego ruchu														*/
	void *Next;								/* wskaŸnik na kolejny ruch														*/
}move_t;

typedef struct TASK_STRUCT					/* struktura w formie listy powi¹zanej elementów MOVE							*/
{
	move_t *FirstMove;						/* pierwszy ruch na liœcie	(head)												*/
	move_t *LastMove;						/* ostatni ruch na liœcie	(tail)												*/
	move_t *CurrentMove;					/* aktualny ruch																*/
	uint8_t Count;							/* licznik elementów															*/
	void (*Insert)(move_t *move);			/* funkcja wstawia ruch do listy												*/
	void (*Remove)(move_t *move);			/* funkcja usuwa ruch z listy													*/	
}task_t;

/*--------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------Deklaracje zmiennych-----------------------------------------------------*/
/* EXTERN:	*/

/* LOCAL:	*/

/*--------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------Deklaracje funkcji-----------------------------------------------------*/

move_t *Work_CreateMove(void);								/* funkcja alokuje pamiêæ dla struktury typu Move				*/

void Work_DeleteMove(move_t *move);							/* funkcja zwalnia pomiêæ zajêt¹ przez strukturê Move			*/

/*--------------------------------------------------------------------------------------------------------------------------*/



#endif /* WORK_H_ */