
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

#include "tic_tac_toe_images.h"

/* Character bitmaps for Shentox 7 48pt */
const uint8_t Bitmaps_X[] = 
{
	/* @0 'X' (35 pixels wide) */
	0xFF, 0xF0, 0x00, 0xFF, 0xE0, // ############            ###########
	0xFF, 0xF0, 0x00, 0xFF, 0xE0, // ############            ###########
	0xFF, 0xF0, 0x00, 0xFF, 0xE0, // ############            ###########
	0xFF, 0xF0, 0x00, 0xFF, 0xE0, // ############            ###########
	0xFF, 0xF0, 0x00, 0xFF, 0xE0, // ############            ###########
	0xFF, 0xF0, 0x00, 0xFF, 0xE0, // ############            ###########
	0xFF, 0xF0, 0x00, 0xFF, 0xE0, // ############            ###########
	0xFF, 0xF0, 0x00, 0xFF, 0xE0, // ############            ###########
	0xFF, 0xF0, 0x00, 0xFF, 0xE0, // ############            ###########
	0xFF, 0xF8, 0x00, 0xFF, 0xE0, // #############           ###########
	0xFF, 0xF8, 0x01, 0xFF, 0xE0, // #############          ############
	0xFF, 0xFC, 0x03, 0xFF, 0xE0, // ##############        #############
	0x7F, 0xFE, 0x07, 0xFF, 0xC0, //  ##############      ############# 
	0x3F, 0xFF, 0x0F, 0xFF, 0xC0, //   ##############    ############## 
	0x1F, 0xFF, 0x8F, 0xFF, 0x80, //    ##############   #############  
	0x0F, 0xFF, 0xDF, 0xFF, 0x00, //     ############## #############   
	0x0F, 0xFF, 0xFF, 0xFE, 0x00, //     ###########################    
	0x07, 0xFF, 0xFF, 0xFC, 0x00, //      #########################     
	0x03, 0xFF, 0xFF, 0xF8, 0x00, //       #######################      
	0x01, 0xFF, 0xFF, 0xF0, 0x00, //        #####################       
	0x00, 0xFF, 0xFF, 0xE0, 0x00, //         ###################        
	0x00, 0x7F, 0xFF, 0xC0, 0x00, //          #################         
	0x00, 0x3F, 0xFF, 0xC0, 0x00, //           ################         
	0x00, 0x7F, 0xFF, 0x80, 0x00, //          ################          
	0x00, 0x7F, 0xFF, 0xC0, 0x00, //          #################         
	0x00, 0xFF, 0xFF, 0xE0, 0x00, //         ###################        
	0x01, 0xFF, 0xFF, 0xF0, 0x00, //        #####################       
	0x03, 0xFF, 0xFF, 0xF8, 0x00, //       #######################      
	0x07, 0xFF, 0xFF, 0xFC, 0x00, //      #########################     
	0x0F, 0xFF, 0xFF, 0xFC, 0x00, //     ##########################     
	0x1F, 0xFF, 0xFF, 0xFE, 0x00, //    ############################    
	0x3F, 0xFF, 0x3F, 0xFF, 0x00, //   ##############  ##############   
	0x3F, 0xFE, 0x1F, 0xFF, 0x80, //   #############    ##############  
	0x7F, 0xFC, 0x0F, 0xFF, 0xC0, //  #############      ############## 
	0x7F, 0xF8, 0x07, 0xFF, 0xC0, //  ############        ############# 
	0xFF, 0xF8, 0x07, 0xFF, 0xE0, // #############        ##############
	0xFF, 0xF0, 0x03, 0xFF, 0xE0, // ############          #############
	0xFF, 0xF0, 0x01, 0xFF, 0xE0, // ############           ############
	0xFF, 0xF0, 0x01, 0xFF, 0xE0, // ############           ############
	0xFF, 0xF0, 0x01, 0xFF, 0xE0, // ############           ############
	0xFF, 0xF0, 0x01, 0xFF, 0xE0, // ############           ############
	0xFF, 0xF0, 0x01, 0xFF, 0xE0, // ############           ############
	0xFF, 0xF0, 0x01, 0xFF, 0xE0, // ############           ############
	0xFF, 0xF0, 0x01, 0xFF, 0xE0, // ############           ############
	0xFF, 0xF0, 0x01, 0xFF, 0xE0, // ############           ############
	0xFF, 0xF0, 0x01, 0xFF, 0xE0, // ############           ############
};

/* Character bitmaps for Shentox 7 48pt */
const uint8_t Bitmaps_O[] = 
{
	/* @0 'O' (34 pixels wide) */
	0x01, 0xFF, 0xFF, 0xE0, 0x00, //        ####################       
	0x0F, 0xFF, 0xFF, 0xFC, 0x00, //     ##########################    
	0x1F, 0xFF, 0xFF, 0xFE, 0x00, //    ############################   
	0x3F, 0xFF, 0xFF, 0xFF, 0x00, //   ##############################  
	0x7F, 0xFF, 0xFF, 0xFF, 0x80, //  ################################ 
	0x7F, 0xFF, 0xFF, 0xFF, 0x80, //  ################################ 
	0x7F, 0xFF, 0xFF, 0xFF, 0x80, //  ################################ 
	0xFF, 0xFF, 0xFF, 0xFF, 0xC0, // ##################################
	0xFF, 0xFF, 0xFF, 0xFF, 0xC0, // ##################################
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xF0, 0x03, 0xFF, 0xC0, // ############          ############
	0xFF, 0xFF, 0xFF, 0xFF, 0xC0, // ##################################
	0xFF, 0xFF, 0xFF, 0xFF, 0xC0, // ##################################
	0xFF, 0xFF, 0xFF, 0xFF, 0xC0, // ##################################
	0x7F, 0xFF, 0xFF, 0xFF, 0x80, //  ################################ 
	0x7F, 0xFF, 0xFF, 0xFF, 0x80, //  ################################ 
	0x3F, 0xFF, 0xFF, 0xFF, 0x00, //   ##############################  
	0x1F, 0xFF, 0xFF, 0xFE, 0x00, //    ############################   
	0x0F, 0xFF, 0xFF, 0xFC, 0x00, //     ##########################    
	0x03, 0xFF, 0xFF, 0xF0, 0x00, //       ######################      
};

