#include "graphics.h"
#include "math.h"

uint16_t defaultColor = LCD_COLOR_BLACK; 

uint16_t defaultBackgroundColor = LCD_COLOR_WHITE; 



enum PLAYER_SELECT player_select_state = PLAYER_ONE_SELECT ; 

int distanceAbs(struct POINT a , struct POINT b) {
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) ;
}

const EVENT_DATA * global_event_data;

void graphics_init_data (EVENT_DATA * event_data) {
	global_event_data = event_data;
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

	drawRect(x + 5, x + controlOptionsWidth, y + 5, y + controlOptionsHieght, LCD_COLOR_BLACK);
	
	drawRect(x + 10, x + controlOptionsWidth - 5, y + 10, y + controlOptionsHieght - 5, LCD_COLOR_WHITE);
	
	//lcd_draw_rectangle_centered (x + xPos-5, 3, y + 14, 3, LCD_COLOR_WHITE);
	
	//controlOptionsHieght-=20;
	
	drawStringSelectedAndCentered("HIT", x + controlOptionsWidth/2, y + 20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	y+=controlOptionsHieght/3;
	
	drawStringCentered("STAND", x + controlOptionsWidth/2, y + 15, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	y+=controlOptionsHieght/3;
	
	drawStringCentered("SPLIT", x + controlOptionsWidth/2, y + 15, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
}

void drawBettingOptions(int x, int y, int width, int height) {
	
	drawString("TOTAL $1000", x , y + 10, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	drawString("BET $500", x , y + 20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	drawStringSelected("INCREASE BET", x , y + 40, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	drawString("DECREASE BET", x , y + 60, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
}

void drawDealer(int x, int y, int width, int height) {
	int increment = 15;
	
	
		
	struct POINT dealerCardOne; 
	struct POINT dealerCardTwo; 
	
	height-=30;
	
	dealerCardOne.x = x+increment;
	dealerCardOne.y = y + height - increment;
	
	dealerCardTwo.x = x+increment*2;
	dealerCardTwo.y = y + height - increment*2;
	
	drawString("DEALER HAND", x , y + 10, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	drawCard(dealerCardOne.x, dealerCardOne.y, 1, 1, 0);
	drawCard(dealerCardTwo.x, dealerCardTwo.y, 1, 1, 3);
	
	
}

void drawPlayer(int x, int y, int width, int height) {
	int increment = 15;
	struct POINT playerCardOne; 
	struct POINT playerCardTwo; 
	struct POINT playerCardThree; 
	
	height-=30;
	
	playerCardOne.x = x+increment;
	playerCardOne.y = y + height - increment;
	
	playerCardTwo.x = x+increment*2;
	playerCardTwo.y = y + height - increment*2;
	
	playerCardThree.x = x+increment*3;
	playerCardThree.y = y + height - increment*3;
	
	drawStringCentered("YOUR HAND", x +30 , y + height + 20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	drawCard(playerCardOne.x, playerCardOne.y, 1, 1, 0);
	drawCard(playerCardTwo.x, playerCardTwo.y, 1, 2, 1);
	drawCard(playerCardThree.x, playerCardThree.y, 1, 1, 3);
}

void drawGameState(int x, int y, int width, int height) {
	drawString("WAIT FOR OTHER PLAYER TO PLAY", x , y + 10, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
}


int drawGameScreenOutLineAndData() {
	
	int lineWidth = 4;
	
	int controlAreaWidth = 50;
	int controlAreaHeight = 70;

	
	int controlColumn;
	
	// Player Area
	drawPlayer(25, (uint16_t)(0.4*ROWS), COLS, (uint16_t)(0.6*ROWS)-50);
	drawBlackjackControlOptions((uint16_t)(0.75*COLS)-15, (uint16_t)(0.4*ROWS),(uint16_t)(0.25*COLS),85 ) ; 
	
	
	// Dealer Area
	
	drawDealer((uint16_t)(0.4*COLS)+10, 0, (uint16_t)(0.6*COLS)-10, (uint16_t)(0.4*ROWS));
	// Controls Areas
	drawRect(0, (uint16_t)(0.4*COLS), 0, (uint16_t)(0.3*ROWS), LCD_COLOR_BLACK);
	drawRect(0, (uint16_t)(0.4*COLS)-4, 0, (uint16_t)(0.3*ROWS)-4, LCD_COLOR_WHITE);
	
	
	drawRect(0,COLS, ROWS-50, ROWS-45, LCD_COLOR_BLACK);
	drawBettingOptions(10, 0, (uint16_t)(0.4*COLS), (uint16_t)(0.4*ROWS)); 
	
	
	// Game state
	
	drawGameState(25, ROWS-50, COLS, 50);
	
	

	return 0;
}


int drawHomeScreen(float theta) {
	int y = ROWS/2;
	int r = 80;
	struct POINT cap_touch_event;
	struct POINT Player2Disp = {COLS/2 - 40, ROWS-30} ; 
	struct POINT Player1Disp = {COLS/2 + 40 , ROWS-30} ;
	LAST_CAP_TOUCH_EVENT eventData = global_event_data->capTouchEvent ; 

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
		player_select_state = PLAYER_TWO_SELECT;
	} else if ( distanceAbs(cap_touch_event , Player1Disp) < CAP_TOUCH_TOLERANCE_SQRD ) {
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
		default:
			return -1;
	}


	drawStringCentered("TOUCH TO SELECT", COLS/2 , ROWS-10, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	
	return 0;
	
}




