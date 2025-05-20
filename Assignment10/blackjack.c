#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*

	..........Black Jack..........

	1) Hit
	2) Double Down
	3) Split
	3) Stay


	Rules:
	1) Split can be done only once during the round
	2) Double Down can be done with Any hand
	3) Dealer cannot split or double down, only hir or stand
	4) Dealer has to take a hit after the soft 17 hand.
	5) Every time the total is calcualted in case of a soft hand, user will have to put 1 or 11 to set the value of Ace.
	6) Surrender and Insurence Options are not available for players.
	7) Dealer has to put 11 for the Soft Hand when caluculating if the total is less than 17

*/

// deck
struct SDeck
{
	int cards[52];
	int index;
} deck;

// player and dealer hands
struct SHand
{
	int cards[12]; // 12 because its the max possible cards required for busting
	int index;
	int cardTotal;
} player, dealer;

// player scores and dealer scores for 10 rounds
int playerScore = 0;
int dealerScore = 0;

// Swap cards function
void SwapCards(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// Non Shuffled Deck
void CreateDeck()
{
	for (int i = 0; i < 52; i++)
	{
		deck.cards[i] = i;
	}
}

// function to shuffle the elements in the array which is deck here.
void ShuffleDeck(int* arr)
{
	srand(time(NULL));

	// picks the random index from 0 to i and swaps it with current index i
	for (int i = 51; i > 0; i--)
	{
		int randomIndex = rand() % (i + 1); // i + 1 to avoid %1 operation when i = 1
		SwapCards(&deck.cards[randomIndex], &deck.cards[i]);
	}
}

// displays the card name by taking input 0 to 51 (card number)
void DisplayCard(int card)
{
	// operation to get card type and card number from 0 to 51
	int cardNumber = card % 13 + 1;
	int cardType = card / 13 + 1;

	char* cardNumberToString = "";
	char* cardTypeToString = "";

	switch (cardNumber)
	{
	case 1:
		cardNumberToString = "Ace";
		break;
	case 2:
		cardNumberToString = "Two";
		break;
	case 3:
		cardNumberToString = "Three";
		break;
	case 4:
		cardNumberToString = "Four";
		break;
	case 5:
		cardNumberToString = "Five";
		break;
	case 6:
		cardNumberToString = "Six";
		break;
	case 7:
		cardNumberToString = "Seven";
		break;
	case 8:
		cardNumberToString = "Eight";
		break;
	case 9:
		cardNumberToString = "Nine";
		break;
	case 10:
		cardNumberToString = "Ten";
		break;
	case 11:
		cardNumberToString = "Jack";
		break;
	case 12:
		cardNumberToString = "Queen";
		break;
	case 13:
		cardNumberToString = "King";
		break;
	default:
		break;
	}

	switch (cardType)
	{
	case 1:
		cardTypeToString = "Hearts";
		break;
	case 2:
		cardTypeToString = "Diamonds";
		break;
	case 3:
		cardTypeToString = "Spades";
		break;
	case 4:
		cardTypeToString = "Clubs";
		break;
	default:
		break;
	}

	printf("%s of %s\n", cardNumberToString, cardTypeToString);
};

// Displays the cards in array which are player cards here
void DisplayHand(int* arr, int size)
{
	// prints the sequence of the cards using DisplayCard() function
	for (int i = 0; i < size; i++)
	{
		printf("%d. ", i + 1);
		DisplayCard(arr[i]);
	}

	printf("\n");
};

// displayes the total of cards in hand and whether it is a soft or not
void DisplayTotal(int* cards, int index)
{
	int temp = 0;
	bool isSoft = false;
	for (int i = 0; i < index; i++)
	{
		int cardValue = cards[i] % 13 + 1;

		if (cardValue >= 10) 
		{
			cardValue = 10;
		}

		if (cardValue == 1)
		{
			isSoft = true;
		}

		temp += cardValue;
	}

	if (isSoft) 
	{

		printf("The Total of this Hand is soft %d that is %d or %d according to the choice.\n", temp+10, temp , temp + 10);
	}
	else
	{
		printf("The Total of this Hand is %d.\n", temp);
	}
};

// gets the total of deck, here user can set the value for ace card
int GetTotal(int* cards, int index)
{
	int total = 0;
	for (int i = 0; i < index; i++)
	{
		int cardValue = cards[i] % 13 + 1;

		if (cardValue >= 10)
		{
			cardValue = 10;
		}

		if (cardValue == 1)
		{
			int choice = 0;
			printf("You have an Ace! What value of ace do you want? (1 / 11)\n");
			
			while (choice != 1 && choice != 11)
			{
				printf("Your Choice: ");
				scanf_s("%d", &choice);
				printf("\n");
				switch (choice)
				{
				case 1:
					cardValue = choice;
					break;
				case 11:
					cardValue = choice;
					break;
				default:
					printf("Invalid Input! Try Again!\n");
					break;
				}
			}
		}

		total += cardValue;
	}
	return total;
}

// if the split is allowed
bool IsSplitAllowed(int* cards)
{
	if ((cards[0] % 13 + 1) == (cards[1] % 13 + 1))
	{
		return true;
	}
	return false;
}

// if the hand is busted
bool IsBusted(int total)
{
	if (total > 21)
	{
		return true;
	}
	return false;
}

// if the total is 21 and hand has a balckjack
bool IsBlackjack(int total)
{
	if (total == 21)
	{
		return true;
	}
	return false;
}

// announce winner of the round based on the totals of player and dealer or splitted player cards
void WinnerOfRound(int playerTotal, int dealerTotal, bool isSplitted, int splitTotal) 
{
	if (!isSplitted)
	{
		if (playerTotal > dealerTotal)
		{
			if (IsBlackjack(playerTotal))
			{
				playerScore += 1;
				printf("Player has a Black Jack!!. Player Wins the 3:2 of Bet Amount!\n");
			}
			else
			{
				playerScore += 1;
				printf("Player has a Better Hand than Dealer. Player Wins the 2:1 of Bet Amount!\n");
			}
		}
		else if (playerTotal == dealerTotal)
		{
			printf("Its a Push. Both will keep thier bets!\n");
		}
		else
		{
			if (IsBlackjack(dealerTotal))
			{
				printf("Dealer has a BlackJAck. Player Loses the Bet Amount!\n");

			}
			else
			{
				printf("dealer has a Better Hand than Player. Player Loses the Bet Amount!\n");
			}
			dealerScore += 1;
		}
	}
	else
	{
		if ((playerTotal < dealerTotal && splitTotal < dealerTotal) || (IsBusted(playerTotal) && splitTotal < dealerTotal) || (IsBusted(splitTotal) && playerTotal < dealerTotal))
		{
			dealerScore += 1;
			printf("dealer has a Better Hand than Player Hands. Player Loses the Bet Amount!\n");
		}
		else if ((playerTotal == dealerTotal && splitTotal == dealerTotal) || (IsBusted(playerTotal) && splitTotal == dealerTotal) || (IsBusted(splitTotal) && playerTotal == dealerTotal))
		{
			printf("Its a Push. Both will keep thier bets!\n");
		}
		else
		{
			playerScore += 1;
			printf("Player has atleast one Better Hand than Dealer. Player Wins the Bet Amount!\n");
		}
	}
}


// display the winner after 10 rounds (in problem statement)
void DisplayWinner(int playerScore, int dealerScore)
{
	printf("After 10 rounds, \n");
	if (playerScore < dealerScore)
	{
		printf("Dealer won more rounds than Player out of 10. Dealer Wins!!\n");
	}
	else if (playerScore > dealerScore)
	{
		printf("Player won more rounds than Dealer out of 10. Player Wins!!\n");
	}
	if (playerScore < dealerScore)
	{
		printf("Both won the same amount of rounds. Game Draw!!\n");
	}
}


int main()
{
	printf("<-----------------------BLACK JACK----------------------->\n\n");
	
	// Rules
	printf("Player Options: \n");
	printf("\t1) Hit : Take Another card from the Deck.\n");
	printf("\t2) Double Down : Take one card, Double Your Bet, and Stand.\n");
	printf("\t3) Stand : You wont get a Card. This Ends your Turn.\n");
	printf("\t4) Split : In case of Same Valued Cards, You can Split the Deck\n\n");

	printf("RULES:\n");
	printf("\t1) Split can be done only once during the round.\n");
	printf("\t2) Double Down can be done with Any hand.\n");
	printf("\t3) Dealer cannot split or double down, only hir or stand\n");
	printf("\t4) Dealer has to take a hit after the soft 17 hand.\n");
	printf("\t5) Every time the total is calcualted in case of a soft hand, user will have to put 1 or 11 to set the value of Ace.\n");
	printf("\t6) Surrender and Insurence Options are not available for players.\n");
	printf("\t7) Dealer has to put 11 for the Soft Hand when caluculating if the total is less than 17\n");

	printf("\n<-----------------------Let The Game Begin!----------------------->\n");


	// create the deck and shuffle the cards
	CreateDeck(deck.cards);
	ShuffleDeck(deck.cards);
	printf("Shuffled Deck has been Generated!!\n");

	for (int round = 1; round <= 10; round++)
	{
		printf("\n<-----------------------Round %d----------------------->\n", round);
		ShuffleDeck(deck.cards);
		deck.index = 0;
		player.index = 0;
		dealer.index = 0;

		bool isSplitted = false;

		// Allot Two Cards to the Player
		printf("Giving 2 Cards to the Player!!\n");
		player.cards[player.index++] = deck.cards[deck.index++];
		player.cards[player.index++] = deck.cards[deck.index++];

		// Display 2 cards of player on board
		DisplayHand(player.cards, player.index); 


		// Allot two cards to the Dealer, showing only one in first turn
		printf("Giving 2 Cards to the Dealer!!\n");
		dealer.cards[dealer.index++] = deck.cards[deck.index++];
		dealer.cards[dealer.index++] = deck.cards[deck.index++];

		// Display 1 card of dealer on board
		DisplayHand(dealer.cards, dealer.index - 1);
		printf("One Dealer card is Hidden.\n");

		// Players variables
		printf("\n<---------------------- Players turn ---------------------->\n");

		bool playerTurnOver = false;
		int playerChoice = 0;
		int playerTotal = 0; // for this round
		int splitTotal = 0; // in case there is splitting

		// options
		printf("Player Options:\n");
		printf("\t1. Hit\n");
		printf("\t2. Double Down\n");
		printf("\t3. Stand/Stay\n");
		if (IsSplitAllowed(player.cards))
		{
			printf("\t4. Split\n");
		}

		while (!playerTurnOver && !IsBusted(playerTotal))
		{
			printf("Your Choice: ");
			scanf_s("%d", &playerChoice);
			printf("\n");
			switch (playerChoice)
			{
			case 1: // Hit
				printf("You chose Hit! Another Player Card is Added to your Hand.\nNow Your Cards are: \n");
				player.cards[player.index++] = deck.cards[deck.index++];
				DisplayHand(player.cards, player.index);
				DisplayTotal(player.cards, player.index);

				playerTotal = GetTotal(player.cards, player.index);

				break;

			case 2: // Double Down
				printf("You chose Double Down! Another Player Card is Added to your Hand.\nNow Your Cards are: \n");
				player.cards[player.index++] = deck.cards[deck.index++];
				DisplayHand(player.cards, player.index);
				DisplayTotal(player.cards, player.index);
				
				playerTotal = GetTotal(player.cards, player.index);

				playerTurnOver = true;
				break;

			case 3: // Stand
				printf("You chose Stand! Your turn will now end.\nYour Final Cards are: \n");
				DisplayHand(player.cards, player.index);
				DisplayTotal(player.cards, player.index);
				playerTurnOver = true;
				break;

			case 4: // Split 
				printf("You chose Split! Your Hand is splitted into 2 separate Hands.\nYour Final Cards are: \n");
				isSplitted = true;
				bool splitTurnOver = false;
				struct SHand splithand = { {0}, 0 }; // split hand
				player.index--; // to bring pointer down by one to get the value becuase it had moved forward by last hit
				splithand.cards[splithand.index++] = player.cards[player.index]; // allot second card

				// Display Both the Hands
				printf("Cards in Hand One: \n");
				DisplayHand(player.cards, player.index);
				printf("Cards in Hand Two: \n");
				DisplayHand(splithand.cards, splithand.index);

				// hand number 1
				while (!playerTurnOver && !IsBusted(playerTotal))
				{
					playerChoice = 0;
					printf("Options for Hand One: \n");
					printf("\t1. Hit\n");
					printf("\t2. Stand/Stay\n");

					printf("Your Choice: ");
					scanf_s("%d", &playerChoice);
					printf("\n");

					switch (playerChoice)
					{
					case 1: // Hit for hand 1 
						printf("You chose Hit! Another Player Card is Added to your Hand One.\nNow Your Cards in Hand One are: \n");
						player.cards[player.index++] = deck.cards[deck.index++];
						DisplayHand(player.cards, player.index);
						DisplayTotal(player.cards, player.index);
						playerTotal = GetTotal(player.cards, player.index);
						break;

					case 2: // Stand for hand 1
						printf("You chose Stand! Your turn for Hand One will now end.\nYour Final Hand One Cards are: \n");
						DisplayHand(player.cards, player.index);
						DisplayTotal(player.cards, player.index);
						playerTurnOver = true;
						break;

					default:
						printf("Invalid Input! Try Again!\n");
						break;
					}
				}

				// hand number 2
				int splitChoice;
				while (!splitTurnOver && !IsBusted(splitTotal))
				{
					splitChoice = 0;
					printf("Options for Hand Two: \n");
					printf("\t1. Hit\n");
					printf("\t2. Stand/Stay\n");

					printf("Your Choice: ");
					scanf_s("%d", &splitChoice); 
					printf("\n");
					
					switch (splitChoice)
					{
					case 1: // Hit for hand 2
						printf("You chose Hit! Another Player Card is Added to your Hand Two.\nNow Your Cards in Hand Two are: \n");
						splithand.cards[player.index++] = deck.cards[deck.index++];
						DisplayHand(splithand.cards, splithand.index);
						DisplayTotal(splithand.cards, splithand.index);
						splitTotal = GetTotal(splithand.cards, splithand.index);
						break;

					case 2: // Stand for hand 2
						printf("You chose Stand! Your turn for Hand Two will now end.\nYour Final Hand Two Cards are: \n");
						DisplayHand(splithand.cards, splithand.index);
						DisplayTotal(splithand.cards, splithand.index);
						splitTurnOver = true;
						break;

					default:
						printf("Invalid Input! Try Again!\n");
						break;
					}
				}
				break;

			default:
				printf("Invalid Input! Try Again!\n");
				break;
			}
		}

		// cheking if the hand is busted after player turn
		printf("Checking for Bust....\n");
		if (IsBusted(playerTotal))
		{
			if (!isSplitted)
			{
				dealerScore += 1;
				printf("Player Hand is Busted!\nPlayer loses the bet!\n");
				printf("\n<-----------------------Round %d Over----------------------->\n", round);
				continue;
			}
				
			else if(isSplitted && !IsBusted(splitTotal))
			{
				dealerScore += 1;
				printf("Both Hands are Busted!\n Player loses both the bets!\n ");
				printf("\n<-----------------------Round %d Over----------------------->\n", round);
				continue;
			}
		}

		printf("Player Hand is Not Busted!\n");
		//player.cardTotal = playerTotal; // redundant

		// Dealer Options
		printf("\n<---------------------- Dealers turn ---------------------->\n");
		int dealerTurnOver = false;
		bool dealerBusted = false;
		int dealerTotal = 0; // for this round
		// display both the cards now, revealing the other hidden card
		printf("Dealers cards are revealed now:\n");
		DisplayHand(dealer.cards, dealer.index);

		dealerTotal = GetTotal(dealer.cards, dealer.index);

		while (!dealerTurnOver && !IsBusted(dealerTotal) && !IsBlackjack(dealerTotal))
		{
			
			if (dealerTotal >= 0 && dealerTotal <= 16)
			{
				printf("Dealer Has to Hit.\n");
				dealer.cards[dealer.index++] = deck.cards[deck.index++];
				printf("A Card is added to the Dealers Hand. Dealers Cards are: \n");
				DisplayHand(dealer.cards, dealer.index);
				DisplayTotal(dealer.cards, dealer.index);

				dealerTotal = GetTotal(dealer.cards, dealer.index);
			}
			else
			{
				printf("Dealer Has to Stand.\n");
				printf("Dealers turn will be over now. \nFinal Dealers Cards are: \n");
				DisplayHand(dealer.cards, dealer.index);
				DisplayTotal(dealer.cards, dealer.index);

				dealerTurnOver = true;
			}
		}

		// cheking if the hand is busted after dealers turn
		printf("Checking for Bust....\n\n");
		if (IsBusted(dealerTotal))
		{
			playerScore += 1;
			printf("Dealer Hand is Busted!\nPlayer Wins the Bet!\n");
			continue;
		}
		printf("Dealer Hand is Not Busted!\n");
		//dealer.cardTotal = dealerTotal;  // redundant

		// calculation based on card values.
		WinnerOfRound(playerTotal, dealerTotal, isSplitted, splitTotal);
		printf("\n<-----------------------Round %d Over----------------------->\n", round);
	}

	// display winner after 10 rounds
	DisplayWinner(playerScore, dealerScore);
	printf("\n<----------------------- GAME ENDED!----------------------->\n");
}
