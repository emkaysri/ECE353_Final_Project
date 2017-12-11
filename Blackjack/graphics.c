#include "graphics.h"
#include "math.h"

#define SUIT_WIDTH 2*8
#define SUIT_HEIGHT 15

#define VAL_WIDTH 8
#define VAL_HEIGHT 9

uint16_t defaultColor = LCD_COLOR_BLACK; 

uint16_t defaultBackgroundColor = LCD_COLOR_WHITE; 

struct POINT {
	uint16_t x;
	uint16_t y;
};




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

void drawStringSelectedAndCentered(char * inputString, int x, int y, uint16_t color, uint16_t colorBackground) {
	
	int stringWidth = calcStringWidth(inputString) ; 
	
	lcd_draw_rectangle_centered (x, stringWidth+18, y, 14, LCD_COLOR_RED);
	
	lcd_draw_rectangle_centered (x, stringWidth+16, y, 12, colorBackground);
		
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
	
	lcd_draw_rectangle_centered (x + xPos-5, 3, y + 14, 3, LCD_COLOR_WHITE);
	
	drawStringSelectedAndCentered("HIT", x + xPos, y + 10, LCD_COLOR_WHITE,LCD_COLOR_BLACK) ; 
	
	y+=controlOptionsHieght/3;
	
	drawString("STAND", x + xPos, y + 10, LCD_COLOR_WHITE,LCD_COLOR_BLACK) ; 
	
	y+=controlOptionsHieght/3;
	
	drawString("SPLIT", x + xPos, y + 10, LCD_COLOR_WHITE,LCD_COLOR_BLACK) ; 
}

void drawBettingOptions(int x, int y, int width, int height) {
	
	drawString("CURRENT $", x , y + 10, LCD_COLOR_WHITE,LCD_COLOR_BLACK) ; 
	
	drawString("BET $500", x , y + 10, LCD_COLOR_WHITE,LCD_COLOR_BLACK) ; 
	
}

void drawDealer(int x, int y, int width, int height) {
	
	drawString("DEALER", x , y + 10, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
}

void drawPlayer(int x, int y, int width, int height) {
	int increment = 20;
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
	
	drawString("YOUR HAND", x , y + 10, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ; 
	
	drawCard(playerCardOne.x, playerCardOne.y, 1, 1, 0);
	drawCard(playerCardTwo.x, playerCardTwo.y, 1, 2, 1);
	drawCard(playerCardThree.x, playerCardThree.y, 1, 1, 3);
	
}



int drawGameScreenOutLineAndData() {
	
	int lineWidth = 4;
	
	int controlAreaWidth = 50;
	int controlAreaHeight = 70;

	
	int controlColumn;
	
	// Player Area
	drawRect(0, COLS, (uint16_t)(0.4*ROWS), (uint16_t)(0.4*ROWS) + lineWidth, LCD_COLOR_BLACK);
	drawPlayer(5, (uint16_t)(0.4*ROWS), COLS, (uint16_t)(0.6*ROWS));
	
	// Dealer Area
	drawRect((uint16_t)(0.4*COLS), (uint16_t)(0.4*COLS) + lineWidth, 0, (uint16_t)(0.4*ROWS), LCD_COLOR_BLACK);
	drawDealer((uint16_t)(0.4*COLS), 0, (uint16_t)(0.6*COLS), (uint16_t)(0.4*ROWS));
	// Controls Areas
	
	drawBlackjackControlOptions((uint16_t)(0.75*COLS), (uint16_t)(0.4*ROWS),(uint16_t)(0.25*COLS),70 ) ; 
	
	drawBettingOptions(0, 0, (uint16_t)(0.4*COLS), (uint16_t)(0.4*ROWS)); 
	

	return 0;
}


int drawHomeScreen(float theta) {
	int y = ROWS/2;
	int r = 80;
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

	//drawCard(playerCardTwo.x, playerCardTwo.y, 1, 2, 1);
	
	//drawCard(playerCardTwo.x, playerCardTwo.y, 1, 2, 1);
	
	
	drawStringSelectedAndCentered("2 PLAYER", COLS/2 , ROWS-40, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	drawStringCentered("1 PLAYER", COLS/2 , ROWS-20, LCD_COLOR_BLACK,LCD_COLOR_WHITE) ;
	
	return 0;
	
}




