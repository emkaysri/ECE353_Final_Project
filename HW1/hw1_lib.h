// Copyright (c) 2017, Joe Krachey
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

#ifndef __HW1_LIB_H__
#define __HW1_LIB_H__


/******************************************************************************
 * Global Variables
 *****************************************************************************/
extern volatile uint8_t Button_Value;

/*******************************************************************************
* Function Name: hw1_draw_up_arrow
********************************************************************************
* Summary: Prints the up arrow to the LCD
* Returns:
*  Nothing
*******************************************************************************/
void hw1_draw_up_arrow(void );

/*******************************************************************************
* Function Name: hw1_draw_down_arrow
********************************************************************************
* Summary: Prints the down arrow to the LCD
* Returns:
*  Nothing
*******************************************************************************/
void hw1_draw_down_arrow(void );

/*******************************************************************************
* Function Name: hw1_draw_left_arrow
********************************************************************************
* Summary: Prints the left arrow to the LCD
* Returns:
*  Nothing
*******************************************************************************/
void hw1_draw_left_arrow(void );

/*******************************************************************************
* Function Name: hw1_draw_right_arrow
********************************************************************************
* Summary: Prints the right arrow to the LCD
* Returns:
*  Nothing
*******************************************************************************/
void hw1_draw_right_arrow(void );

/*******************************************************************************
* Function Name: hw1_clear_arrow
********************************************************************************
* Summary: Clears the current arrow drawn on the LCD
* Returns:
*  Nothing
*******************************************************************************/
void hw1_clear_arrow(void );

/*******************************************************************************
* Function Name: hw1_ai_init_pattern
********************************************************************************
* Summary: Initializes an array of values to pseudo random values.  The values
*          returned will have one of 4 values: 0x01, 0x02, 0x04, or 0x08.
* Returns:
*  Nothing
*******************************************************************************/
void hw1_ai_init_pattern(uint8_t *pattern, uint16_t moves, uint32_t seed);

/*******************************************************************************
* Function Name: hw1_simon_says
********************************************************************************
* Summary: Prints the string "Simon Says" and delays for a short time.
* Returns:
*  Nothing
*******************************************************************************/
void hw1_simon_says(void);

/*******************************************************************************
* Function Name: hw1_simon_clears
********************************************************************************
* Summary: Clears the string "Simon Says" from the LCD screen
* Returns:
*  Nothing
*******************************************************************************/
void hw1_simon_clears(void);

/*******************************************************************************
* Function Name: hw1_game_over
********************************************************************************
* Summary: Prints the string "GAME OVER" to the 
* Returns:
*  Nothing
*******************************************************************************/
void hw1_game_over(void);


/*******************************************************************************
* Function Name: hw1_wait_for_start
********************************************************************************
* Summary: Prints a message to the user to press the UP button.  Will wait
*          indefinitely until the UP button is pressed
* Returns:
*  Nothing
*******************************************************************************/
uint32_t hw1_wait_for_start(void);

/*******************************************************************************
* Function Name: hw1_wait_ms
********************************************************************************
* Summary: Busy waits for an arbitrary set of milliseconds
* Returns:
*  Nothing
*******************************************************************************/
void hw1_wait_ms(uint32_t milliseconds);


/*******************************************************************************
* Function Name: hw1_init
********************************************************************************
* Summary: Initializes hardware resources needed for this assignment.  
* Returns:
*  Nothing
*******************************************************************************/
void hw1_init(void);





#endif


