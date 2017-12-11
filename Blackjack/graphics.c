#include "graphics.h"

#define SUIT_WIDTH 2*8
#define SUIT_HEIGHT 15

#define VAL_WIDTH 8
#define VAL_HEIGHT 9

uint16_t defaultColor = LCD_COLOR_BLACK; 

uint16_t defaultBackgroundColor = LCD_COLOR_WHITE; 



void clear(){
	lcd_clear_screen(defaultBackgroundColor) ; 
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
void drawString(char * inputString, int x, int y, uint16_t color) {
	
	while (*inputString != 0) {
			int charNumber = -1;
			int charWidth;
			int charHeight = 10;
			char currentChar = *inputString;
			
			// Lower case letters
			if (currentChar >= 97 && currentChar <= 122) {
				charNumber = currentChar - 97;
			} else if (currentChar >= 65 && currentChar <= 90) {
			// Upper case letters
				charNumber = currentChar - 65;
			} else if (currentChar == 32){
				// Space
				charNumber = -1;
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
				
				lcd_draw_image(xCalc, charWidth, yCalc, charHeight, microsoftSansSerif_8ptBitmaps+bitmapOffset, color, LCD_COLOR_WHITE);
	
				// Increment x
				x+=charWidth+1; 
			}
		
			inputString++; 
	}
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


int drawCard(int x, int y, CARD_VALUE val, CARD_SUIT suit) {
	int valIndex = 0 ; 
	uint16_t foregroundColor; 
	
	uint8_t * suitPointer ;
	int valOffset ;
	
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

