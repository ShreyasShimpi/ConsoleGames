#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

#include "gofish_deck.h"
#include "gofish_player.h"

void GivePlayerCards(struct SHand* hand, struct SDeck* deck)
{
	if (deck->sizeOfDeck >= 5)
	{
		for (short i = 0; i < 5; i++)
		{
			InsertInHand(hand, PopFromDeck(deck));
		}
		printf("5 Cards has been given to the Player!!\n");
	}

	else if (deck->sizeOfDeck > 0 && deck->sizeOfDeck < 5)
	{
		for (short i = 0; i < deck->sizeOfDeck; i++)
		{
			InsertInHand(hand, PopFromDeck(deck));
		}
		printf("Deck Contains less than 5 cards. Remaining Cards has been given to the Player!!\n");
	}

	else
	{
		printf("Deck has No cards!!\n");
	}
}



void Game()
{

	printf("<----------------------- Welcome to Go Fish ----------------->\n");
	// Create the deck
	struct SDeck* deck = CreateDeck();

	// fill the deck and shuffle
	FillDeck(deck);
	ShuffleDeck(deck);

	// initialize the player hands
	struct SHand* playerHand[NUMBEROFPLAYERS];

	for (int i = 0; i < NUMBEROFPLAYERS; i++)
	{
		playerHand[i] = InitializeHand();
	}

	// card distrubution
	short initialCards = 0;
	printf("Choose the Initial Cards : ");
	scanf_s("%hi", &initialCards);

	for (int i = 0; i < initialCards; i++)
	{
		for (int j = 0; j < NUMBEROFPLAYERS; j++)
		{
			InsertInHand(playerHand[j], PopFromDeck(deck));
		}
	}

	// game begins
	short turn = 0; // to player 1

	while (!GameOver(playerHand))
	{

		printf("\n<--------------- Player %d Turn --------------->\n", turn + 1);
		bool isRecieved = true;
		// start from player 0
		while (isRecieved)
		{

			// display all player cards
			DisplayHand(playerHand[turn]);

			// player makes choice which card to take
			short cardChoice;
			short playerChoice;

			// for checking if the card player asking for is in his hand or not 
			do
			{
				printf("Choose which card from the hand do you want to ask for: ");
				scanf_s("%hi", &cardChoice);

			} while (!HaveCard(playerHand[turn], cardChoice));

			// from which player does current player want cards from
			do
			{
				printf("Choose which player do you want the card from (1- %d) : ", NUMBEROFPLAYERS);
				scanf_s("%hi", &playerChoice);
			} while (playerChoice < 1 || playerChoice > NUMBEROFPLAYERS);


			// if player have the cards, he will trasfer all cards to him
			if (HaveCard(playerHand[playerChoice - 1], cardChoice - 1))
			{
				printf("Player %hi Has the card/cards you asked for!!\n", playerChoice);
				printf("Tranfering the Cards to your Deck.....\n");
				Sleep(2000);

				TransferCards(playerHand[playerChoice - 1], playerHand[turn], cardChoice);

				printf("Done!\n");
				printf("Turn Continues!\n");
			}

			// if he dont have, he will say "Go fish", and player will pick a card from deck
			else
			{
				printf("GO FISH!!\n");
				printf("Player %hi will pick a card from a deck!\n", turn + 1);
				printf("Fishing...\n");
				Sleep(2000);

				short cardValue = PopFromDeck(deck);
				InsertInHand(playerHand[turn], cardValue);

				printf("Its ");
				DisplayCard(cardValue);

				// if the card from deck matches the choice he will get another turn
				if (cardChoice == (cardValue % 13 + 1))
				{
					printf("It matches with the Card of Choice!\n");
					printf("Turn Continues!\n");
				}

				// else the turn is over
				else
				{
					printf("Turn Over!\n");
					isRecieved = false;
				}
			}

			// Check for catch

			CheckForCatch(playerHand[turn]);


			// if the cards in hand get exhausted give the player 5 cards from thr deck
			if (playerHand[turn]->numberOfCards == 0)
			{
				GivePlayerCards(playerHand[turn], deck);
			}

		}

		printf("\n<--------------- Player %d Turn Over--------------->\n", turn + 1);
		// increment the turn
		turn = (turn + 1) % NUMBEROFPLAYERS;
	}

	DisplayWinner(playerHand);
}