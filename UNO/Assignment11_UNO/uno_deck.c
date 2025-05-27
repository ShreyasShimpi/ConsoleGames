#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "uno_deck.h"


// creatiing stack
struct SDeck* CreateDeck()
{
	struct SDeck* temp = (struct SDeck*)malloc(10 * sizeof(struct SDeck));
	if (temp)
	{
		temp->sizeOfDeck = 0;
		temp->topCard = temp->card; // top should point to the first location
		temp->topCard--; // now its at -1 index, when we will push, it comes to 0.
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

void FillDeck(struct SDeck* temp)
{
	for (int i = 0; i < DECKSIZE; i++)
	{
		PushInDeck(i, temp);
	}
}

// displays the card by taking input 0 to 107 (uno card number)

void DisplayCard(int card)
{
	int cardType = 0;
	int cardColor = 0;

	char* cardTypeString = "";
	char* cardColorString = "";


	if (card < 100)
	{
		cardType = card % 25 + 1; // 1 to 25 values - ( 0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9, Draw2, Draw2, Skip, Skip, Reverse, Reverse ) - all of same color
		cardColor = card / 25 + 1; // 1 to 4 values - ( Red, Green, Blue, Yellow )

		switch (cardType)
		{
		case 1:
			cardTypeString = "Zero";
			break;
		case 2:
		case 3:
			cardTypeString = "One";
			break;
		case 4:
		case 5:
			cardTypeString = "Two";
			break;
		case 6:
		case 7:
			cardTypeString = "Three";
			break;
		case 8:
		case 9:
			cardTypeString = "Four";
			break;
		case 10:
		case 11:
			cardTypeString = "Five";
			break;
		case 12:
		case 13:
			cardTypeString = "Six";
			break;
		case 14:
		case 15:
			cardTypeString = "Seven";
			break;
		case 16:
		case 17:
			cardTypeString = "Eight";
			break;
		case 18:
		case 19:
			cardTypeString = "Nine";
			break;
		case 20:
		case 21:
			cardTypeString = "Draw 2";
			break;
		case 22:
		case 23:
			cardTypeString = "Skip";
			break;
		case 24:
		case 25:
			cardTypeString = "Reverse";
			break;
		default:
			break;
		}

		switch (cardColor)
		{
		case 1:
			cardColorString = "Red";
			break;
		case 2:
			cardColorString = "Green";
			break;
		case 3:
			cardColorString = "Blue";
			break;
		case 4:
			cardColorString = "Yellow";
			break;
		default:
			break;
		}

		printf("%s %s Card", cardColorString, cardTypeString);
	}
	else if (card >= 100 && card < 104)
	{
		printf("A Wild Card.");
	}
	else if (card >= 104 && card < 108)
	{
		printf("A Wild Draw 4 Card.");
	}
	printf("\n");

}
