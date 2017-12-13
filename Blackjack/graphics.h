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
#include "math.h"
#include <stdlib.h>

#include "blackjack.h"



int drawGameScreenOutLineAndData();
int drawHomeScreen(float theta);
void clear();
int draw(); 

extern EVENT_DATA   global_event_data;
extern GAMESTATE_DATA  global_game_state_data;
extern player this_player;


#endif