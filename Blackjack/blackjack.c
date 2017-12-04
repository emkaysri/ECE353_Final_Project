// Copyright (c) 2017, Srinidhi Emkay
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

#include "blackjack.h"

/*******************************************************************************
* Function Name: display_main_menu
********************************************************************************
*******************************************************************************/

bool display_main_menu(void){
  return true;
}

/*******************************************************************************
* Function Name: display_main_menu
********************************************************************************
*******************************************************************************/

void master_game(void){
  uint8_t i;
  for(i = 0; i < 52; i++){
    cleanDeck[i] = i;
  }
  if(quit){
    return;
  }
  int cardselect = 0;
  while(1){
    if(51 - cardselect < numplayers * 3 + 2){
      shuffle_cards();
      cardselect = 0;
      cards[0]
    }
  }
}


void play_game(void){
  //find master
  if(quit){
    return;
  }
}

void shuffle_cards(){
  uint8_t i;
	for (i = 0; i < 51; i++) {
	  uint8_t j = i + rand() / (RAND_MAX / (52 - i) + 1);
	  int t = array[j];
	  array[j] = array[i];
	  array[i] = t;
	}
}
