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

#include "tic_tac_toe.h"

char individual_1[] = "Srinidhi Emkay";
PS2_DIR_t Current_Direction = PS2_DIR_CENTER;
PS2_DIR_t Previous_Direction = PS2_DIR_CENTER;
int piecesInPlay;
int curr_x, curr_y;
char board[3][3];
int score[8]; // {R1,R2,R3,C1,C2,C3,DLR,DRL} sum X to 1 and O to -1
volatile int pressed;
bool isX;
volatile bool ALERT_SAMPLE;
volatile uint16_t X_Val, Y_Val;
TIMER0_Type *gp_timer;
uint16_t yloc[] = {UPPER_Y, CENTER_Y, LOWER_Y};
uint16_t xloc[] = {LEFT_X, CENTER_X, RIGHT_X};



/*******************************************************************************
* Function Name: tic_tac_toe_hw_init
********************************************************************************
*******************************************************************************/
void tic_tac_toe_hw_init(void)
{
	
	uint32_t ticks = 50000;
	
	
	gpio_enable_port(GPIOF_BASE);
  gpio_config_digital_enable( GPIOF_BASE, SW2_M);
  gpio_config_enable_input(GPIOF_BASE, SW2_M);
  gpio_config_enable_pullup( GPIOF_BASE, SW2_M);
	gpio_config_alternate_function(GPIOF_BASE, SW2_M);
	
	
  ps2_initialize();
	/*
	initialize_adc(ADC0_BASE);
	gpio_enable_port(ADC0_BASE);
	gpio_config_analog_enable(ADC0_BASE, SW2_M);
	gpio_config_enable_input(ADC0_BASE, SW2_M);
	*/
	
  gp_timer_config_32(TIMER5_BASE, TIMER_TAMR_TAMR_PERIOD, false, true);
	//gp_timer_wait(TIMER5_BASE, ticks);
	
	NVIC_EnableIRQ(TIMER5A_IRQn);	
	NVIC_SetPriority(TIMER5A_IRQn ,0);
	
	gp_timer = (TIMER0_Type *)TIMER5_BASE;		
	
	//gp_timer->CTL &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN);
	
	gp_timer->TAILR = ticks;
	
	gp_timer->ICR |= TIMER_ICR_TATOCINT;
	gp_timer->CTL |= TIMER_CTL_TAEN;
	
  NVIC_EnableIRQ(ADC0SS2_IRQn);	
	NVIC_SetPriority(ADC0SS2_IRQn, 1);
 
	
	lcd_config_gpio();
	lcd_config_screen();	

  return;
}


/*******************************************************************************
* Function Name: tic_tac_toe_game_init
********************************************************************************
*******************************************************************************/
void tic_tac_toe_game_init(TTT_SQUARE_STATUS_t active_player)
{

  // Modify this function as needed.  The code below is used only to show you how to draw the
  // lines for the Tic Tac Toe board.
  int i, j;
	piecesInPlay = 0, pressed = 0;
	isX = active_player == X_ENTRY;
	curr_x = 1, curr_y = 1;
	
	//Clear board to not set
  for(i = 0; i < sizeof(board)/sizeof(board[0]); i++){
    for(j = 0; j < sizeof(board[i])/sizeof(board[i][0]); j++){
      board[i][j] = 'N';
    }
  }
	//clear the point sums
  for(i = 0; i < sizeof(score)/sizeof(score[0]); i++){
    score[i] = 0;
  }
	
	//clear the screen
  lcd_clear_screen(LCD_COLOR_BLACK);

  // Horizontal Lines (Uncomment to draw lines)
  lcd_draw_rectangle_centered(SCREEN_CENTER_X, LINE_LENGTH, UPPER_HORIZONTAL_LINE_Y,LINE_WIDTH,LCD_COLOR_BLUE);
  lcd_draw_rectangle_centered(SCREEN_CENTER_X,LINE_LENGTH,LOWER_HORIZONTAL_LINE_Y,LINE_WIDTH,LCD_COLOR_BLUE);

  //Vertical Lines (Uncomment to draw lines)
  lcd_draw_rectangle_centered(LEFT_HORIZONTAL_LINE_X,LINE_WIDTH, SCREEN_CENTER_Y,LINE_LENGTH,LCD_COLOR_BLUE);
  lcd_draw_rectangle_centered(RIGHT_HORIZONTAL_LINE_X,LINE_WIDTH,SCREEN_CENTER_Y,LINE_LENGTH,LCD_COLOR_BLUE);

  tic_tac_toe_update_game_board(PS2_DIR_INIT);

}


/*******************************************************************************
* Function Name: tic_tac_toe_update_game_board.
********************************************************************************
*******************************************************************************/
void tic_tac_toe_update_game_board(PS2_DIR_t direction)
{
	int past_x = curr_x, past_y = curr_y;
	
	//check if x and y are within bounds and add or subtract one
	switch(direction){
		case PS2_DIR_UP:
			curr_y = curr_y == 0 ? curr_y : --curr_y;
			break;
 		case PS2_DIR_DOWN:
			curr_y = curr_y == 2 ? curr_y : ++curr_y;
			break;
 		case PS2_DIR_LEFT:
			curr_x = curr_x == 0 ? curr_x : --curr_x;
			break;
 		case PS2_DIR_RIGHT:
			curr_x = curr_x == 2 ? curr_x : ++curr_x;
			break;
		case PS2_DIR_INIT:
			curr_x = 1, curr_y = 1;
			break;
 		default:
			return;
	}
	update_game(past_x, past_y);
  return;
}


void update_game(int past_x, int past_y){
	//reset the past square
	lcd_draw_rectangle_centered(xloc[past_x],SQUARE_SIZE, yloc[past_y],SQUARE_SIZE,FG_COLOR_UNCLAIMED);
	
	if(board[past_y][past_x] == 'X'){
		lcd_draw_image(xloc[past_x], X_WIDTH, yloc[past_y], X_HEIGHT, Bitmaps_X, FG_COLOR_X, BG_COLOR_X);
	} else if(board[past_y][past_x] == 'O'){
		lcd_draw_image(xloc[past_x], O_WIDTH, yloc[past_y], O_HEIGHT, Bitmaps_O, FG_COLOR_O, BG_COLOR_O);
	}
	
	//update the current square to match specifications
	lcd_draw_rectangle_centered(xloc[curr_x],SQUARE_SIZE, yloc[curr_y],SQUARE_SIZE, LCD_COLOR_BLACK);
	
	if(board[curr_y][curr_x] == 'N'){
		lcd_draw_rectangle_centered(xloc[curr_x],SQUARE_SIZE, yloc[curr_y],SQUARE_SIZE,BG_COLOR_UNCLAIMED);
		if(isX){
			lcd_draw_image(xloc[curr_x], X_WIDTH, yloc[curr_y], X_HEIGHT, Bitmaps_X, BG_COLOR_X, BG_COLOR_UNCLAIMED);
		}else{
			lcd_draw_image(xloc[curr_x], O_WIDTH, yloc[curr_y], O_HEIGHT, Bitmaps_O, BG_COLOR_O, BG_COLOR_UNCLAIMED);
		}
	} else {
		lcd_draw_rectangle_centered(xloc[curr_x],SQUARE_SIZE, yloc[curr_y],SQUARE_SIZE,BG_COLOR_CLAIMED);
		if(board[curr_y][curr_x] == 'X'){
			lcd_draw_image(xloc[curr_x], X_WIDTH, yloc[curr_y], X_HEIGHT, Bitmaps_X, BG_COLOR_X, BG_COLOR_CLAIMED);
		}else{
			lcd_draw_image(xloc[curr_x], O_WIDTH, yloc[curr_y], O_HEIGHT, Bitmaps_O, BG_COLOR_O, BG_COLOR_CLAIMED);
		}
	}	
}


/*******************************************************************************
* Function Name: tic_tac_toe_check_for_win
********************************************************************************
*******************************************************************************/
TTT_GAME_STATUS_t tic_tac_toe_check_for_win(void)
{
  int i;
  for(i = 0; i < sizeof(score)/sizeof(score[0]); i++){
    if(score[i] == 3){
      return X_WINNER;
    }
    if(score[i] == -3){
      return O_WINNER;
    }
  }

  if(piecesInPlay != 9){
    return ONGOING;
  } else{
    return TIE;
  }
}

/*******************************************************************************
* Function Name: tic_tac_toe_sw2_pressed
********************************************************************************
*******************************************************************************/
bool tic_tac_toe_sw2_pressed(void)
{
	// 8 round debouncer
	return (pressed = (GPIOF->DATA & SW2_M) == 0 ? ++pressed : 0) == 8;
}

/*******************************************************************************
* Function Name: tic_tac_toe_return_direction.
********************************************************************************
*******************************************************************************/
PS2_DIR_t tic_tac_toe_return_direction(uint16_t ps2_x, uint16_t ps2_y)
{
  if((ps2_x <= PS2_HIGH && ps2_x >= PS2_LOW) && (ps2_y <= PS2_HIGH && ps2_y >= PS2_LOW)){
    return PS2_DIR_CENTER;
  }
  if(ps2_y > PS2_HIGH){
    return PS2_DIR_UP;
  }
  if(ps2_y < PS2_LOW){
    return PS2_DIR_DOWN;
  }
  if(ps2_x < PS2_HIGH){
    return PS2_DIR_RIGHT;
  }
  if(ps2_x > PS2_LOW){
    return PS2_DIR_LEFT;
  }
  return PS2_DIR_CENTER;
}


/*******************************************************************************
* Function Name: tic_tac_toe_claim_square
********************************************************************************
*******************************************************************************/
void tic_tac_toe_claim_square(void)
{
  if(board[curr_y][curr_x] == 'N'){
    board[curr_y][curr_x] = isX ? 'X' : 'O';
    score[curr_y] += isX ? 1 : -1;
    score[curr_x + 3] += isX ? 1 : -1;
    if(curr_x == curr_y){
      score[6] += isX ? 1 : -1;
    }
    if(curr_x + curr_y == 2){
      score[7] += isX ? 1 : -1;
    }
    piecesInPlay++;
		claimSquare();
		isX = !isX;
  }
  return;
}

void claimSquare(void){
		
	lcd_draw_rectangle_centered(xloc[curr_x],SQUARE_SIZE, yloc[curr_y],SQUARE_SIZE, LCD_COLOR_BLACK);
	
	if(board[curr_y][curr_x] == 'X'){
		lcd_draw_image(xloc[curr_x], X_WIDTH, yloc[curr_y], X_HEIGHT, Bitmaps_X, FG_COLOR_X, BG_COLOR_X);
	} else if(board[curr_y][curr_x] == 'O'){
		lcd_draw_image(xloc[curr_x], O_WIDTH, yloc[curr_y], O_HEIGHT, Bitmaps_O, FG_COLOR_O, BG_COLOR_O);
	}
	
}

/*******************************************************************************
* Function Name: tic_tac_toe_sample_ready
********************************************************************************
*******************************************************************************/
bool tic_tac_toe_sample_ready(void)
{	
	if (ALERT_SAMPLE){
		ALERT_SAMPLE = false;
		return true;
	}	
  return ALERT_SAMPLE;
}

void TIMER5A_Handler(void)
{
	ADC0_Type *myADC;
	
	myADC = (ADC0_Type *) ADC0_BASE;
	
	myADC->SSMUX2 = (PS2_Y_ADC_CHANNEL << 4) | PS2_X_ADC_CHANNEL;
	
	myADC->ACTSS |= ADC_ACTSS_ASEN2;
	
	// Start the next ADC sample sequencers
	ADC0->PSSI |=   ADC_PSSI_SS2;

	// Clear the interrupt
	TIMER5->ICR |= TIMER_ICR_TATOCINT;
	
}

void ADC0SS2_Handler(void)
{	
  ALERT_SAMPLE = true;
  X_Val = ADC0 -> SSFIFO2 & 0xFFF;
  Y_Val = ADC0 -> SSFIFO2 & 0xFFF;
  ADC0 -> ISC |= ADC_ISC_IN2;
}
