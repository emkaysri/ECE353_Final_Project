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

int drawCard(int x, int y, CARD_VALUE val, CARD_SUIT suit) ;
void clear();



#endif