#include "graphics.h"


uint16_t defaultColor = LCD_COLOR_BLACK; 

uint16_t defaultBackgroundColor = LCD_COLOR_WHITE; 



enum PLAYER_SELECT player_select_state = NONE ; 

int distanceAbs(struct POINT a , struct POINT b) {
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) ;
}





void clear(){
	lcd_clear_screen(defaultBackgroundColor) ; 
}

// Draw rectangle given the corners
void drawRect(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t color) {
	int xAbs;
	int yAbs;
	
	if (x2 > x1) {
		xAbs = x2 - x1;
	} else {
		xAbs = x1 - x2;
	}
	
	if (y2 > y1) {
		yAbs = y2 - y1;
	} else {
		yAbs = y1 - y2;
	}
	
	lcd_draw_rectangle_centered ((x1 + x2)/2, xAbs, (y1 + y2)/2, yAbs, color);
}

const int x_offset = 8 ;
const int y_offset = 15;


/* Display arbitrary null terminated string starting at x,y specified
	x  -	Starting x position of string
	y	 -	Bottom of position of string

	Will draw off screen if string is too large

	Only draws upper case letters
	Sets erronous characters to X
*/
void drawString(char * inputString, int x, int y, uint16_t color, uint16_t colorBackground) {
	
	while (*inputString != 0) {
			int charNumber = -1;
			int charWidth;
			int charHeight = 10;
			char currentChar = *inputString;
			
			// Lower case letters
			if (currentChar >= 97 && currentChar <= 122) {
				charNumber = currentChar - 86;
			} else if (currentChar >= 65 && currentChar <= 90) {
			// Upper case letters
				charNumber = currentChar - 54;
			} else if (currentChar >= 48 && currentChar <= 57){
				// Numbers
				charNumber = currentChar - 47;
			} else if (currentChar == 32){
				// Space
				charNumber = -1;
			} else if (currentChar == 36){
				// $ to zero
				charNumber = 0;
			} else {
				// Erronous characters to an X
				charNumber = 23;
			}
		
			if (charNumber == -1) {
				// Create a space with 2 pixel offset
				x+=3;
			} else {
				int xCalc;
				int yCalc; 
				int bitmapOffset = microsoftSansSerif_8ptDescriptors[charNumber].position;
				
				charWidth = microsoftSansSerif_8ptDescriptors[charNumber].width;
				// Center xClac
				xCalc = x + charWidth/2;
				
				// Center yCalc with text hieght of charHeight
				yCalc = y + charHeight/2;
				
				lcd_draw_image(xCalc, charWidth, yCalc, charHeight, microsoftSansSerif_8ptBitmaps+bitmapOffset, color, colorBackground);
	
				// Increment x
				x+=charWidth+1; 
			}
		
			inputString++; 
	}
}

int calcStringWidth(char * inputString) {
	int xLength = 0;	
	while (*inputString != 0) {
		int charNumber = -1;
		char currentChar = *inputString;
		
		// Lower case letters
			if (currentChar >= 97 && currentChar <= 122) {
				charNumber = currentChar - 86;
			} else if (currentChar >= 65 && currentChar <= 90) {
			// Upper case letters
				charNumber = currentChar - 54;
			} else if (currentChar >= 48 && currentChar <= 57){
				// Numbers
				charNumber = currentChar - 47;
			} else if (currentChar == 32){
				// Space
				charNumber = -1;
			} else if (currentChar == 36){
				// $ to zero
				charNumber = 0;
			} else {
				// Erronous characters to an X
				charNumber = 23;
			}
			
			if (charNumber == -1) {
				xLength += 3;
			} else {
				xLength += microsoftSansSerif_8ptDescriptors[charNumber].width;
			}
			xLength++;
			
			
			inputString++; 
		
	}
	
	return xLength; 
}

void drawStringCentered(char * inputString, int x, int y, uint16_t color, uint16_t colorBackground) {
	char * originalInput = inputString;
	
	int charHeight = 10;
	
	int xLength = calcStringWidth(inputString);
	
	drawString(originalInput,  x - xLength/2,  y - charHeight/2,  color,  colorBackground);
	
}

void drawStringSelected (char * inputString, int x, int y, uint16_t color, uint16_t colorBackground) {
	int stringWidth = calcStringWidth(inputString) ; 
	
	drawRect (x-4, x + stringWidth+4, y-4, y+10+4 , LCD_COLOR_RED);
	
	drawRect (x-2, x + stringWidth+2, y-2, y +12, colorBackground);
	
	drawString(inputString,  x,  y,  color, colorBackground) ;
}

void drawStringSelectedAndCentered(char * inputString, int x, int y, uint16_t color, uint16_t colorBackground) {
	
	int stringWidth = calcStringWidth(inputString) ; 
	
	lcd_draw_rectangle_centered (x, stringWidth+8, y, 18, LCD_COLOR_RED);
	
	lcd_draw_rectangle_centered (x, stringWidth+4, y, 14, colorBackground);
		
	drawStringCentered(inputString,  x,  y,  color, colorBackground) ; 
}



int drawTen(uint16_t foregroundColor, uint8_t * suitPointer, int x, int y)  {
	
	
	// Draw background
	
	lcd_draw_image(x, cardBorderWidthPages*8, y, cardBorderHeightPixels, cardBorderBitmap, defaultColor, LCD_COLOR_WHITE);
	
	// Draw values
	//1
	lcd_draw_image(x-x_offset-3, VAL_WIDTH, y-y_offset, VAL_HEIGHT, calibri_10ptBitmap+9, foregroundColor, LCD_COLOR_WHITE);
	//0
	lcd_draw_image(x-x_offset+3, VAL_WIDTH, y-y_offset, VAL_HEIGHT, calibri_10ptBitmap, foregroundColor, LCD_COLOR_WHITE);
	
	
	// Draw values
	//1
	lcd_draw_image(x+x_offset-3, VAL_WIDTH, y+y_offset, VAL_HEIGHT, calibri_10ptBitmap+9, foregroundColor, LCD_COLOR_WHITE);
	//0
	lcd_draw_image(x+x_offset+3, VAL_WIDTH, y+y_offset, VAL_HEIGHT, calibri_10ptBitmap, foregroundColor, LCD_COLOR_WHITE);
	
	// Draw suit
	
	lcd_draw_image(x, SUIT_WIDTH, y, SUIT_HEIGHT, suitPointer, foregroundColor, LCD_COLOR_WHITE);
	return 0 ; 
}

// state bit numbers
//			TRUE			FALSE
// bit 0 == normal / flipped
// bit 1 == selected / not selected
//
int drawCard(int x, int y, CARD_VALUE val, CARD_SUIT suit, int state) {
	int valIndex = 0 ; 
	uint16_t foregroundColor; 
	uint16_t defaultColor;
	
	uint8_t * suitPointer ;
	int valOffset ;
	
		
	if ((state & 0x2) == 1 ) {
		// selected
		defaultColor = LCD_COLOR_GREEN;
	} else {
		defaultColor = LCD_COLOR_BLACK;
	}
	
	if ((state & 0x1) == 0 ) {
		lcd_draw_image(x, cardBackWidthPages*8, y, cardBackHeightPixels, cardBackBitmap, defaultColor, LCD_COLOR_WHITE);
		return 0; 
	}

	switch(suit) {
		case SPADES:
			suitPointer = (uint8_t *)spadeBitmap ; 
			foregroundColor = LCD_COLOR_BLACK;
			break;
		case CLUBS:
			suitPointer = (uint8_t *)clubBitmap ; 
			foregroundColor = LCD_COLOR_BLACK;
			break;
		case HEARTS:
			suitPointer = (uint8_t *)heartBitmap;
			foregroundColor = LCD_COLOR_RED;
			break;
		case DIAMONDS:
			suitPointer = (uint8_t *)diamondBitmap;
			foregroundColor = LCD_COLOR_RED;
			break;
		default:
			return -1; // Return on error
	}
	
	switch(val) {
		case ACE:
			valOffset = 90 ; 
			break;
		case TEN:
			return drawTen(foregroundColor,suitPointer, x, y); // ten is a bitch, handle it in another function
		case JACK:
			valOffset = 99 ; 
			break;
		case QUEEN:
			valOffset = 117 ; 
			break;
		case KING:
			valOffset = 108 ; 
			break;
		default:
			valOffset = (val+1)*9;
			break;
	}
	
	// Draw background
	
	lcd_draw_image(x, cardBorderWidthPages*8, y, cardBorderHeightPixels, cardBorderBitmap, defaultColor, LCD_COLOR_WHITE);
	
	// Draw values

	lcd_draw_image(x-x_offset, VAL_WIDTH, y-y_offset, VAL_HEIGHT, calibri_10ptBitmap+valOffset, foregroundColor, LCD_COLOR_WHITE);
	
		
	lcd_draw_image(x+x_offset, VAL_WIDTH, y+y_offset, VAL_HEIGHT, calibri_10ptBitmap+valOffset, foregroundColor, LCD_COLOR_WHITE);
	
	
	// Draw suit
	
	lcd_draw_image(x, SUIT_WIDTH, y, SUIT_HEIGHT, suitPointer, foregroundColor, LCD_COLOR_WHITE);
	
	return 0;
}

void drawBlackjackControlOptions(int x, int y, int controlOptionsWidth, int controlOptionsHieght) {
	
	int xPos = controlOptionsWidth/2-10;

	//drawRect(x + 5, x + controlOptionsWidth, y + 5, y + controlOptionsHieght, LCD_COLOR_BLACK);
	
	//drawRect(x + 10, x + controlOptionsWidth - 5, y + 10, y + controlOptionsHieght - 5, LCD_COLOR_WHITE);
	
	//lcd_draw_rectangle_centered (x + xPos-5, 3, y + 14, 3, LCD_COLOR_WHITE);
	
	//controlOptionsHieght-=20;
	
	x+=controlOptionsWidth/2;
	y+=controlOptionsHieght/2;
	
	drawStringSelectedAndCentered("STAND", x , y + 20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	drawStringSelectedAndCentered("HIT", x - 20 , y , LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	drawStringSelectedAndCentered("SPLIT", x , y - 20 , LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
}


void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}  

/* itoa:  convert n to characters in s */
 void itoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}  

void drawBettingOptions(int x, int y, int width, int height) {
	
	
	char totalMoney[50] = "TOTAL$";
	char betMoney[50] = "BET $";
	
	char number[10];
	drawRect(x, x+60,y, y +40, LCD_COLOR_WHITE);
	itoa(global_game_state_data.playerOneMoney,number);
	
	strcat(totalMoney, number);
	 
	drawString(totalMoney, x , y + 10, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;


	itoa(global_game_state_data.playerOneBet,number);
	
	strcat(betMoney, number);	
	
	drawString(betMoney, x , y + 20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	drawStringSelected("INCREASE BET", x , y + 40, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	drawStringSelected("DECREASE BET", x , y + 60, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
}

void drawDealer(int x, int y, int width, int height, bool reveal) {
	int increment = 15;
	
	int i = 0 ;
	struct POINT dealerCards[5];
	for (i = 0 ; i<5;i++) {
		dealerCards[i].x = x+increment*i;
		dealerCards[i].y = y + height - increment*i;
	}
	
	height-=30;
	
	drawString("DEALER HAND", x , y + 10, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	if(reveal){
		i = 0;
	} else{
		drawCard(dealerCards[i].x, dealerCards[i].y, dealerHand[i] % 13, dealerHand[i] / 13, 0);
		i = 1;
	}
	for (; i<dealerNumCards;i++) {
		drawCard(dealerCards[i].x, dealerCards[i].y, dealerHand[i]%13, dealerHand[i]/13, 3);
	}
	
	
}

void drawPlayer(int x, int y, int width, int height) {
	int increment = 12;
	int i;
	struct POINT playerCards[2][5]; 
	
	height-=30;
	
	for (i = 0 ; i<5;i++) {
		playerCards[0][i].x = x+increment*i;
		playerCards[0][i].y = y + height - increment*i;
	}
	x+=20;
	
	for (i = 0 ; i<5;i++) {
		playerCards[1][i].x = x+increment*i;
		playerCards[1][i].y = y + height - increment*i;
	}

	
	drawStringCentered("YOUR HAND", x +30 , y + height + 20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	for (i = 0 ; i<this_player.numCards[0];i++) {
		drawCard(playerCards[0][i].x, playerCards[0][i].y, this_player.hand[0][i]%13,this_player.hand[0][i]/13, 3);
	}
	
	for (i = 0 ; i<this_player.numCards[1];i++) {
		drawCard(playerCards[1][i].x, playerCards[1][i].y, this_player.hand[1][i]%13,this_player.hand[1][i]/13, 3);
	}

}

void drawGameState(int x, int y, int width, int height) {
	x+=width/2;
	y+=height/2;
	drawStringCentered("WAIT FOR OTHER PLAYER TO PLAY", x , y + 10, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	drawStringCentered("PRESS RIGHT BUTTON FOR CONTROL", x , y, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
}


int drawGameScreenOutLineAndData() {
	
	int lineWidth = 4;
	
	int controlAreaWidth = 50;
	int controlAreaHeight = 70;

	
	int controlColumn;
	
	// Player Area
	drawPlayer(25, (uint16_t)(0.4*ROWS), COLS, (uint16_t)(0.6*ROWS)-50);
	drawBlackjackControlOptions((uint16_t)(0.75*COLS)-15, (uint16_t)(0.6*ROWS),(uint16_t)(0.25*COLS),60 ) ; 
	
	
	// Dealer Area
	
	drawDealer((uint16_t)(0.4*COLS)+10, 0, (uint16_t)(0.6*COLS)-10, (uint16_t)(0.4*ROWS), false);
	// Controls Areas
	//drawRect(0, (uint16_t)(0.4*COLS), 0, (uint16_t)(0.3*ROWS), LCD_COLOR_BLACK);
	//drawRect(0, (uint16_t)(0.4*COLS)-4, 0, (uint16_t)(0.3*ROWS)-4, LCD_COLOR_WHITE);
	
	
	//drawRect(0,COLS, ROWS-50, ROWS-45, LCD_COLOR_BLACK);
	drawBettingOptions(10, 0, (uint16_t)(0.4*COLS), (uint16_t)(0.4*ROWS)); 
	
	
	// Game state
	
	drawGameState(0, ROWS-50, COLS, 50);
	
	

	return 0;
}


int drawHomeScreen(float theta) {
	int y = ROWS/2;
	int r = 80;
	struct POINT cap_touch_event;
	struct POINT Player2Disp = {COLS/2 - 40, ROWS-30} ; 
	struct POINT Player1Disp = {COLS/2 + 40 , ROWS-30} ;
	LAST_CAP_TOUCH_EVENT eventData = global_event_data.capTouchEvent ; 

	theta += 3.1419/100.0 ;	
	drawStringCentered("BLACKJACK", COLS/2 , ROWS/2, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	
	drawStringCentered("ECE 353", COLS/2 , ROWS/2+20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	
//	drawStringCentered("JOHN COMPAS", COLS/2+cos(theta)*r , ROWS/2+sin(theta)*r, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	theta+=(3.1419*(2.0/4.0));
	drawCard(COLS/2+cos(theta)*r , ROWS/2+sin(theta)*r, 0, 0, 3);
		theta+=(3.1419*(2.0/4.0));
//	drawStringCentered("JASON SYLVESTRE", COLS/2+cos(theta)*r , ROWS/2+sin(theta)*r, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	drawCard(COLS/2+cos(theta)*r , ROWS/2+sin(theta)*r, 0, 3, 3);
		theta+=(3.1419*(2.0/4.0));
//	drawStringCentered("SRINIDHI EMKAY", COLS/2+cos(theta)*r , ROWS/2+sin(theta)*r, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	drawCard(COLS/2+cos(theta)*r , ROWS/2+sin(theta)*r, 0, 1, 3);
		theta+=(3.1419*(2.0/4.0));
	
	drawCard(COLS/2+cos(theta)*r , ROWS/2+sin(theta)*r, 0, 2, 3);
	
	// update state
	
	cap_touch_event.x = eventData.x ;
	cap_touch_event.y = eventData.y ;
	
	if ( distanceAbs(cap_touch_event , Player2Disp) < CAP_TOUCH_TOLERANCE_SQRD ) {
		global_game_state_data.currentScreenState = GAME_SCREEN;
		clear();
		
		
		player_select_state = PLAYER_TWO_SELECT;
	} else if ( distanceAbs(cap_touch_event , Player1Disp) < CAP_TOUCH_TOLERANCE_SQRD ) {
		global_game_state_data.currentScreenState = GAME_SCREEN;
		clear();
		
	
		player_select_state = PLAYER_ONE_SELECT;
	}
	// cheat
	
	drawRect(0, Player2Disp.y - 8, COLS, Player2Disp.y + 8, LCD_COLOR_WHITE);
	
	switch(player_select_state) {
		case PLAYER_TWO_SELECT :
				drawStringSelectedAndCentered("2 PLAYER", Player2Disp.x, Player2Disp.y ,LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
				drawStringCentered("1 PLAYER",Player1Disp.x, Player1Disp.y , LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
				break;
		case PLAYER_ONE_SELECT :
				drawStringCentered("2 PLAYER", Player2Disp.x, Player2Disp.y ,LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
				drawStringSelectedAndCentered("1 PLAYER",Player1Disp.x, Player1Disp.y , LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
				break;
		case NONE :
				drawStringCentered("2 PLAYER", Player2Disp.x, Player2Disp.y ,LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
				drawStringCentered("1 PLAYER",Player1Disp.x, Player1Disp.y , LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
				break;
		default:
			return -1;
	}

	if (player_select_state==NONE) {
		drawStringCentered("TOUCH TO SELECT", COLS/2 , ROWS-10, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	}
	
	return 0;
	
}


int drawWirelessSearchScreen(float theta) {
	int y = ROWS/2;
	int r = 80;
	
	theta+=(3.1419*(2.0/4.0));
	lcd_draw_rectangle_centered(COLS/2+cos(theta)*r , ROWS/2+sin(theta)*r, 0, 0, 3);
		theta+=(3.1419*(2.0/4.0));
//	drawStringCentered("JASON SYLVESTRE", COLS/2+cos(theta)*r , ROWS/2+sin(theta)*r, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	lcd_draw_rectangle_centered(COLS/2+cos(theta)*r , ROWS/2+sin(theta)*r, 0, 3, 3);
		theta+=(3.1419*(2.0/4.0));
//	drawStringCentered("SRINIDHI EMKAY", COLS/2+cos(theta)*r , ROWS/2+sin(theta)*r, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	lcd_draw_rectangle_centered(COLS/2+cos(theta)*r , ROWS/2+sin(theta)*r, 0, 1, 3);
		theta+=(3.1419*(2.0/4.0));
}

int drawControls() {
	drawStringCentered("MOVE JOYSTICK UP AND DOWN", COLS/2 , 60, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	drawStringCentered("TO INCREASE AND DECREASE", COLS/2 , 70, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	drawStringCentered("BET AMOUNT", COLS/2 , 80, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	
	
	drawStringCentered("LEFT BUTTON IS HIT", COLS/2 , 100, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	drawStringCentered("UP IS SPLIT", COLS/2 , 110, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	drawStringCentered("DOWN IS STAND", COLS/2 , 120, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
}

int drawEndGame() {
	int x = ROWS/2;
	int y = COLS/2;

	
	
	if (global_game_state_data.playerOneWin == 1) {
	char totalMoney[50] = "YOU HAVE$";
	char betMoney[50] = "YOU WON $";
	
	char number[10];
	clear();
		drawStringCentered("CONGRATS", COLS/2 , y-20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	itoa(global_game_state_data.playerOneMoney,number);
	
	strcat(totalMoney, number);
	 
	drawString(totalMoney, x , y + 10, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;


	itoa(global_game_state_data.playerOneBet,number);
	
	strcat(betMoney, number);	
	
	drawString(betMoney, x , y + 20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
		

	} else {
		
		
			char totalMoney[50] = "YOU HAVE $";
	char betMoney[50] = "YOU LOST $";
	
	char number[10];
	clear();
		drawStringCentered("YOU LOST", COLS/2 , y-20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	itoa(global_game_state_data.playerOneMoney,number);
	
	strcat(totalMoney, number);
	 
	drawString(totalMoney, x , y + 10, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;


	itoa(global_game_state_data.playerOneBet,number);
	
	strcat(betMoney, number);	
	
	drawString(betMoney, x , y + 20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	}
	
	drawStringCentered("PRESS SCREEN TO CONTINUE", COLS/2 , y-20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	
	if (global_event_data.capTouchEvent.valid) {
		global_game_state_data.currentScreenState = RESET;
	}
}

static float theta = 3.1419/2;

SCREEN_STATE prev_state;

int draw() {
	

	if (prev_state!=global_game_state_data.currentScreenState) {
		clear();
		prev_state = global_game_state_data.currentScreenState; 
	}
	

	
	switch(global_game_state_data.currentScreenState) {
		case START_SCREEN:
			drawHomeScreen(theta);
			theta +=0.04;
			break;
		case GAME_SCREEN:
			drawGameScreenOutLineAndData();
			break;
		case CONTROLS:
			drawControls();
			break;
		case END_GAME:
			drawEndGame();
			break;
		default:
			drawStringCentered("DRAW STATE ERROR", COLS/2 , ROWS/2, LCD_COLOR_RED,LCD_COLOR_WHITE) ;
			return -1;
	}
}




