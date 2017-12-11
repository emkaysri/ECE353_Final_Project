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

	// PS2 TODO INTERRUPTS CODE
	ps2_initialize_ss2();
	
	// EEPROM
	eeprom_init();

	// TIMERS
	timers_init(TIMER1_BASE, 5000, 10, TIMER1A_IRQn, 1, TIMER5_BASE, 150000000, 0, TIMER5A_IRQn, 1); 

	//

	// LCD
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
  SysTick_Config(10000000);
	
  EnableInterrupts();
}

//*****************************************************************************
// EEPROM - Read Board Data
//*****************************************************************************
void eeprom_read_board_data()
{
	//eeprom_read((uint8_t *)s, EEPROM_STUDENT1, 80);
	//printf("%s\n", s);
	
	//eeprom_read((uint8_t *)s, EEPROM_STUDENT2, 80);
	//printf("%s\n", s);
	
	//eeprom_read((uint8_t *)s, EEPROM_STUDENT3, 80);
	//printf("%s\n", s);
	
	//eeprom_read((uint8_t *)s, EEPROM_GROUP, 80);
	//printf("%s\n", s);
	
}

//*****************************************************************************
// Wireless - Configure Wireless point-point connection
//*****************************************************************************
void wireless_connect(){
	
	// Input correct IDs for boards
	uint8_t myID[]  				= { 3,5,3,2,3};
	uint8_t remoteID[]      = { 4,5,3,2,2};
	
	wireless_configure_device(myID, remoteID); 
}


//*****************************************************************************
// Switch 2 Debounce 
//*****************************************************************************
bool sw2_debounce(void) 
{
	if (lp_io_read_pin(SW2_BIT)){
	// button pressed
	  return false;
	}
	// button not pressed
	return true;
}


//*****************************************************************************
// Main Function
//*****************************************************************************
int 
main(void)
{
	//while(1){
	// display_main_menu return true if master user
    //if(display_main_menu()){
      //master_game();
   // }else{
      //play_game();
   // }
	//}
	int x = 30 ; 
	int i = SPADES ;
	int t = 0 ;
	lcd_config_gpio();
	lcd_config_screen();	
	
	clear() ;

		
	
	while(true) {
	
	clear() ;
		
	drawString("AB CDE", 30, 220, LCD_COLOR_BLACK) ; 
	drawString("FG HIJKL MN", 30, 231, LCD_COLOR_RED) ; 
		
	drawString("OP QR%$#$%^STU", 30, 242, LCD_COLOR_GREEN) ; 
		
	drawString("VWXYZ", 30, 253, LCD_COLOR_BLUE) ; 
		
	drawString("BLACK JACK FUCK YEAH LETS GO", 30, 263, LCD_COLOR_BLACK) ; 
		
		   
		
	x = 30;
	drawCard(x, 30,ACE, i) ;
	x+=45;
	drawCard(x, 30,TWO, i) ;
	x+=45;
	drawCard(x, 30,THREE, i) ;
	x+=45;
	drawCard(x, 30,FOUR, i) ;
	x+=45;
	drawCard(x, 30,FIVE, i) ;
	x=30;
	
	drawCard(x, 90,SIX, i) ;
	x+=45;
	drawCard(x, 90,SEVEN, i) ;
	x+=45;
	drawCard(x, 90,EIGHT, i) ;
	x+=45;
	drawCard(x, 90,NINE, i) ;
	x+=45;
	drawCard(x, 90,TEN, i) ;
	x=30;
	
	
	drawCard(x, 150,JACK, i) ;
	x+=45;
	drawCard(x, 150,QUEEN, i) ;
	x+=45;
	drawCard(x, 150,KING, i) ;
	
	i++;
	
	if (i > DIAMONDS) {
		i = SPADES ; 
	}
	
	
	for (t = 0 ; t < 5000000; t++) {
		//wait
	}
	
	
	
}
	// If SW2 is pressed, write names and group number to EEPROM
	if (sw2_debounce()) 
	{
		//eeprom_write((uint8_t *)s, EEPROM_STUDENT1, 80);
	  	//eeprom_write((uint8_t *)s, EEPROM_STUDENT2, 80);
		//eeprom_write((uint8_t *)s, EEPROM_STUDENT3, 80);
		//eeprom_write((uint8_t *)s, EEPROM_GROUP, 80);
	}


	

}
