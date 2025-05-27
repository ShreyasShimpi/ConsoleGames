#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

#include "gofish_player.h"

// stack function for sequence of cards
struct SCardSequence* CreateCardSequence()
{
	struct SCardSequence* temp = (struct SCardSequence*)malloc(sizeof(struct SCardSequence));
	if (temp)
	{
		temp->sizeOfDeck = 0;
		temp->topCard = temp->card; // top should point to the first location
		temp->topCard--; // now its at -1 index, when we will push, it comes to 0.
	}
	return temp;
}

void PushInSequence(int val, struct SCardSequence* temp)
{
	temp->topCard++;
	*(temp->topCard) = val;
	temp->sizeOfDeck++;
}

short PopFromSequnce(struct SCardSequence* temp)
{
	short val = *(temp->topCard);
	temp->topCard--;
	temp->sizeOfDeck--;
	return val;
}
// stack functions complete



// player hand -- functions
struct SHand* InitializeHand()
{
	struct SHand* temp = (struct SHand*)malloc(sizeof(struct SHand));
	if (temp)
	{
		for (short i = 0; i < 13; i++)
		{
			temp->stackOfCard[i] = CreateCardSequence();
		}
		temp->score = 0;
		temp->numberOfCards = 0;
	}
	return temp;
}

void InsertInHand(struct SHand* hand, int card)
{
	// card = 0 to 51
	// cardvalue  = 0 to 12 ( to matc the index of stackOfCards)
	short cardValue = card % 13;
	PushInSequence(card, hand->stackOfCard[cardValue]);
	hand->numberOfCards += 1;
}

short RemoveFromHand(struct SHand* hand, int card)
{
	int cardValue = card % 13;
	short temp = PopFromSequnce(hand->stackOfCard[cardValue]);
	hand->numberOfCards -= 1;
	return temp;
}

// if all cards are gone from the hand of each player, the game is over
bool GameOver(struct SHand* hand[])
{
	int totalCards = 0;
	for (short i = 0; i < NUMBEROFPLAYERS; i++)
	{
		totalCards += hand[i]->numberOfCards;
	}

	return (totalCards == 0) ? false : true;
}

// displays the card 
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


// to print the cards in the player hand
void DisplayHand(struct SHand* hand)
{
	for (short i = 0; i < 13; i++)
	{
		// display only card which are not catched means if sequnce if full dont display that
		for (short j = 0; (hand->stackOfCard[i]->sizeOfDeck != 4) && j < hand->stackOfCard[i]->sizeOfDeck; j++)
		{
			DisplayCard(hand->stackOfCard[i]->card[j]);
		}
	}
}

bool HaveCard(struct SHand* hand, short cardChoice)
{
	return (hand->stackOfCard[cardChoice - 1]->sizeOfDeck != 0) ? true : false;
}


// tranfer all the similar valued card ( CARDCHOICE ) from HAND 1 to HAND 2 
void TransferCards(struct SHand* hand1, struct SHand* hand2, short cardChoice)
{
	for (short i = 0; i < hand1->stackOfCard[cardChoice - 1]->sizeOfDeck; i++)
	{
		short temp = PopFromSequnce(hand1->stackOfCard[cardChoice - 1]);
		InsertInHand(hand2, temp);
	}
}

void CheckForCatch(struct SHand* hand)
{
	printf("Checking for Catch.....\n");
	for (short i = 0; i < 13; i++)
	{
		if (hand->stackOfCard[i]->sizeOfDeck == 4)
		{
			printf("Catch Found for value : %hi\n", i + 1);
			hand->score += 1;
			hand->numberOfCards -= 4;
		}
	}
}


// for 2 players
void DisplayWinner(struct SHand* hand[])
{
	short maxPlayer = 0;
	short maxPlayerScore = hand[0]->score;
	for (short i = 1; i < NUMBEROFPLAYERS; i++)
	{
		if (hand[i]->score > maxPlayerScore)
		{
			maxPlayer = i;
		}
	}
	printf("Player %hi Wins!!\n\n", maxPlayer + 1);
}