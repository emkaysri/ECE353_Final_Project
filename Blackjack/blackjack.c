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

static struct player playerList[2];

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

void master_game(uint8_t *playerID){
	player this_player;
  currCard = 0;
	*dealerHand = malloc(sizeof(uint8_t));
  this_player.playerID = playerID;
  this_player.money = 25000;
  playerList[0] = this_player;
  playerList[1] = getplayer();
  shuffle_cards();
  while(1){
    //get bet
    setbet(playerList[0],Bet(playerList[0]));
    requestbet(playerList[1]);

    int i;
    for(i = 0; i < 2; i++){
      *(dealerHand + i) = Deck[currCard++];
      playerList[0].hand[0][i] = Deck[currCard++];
      playerList[1].hand[0][i] = Deck[currCard++];
    }

  uint8_t dealerSum;
  if(dealerHand[0] % 13 == 1){
    dealerSum = 11;
  } else if(dealerHand[0] % 13 > 10 || dealerHand[0] % 13 == 0){
    dealerSum = 10;
  }

  if(dealerHand[1] % 13 == 1){
    dealerSum += 11;
  } else if(dealerHand[1] % 13 > 10 || dealerHand[1] % 13 == 0){
    dealerSum += 10;
  }

  if(dealerSum == 21){
    //score user
  }

}
}
bool requestbet(player *p){
	 p->bet = 1; 
	//userBet;
}

int Bet(void){
  int userBet;
  bool betset = false;

  while(!betset){
    if(press_positive){
      userBet = userBet < money : userBet + 500 ? money
    } else if(press_negitive){
      userBet = userBet > 0 : userBet - 500 ? 0;
    }
  }

  return userBet;
}


void play_game(void){
  //find master and get id
  getplayer();
  //if return
	while (1){
		sendbet();
	}
}
void sendbet(){
	Bet();
	//transfer this to master
}

void shuffle_cards(void){
  currCard = 0;
  int index, i;
	int high, low, random;

  for(i = 0; i < 52; i++){
    Deck[i] = i;
  }

	for(i=0; i<52; i++) {
		high = 51;
		low = i;
		index = rand() % (high - low + 1) + low;
		swap(Deck+i, Deck+index);
	}
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
