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

