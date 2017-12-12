#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#define SUIT_WIDTH 2*8
#define SUIT_HEIGHT 15

#define VAL_WIDTH 8
#define VAL_HEIGHT 9

#define CAP_TOUCH_TOLERANCE_SQRD 255

#include "lcd.h"
#include "image_data.h"

// Event variables

// Capacitive Touch

typedef struct  {
	bool valid;
	uint16_t x;
	uint16_t y;
} LAST_CAP_TOUCH_EVENT ;



typedef enum  {
	UP_DIR,
	DOWN_DIR,
	LEFT_DIR,
	RIGHT_DIR
}DIRECTION;

// Joystick
typedef struct  {
	DIRECTION dir;
	uint16_t x;
	uint16_t y;
} LAST_JOYSTICK_EVENT;


// All event data
typedef struct  {
	LAST_CAP_TOUCH_EVENT capTouchEvent;
	LAST_JOYSTICK_EVENT joystickEvent;
	int LAST_PUSHBUTTON_X ;
	int LAST_PUSHBUTTON_Y ;	
} EVENT_DATA;

struct POINT {
	uint16_t x;
	uint16_t y;
};

enum PLAYER_SELECT {
	PLAYER_ONE_SELECT,
	PLAYER_TWO_SELECT,
};


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
void graphics_init_data (EVENT_DATA * event_data);



#endif