/*
 * frame.c
 *
 * Created: 07.02.2022 18:56:46
 *  Author: rybka
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include "frame.h"
#include "../USART/usart.h"
#include "../USART/BUFFER/buffer.h"

/*----------------------------------Deklaracje zmiennych----------------------------------------------------------------*/
/* EXTERN:	*/
frame_t *ReceivingFrame = NULL;												/* ramka odbiorcza							*/
frame_t *SendingFrame = NULL;												/* ramka nadawcza							*/

/* LOCAL:	*/
char *StartCode = "SF";														/* kod pocz¹tku ramki						*/
char *EndCode = "EF";														/* kod koñca ramki							*/
char *FrameTypes[4] = { "STATUS", "MOVE", "TASK", "JOB" };					/* typy ramek								*/

/*----------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------Definicje funkcji-------------------------------------------------------------------*/

frame_t *Frame_Init(frame_t *frame)
{
	frame = (frame_t *)malloc(sizeof(frame_t));								/* alokacja pamiêci dla ramki				*/
	frame->StartCode = (char *)malloc(sizeof(char) * RECEIVE_MAX_CHARS);	/* alokacja pamiêci na kodu startu  ramki	*/
	strcpy(frame->StartCode, "");											/* zawartoœæ pocz¹tkowa kodu startu  ramki	*/
	frame->FrameType = (char *)malloc(sizeof(char) * RECEIVE_MAX_CHARS);	/* alokacja pamiêci na typ ramki			*/
	strcpy(frame->FrameType, "");											/* zawartoœæ pocz¹tkowa typu ramki			*/
	frame->Data1 = (char *)malloc(sizeof(char) * RECEIVE_MAX_CHARS);		/* alokacja pamiêci na dane ramki			*/
	strcpy(frame->Data1, "");												/* zawartoœæ pocz¹tkowa danych ramki		*/
	frame->Data2 = (char *)malloc(sizeof(char) * RECEIVE_MAX_CHARS);		/* alokacja pamiêci na dane ramki			*/
	strcpy(frame->Data2, "");												/* zawartoœæ pocz¹tkowa danych ramki		*/
	frame->Data3 = (char *)malloc(sizeof(char) * RECEIVE_MAX_CHARS);		/* alokacja pamiêci na dane ramki			*/
	strcpy(frame->Data3, "");												/* zawartoœæ pocz¹tkowa danych ramki		*/
	frame->Data4 = (char *)malloc(sizeof(char) * RECEIVE_MAX_CHARS);		/* alokacja pamiêci na dane ramki			*/
	strcpy(frame->Data4, "");												/* zawartoœæ pocz¹tkowa danych ramki		*/
	frame->EndCode = (char *)malloc(sizeof(char) * RECEIVE_MAX_CHARS);		/* alokacja pamiêci na kod koñca ramki		*/
	strcpy(frame->EndCode, "");												/* zawartoœæ pocz¹tkowa kodu koñca ramki	*/
	return frame;
}

uint8_t Frame_Fill(buffer_t *buffer)
{
	strcpy(ReceivingFrame->StartCode, Buffer_GetString(buffer));			/* pobranie kodu ramki						*/
	if (!(strncmp(StartCode, ReceivingFrame->StartCode, 2)))				/* jeœli kod ramki jest poprawny to:		*/
	{
		strcpy(ReceivingFrame->FrameType, Buffer_GetString(buffer));		/* pobierz typ ramki						*/
		strcpy(ReceivingFrame->Data1, Buffer_GetString(buffer));			/* pobierz pierwszy wiersz danych			*/
		strcpy(ReceivingFrame->Data2, Buffer_GetString(buffer));			/* pobierz pierwszy wiersz danych			*/
		strcpy(ReceivingFrame->Data3, Buffer_GetString(buffer));			/* pobierz pierwszy wiersz danych			*/
		strcpy(ReceivingFrame->Data4, Buffer_GetString(buffer));			/* pobierz pierwszy wiersz danych			*/
		strcpy(ReceivingFrame->EndCode, Buffer_GetString(buffer));			/* pobierz kod koñca ramki					*/
		if (!(strncmp(EndCode, ReceivingFrame->EndCode, 2)))				/* jeœli kod koñca ramki jest poprawny to:	*/
		{
			Buffer_Clear(buffer);											/* czyszczenie bufora						*/
			return 1;														/* zwróæ 1 (odczyt OK)						*/													
		}
		else
		{
			Buffer_Clear(buffer);											/* czyszczenie bufora						*/
			return 0;														/* jeœli kod koñca nie w³aœciwy to zwróæ 0	*/
		}
	}
	else
	{
		Buffer_Clear(buffer);												/* czyszczenie bufora						*/
		return 0;															/* jeœli kod startu nie w³aœciwy to zwróæ 0	*/
	}
	return 1;
}

/*----------------------------------------------------------------------------------------------------------------------*/
