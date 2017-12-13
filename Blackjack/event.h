#ifndef __EVENT_H__
#define __EVENT_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Event variables

// Capacitive Touch

typedef struct  {
	uint8_t valid;
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
	int LAST_PUSHBUTTON;	
} EVENT_DATA;

struct POINT {
	uint16_t x;
	uint16_t y;
};

enum PLAYER_SELECT {
	PLAYER_ONE_SELECT,
	PLAYER_TWO_SELECT,
	NONE
};

typedef enum  {
	START_SCREEN,
	GAME_SCREEN,
	CONTROLS,
	END_GAME,
	RESET
}SCREEN_STATE;


typedef struct {
	uint8_t numPlayer;
	SCREEN_STATE currentScreenState;
	uint16_t playerOneMoney;
	uint16_t playerOneBet;
	uint16_t playerOneWin;
} GAMESTATE_DATA;



#endif