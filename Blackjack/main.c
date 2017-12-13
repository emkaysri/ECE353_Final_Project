// Copyright (c) 2015-16, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "main.h"
//*****************************************************************************
// Global Variables
//*****************************************************************************
// strings to display to uart and store to eeprom
char student_1[] = "Student1: Jason Sylvestre";
char student_2[] = "Student2: Srinidhi Emkay";
char student_3[] = "Student1: John Compas";
char group[] =     "Team Number: 36";

// timer variables
extern volatile bool ALERT_1MS;
extern volatile bool ALERT_5000MS;
extern volatile int up, down, left, right;

//*****************************************************************************
// 
//*****************************************************************************
void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}

//*****************************************************************************
// 
//*****************************************************************************
void EnableInterrupts(void)
{
  __asm {
    CPSIE  I
  }
}

//*****************************************************************************
// Initialize board hardware
//*****************************************************************************
void initializeBoard(void)
{
  DisableInterrupts();
	
	// GPIO 
	lp_io_init();

	// PS2
	ps2_initialize();
	
	// EEPROM
	eeprom_init();
	
	// GPIO EXPANDER
	io_expander_init();

	// LCD
	lcd_config_gpio();
	lcd_config_screen();
	lcd_clear_screen(LCD_COLOR_WHITE);
	
	// CAPACITIVE TOUCH
	ft6x06_init();

	// SERIAL DEBUG
  init_serial_debug(true, true); 
	
	// WIRELESS
	spi_select_init();
  spi_select(NORDIC);
  wireless_initialize();
  //SysTick_Config(10000000);
	
	
	// TIMERS
	/* TIMER1
		TICK = 250000000
		250000000 / 50e6 = 5s
		Thus will fire every 5 sec
		
		TIMER 5
		TICK = 12500
		PRESCALE = 4
		20ns * 12500 * (3+1) = 0.001s
	*/
	timers_init(TIMER1_BASE, 250000000, 0, TIMER1A_IRQn, 1, TIMER5_BASE, 12500, 3, TIMER5A_IRQn, 1); 
	
  EnableInterrupts();
}

//*****************************************************************************
// Wireless - Configure Wireless point-point connection
//*****************************************************************************
void wireless_connect(){
	
	// Input correct IDs for boards
	uint8_t myID[]  				= { 3,5,3,9,1} ;
	uint8_t remoteID[]      = { 3,5,3,9,2};
	
	wireless_configure_device(myID, remoteID); 
}


//*****************************************************************************
// Switch 2 Debounce 
//*****************************************************************************
void button_debounce(void) 
{
	uint8_t buttons;
	buttons = io_expander_read_buttons();
	up = (buttons & DIR_BTN_UP_PIN) == 0 ? ++up : 0;
	down = (buttons & DIR_BTN_DOWN_PIN) == 0 ? ++down : 0;	
	right = (buttons & DIR_BTN_RIGHT_PIN) == 0 ? ++right : 0;	
	left = (buttons & DIR_BTN_LEFT_PIN) == 0 ? ++left : 0;
}



void update_global_event_data() {
	uint8_t buttons;
	if (ft6x06_read_td_status()) {
		
		uint16_t xRead = ft6x06_read_x();
		uint16_t yRead = ft6x06_read_y();
		if (xRead < 400 && yRead<400) {
			global_event_data.capTouchEvent.valid = true;
			global_event_data.capTouchEvent.x = ft6x06_read_x();
			global_event_data.capTouchEvent.y = ft6x06_read_y();
		}
		
	} else {
		global_event_data.capTouchEvent.valid = false;
	}
	
	global_event_data.joystickEvent.x = ps2_get_x() ; 
	global_event_data.joystickEvent.y = ps2_get_y() ; 
	
	
	
	// TODO CURRENTLY ONE OVERWRITES THE OTHER
	
	if (global_event_data.joystickEvent.x > JOYSTICK_THRESH*3) {
		global_event_data.joystickEvent.dir = LEFT_DIR;
	} else if (global_event_data.joystickEvent.x < JOYSTICK_THRESH) {
		global_event_data.joystickEvent.dir = RIGHT_DIR;
	}
	
	if (global_event_data.joystickEvent.y > 2100) {
		uint16_t inc = (global_event_data.joystickEvent.y-2040)/100;
		global_event_data.joystickEvent.dir = UP_DIR ; 
		
		if (global_game_state_data.playerOneBet+inc <= global_game_state_data.playerOneMoney) {
			global_game_state_data.playerOneBet+=inc;
		}
		
	} else if (global_event_data.joystickEvent.y < 2000) {
		uint16_t inc = (2040-global_event_data.joystickEvent.y)/100;		
		global_event_data.joystickEvent.dir = DOWN_DIR ;
		
		if (global_game_state_data.playerOneBet-inc >= 0) {
			global_game_state_data.playerOneBet-=inc;
		}
	}
	
	
	 buttons = io_expander_read_buttons();
	
	global_event_data.LAST_PUSHBUTTON = -1;
	if (buttons & DIR_BTN_UP_PIN) {
		global_event_data.LAST_PUSHBUTTON = UP_DIR;
	}
	
	if (buttons & DIR_BTN_DOWN_PIN) {
		global_event_data.LAST_PUSHBUTTON = DOWN_DIR;
	}
	if (buttons & DIR_BTN_LEFT_PIN) {
		global_event_data.LAST_PUSHBUTTON = LEFT_DIR;
	}
	if (buttons & DIR_BTN_RIGHT_PIN) {
		global_event_data.LAST_PUSHBUTTON = RIGHT_DIR;
	}
	
	
}

void initGameState() {
	global_game_state_data.numPlayer = 1;
	global_game_state_data.currentScreenState = START_SCREEN; 
	global_game_state_data.playerOneMoney = 25000;
	global_game_state_data.playerOneBet = 0;
}

void write_debug_data() {	
	
	
	uint8_t LEDs = 0xF1;
	char info[80];
	
	printf("**************************************\n\r");
  printf("* BLACK JACK DEBUG DATA\n\r");
	printf("* CAP TOUCH EVENT #: %d\n\r",global_event_data.capTouchEvent.valid);
	
	if (global_event_data.capTouchEvent.valid) {
		printf("* CAP TOUCH X: %d Y: %d\n\r",global_event_data.capTouchEvent.x,global_event_data.capTouchEvent.y);
	}
	printf("* PS2 X: %d Y: %d\n\r",global_event_data.joystickEvent.x,global_event_data.joystickEvent.y);
	printf("* LAST PUSHBUTTON X: %d Y: %d \n\r",0,0);
  printf("**************************************\n\r");
	
	// Test I2C buttons

	
	// Test I2C LEDs
	io_expander_write_LEDs(LEDs);
	
//	// Test EEPROM
//	eeprom_bytes_write((uint8_t *) student_1, EEPROM_STUDENT1, 80);
//	eeprom_bytes_read((uint8_t *)info, EEPROM_STUDENT1, 80);
//	printf("%s\n\r", info);

}


//*****************************************************************************
// Main Function
//*****************************************************************************
int 
main(void)
{
	char info[80];
	int x = 30 ; 
	int i = SPADES ;
	int t = 0 ;
	float theta = 3.1419/2; 
	up = 0, down = 0, left = 0, right = 0;
	SCREEN_STATE prev_state = START_SCREEN;

	
	initializeBoard() ;
	initGameState();
	graphics_init_data (&global_event_data,&global_game_state_data);
	
	
	printf("**************************************\n\r");
	
	printf("****				INIT BLACK JACK				****\n\r");
	
	printf("**************************************\n\r");
	
	
	
//	eeprom_bytes_read((uint8_t *)info, EEPROM_STUDENT1, 80);
//	printf("%s\n", info);
//	
//	eeprom_bytes_read((uint8_t *)info, EEPROM_STUDENT2, 80);
//	printf("%s\n", info);
//	
//	eeprom_bytes_read((uint8_t *)info, EEPROM_STUDENT3, 80);
//	printf("%s\n", info);
//	
//	eeprom_bytes_read((uint8_t *)info, EEPROM_GROUP, 80);
//	printf("%s\n", info);
	
	
	// connect to wireless network 
	wireless_connect();
	
	clear() ;
	
	//Throw out first few cap touch event
	write_debug_data() ; 
	write_debug_data() ; 
		
	// MAIN GAME LOGIC LOOP
	// Program should never exit this loop, from starting screen to games
	while(true) {
		bool startScreen = true;
		float theta = 3.1419/2;
		update_global_event_data() ;
		write_debug_data() ; 
		//wireless_test();
		draw() ;
		if (	global_game_state_data.currentScreenState != 	prev_state &&
			global_game_state_data.currentScreenState != CONTROLS	) {
				prev_state = global_game_state_data.currentScreenState;
		}
	

	// If SW2 is pressed, write names and group number to EEPROM
	if (sw2_debounce()) 
	{
		eeprom_bytes_write((uint8_t *) student_1, EEPROM_STUDENT1, 80);
	  eeprom_bytes_write((uint8_t *) student_2, EEPROM_STUDENT2, 80);
		eeprom_bytes_write((uint8_t *) student_3, EEPROM_STUDENT3, 80);
		eeprom_bytes_write((uint8_t *) group, EEPROM_GROUP, 80);
	}
	
		if (global_event_data.LAST_PUSHBUTTON == RIGHT_DIR
			&& global_game_state_data.currentScreenState == GAME_SCREEN) {
			global_game_state_data.currentScreenState = CONTROLS ;  

		} else if (global_event_data.LAST_PUSHBUTTON != RIGHT_DIR
			&& global_game_state_data.currentScreenState == CONTROLS) { 
			global_game_state_data.currentScreenState = GAME_SCREEN ; 
		}
	

	
	
	for (i =0 ; i< 10; i++) {
				while (!ALERT_1MS) {
				
				}
			
				ALERT_1MS = false; 
			}

			reset_watchDog();
	}

}
