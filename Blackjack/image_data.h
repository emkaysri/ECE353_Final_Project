#ifndef __IMAGE_DATA_H__
#define __IMAGE_DATA_H__

#include <stdint.h>

struct FONT_CHAR_INFO {
	uint16_t width;
	uint16_t position; 
};

extern const uint8_t spadeBitmap[];
extern const uint8_t spadeWidthPages;
extern const uint8_t spadeHeightPixels;

extern const uint8_t heartBitmap[];
extern const uint8_t heartWidthPages;
extern const uint8_t heartHeightPixels;

extern const uint8_t diamondBitmap[];
extern const uint8_t diamondWidthPages;
extern const uint8_t diamondHeightPixels;

extern const uint8_t clubBitmap[];
extern const uint8_t clubWidthPages;
extern const uint8_t clubHeightPixels;

extern const uint8_t cardBackBitmap[];
extern const uint8_t cardBackWidthPages;
extern const uint8_t cardBackHeightPixels;

extern const uint8_t cardBorderBitmap[];
extern const uint8_t cardBorderWidthPages;
extern const uint8_t cardBorderHeightPixels;

extern const uint8_t calibri_10ptBitmap[];

extern const uint8_t microsoftSansSerif_8ptBitmaps[];

extern const struct FONT_CHAR_INFO microsoftSansSerif_8ptDescriptors[];



#endif
