// Copyright (c) 2017, Srinidhi Emkay
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without
// modification,
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
/*
#include "blackjack.h"

static struct player playerList[2];
int dealerSum, dealerNumCards;

/*******************************************************************************
* Function Name: display_main_menu
********************************************************************************
*******************************************************************************/

//bool display_main_menu(void) { return true; }

/*******************************************************************************
* Function Name: display_main_menu
********************************************************************************
*******************************************************************************/
/*
<<<<<<< HEAD
void master_game(uint8_t* playerID) {
  player this_player;
  bool nextRound;
  currCard = 0;
  *dealerHand = malloc(sizeof(uint8_t));
  this_player.playerID = playerID;
  this_player.money = 25000;
  playerList[0] = this_player;
  playerList[1] = getplayer();
  shuffle_cards();
  while (1) {
    // get bet
    setbet(playerList[0], Bet(playerList[0]));
    requestbet(playerList[1]);

    dealerNumCards = 0;

    int i, j;
    for (i = 0; i < 2; i++) {
      playerList[i].spilt = false;
      for (j = 0; j < 2; j++) {
        playerList[i].stand[j] = false;
        playerList[i].numCards[j] = 0;
      }
=======
void master_game(uint8_t* playerID)
{
    player this_player;
    bool nextRound;
    currCard = 0;
    *gameState.dealerHand = malloc(sizeof(uint8_t));
    this_player.playerID = playerID;
    this_player.money = 25000;
    playerList[0] = this_player;
    playerList[1] = getplayer();
    shuffle_cards();
    while (1) {
        //get bet
        setbet(playerList[0], Bet(playerList[0]));
        requestbet(playerList[1]);

        dealerNumCards = 0;

        int i, j;
        for (i = 0; i < 2; i++) {
            playerList[i].spilt = false;
            for (j = 0; j < 2; j++) {
                playerList[i].stand[j] = false;
                playerList[i].numCards[j] = 0;
            }
        }

        for (i = 0; i < 2; i++) {
            *(gameState.dealerHand + i) = gameState.Deck[currCard++];
            dealerNumCards++;
            playerList[0].hand[0][i] = gameState.Deck[currCard++];
            playerList[0].numCards[0]++;
            playerList[1].hand[0][i] = gameState.Deck[currCard++];
            playerList[1].numCards[0]++;
        }

        if (score(gameState.dealerHand, 2, true) == 21) {
            dealerSum = 21;
            finalScore();
        }
        bool done;
        do {
            done = true;
            for (i = 0; i < 2; i++) {
                done = done && playerturn(playerList[i]) ? true : false;
            }
        } while (!done)
            finalScore();
>>>>>>> c4c9601f36a0b5d4779eca85c9ff5d2660e7b0e8
    }

    for (i = 0; i < 2; i++) {
      *(dealerHand + i) = nextCard();
      dealerNumCards++;
      playerList[0].hand[0][i] = nextCard();
      playerList[0].numCards[0]++;
      playerList[1].hand[0][i] = nextCard();
      playerList[1].numCards[0]++;
    }

    if (score(dealerHand, 2, true) == 21) {
      dealerSum = 21;
      endTurn();
    }
    bool done;
    do {
      done = true;
      for (i = 0; i < 2; i++) {
        done = done && playerturn(playerList[i]) ? true : false;
      }
    } while (!done);
    while (score(dealerHand, dealerNumCards, true) < 17) {
      dealerHand[dealerNumCards++] = nextCard();
    }
    endTurn();
  }
}

bool requestbet(player* p) {
  p->bet = 1;
  // userBet;
}

int score(int[] val, int num, bool high) {
  int i, sum = 0;
  for (i = 0; i < num; i++) {
    if (val[i] % 13 == 0) {
      if (high) {
        sum += 11;
      }
      sum += 1;
    } else if (val[i] % 13 > 10) {
      sum += 10
    } else {
      sum += val[i] % 13;
    }
  }
  return sum;
}

bool playerturn(player* p) {
  bool finished = true;
  if (split && (p->hand[0][0] % 13 == p->hand[0][1] % 13)) {
    p->hand[0][0] = p->hand[0][1];
    p->numCards[0]--;
    p->numCards[1]++;
    return;
  }
  for (i = 0; numCards[i]; i++) {
    if (hit && score(p->hand[i], numCards[i], false)) {
      p->hand[i][numCards[i]++] = nextCard();
      finished = false;
    } else if (stand) {
      p->stand[i] = true;
    }
  }
  return finished;
}

void endTurn(void) {
  int i, j, k, totalmoney, playersum_l, playersum;
  struct player* currPlayer;
  for (i = 0; i < 2; i++) {
    currPlayer = playerList[i];
    totalmoney = 0;
    for (j = 0; j < 2; j++) {
      playersum_l = 0;
      playersum = 0;

      playersum += score(currPlayer->hand[j], currPlayer->numCards[j], true);
      playersum_l += score(currPlayer->hand[j], currPlayer->numCards[j], false);

      if (playersum > 21) {
        playersum = playersum;
      }
      if (!playersum) {
        continue;
      }
      if (currPlayer->numCards[j] == 2) {
        totalmoney += currPlayer->bet * 2;
      } else if (playersum > 21 || dealerSum > playersum) {
        totalmoney -= currPlayer->bet;
      } else if (dealerSum < playersum) {
        totalmoney += currPlayer->bet;
      }
    }
    currPlayer->money += totalmoney;
    DisplayWinorLoss(currPlayer, totalmoney);
  }
}

int Bet(void) {
  int userBet;
  bool betset = false;

  while (!betset) {
    if (press_positive) {
      userBet = userBet < money : userBet + 500 ? money;
    } else if (press_negitive) {
      userBet = userBet > 0 : userBet - 500 ? 0;
    }
  }

  return userBet;
}

void play_game(void) {
  // find master and get id
  getplayer();
  // if return
  while (1) {
    sendbet();
  }
}

void sendbet() {
  Bet();
  // transfer this to master
}

int nextCard(void) {
  if (currCard == 52) {
    currCard = 0;
    int index, i;
    int high, low, random;

    for (i = 0; i < 52; i++) {
      Deck[i] = i;
    }

    for (i = 0; i < 52; i++) {
      high = 51;
      low = i;
      index = rand() % (high - low + 1) + low;
      swap(Deck + i, Deck + index);
    }
  }
  return Deck[currCard++];
}

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
*/