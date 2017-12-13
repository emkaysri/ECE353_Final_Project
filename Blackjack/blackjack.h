// Copyright (c) 2017, Srinidhi Emkay
// All rights reserved.
//
// Redistribution and use in binary form, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in binary form must reproduce the above copyright
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
#ifndef __BLACKJACK_H__
#define __BLACKJACK_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "event.h"

#define DEALER_CARD_WIDTH     XX
#define DEALER_CARD_HEIGHT    XX
extern const uint8_t Bitmaps_X[];

#define USER_CARD_WIDTH     XX
#define USER_CARD_HEIGHT    XX
extern const uint8_t Bitmaps_X[];

extern volatile int up, down, left, right;

typedef struct{
  int hand[2][5];
  bool stand[2];
  int numCards[2];
  int money;
  int bet;
  uint8_t *playerID;
} player;

player this_player;
/*
* cardnum % 13 = CARD_VALUE
* cardnum / 13 = CARD_SUIT
*/
int *dealerHand;
int dealerNumCards;

int currCard;
int Deck[52];
int dealerSum;


enum BLACKJACK_GAME_OPTION {
	HIT,
	STAND,
	SPLIT,
	NOTVALID
};


enum BLACKJACK_BET_OPTIONS {
	INCREASE,
	DECREASE
};

enum GAME_OPTIONS {
	ONE_PLAYER,
	TWO_PLAYER
} ;


typedef struct{
	player masterPlayer;
	player slavePlayer;
	int *dealerHand;
	int Deck[52];
	
	
} CURRENT_GAME_STATE;


CURRENT_GAME_STATE gameState;

typedef enum{
  ACE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING
} CARD_VALUE;

typedef enum{
  SPADES,
  CLUBS,
  HEARTS,
  DIAMONDS
} CARD_SUIT;



/*******************************************************************************
* Function Name: display_main_menu
********************************************************************************
* Summary: Waits for user to select if they are the master or not, if master returns true
*
* Returns:
*  True for Master Device.  False for all other conditions
*******************************************************************************/
bool display_main_menu(void);

/*******************************************************************************
* Function Name: master_game
********************************************************************************
* Summary: Creates game
*
*******************************************************************************/
void master_game(uint8_t* playerOneID, uint8_t* playerTwoID);

/*******************************************************************************
* Function Name: play_game
********************************************************************************
* Summary: joins game
*
*******************************************************************************/
void play_game(void);

/*******************************************************************************
* Function Name: shuffle_cards
********************************************************************************
* Summary: creates a deck and suffles it
*
*******************************************************************************/
int nextCard(void);
int Bet(player *p);
bool requestbet();
void play_game(void);
void shuffle_cards(void);
void swap(int *a, int *b);
void sendbet(void);
void endTurn(void);
void DisplayWinorLoss(player * p, int winLoss);
bool playerturn();
int score(int * val, int num, bool high);
#endif
