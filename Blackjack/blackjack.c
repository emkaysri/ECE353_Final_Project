
#include "blackjack.h"
/*
 EVENT_DATA * global_event_data;
 GAMESTATE_DATA * global_game_state_data;

int dealerSum, dealerNumCards;
player this_player;
*/
/*******************************************************************************
* Function Name: display_main_menu
********************************************************************************
*******************************************************************************/

bool display_main_menu(void) { return true; }

/*******************************************************************************
* Function Name: display_main_menu
********************************************************************************
*******************************************************************************/
/* 
void master_game(uint8_t* playerOneID, uint8_t* playerTwoID )
{
    
    bool nextRound;
		int i, j;
	
	
    currCard = 0;
    *gameState.dealerHand = malloc(sizeof(uint8_t));
    this_player.playerID = playerOneID;
    this_player.money = 25000;
    shuffle_cards();
    while (1) {
        //get bet
        setbet(this_player, Bet(this_player));

        dealerNumCards = 0;

        
        this_player.spilt = false;
        for (j = 0; j < 2; j++) {
            this_player.stand[j] = false;
            this_player.numCards[j] = 0;
        }
        

        
         *(gameState.dealerHand + i) = gameState.Deck[currCard++];
        dealerNumCards++;
        this_player.hand[0][i] = gameState.Deck[currCard++];
        this_player.numCards[0]++;
        this_player.hand[0][i] = gameState.Deck[currCard++];
        this_player.numCards[0]++;
        

        if (score(gameState.dealerHand, 2, true) == 21) {
            dealerSum = 21;
            finalScore();
        }
        bool done;
        do {
            done = true;
            for (i = 0; i < 2; i++) {
                done = done && playerturn(&this_player) ? true : false;
            }
        } while (!done)
            finalScore();
    }

 
    *(dealerHand + i) = nextCard();
    dealerNumCards++;
    this_player.hand[0][i] = nextCard();
    this_player.numCards[0]++;
    this_player.hand[0][i] = nextCard();
    this_player.numCards[0]++;
    

    if (score(dealerHand, 2, true) == 21) {
      dealerSum = 21;
      endTurn();
    }
    bool done;
    do {
      done = true;
      for (i = 0; i < 2; i++) {
        done = done && playerturn(&this_player) ? true : false;
      }
    } while (!done);
    while (score(dealerHand, dealerNumCards, true) < 17) {
      dealerHand[dealerNumCards++] = nextCard();
    }
    endTurn();
 }


bool requestbet() {
  this_player.bet = 1;
  // userBet;
	global_game_state_data
}

int score(int * val, int num, bool high) {
  int i, sum = 0;
  for (i = 0; i < num; i++) {
    if (val[i] % 13 == 0) {
      if (high) {
        sum += 11;
      }
      sum += 1;
    } else if (val[i] % 13 > 10) {
      sum += 10;
    } else {
      sum += val[i] % 13;
    }
  }
  return sum;
}

void playerturn() {
	int i = 0 ;
  bool finished = true;
  if (this_player.split && (this_player.hand[0][0] % 13 == this_player.hand[0][1] % 13)) {
    this_player.hand[0][0] = this_player.hand[0][1];
    this_player.numCards[0]--;
    this_player.numCards[1]++;
    return ;
  }
  for (i = 0; this_player.numCards[i]; i++) {
    if (this_player.hit && score(this_player.hand[i], this_player.numCards[i], false)) {
      this_player.hand[i][this_player.numCards[i]++] = nextCard();
      finished = false;
    } else if (this_player.stand) {
      this_player.stand[i] = true;
    }
  }
  return ;
}

void endTurn(void) {
  int i, j, k, totalmoney, playersum_l, playersum;
    totalmoney = 0;
    for (j = 0; j < 2; j++) {
      playersum_l = 0;
      playersum = 0;

      playersum += score(this_player.hand[j], this_player.numCards[j], true);
      playersum_l += score(this_player.hand[j], this_player.numCards[j], false);

      if (playersum > 21) {
        playersum = playersum;
      }
      if (!playersum) {
        continue;
      }
      if (this_player.numCards[j] == 2) {
        totalmoney += this_player.bet * 2;
      } else if (playersum > 21 || dealerSum > playersum) {
        totalmoney -= this_player.bet;
      } else if (dealerSum < playersum) {
        totalmoney += this_player.bet;
      }
    }
    this_player.money += totalmoney;
    DisplayWinorLoss(this_player, totalmoney);
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