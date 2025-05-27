#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "uno_player.h"
#include "uno_deck.h"

int SetColor()
{
	int choice = 0;
	printf("Set The color of Wild / Wild Draw 4 Card: \n");
	printf("\t1. Red\n");
	printf("\t2. Green\n");
	printf("\t3. Blue\n");
	printf("\t4. Yellow\n");

	while (1)
	{

		printf("Your Choice: ");
		scanf_s("%d", &choice);
		if (choice >= 1 && choice <= 4)
		{
			printf("The Color Has Been Set to the Card!\n");
			break;
		}
		else
		{
			printf("Invalid Input! Try Again!\n");
		}
	}

	return choice;
}


bool IsAllowed(int discardCard, int playerCard, int discardCardColor)
{
	if (playerCard < 100 && discardCard < 100)
	{
		int playerCardType = playerCard % 25 + 1;
		int playerCardColor = playerCard / 25 + 1;

		int discardCardType = discardCard % 25 + 1;
		int discardCardColor = discardCard / 25 + 1;

		if (playerCardColor == discardCardColor || playerCardType == discardCardType)
		{
			return true;
		}
	}
	else if (playerCard < 100 && discardCard > 100)
	{
		int playerCardColor = playerCard / 25 + 1;

		if (playerCardColor == discardCardColor)
		{
			return true;
		}

	}
	return false;
}

int PickCard(struct SCard* player, struct SDeck* drawPile, struct SDeck* discardPile, int discardCardColor)
{
	int card;
	int choice = 0;

	while (1)
	{
		int size = SizeOfHand(player);
		printf("Pick A Card from your Hand: \n");
		DisplayPlayerHand(player);
		printf("\tOR\n\t%d. Take a Card From the Deck.\n", size + 1);
		printf("Your Choice : ");
		scanf_s("%d", &choice);

		if (choice >= 1 && choice <= size)
		{
			card = PeekAtHand(player, choice - 1);
		}
		else if (choice == size + 1)
		{
			InsertAtEnd(player, PopFromDeck(drawPile));
			card = PeekAtHand(player, choice - 1);
		}
		else
		{
			printf("Invalid Input! Try Again!\n");
			continue;
		}

		// after selecting the card
		if (IsAllowed(PeekDeck(discardPile), card, discardCardColor))
		{
			printf("Player Chose : ");
			DisplayCard(card);
			RemoveFromHand(player, choice - 1);
			break;
		}
		else
		{
			printf("The Selected Card is not allowed to Play. Pick Another Card.\n");
		}

	}

	return card;
}


void RestartDrawPile(struct SDeck* drawPile, struct SDeck* discardPile)
{
	printf("Your Draw Pile is Exhausted!\n");
	printf("Making a New Draw Pile with Discard Pile and Shuffelling...\n");
	// temp top variable which we will append to the discard pile at the end
	int tempTop = PopFromDeck(discardPile);
	// all remaining elemets will be appended into the draw pile
	for (int i = 0; i < discardPile->sizeOfDeck; i++)
	{
		PushInDeck(PopFromDeck(discardPile), drawPile);
	}
	// shuffle the draw pile
	ShuffleDeck(drawPile);

	PushInDeck(tempTop, discardPile);
	printf("Done!\n");
}

int Winner(struct SCard* player[NUMBEROFPLAYERS])
{
	// returns 0 -3 values according to player who wins
	for (int i = 0; i < NUMBEROFPLAYERS; i++)
	{
		if (SizeOfHand(player[i]) == 0)
		{
			return i;
		}
	}
	// else returns -1 
	return -1;
}


// initiating the heads of the linked lists of player hands
void Game()
{

	printf("<--------------------------Welcome To UNO------------------------->\n");

	// creating array of linked lists for 4(NUMBEROFPLAYERS) players (0 - 3)
	struct SCard* player[NUMBEROFPLAYERS];

	// to keep the track of turn (0 - 3), starting from player 0
	int turn = 0;

	// to keep the track of reverse opration, we can change it to -1 if necessary
	int reverse = 1;


	// assigning heads
	for (int i = 0; i < NUMBEROFPLAYERS; i++)
	{
		player[i] = CreatePlayerHand(-1); // player is referring to the head of the hand(linked list)
	}


	// create decks
	struct SDeck* drawPile = CreateDeck();
	struct SDeck* discardPile = CreateDeck();

	// draw pile filling
	FillDeck(drawPile);

	// shuffle draw pile
	ShuffleDeck(drawPile);

	// allot seven cards to each player
	printf("Assigning 7 Cards to each player...\n");
	for (turn = 0; turn < NUMBEROFPLAYERS; turn++)
	{
		for (int i = 0; i < 7; i++)
		{
			int val = PopFromDeck(drawPile);
			InsertAtEnd(player[turn], val);
		}
	}
	printf("Done!\n");


	// revert the turn to player 0
	turn = 0;

	// initiate discard pile with top card of draw pile
	printf("Initializing the Discard Pile with first card drawn...\n");
	PushInDeck(PopFromDeck(drawPile), discardPile);

	// game begins
	while (Winner(player) == -1)
	{
		int currentTurn = turn;
		printf("<--------------------------Player %d Turn------------------------->\n", currentTurn + 1);

		// variable for storing the color of top card of discard pile
		int discardCardColor = 0; // to do

		// take a look at the first card of discard pile and set a color to it
		int discardCard = PeekDeck(discardPile);
		// display the card on top of the discard pile
		printf("Top Card of The Discard Pile : ");
		DisplayCard(discardCard);

		if (discardCard >= 100 && discardCard < 108)
		{
			// we can set the color of the staring card
			discardCardColor = SetColor();
		}
		else
		{
			discardCardColor = discardCard / 25 + 1;
		}

		// take out a card from a deck which is allowed to play on top
		int playerCardPick = PickCard(player[turn], drawPile, discardPile, discardCardColor);

		// SHOUT UNO IF ONE CARD LEFT
		if (SizeOfHand(player[turn]) == 1)
		{
			printf("UNO!!\n\n");
		}


		// now the card is allowed for discarding
		// conditions respective to what card player discarded
		if (playerCardPick < 100)
		{
			int playerCardType = playerCardPick % 25 + 1;
			int playerCardColor = playerCardPick / 25 + 1;

			// if its a number card, move to next turn
			if (playerCardType >= 1 && playerCardType <= 19)
			{
				printf("Its a Normal Card!\n");
				turn = (turn + 1 * reverse) % NUMBEROFPLAYERS;
			}

			// if the card is Draw 2, then draw 2 for next player and skip his turn
			else if (playerCardType == 20 || playerCardType == 21)
			{
				printf("Its a Draw 2 Card! Next player will draw 2 cards and the turn will be skipped!\n");
				turn = (turn + 1 * reverse) % NUMBEROFPLAYERS;
				// Draw 4
				printf("Player %d is dealt with 2 cards!\n", turn + 1);
				InsertAtEnd(player[turn], PopFromDeck(drawPile));
				InsertAtEnd(player[turn], PopFromDeck(drawPile));
				// Skip the turn
				printf("Turn Skipped!\n");
				turn = (turn + 1 * reverse) % NUMBEROFPLAYERS;
			}

			// if the card is Skip, then skip his turn
			else if (playerCardType == 22 || playerCardType == 23)
			{
				// change the turn to the next to next player
				printf("Its a Skip Card! It will Skip the turn for next player!\n");
				turn = (turn + 1 * reverse) % NUMBEROFPLAYERS;
				printf("Turn Skipped!\n");
				turn = (turn + 1 * reverse) % NUMBEROFPLAYERS;
			}

			// if the card is Reverse, then change the direction of the turns
			else if (playerCardType == 22 || playerCardType == 23)
			{
				// change the sign of reverse whenever reverse card is played
				printf("Its a Reverse Card! Playing Direction has Been Changed!\n");
				reverse = -1 * reverse;
				// change the turn to the next player
				turn = (turn + 1 * reverse) % NUMBEROFPLAYERS;
				printf("Player %d will play next!\n", turn + 1);
			}

		}
		// Wild CArd
		else if (playerCardPick >= 100 && playerCardPick < 104)
		{
			// color can be changed at start of the turn
			printf("Its a Wild Card! \nPlayer will decide the color of the card in next turn!\n");
			turn = (turn + 1 * reverse) % NUMBEROFPLAYERS;
		}

		// Wild Draw 4 Card
		else if (playerCardPick >= 104 && playerCardPick < 108)
		{
			// color can be changed at start of the turn
			printf("Its a Wild Draw 4 Card! \nNext Player will draw 4 cards and skip! \nPlayer will decide the color of the card in next turn!\n");
			turn = (turn + 1 * reverse) % NUMBEROFPLAYERS;
			// Draw 4
			printf("Player %d is dealt with 4 cards!\n", turn + 1);
			InsertAtEnd(player[turn], PopFromDeck(drawPile));
			InsertAtEnd(player[turn], PopFromDeck(drawPile));
			InsertAtEnd(player[turn], PopFromDeck(drawPile));
			InsertAtEnd(player[turn], PopFromDeck(drawPile));
			// Skip the turn
			printf("Turn Skipped!\n");
			turn = (turn + 1 * reverse) % NUMBEROFPLAYERS;
		}

		// finally append the card picked by player into the discard pile
		printf("The Player card goes to the Discard Pile!\n");
		PushInDeck(playerCardPick, discardPile);

		// if the draw pile is exhausted then add all the below elemets of the discard pile to the drawpile and shuffle
		if (drawPile->sizeOfDeck == 0)
		{
			RestartDrawPile(drawPile, discardPile);
		}

		printf("<------------------------Player %d Turn Ends----------------------->\n", currentTurn + 1);
	}

	// announce winner
	printf("Player %d Wins the Game!!\n", Winner(player));

}
