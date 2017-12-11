#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "lcd.h"
#include "image_data.h"

typedef enum{
  ACE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING
} CARD_VALUE;

typedef enum{
  SPADES,
  CLUBS,
  HEARTS,
  DIAMONDS
} CARD_SUIT;

int drawCard(int x, int y, CARD_VALUE val, CARD_SUIT suit, int state) ;
void drawString(char * inputString, int x, int y, uint16_t color, uint16_t colorBackground);

int drawGameScreenOutLineAndData();
int drawHomeScreen();
void clear();



#endif