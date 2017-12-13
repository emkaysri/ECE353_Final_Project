
#include "blackjack.h"

/*******************************************************************************
* Function Name: display_main_menu
********************************************************************************
*******************************************************************************/
bool display_main_menu(void) { return true; }

/*******************************************************************************
* Function Name: display_main_menu
********************************************************************************
*******************************************************************************/
 
extern EVENT_DATA   global_event_data;
extern GAMESTATE_DATA  global_game_state_data;

void master_game(uint8_t* playerOneID, uint8_t* playerTwoID)
{
    
    bool nextRound, done;
		int i, j;
	
	
    currCard = 0;
    *gameState.dealerHand = (int) malloc(sizeof(uint8_t));
    this_player.playerID = playerOneID;
    this_player.money = 25000;
    nextCard();
    while (1) {
        //get bet
			
        bool done;
			this_player.bet = global_game_state_data.playerOneBet;

        dealerNumCards = 0;       
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
            endTurn();
        }
        do {
            done = true;
            for (i = 0; i < 2; i++) {
                done = done && playerturn(&this_player) ? true : false;
            }
        } while (!done);
            endTurn();
    }
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

bool playerturn() {
	enum BLACKJACK_GAME_OPTION x = NOTVALID;
	int i, num = 1;
  bool finished = true;
	while(x == NOTVALID){
	if(up == 8)
			x = HIT;
	if(down == 8)
			x = STAND;
	if(left == 8)
			x = SPLIT;
}
  if ((x == SPLIT) && (this_player.hand[0][0] % 13 == this_player.hand[0][1] % 13) && !this_player.numCards[1]) {
    this_player.hand[0][0] = this_player.hand[0][1];
    this_player.numCards[0]--;
    this_player.numCards[1]++;
    return false;
  }
	if (this_player.numCards[1]){
		num = 2;
	}
	for(i = 0; i < num; i++){
		if (this_player.stand[i]){
		} else if (x == STAND) {
      this_player.stand[i] = true;
    } else if ((x == HIT) && score(this_player.hand[i], this_player.numCards[i], false)) {
			this_player.hand[i][this_player.numCards[i]++] = nextCard();
      finished = false;
    }
	}	
  return finished;
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
    //this_player.money += totalmoney;
		
		global_game_state_data.playerOneMoney += totalmoney;
		
		if (totalmoney < 0) {
			global_game_state_data.playerOneWin = -1;
		} else {
			global_game_state_data.playerOneWin = 1;
		}
		
		global_game_state_data.currentScreenState = END_GAME;
    //DisplayWinorLoss(&this_player, totalmoney);
}
/*
int Bet(player *p) {
	int money = p->money;
  int userBet;
  bool betset = false;
  while (!betset) {
    if (global_event_data->joystickEvent.y > 3000) {
      userBet = userBet < money ? userBet + 500 : money;
    } else if (global_event_data->joystickEvent.y < 1000) {
      userBet = userBet > 0 ? userBet - 500 : 0;
    }
  }

  return userBet;
}
*/


int nextCard(void) {
  if (currCard == 52) {
		int index, i;
    int high, low, random;
    currCard = 0;

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