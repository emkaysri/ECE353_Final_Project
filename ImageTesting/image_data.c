#include "image_data.h"

// 
//  Font data for Calibri 10pt
// 

// Character bitmaps for Calibri 10pt
const uint8_t calibri_10ptBitmap[] = 
{
	// @0 '0' (6 pixels wide)
	0x78, //  #### 
	0xCC, // ##  ##
	0xCC, // ##  ##
	0xCC, // ##  ##
	0xCC, // ##  ##
	0xCC, // ##  ##
	0xCC, // ##  ##
	0x78, //  #### 
	0x00, //       

	// @9 '1' (6 pixels wide)
	0x30, //   ##  
	0x70, //  ###  
	0xB0, // # ##  
	0x30, //   ##  
	0x30, //   ##  
	0x30, //   ##  
	0x30, //   ##  
	0xFC, // ######
	0x00, //       

	// @18 '2' (6 pixels wide)
	0x78, //  #### 
	0x8C, // #   ##
	0x0C, //     ##
	0x0C, //     ##
	0x18, //    ## 
	0x30, //   ##  
	0x60, //  ##   
	0xFC, // ######
	0x00, //       

	// @27 '3' (6 pixels wide)
	0x78, //  #### 
	0x8C, // #   ##
	0x0C, //     ##
	0x78, //  #### 
	0x0C, //     ##
	0x0C, //     ##
	0x8C, // #   ##
	0x78, //  #### 
	0x00, //       

	// @36 '4' (6 pixels wide)
	0x38, //   ### 
	0x38, //   ### 
	0x58, //  # ## 
	0x58, //  # ## 
	0x98, // #  ## 
	0xFC, // ######
	0x18, //    ## 
	0x18, //    ## 
	0x00, //       

	// @45 '5' (6 pixels wide)
	0xFC, // ######
	0xC0, // ##    
	0xC0, // ##    
	0xF8, // ##### 
	0x0C, //     ##
	0x0C, //     ##
	0x8C, // #   ##
	0x78, //  #### 
	0x00, //       

	// @54 '6' (6 pixels wide)
	0x38, //   ### 
	0x60, //  ##   
	0xC0, // ##    
	0xF8, // ##### 
	0xCC, // ##  ##
	0xCC, // ##  ##
	0xCC, // ##  ##
	0x78, //  #### 
	0x00, //       

	// @63 '7' (6 pixels wide)
	0xFC, // ######
	0x0C, //     ##
	0x18, //    ## 
	0x18, //    ## 
	0x30, //   ##  
	0x30, //   ##  
	0x60, //  ##   
	0x60, //  ##   
	0x00, //       

	// @72 '8' (6 pixels wide)
	0x78, //  #### 
	0xCC, // ##  ##
	0xCC, // ##  ##
	0x78, //  #### 
	0xCC, // ##  ##
	0xCC, // ##  ##
	0xCC, // ##  ##
	0x78, //  #### 
	0x00, //       

	// @81 '9' (6 pixels wide)
	0x78, //  #### 
	0xCC, // ##  ##
	0xCC, // ##  ##
	0xCC, // ##  ##
	0x7C, //  #####
	0x0C, //     ##
	0x18, //    ## 
	0xF0, // ####  
	0x00, //       

	// @90 'A' (7 pixels wide)
	0x38, //   ###  
	0x38, //   ###  
	0x6C, //  ## ## 
	0x6C, //  ## ## 
	0x6C, //  ## ## 
	0xFE, // #######
	0xC6, // ##   ##
	0xC6, // ##   ##
	0x00, //        

	// @99 'J' (4 pixels wide)
	0x30, //   ##
	0x30, //   ##
	0x30, //   ##
	0x30, //   ##
	0x30, //   ##
	0x30, //   ##
	0x30, //   ##
	0xE0, // ### 
	0x00, //     

	// @108 'K' (6 pixels wide)
	0xCC, // ##  ##
	0xD8, // ## ## 
	0xD8, // ## ## 
	0xF0, // ####  
	0xF0, // ####  
	0xD8, // ## ## 
	0xD8, // ## ## 
	0xCC, // ##  ##
	0x00, //       

	// @117 'Q' (8 pixels wide)
	0x7C, //  #####  
	0xC6, // ##   ## 
	0xC6, // ##   ## 
	0xC6, // ##   ## 
	0xC6, // ##   ## 
	0xC6, // ##   ## 
	0xC6, // ##   ## 
	0x7C, //  #####  
	0x03, //       ##
};


struct FONT_CHAR_INFO{
	int width;
	int startIndex; 
} ; 
// Character descriptors for Calibri 10pt
// { [Char width in bits], [Offset into calibri_10ptCharBitmaps in bytes] }
const struct FONT_CHAR_INFO calibri_10ptDescriptors[] = 
{
	{6, 0}, 		// 0 
	{6, 9}, 		// 1 
	{6, 18}, 		// 2 
	{6, 27}, 		// 3 
	{6, 36}, 		// 4 
	{6, 45}, 		// 5 
	{6, 54}, 		// 6 
	{6, 63}, 		// 7 
	{6, 72}, 		// 8 
	{6, 81}, 		// 9 
	{7, 90}, 		// A 
	{4, 99}, 		// J 
	{6, 108}, 		// K 
	{8, 117}, 		// Q 
};

/* 
**  Image data for spade
*/

const uint8_t spadeBitmap[] =
{
	0x01, 0x00, //        #       
	0x03, 0x80, //       ###      
	0x07, 0xC0, //      #####     
	0x0F, 0xE0, //     #######    
	0x1F, 0xF0, //    #########   
	0x3F, 0xF8, //   ###########  
	0x7F, 0xFC, //  ############# 
	0x7F, 0xFC, //  ############# 
	0xFF, 0xFE, // ###############
	0xFF, 0xFE, // ###############
	0xFF, 0xFE, // ###############
	0xFD, 0x7E, // ###### # ######
	0x79, 0x3C, //  ####  #  #### 
	0x03, 0x80, //       ###      
	0x07, 0xC0, //      #####     
};

/* Bitmap sizes for spade */
const uint8_t  spadeWidthPages = 2;
const uint8_t  spadeHeightPixels = 15;


// 
//  Image data for heart
// 

const uint8_t heartBitmap[] =
{
	0x3C, 0x78, //   ####   ####  
	0x7E, 0xFC, //  ###### ###### 
	0xFE, 0xFE, // ####### #######
	0xFF, 0xFE, // ###############
	0xFF, 0xFE, // ###############
	0xFF, 0xFE, // ###############
	0xFF, 0xFE, // ###############
	0x7F, 0xFC, //  ############# 
	0x7F, 0xFC, //  ############# 
	0x3F, 0xF8, //   ###########  
	0x1F, 0xF0, //    #########   
	0x0F, 0xE0, //     #######    
	0x07, 0xC0, //      #####     
	0x03, 0x80, //       ###      
	0x01, 0x00, //        #       
};

// Bitmap sizes for heart
const uint8_t heartWidthPages = 2;
const uint8_t heartHeightPixels = 15;

// 
//  Image data for diamond
// 

const uint8_t diamondBitmap[] =
{
	0x02, 0x00, //       #      
	0x07, 0x00, //      ###     
	0x0F, 0x80, //     #####    
	0x1F, 0xC0, //    #######   
	0x3F, 0xE0, //   #########  
	0x3F, 0xE0, //   #########  
	0x7F, 0xF0, //  ########### 
	0xFF, 0xF8, // #############
	0x7F, 0xF0, //  ########### 
	0x3F, 0xE0, //   #########  
	0x3F, 0xE0, //   #########  
	0x1F, 0xC0, //    #######   
	0x0F, 0x80, //     #####    
	0x07, 0x00, //      ###     
	0x02, 0x00, //       #      
};

// Bitmap sizes for diamond
const uint8_t diamondWidthPages = 2;
const uint8_t diamondHeightPixels = 15;


// 
//  Image data for club
// 

const uint8_t clubBitmap[] =
{
	0x03, 0x80, //       ###      
	0x07, 0xC0, //      #####     
	0x0F, 0xE0, //     #######    
	0x0F, 0xE0, //     #######    
	0x0F, 0xE0, //     #######    
	0x07, 0xC0, //      #####     
	0x3B, 0xB8, //   ### ### ###  
	0x7F, 0xFC, //  ############# 
	0xFF, 0xFE, // ###############
	0xFF, 0xFE, // ###############
	0xFF, 0xFE, // ###############
	0x7D, 0x7C, //  ##### # ##### 
	0x39, 0x38, //   ###  #  ###  
	0x03, 0x80, //       ###      
	0x07, 0xC0, //      #####     
};

// Bitmap sizes for club
const uint8_t clubWidthPages = 2;
const uint8_t clubHeightPixels = 15;



const uint8_t cardBackBitmap[] =
{
	0xFF, 0xFF, 0xFF, 0xFF, 0xF0, // ####################################
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x9F, 0xFF, 0xFF, 0xFF, 0x90, // #  ##############################  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0xFF, 0xFF, 0xFF, 0xFF, 0xF0, // ####################################
};

// Bitmap sizes for cardBack
const uint8_t cardBackWidthPages = 5;
const uint8_t cardBackHeightPixels = 48;

// 
//  Image data for cardBorder
// 

const uint8_t cardBorderBitmap[] =
{
	0xFF, 0xFF, 0xFF, 0xFF, 0xF0, // ####################################
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0x80, 0x00, 0x00, 0x00, 0x10, // #                                  #
	0xFF, 0xFF, 0xFF, 0xFF, 0xF0, // ####################################
};

// Bitmap sizes for cardBorder
const uint8_t cardBorderWidthPages = 5;
const uint8_t cardBorderHeightPixels = 48;


