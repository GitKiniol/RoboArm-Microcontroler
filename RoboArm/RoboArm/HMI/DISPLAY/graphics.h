/*
 * graphics.h
 *
 * Created: 07.12.2022 17:54:41
 *  Author: rybka
 */ 


#ifndef GRAPHICS_H_
#define GRAPHICS_H_


#include "avr/pgmspace.h"

/*pusty obraz ikonki													*/
extern __memx const uint8_t EmptyIcon [];

/*ikonka ilustruj¹ca pracê robota										*/
extern __memx const uint8_t RunIcon [];

/*pusty obraz do czysczenia paska statusu								*/
extern __memx const uint8_t EmptyStatus [];

/*pusty obraz do czyszczenia menu										*/
extern __memx const uint8_t EmptyMenu[];

extern __memx const uint8_t lightingImg[];

extern __memx const uint8_t splashImg[];

extern __memx const uint8_t clrScrImg[];

extern __memx const uint8_t arrowUpImg[];

extern __memx const uint8_t arrowDownImg[];

extern __memx const uint8_t arrowRightImg[];

extern __memx const uint8_t arrowLeftImg[];

extern __memx const uint8_t grappleClosedImg[];

extern __memx const uint8_t grappleOpenImg[];

extern __memx const uint8_t arrowsImg[];

extern __memx const uint8_t rotationRightImg[];

extern __memx const uint8_t rotationLeftImg[];


#endif /* GRAPHICS_H_ */