#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#define SUIT_WIDTH 2*8
#define SUIT_HEIGHT 15

#define VAL_WIDTH 8
#define VAL_HEIGHT 9

#define CAP_TOUCH_TOLERANCE_SQRD 255

#include "lcd.h"
#include "event.h"
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
int drawHomeScreen(float theta);
void clear();

void graphics_init_data (EVENT_DATA * event_data,GAMESTATE_DATA * global_game_state_data);
int draw(); 


#endif