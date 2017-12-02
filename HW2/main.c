// @author Srinidhi Emkay
// 9071272901
// emkay@wisc.edu
//
//
//
//
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
#include <stdlib.h>


extern void ece353_hw2_init_serial(void);

//*****************************************************************************
// Transmits the string "OK" from the Tiva Launchpad to the PC over the 
// serial debug interface (UART0)
//*****************************************************************************
void send_ack(void)
{
  hw2_put_string("OK\n");
}

//*****************************************************************************
// This function is used to receive and acknowledge the data from the PC.  
// You can assume that all the commands being sent will be valid commands in 
// the order specified above.  
//
// When receiving the data from the PC, you MUST dynamically allocate space for 
// the image data from the heap using the malloc command.  Once the image has 
// been displayed, be sure to free the data.
//*****************************************************************************
void get_image( void )
{
	int i, j, buildnumber;
	uint16_t height, width;

	uint8_t *line;
	
	for(i = 0; i < 5; i++){
		buildnumber = hw2_get_byte();
		// check if 
		if (buildnumber == 'S' || buildnumber == 'H' || buildnumber == 'W'){
			// ignore next 3 bytes
			hw2_get_byte();
			hw2_get_byte();
			hw2_get_byte();
			
			send_ack(); // input of "STRT" or "HGHT" or "WDTH"
			continue;
		}
		// ASCII TO Decimal
		buildnumber -= ASCII_NUMBER_TO_DECIMAL;
		
		for(j = 0; j < 3; j++){
			// decimal shift left 1
			buildnumber *= 10;
			// ASCII TO Decimal
			buildnumber += hw2_get_byte() - ASCII_NUMBER_TO_DECIMAL;
		} // input of Height or Width value
		
		height = i == 2 ? buildnumber : height;
		width = i == 4 ? buildnumber : width;
		send_ack();
	}
	
	
	line = malloc(width * sizeof(char));
	for(i = 0; i < height; i++){
		for(j = 0; j < 4; j++){
			hw2_get_byte();
		}
		send_ack(); // input of "LINE"
		
		buildnumber = 0;
		for(j = 0; j < 4; j++){
			buildnumber *= 10;
			buildnumber += hw2_get_byte() - ASCII_NUMBER_TO_DECIMAL;
		}
		send_ack(); // input of LINE number
		
		for(j = 0; j < 4; j++){
			hw2_get_byte();
		}
		send_ack(); // input of "DATA"
		
		for(j = 0; j < width; j++){
			line[j] = hw2_get_byte();
		}		send_ack(); // input of image file line
		
		lcd_draw_color_image(width / 3, buildnumber, line);
		
	}	
	free(line);
}


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
 
  ece353_hw2_init_serial();
  
  lcd_config_screen();
  lcd_clear_screen(LCD_COLOR_BLACK);
  while(1){
    get_image();
  };
  
  
  
}
