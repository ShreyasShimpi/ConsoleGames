#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

#include "solitaire_stack.h"


// normal deck functions

// creating stack
struct SDeck* CreateDeck(int size)
{
	struct SDeck* temp = (struct SDeck*)malloc(sizeof(struct SDeck));
	if (temp)
	{
		temp->card = (int*)calloc(size, sizeof(int)); // dynamic allocation of stack array
		temp->topCard = temp->card; // top should point to the first location
		temp->topCard--; // now its at -1 index, when we will push, it comes to 0.
		temp->sizeOfDeck = 0;
	}
	return temp;
}

void PushInDeck(int val, struct SDeck* temp)
{
	temp->topCard++;
	*(temp->topCard) = val;
	temp->sizeOfDeck++;
}

int PopFromDeck(struct SDeck* temp)
{
	int val = *(temp->topCard);
	*(temp->topCard) = 0	;
	temp->topCard--;
	temp->sizeOfDeck--;
	return val;
}

int PeekDeck(struct SDeck* temp)
{
	return *(temp->topCard);
}

// Swap cards function
void SwapCards(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// function to shuffle the elements in the array which is deck here.
void ShuffleDeck(struct SDeck* temp)
{
	srand(time(NULL));

	// picks the random index from 0 to i and swaps it with current index i
	for (int i = DECKSIZE - 1; i > 0; i--)
	{
		int randomIndex = rand() % (i + 1); // i + 1 to avoid %1 operation when i = 1
		SwapCards(&temp->card[randomIndex], &temp->card[i]);
	}
}

// fill the deck with cards 1 to 52
void FillDeck(struct SDeck* temp)
{
	for (int i = 1; i <= DECKSIZE; i++)
	{
		PushInDeck(i, temp);
	}
}

// displays the card by taking input 1 to 52
void DisplayCard(int card)
{
	// operation to get card type and card number from 1 to 52
	if (card >= 1 && card <= 52)
	{
		int cardNumber = (card - 1) % 13 + 1;
		int cardType = (card - 1) / 13 + 1;

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

		if (cardType == 1 || cardType == 2)
		{

			printf("[\033[1;31m%6s of %-9s\033[0m] ", cardNumberToString, cardTypeToString);
		}
		else
		{
			printf("[\033[0;37m%6s of %-9s\033[0m] ", cardNumberToString, cardTypeToString);
		}
	}
	else
	{
		printf("[                   ] ");
	}
};


// tableau deck functions

struct STableau* CreateTableauDeck(int size)
{
	struct STableau* temp = (struct STableau*)malloc(sizeof(struct STableau));
	if (temp)
	{
		temp->deck = CreateDeck(19);
		temp->startIndex = 0;
		temp->endIndex = 0;
	}
	return temp;
}
